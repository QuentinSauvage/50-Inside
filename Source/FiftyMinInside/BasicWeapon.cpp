// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicWeapon.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "TimerManager.h"

void ABasicWeapon::FireProjectile() {
	if (BulletClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;

		FVector Offset = FVector(0.f, 70.f, 0.f);
		Offset = GetTransform().TransformPosition(Offset);

		FTransform BulletTransform;
		BulletTransform.SetLocation(Offset);
		BulletTransform.SetRotation(GetActorRotation().Quaternion());
		BulletTransform.SetScale3D(FVector(1.f));
		GetWorld()->SpawnActor <ABullet>(BulletClass, BulletTransform, SpawnParams);

		Offset = FVector(0.f, -70.f, 0.f);
		Offset = GetTransform().TransformPosition(Offset);
		BulletTransform.SetLocation(Offset);
		GetWorld()->SpawnActor <ABullet>(BulletClass, BulletTransform, SpawnParams);
	}

	if (bTryFire)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeHandleFiring, this, &ABasicWeapon::FireProjectile, DelayBetweenShots, false);
	}

	LastFire = GetWorld()->GetTimeSeconds();
}