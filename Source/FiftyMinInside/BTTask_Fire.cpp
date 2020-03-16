// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fire.h"
#include "EnemyPawn.h"
#include "EnemyPawnController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"



EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyPawnController* Controller = Cast<AEnemyPawnController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(Controller->TargetKeyID));
		AEnemyPawn* Pawn = Cast<AEnemyPawn>(Controller->GetPawn());
		if (Pawn)
		{
			if (Target)
			{
				float DistanceToTarget = (Pawn->GetActorLocation() - Target->GetActorLocation()).Size();
				if (DistanceToTarget < 20000 && Pawn->CanFireTo(Target))
				{
					Pawn->OnFire();
					return EBTNodeResult::Succeeded;
				}
			}
			Pawn->StopFire();
			OwnerComp.GetBlackboardComponent()->ClearValue(Controller->TargetKeyID);
		}
	}
	return EBTNodeResult::Failed;

}