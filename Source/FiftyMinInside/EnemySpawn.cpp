// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "EnemyPawn.h"
#include "Engine/World.h"
#include "FiftyMinInsidePawn.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

AEnemySpawn::AEnemySpawn()
{
	PrimaryActorTick.bCanEverTick = true;


	DelayBetweenSpawns = 10.0f;
	LastSpawn = 0.0f;
	bPlayerNear = false;
}

void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandleSpawning, this, &AEnemySpawn::Spawn, LastSpawn + DelayBetweenSpawns - GetWorld()->GetTimeSeconds(), true, 0.0f);
}

void AEnemySpawn::Spawn()
{
	if (EnemyClass) {
		if (bPlayerNear)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AEnemyPawn* Spawned = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		}
		LastSpawn = GetWorld()->GetTimeSeconds();
	}
}
