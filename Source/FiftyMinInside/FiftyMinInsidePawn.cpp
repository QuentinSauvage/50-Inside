// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FiftyMinInsidePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Weapon.h"


AFiftyMinInsidePawn::AFiftyMinInsidePawn()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());	// Set static mesh
	RootComponent = PlaneMesh;

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = false;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	Acceleration = 1500.f;
	DecelerationRate = 1.5f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = -3000.f;
	CurrentForwardSpeed = 0.f;
	CurrentRightSpeed = 0.f;
	CurrentUpSpeed = 0.f;

	// Set Health parameters
	FullHealth = 100.0f;
	RemainingHealth = FullHealth;
	PercentageHealth = 1.0f;

	SelectedWeapon = 0;

}

void AFiftyMinInsidePawn::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, CurrentRightSpeed * DeltaSeconds, CurrentUpSpeed * DeltaSeconds);
	if (!LocalMove.IsNearlyZero(0.5f)) {
		// Move plan forwards (with sweep so we stop when we collide with things)
		AddActorLocalOffset(LocalMove, true);
	}


	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate plane
	AddActorLocalRotation(DeltaRotation);

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void AFiftyMinInsidePawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}


void AFiftyMinInsidePawn::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	RocketLauncher = GetWorld()->SpawnActor<AWeapon>(RocketClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!RocketLauncher)
		RocketLauncher = CreateDefaultSubobject<AWeapon>(TEXT("WeaponSpecial"));
	RocketLauncher->AttachToComponent(PlaneMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	FVector RocketLauncherOffset = RocketLauncher->GetActorLocation();
	RocketLauncherOffset.X += 200.f;
	RocketLauncherOffset.Z -= 25.f;
	RocketLauncher->SetActorLocation(RocketLauncherOffset);

	FlareLauncher = GetWorld()->SpawnActor<AWeapon>(FlareClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!FlareLauncher)
		FlareLauncher = CreateDefaultSubobject<AWeapon>(TEXT("FlareLauncher"));
	FlareLauncher->AttachToComponent(PlaneMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	FlareLauncher->SetActorLocation(RocketLauncherOffset);

	for (int i = 0; i < WeaponsClass.Num(); ++i) {
		WeaponsList[i] = GetWorld()->SpawnActor<AWeapon>(WeaponsClass[i], FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (!WeaponsList[i])
			WeaponsList[i] = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));
		WeaponsList[i]->AttachToComponent(PlaneMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		FVector WeaponOffset = RocketLauncherOffset;
		WeaponsList[i]->SetActorLocation(WeaponOffset);
	}
}

void AFiftyMinInsidePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("MoveForward", this, &AFiftyMinInsidePawn::MoveForwardInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFiftyMinInsidePawn::MoveRightInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &AFiftyMinInsidePawn::MoveUpInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFiftyMinInsidePawn::LookUpInput);
	PlayerInputComponent->BindAxis("Turn", this, &AFiftyMinInsidePawn::TurnInput);
	PlayerInputComponent->BindAxis("Roll", this, &AFiftyMinInsidePawn::RollInput);


	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFiftyMinInsidePawn::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFiftyMinInsidePawn::StopFire);
	PlayerInputComponent->BindAction("FireSpecial", IE_Pressed, this, &AFiftyMinInsidePawn::OnFireSpecial);
	PlayerInputComponent->BindAction("FireSpecial", IE_Released, this, &AFiftyMinInsidePawn::StopFireSpecial);
	PlayerInputComponent->BindAction("FireFlare", IE_Pressed, this, &AFiftyMinInsidePawn::OnFireFlare);
	PlayerInputComponent->BindAction("FireFlare", IE_Released, this, &AFiftyMinInsidePawn::StopFireFlare);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &AFiftyMinInsidePawn::OnNextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Released, this, &AFiftyMinInsidePawn::OnPreviousWeapon);

}

void AFiftyMinInsidePawn::MoveForwardInput(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc;
	if (bHasInput)
		CurrentAcc = Val * Acceleration;
	else
		CurrentAcc = CurrentForwardSpeed > 0.f ? (-DecelerationRate * Acceleration) : (DecelerationRate * Acceleration);
	// Calculate new speed
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void AFiftyMinInsidePawn::MoveRightInput(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc;
	if (bHasInput)
		CurrentAcc = Val * Acceleration;
	else
		CurrentAcc = CurrentRightSpeed > 0.f ? (-DecelerationRate * Acceleration) : (DecelerationRate * Acceleration);
	// Calculate new speed
	float NewRightSpeed = CurrentRightSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentRightSpeed = FMath::Clamp(NewRightSpeed, MinSpeed, MaxSpeed);
}

void AFiftyMinInsidePawn::MoveUpInput(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc;
	if (bHasInput)
		CurrentAcc = Val * Acceleration;
	else
		CurrentAcc = CurrentUpSpeed > 0.f ? (-DecelerationRate * Acceleration) : (DecelerationRate * Acceleration);
	// Calculate new speed
	float NewRightSpeed = CurrentUpSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentUpSpeed = FMath::Clamp(NewRightSpeed, MinSpeed, MaxSpeed);
}

void AFiftyMinInsidePawn::LookUpInput(float Val)
{
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

}

void AFiftyMinInsidePawn::TurnInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

}

void AFiftyMinInsidePawn::RollInput(float Val)
{
	// Target yaw speed is based on input
	float TargetRollSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AFiftyMinInsidePawn::OnFire()
{
	if (SelectedWeapon != 0 && WeaponsList[SelectedWeapon]->GetMunitionCount() == 0)
	{
		WeaponsList[SelectedWeapon]->StopFire();
		OnNextWeapon();
	}
	WeaponsList[SelectedWeapon]->Fire();
}

void AFiftyMinInsidePawn::StopFire()
{
	WeaponsList[SelectedWeapon]->StopFire();
}


void AFiftyMinInsidePawn::OnFireSpecial()
{
	RocketLauncher->Fire();
}

void AFiftyMinInsidePawn::StopFireSpecial()
{
	RocketLauncher->StopFire();
}

void AFiftyMinInsidePawn::OnFireFlare()
{
	FlareLauncher->Fire();
}

void AFiftyMinInsidePawn::StopFireFlare()
{
	FlareLauncher->StopFire();
}

void AFiftyMinInsidePawn::OnNextWeapon()
{
	WeaponsList[SelectedWeapon]->StopFire();
	while (1) {
		SelectedWeapon = (SelectedWeapon + 1) % WeaponsList.Num();
		if (WeaponsList[SelectedWeapon]->GetMunitionCount() > 0 || SelectedWeapon == 0) break;
	}
}

void AFiftyMinInsidePawn::OnPreviousWeapon()
{
	WeaponsList[SelectedWeapon]->StopFire();
	while (1) {
		SelectedWeapon = (SelectedWeapon + WeaponsList.Num() - 1) % WeaponsList.Num();
		if (WeaponsList[SelectedWeapon]->GetMunitionCount() > 0 || SelectedWeapon == 0) break;
	}
}

float AFiftyMinInsidePawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UpdateHealth(-DamageAmount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player new health %f "), RemainingHealth));
	return DamageAmount;
}

float AFiftyMinInsidePawn::UpdateHealth(float HealthChange)
{
	RemainingHealth += HealthChange;
	RemainingHealth = FMath::Clamp(RemainingHealth, 0.0f, FullHealth);
	PercentageHealth = RemainingHealth / FullHealth;
	return RemainingHealth;
}

bool AFiftyMinInsidePawn::CollectWeapon(int WeaponIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f - %f "), WeaponsList[WeaponIndex]->GetMunitionCount(), WeaponsList[WeaponIndex]->GetBaseMunitionCount()));
	if (WeaponsList[WeaponIndex]->GetMunitionCount() == WeaponsList[WeaponIndex]->GetBaseMunitionCount())
	{
		return false;
	}
	WeaponsList[SelectedWeapon]->StopFire();
	WeaponsList[WeaponIndex]->SetMunitionCount(WeaponsList[WeaponIndex]->GetBaseMunitionCount());
	SelectedWeapon = WeaponIndex;
	return true;
}
