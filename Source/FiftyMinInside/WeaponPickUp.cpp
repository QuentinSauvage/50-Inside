// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUp.h"
#include "FiftyMinInsidePawn.h"
#include "Engine/World.h"
#include "Weapon.h"

void AWeaponPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("COLLECT WEAPON")));
	if (OtherActor && OtherActor != this) {
		AFiftyMinInsidePawn* Pawn = Cast<AFiftyMinInsidePawn>(OtherActor);
		if (Pawn && Pawn->CollectWeapon(WeaponIndex)) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("COLLECT WEAPON")));
			Destroy();
		}
	}
}