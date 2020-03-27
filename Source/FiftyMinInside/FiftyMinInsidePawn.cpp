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
#include "GuidedRocket.h"


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
	SelectedRocket = 0;


	GuidedRocket = nullptr;
}

void AFiftyMinInsidePawn::Tick(float DeltaSeconds)
{
	FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, CurrentRightSpeed * DeltaSeconds, CurrentUpSpeed * DeltaSeconds);

	if (!LocalMove.IsNearlyZero(0.5f)) {
		// Move plan forwards (with sweep so we stop when we collide with things)
		AddActorLocalOffset(LocalMove, true);
	}

	if (GuidedRocket) {
		const FVector LocalGuidedMove = FVector(GuidedForwardSpeed * DeltaSeconds, CurrentGuidedRightSpeed * DeltaSeconds, CurrentGuidedUpSpeed * DeltaSeconds);
		if (!LocalGuidedMove.IsNearlyZero(0.5f)) {
			GuidedRocket->AddActorLocalOffset(LocalGuidedMove, true);
		}
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

	FVector LauncherOffset = FVector::ZeroVector;

	FlareLauncher = GetWorld()->SpawnActor<AWeapon>(FlareClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!FlareLauncher)
		FlareLauncher = CreateDefaultSubobject<AWeapon>(TEXT("FlareLauncher"));
	FlareLauncher->AttachToComponent(PlaneMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	LauncherOffset.X += 600.f;
	FlareLauncher->AddActorLocalOffset(LauncherOffset);

	for (int i = 0; i < WeaponsClass.Num(); ++i) {
		WeaponsList[i] = GetWorld()->SpawnActor<AWeapon>(WeaponsClass[i], FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (!WeaponsList[i])
			WeaponsList[i] = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));
		WeaponsList[i]->AttachToComponent(PlaneMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		WeaponsList[i]->AddActorLocalOffset(LauncherOffset);
	}

	for (int i = 0; i < RocketsClass.Num(); ++i) {
		RocketsList[i] = GetWorld()->SpawnActor<AWeapon>(RocketsClass[i], FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (!RocketsList[i])
			RocketsList[i] = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));
		RocketsList[i]->AttachToComponent(PlaneMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		RocketsList[i]->AddActorLocalOffset(LauncherOffset);
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

	PlayerInputComponent->BindAxis("MoveGuidedRight", this, &AFiftyMinInsidePawn::MoveGuidedRight);
	PlayerInputComponent->BindAxis("MoveGuidedUp", this, &AFiftyMinInsidePawn::MoveGuidedUp);

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
	float NewUpSpeed = CurrentUpSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentUpSpeed = FMath::Clamp(NewUpSpeed, MinSpeed, MaxSpeed);
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

void AFiftyMinInsidePawn::MoveGuidedUp(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? Val * GuidedAcceleration : 0;
	// Calculate new speed
	float NewUpSpeed = CurrentGuidedUpSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentGuidedUpSpeed = FMath::Clamp(NewUpSpeed, MinSpeed, MaxSpeed);
}

void AFiftyMinInsidePawn::MoveGuidedRight(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? Val * GuidedAcceleration : 0;
	// Calculate new speed
	float NewRightSpeed = CurrentGuidedRightSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentGuidedRightSpeed = FMath::Clamp(NewRightSpeed, MinSpeed, MaxSpeed);
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
	if (GuidedRocket) {
		CurrentGuidedRightSpeed = 0;
		CurrentGuidedUpSpeed = 0;
	}
	RocketsList[SelectedRocket]->Fire();
}

void AFiftyMinInsidePawn::StopFireSpecial()
{
	RocketsList[SelectedRocket]->StopFire();
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

void AFiftyMinInsidePawn::OnNextRocket()
{
	WeaponsList[SelectedRocket]->StopFire();
	while (1) {
		SelectedRocket = (SelectedRocket + 1) % RocketsList.Num();
		if (RocketsList[SelectedRocket]->GetMunitionCount() > 0 || SelectedRocket == 0) break;
	}
}

void AFiftyMinInsidePawn::OnPreviousRocket()
{
	RocketsList[SelectedRocket]->StopFire();
	while (1) {
		SelectedRocket = (SelectedRocket + RocketsList.Num() - 1) % RocketsList.Num();
		if (RocketsList[SelectedRocket]->GetMunitionCount() > 0 || SelectedRocket == 0) break;
	}
}

float AFiftyMinInsidePawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UpdateHealth(-DamageAmount);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player new health %f "), RemainingHealth));
	return DamageAmount;
}

float AFiftyMinInsidePawn::UpdateHealth(float HealthChange)
{
	float previousHealth = RemainingHealth;
	RemainingHealth += HealthChange;
	RemainingHealth = FMath::Clamp(RemainingHealth, 0.0f, FullHealth);
	if (RemainingHealth == 0)
	{
		if (RemainingLives == 1)
		{
			this->DisplayGameOver();
		}
		else
		{
			--RemainingLives;
			RemainingHealth = FullHealth;
			this->UpdateFireParticles();
		}
	}
	else if ((RemainingHealth < 50 && previousHealth >= 50) || (RemainingHealth >= 50 && previousHealth < 50))
	{
		this->UpdateFireParticles();
	}
	PercentageHealth = RemainingHealth / FullHealth;
	return RemainingHealth;
}

void AFiftyMinInsidePawn::SetGuidedRocket(AGuidedRocket* Rocket)
{
	GuidedForwardSpeed = 0;
	CurrentGuidedRightSpeed = 0;
	CurrentGuidedUpSpeed = 0;
	GuidedRocket = Rocket;
}

bool AFiftyMinInsidePawn::CollectWeapon(int WeaponIndex, bool bWeapon)
{
	if (bWeapon) {

		if (WeaponsList[WeaponIndex]->GetMunitionCount() == WeaponsList[WeaponIndex]->GetBaseMunitionCount())
		{
			return false;
		}
		WeaponsList[SelectedWeapon]->StopFire();
		WeaponsList[WeaponIndex]->SetMunitionCount(WeaponsList[WeaponIndex]->GetBaseMunitionCount());
		SelectedWeapon = WeaponIndex;
	}
	else {
		if (RocketsList[WeaponIndex]->GetMunitionCount() == RocketsList[WeaponIndex]->GetBaseMunitionCount())
		{
			return false;
		}
		RocketsList[SelectedRocket]->StopFire();
		RocketsList[WeaponIndex]->SetMunitionCount(RocketsList[WeaponIndex]->GetBaseMunitionCount());
		SelectedRocket = WeaponIndex;
	}
	return true;
}

int AFiftyMinInsidePawn::PickWeapon()
{
	return rand() % WeaponsClass.Num();
}

int AFiftyMinInsidePawn::PickSpecialWeapon()
{
	return rand() % RocketsClass.Num();
}