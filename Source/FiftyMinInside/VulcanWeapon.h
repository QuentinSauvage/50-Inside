// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "VulcanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API AVulcanWeapon : public AWeapon
{
	GENERATED_BODY()
	
protected:
	virtual void FireProjectile() override;
};
