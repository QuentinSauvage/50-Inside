// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "TimerManager.h"

ARocketLauncher::ARocketLauncher() {
	PrimaryActorTick.bCanEverTick = true;

	bFireLeft = false;
}

void ARocketLauncher::FireProjectile() {
	if (BulletClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Pew Rocket!"));

		if (MunitionCount == 0) {
			return;
		}
		--MunitionCount;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;

		FVector Offset = GetActorLocation();
		Offset.Y += (bFireLeft) ? -70.f : 70.f;
		bFireLeft = !bFireLeft;

		FTransform BulletTransform;
		BulletTransform.SetLocation(Offset);
		BulletTransform.SetRotation(GetActorRotation().Quaternion());
		BulletTransform.SetScale3D(FVector(1.f));

		GetWorld()->SpawnActor <ABullet>(BulletClass, BulletTransform, SpawnParams);
	}

	if (bTryFire)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeHandleFiring, this, &ARocketLauncher::FireProjectile, DelayBetweenShots, false);
	}

	LastFire = GetWorld()->GetTimeSeconds();
}