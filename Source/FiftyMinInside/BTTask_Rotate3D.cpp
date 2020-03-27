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


#include "DrawDebugHelpers.h"


UBTTask_Rotate3D::UBTTask_Rotate3D(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

bool UBTTask_Rotate3D::CanHit(AEnemyPawn* Pawn, FVector Location)
{
	FHitResult Hit;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(Pawn);
	CollisionParameters.AddIgnoredActor(Pawn->MainWeapon);
	return	!GetWorld()->LineTraceSingleByChannel(Hit, Pawn->MainWeapon->GetActorLocation(), Location, ECC_Camera, CollisionParameters);
}

EBTNodeResult::Type UBTTask_Rotate3D::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	const float AproximateImpactDelay = 3;   //DistanceToTarget/BulletSpeed

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
				FVector LocalMove = FVector(Player->CurrentForwardSpeed, Player->CurrentRightSpeed, Player->CurrentUpSpeed);
				if (Player && !LocalMove.IsNearlyZero(0.5f))
				{
					//Try to predict player's futur location
					FVector NextLocation = LocalMove * Player->GetActorForwardVector() * AproximateImpactDelay;
					if (CanHit(Pawn, NextLocation))
					{
						TargetLocation += NextLocation;
					}

				}
				
				//DrawDebugSphere(GetWorld(), TargetLocation, 24, 32, FColor(255, 0, 0), false, 2);
				//DrawDebugLine(GetWorld(), TargetLocation, Pawn->GetActorLocation(), FColor::Red, false, 2);
				Pawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Pawn->GetActorLocation(), TargetLocation));
			}
		}

	}
	return EBTNodeResult::Succeeded;
}