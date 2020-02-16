// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h"
#include "BTTask_Rotate3D.generated.h"

/**
 * 
 */
UCLASS()
class FIFTYMININSIDE_API UBTTask_Rotate3D : public UBTTask_RotateToFaceBBEntry
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBTTask_Rotate3D(const FObjectInitializer& ObjectInitializer);

};
