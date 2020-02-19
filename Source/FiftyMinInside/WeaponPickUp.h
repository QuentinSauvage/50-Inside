// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "WeaponPickUp.generated.h"

/**
 *
 */
UCLASS()
class FIFTYMININSIDE_API AWeaponPickUp : public APickUp
{
	GENERATED_BODY()

		virtual void BeginPlay();

	UPROPERTY(EditAnywhere, Category = Armaments)
		TSubclassOf<class AWeapon> WeaponClass;

	class AWeapon* Weapon;

public:
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
