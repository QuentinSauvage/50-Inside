// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawn.h"
#include "ArenaEnemySpawn.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API AArenaEnemySpawn : public AEnemySpawn
{
	GENERATED_BODY()
	

	protected:
		void Spawn() override;

};
