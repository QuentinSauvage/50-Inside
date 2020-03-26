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
}

void AGuidedRocketLauncher::ResetFiring()
{
	bFiring = false;
	Player->SetGuidedRocket(nullptr);
}

bool AGuidedRocketLauncher::GetFiring()
{
	return bFiring;
}

void AGuidedRocketLauncher::Fire()
{
	if (!bFiring)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Pew Guided!"));
		FireProjectile();
	}
}

void AGuidedRocketLauncher::FireProjectile() {
	if (RocketClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Pew Pew Guided!"));

		if (MunitionCount == 0) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("BaseMunitionCount %f "), BaseMunitionCount));
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
		else
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("no player!"));
		bFiring = true;
	}
}