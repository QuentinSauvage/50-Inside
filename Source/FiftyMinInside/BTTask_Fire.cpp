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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("fire")));

	if (Controller)
	{
		APawn* Enemy = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(Controller->TargetKeyID));
		AEnemyPawn* Pawn = Cast<AEnemyPawn>(Controller->GetPawn());
		if (Pawn)
		{
			if (Enemy) // && can touch target
			{
				Pawn->OnFire();
				/*FVector Forward = (Enemy->GetActorLocation() - Char->GetActorLocation());
				FVector StartTmp = Char->GetActorLocation();
				StartTmp.Z += 50.0f;
				if (Char->CurrentWeapon->CanTouch(Enemy, StartTmp, Forward))
				{
					Char->FireToDirection(Forward);
					Char->StopFire();
					return EBTNodeResult::Succeeded;
				}*/
				return EBTNodeResult::Succeeded;
			}
			Pawn->StopFire();
			OwnerComp.GetBlackboardComponent()->ClearValue(Controller->TargetKeyID);
		}
	}
	return EBTNodeResult::Failed;

}