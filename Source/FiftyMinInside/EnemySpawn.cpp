// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "EnemyPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

AEnemySpawn::AEnemySpawn()
{
	PrimaryActorTick.bCanEverTick = true;


	DelayBetweenSpawns = 10.f;
	LastSpawn = 0.0f;
	bPlayerNear = false;
	bFirstLoop = true;
}

void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandleSpawning, this, &AEnemySpawn::Spawn, LastSpawn + DelayBetweenSpawns - GetWorld()->GetTimeSeconds(), true, 5.0f);
}

void AEnemySpawn::Spawn()
{
	if (EnemyClass) {
		if (!bArenaSpawn && bPlayerNear)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AEnemyPawn* Spawned = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		}
		else if (bArenaSpawn)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			float spawnX = FMath::RandRange(-8000.f, 8000.f);
			float spawnY = FMath::RandRange(-8000.f, 8000.f);
			float spawnZ = FMath::RandRange(-8000.f, 8000.f);
			FVector EnemySpawnLocation = FVector(spawnX, spawnY, spawnZ);

			AEnemyPawn* Spawned = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, EnemySpawnLocation, GetActorRotation(), SpawnParams);
		}
		LastSpawn = GetWorld()->GetTimeSeconds();
	}
}
