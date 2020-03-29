// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "TimerManager.h"

ARocketLauncher::ARocketLauncher() {
	PrimaryActorTick.bCanEverTick = true;

	bFireLeft = false;
}

void ARocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	MunitionCount = BaseMunitionCount;
}

void ARocketLauncher::Fire()
{
	Super::Fire();
}

void ARocketLauncher::FireProjectile() {
	if (BulletClass)
	{

		if (MunitionCount == 0) {
			return;
		}
		--MunitionCount;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;

		FVector Offset = FVector(-500.f, 0.f, 0.f);
		Offset.Y += (bFireLeft) ? -300.f : 300.f;
		Offset = GetTransform().TransformPosition(Offset);
		bFireLeft = !bFireLeft;

		FTransform BulletTransform;
		BulletTransform.SetLocation(Offset);
		BulletTransform.SetRotation(GetActorRotation().Quaternion());
		BulletTransform.SetScale3D(FVector(1.f));

		ABullet *bullet = GetWorld()->SpawnActor <ABullet>(BulletClass, BulletTransform, SpawnParams);
	}

	if (bTryFire)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeHandleFiring, this, &ARocketLauncher::FireProjectile, DelayBetweenShots, false);
	}

	LastFire = GetWorld()->GetTimeSeconds();
}