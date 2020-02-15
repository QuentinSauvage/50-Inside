// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "RocketLauncher.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API ARocketLauncher : public AWeapon
{
	GENERATED_BODY()
	
public:
	ARocketLauncher();

protected:
	virtual void FireProjectile() override;

	/** If bAltern set to true, indicates which side is firing */
	bool bFireLeft;
};
