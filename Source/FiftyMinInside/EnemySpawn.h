// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

UCLASS()
class FIFTYMININSIDE_API AEnemySpawn : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AEnemyPawn> EnemyClass;

	UPROPERTY(EditAnywhere)
		float DelayBetweenSpawns;

	float LastSpawn;

	UPROPERTY(EditAnywhere)
		float Radius;

	FTimerHandle TimeHandleSpawning;

public:
	// Sets default values for this actor's properties
	AEnemySpawn();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPlayerNear;

	void Spawn();
};
