// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RocketLauncher.h"
#include "GuidedRocketLauncher.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API AGuidedRocketLauncher : public ARocketLauncher
{
	GENERATED_BODY()

	public:
		AGuidedRocketLauncher();

		void ResetFiring();

		bool GetFiring();

	protected:
		class AFiftyMinInsidePawn* Player;

		UPROPERTY(EditAnywhere, Category = "Bullet")
			TSubclassOf<class AGuidedRocket> RocketClass;

		bool bFiring;

		virtual void Fire() override;

		virtual void FireProjectile() override;
};
