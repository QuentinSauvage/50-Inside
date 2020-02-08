// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindTarget.h"
#include "EnemyPawnController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


UBTService_FindTarget::UBTService_FindTarget()
{
	bCreateNodeInstance = true;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyPawnController* Controller = Cast<AEnemyPawnController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		APawn* Target = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Target)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(Controller->TargetKeyID, Target);
		}
	}
}