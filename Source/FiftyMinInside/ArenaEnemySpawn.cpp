// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaEnemySpawn.h"
#include "Engine/World.h"
#include "FiftyMinInsidePawn.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

void AArenaEnemySpawn::Spawn()
{
	/*if (EnemyClass) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AEnemyPawn* Spawned = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		LastSpawn = GetWorld()->GetTimeSeconds();
	}*/
}