// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUp.h"
#include "FiftyMinInsidePawn.h"
#include "Engine/World.h"
#include "Weapon.h"

void AWeaponPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor != this) {
		AFiftyMinInsidePawn* Pawn = Cast<AFiftyMinInsidePawn>(OtherActor);
		if (Pawn && Pawn->CollectWeapon(WeaponIndex, bWeapon)) {
			Destroy();
		}
	}
}