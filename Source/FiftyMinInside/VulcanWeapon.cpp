// Fill out your copyright notice in the Description page of Project Settings.


#include "VulcanWeapon.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "TimerManager.h"

void AVulcanWeapon::FireProjectile() {
	if (BulletClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Pew Basic!"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;

		FVector Offset = GetActorLocation();

		FTransform BulletTransform;
		BulletTransform.SetLocation(Offset);
		BulletTransform.SetRotation(GetActorRotation().Quaternion());
		BulletTransform.SetScale3D(FVector(1.f));
		GetWorld()->SpawnActor <ABullet>(BulletClass, BulletTransform, SpawnParams);
	}

	if (bTryFire)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeHandleFiring, this, &AVulcanWeapon::FireProjectile, DelayBetweenShots, false);
	}

	LastFire = GetWorld()->GetTimeSeconds();
}