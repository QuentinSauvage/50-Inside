// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUp.h"
#include "FiftyMinInsidePawn.h"
#include "Engine/World.h"
#include "Weapon.h"

void AWeaponPickUp::BeginPlay()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!Weapon)
		Weapon = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));
}

void AWeaponPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor != this) {
		AFiftyMinInsidePawn* Pawn = Cast<AFiftyMinInsidePawn>(OtherActor);
		if (Pawn && Pawn->CollectWeapon(Weapon)) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("COLLECT WEAPON")));
			Weapon->Destroy();
			Destroy();
		}
	}
}