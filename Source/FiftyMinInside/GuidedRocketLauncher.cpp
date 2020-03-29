// Fill out your copyright notice in the Description page of Project Settings.


#include "GuidedRocketLauncher.h"
#include "Engine/World.h"
#include "GuidedRocket.h"
#include "FiftyMinInsidePawn.h"
#include "Kismet/GameplayStatics.h"

AGuidedRocketLauncher::AGuidedRocketLauncher() {
	bFiring = false;
	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player = Cast<AFiftyMinInsidePawn>(pawn);
	MunitionCount = 0.f;
}

void AGuidedRocketLauncher::ResetFiring()
{
	bFiring = false;
	Player->SetGuidedRocket(nullptr);
}

void AGuidedRocketLauncher::BeginPlay()
{
	MunitionCount = 0;
}


bool AGuidedRocketLauncher::GetFiring()
{
	return bFiring;
}

void AGuidedRocketLauncher::Fire()
{
	if (!bFiring)
	{
		FireProjectile();
	}
}

void AGuidedRocketLauncher::FireProjectile() {
	if (RocketClass)
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

		AGuidedRocket *Rocket = GetWorld()->SpawnActor <AGuidedRocket>(RocketClass, BulletTransform, SpawnParams);

		if (Player)
			Player->SetGuidedRocket(Rocket);
		bFiring = true;
	}
}