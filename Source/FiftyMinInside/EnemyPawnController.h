// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyPawnController.generated.h"

/**
 *
 */
UCLASS()
class FIFTYMININSIDE_API AEnemyPawnController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient)
		class UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
		class UBehaviorTreeComponent* BehaviorComp;

public:
	AEnemyPawnController();

	virtual void OnPossess(APawn* InPawn) override;

	uint8 DirectionKeyID;
	uint8 TargetKeyID;
	uint8 FlokingLocationKeyID;

};
