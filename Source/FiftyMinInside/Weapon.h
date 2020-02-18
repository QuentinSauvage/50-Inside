// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class FIFTYMININSIDE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	void Fire();

	void StopFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool CanFire();

	virtual void FireProjectile();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetMunitionCount();

	float GetBaseMunitionCount();

	void SetMunitionCount(float Amount);

	int GetWeaponIndex();

protected:
	bool bTryFire;

	float LastFire;

	UPROPERTY(EditAnywhere)
	float DelayBetweenShots;

	FTimerHandle TimeHandleFiring;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Munition)
	bool bUseMunition;

	/** Should the weapon change its spawn of bullet each time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Munition)
	bool bAltern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Munition)
	int BaseMunitionCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	int WeaponIndex;

	int MunitionCount;

};
