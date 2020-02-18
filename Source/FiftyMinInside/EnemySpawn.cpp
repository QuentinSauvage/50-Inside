// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "EnemyPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"

AEnemySpawn::AEnemySpawn()
{
	DelayBetweenSpawns = 10.0f;
	LastSpawn = 0.0f;
}

void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandleSpawning, this, &AEnemySpawn::Spawn, LastSpawn + DelayBetweenSpawns - GetWorld()->GetTimeSeconds(), true, 0.0f);
}

void AEnemySpawn::Spawn()
{
	if (EnemyClass) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AEnemyPawn* Spawned = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		LastSpawn = GetWorld()->GetTimeSeconds();
	}
}
