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


UBTTask_Rotate3D::UBTTask_Rotate3D(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), lastPosition() {}


void UBTTask_Rotate3D::PostInitProperties()
{
	Super::PostInitProperties();

	PrecisionDot = FMath::Cos(FMath::DegreesToRadians(Precision));
}

EBTNodeResult::Type UBTTask_Rotate3D::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyPawnController* Controller = Cast<AEnemyPawnController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			APawn* Pawn = Controller->GetPawn();

			UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
			AActor* ActorValue = Cast<AActor>(KeyValue);

			if (ActorValue != NULL)
			{
				Pawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Pawn->GetActorLocation(), ActorValue->GetActorLocation()));
			}
		}

	}
	return EBTNodeResult::Succeeded;
}