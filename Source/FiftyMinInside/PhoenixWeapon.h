// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "PhoenixWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API APhoenixWeapon : public AWeapon
{
	GENERATED_BODY()

	public:
		APhoenixWeapon();

	protected:
		bool bHRotation;
		virtual void FireProjectile() override;
};
