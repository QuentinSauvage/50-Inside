// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FlyTo.h"
#include "BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyPawnController.h"
#include "EnemyPawn.h"


EBTNodeResult::Type UBTTask_FlyTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	AEnemyPawnController* Controller = Cast<AEnemyPawnController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			const FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());

			if (FAISystem::IsValidLocation(KeyValue))
			{
				AEnemyPawn* P = Cast<AEnemyPawn>(Controller->GetPawn());
				P->CurrentDirection = KeyValue - P->GetActorLocation();
			}
		}
	}
	return EBTNodeResult::Succeeded;
}