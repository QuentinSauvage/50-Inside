// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "BasicWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API ABasicWeapon : public AWeapon
{
	GENERATED_BODY()
	
protected:
	virtual void FireProjectile() override;
};
