// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Rotate3D.h"
#include "BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyPawnController.h"
#include "Kismet/KismetMathLibrary.h"
#include "FiftyMinInsidePawn.h"
#include "EnemyPawn.h"
#include "Weapon.h"

UBTTask_Rotate3D::UBTTask_Rotate3D(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

EBTNodeResult::Type UBTTask_Rotate3D::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	const float AproximateBulletSpeed = 4000;

	AEnemyPawnController* Controller = Cast<AEnemyPawnController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			AEnemyPawn* Pawn = Cast< AEnemyPawn>(Controller->GetPawn());

			UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
			AActor* ActorValue = Cast<AActor>(KeyValue);

			if (ActorValue && Pawn)
			{
				FVector TargetLocation = ActorValue->GetActorLocation();
				AFiftyMinInsidePawn* Player = Cast<AFiftyMinInsidePawn>(ActorValue);
				if (Player && !Player->LocalMove.IsNearlyZero(0.5f))
				{
					TargetLocation += Player->LocalMove * ((Pawn->GetActorLocation() - Player->GetActorLocation()) / AproximateBulletSpeed).GetAbs();
				}
				Pawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Pawn->GetActorLocation(), TargetLocation));
			}
		}

	}
	return EBTNodeResult::Succeeded;
}