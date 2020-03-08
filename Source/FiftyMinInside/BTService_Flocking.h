// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Flocking.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API UBTService_Flocking : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Flocking();

		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
