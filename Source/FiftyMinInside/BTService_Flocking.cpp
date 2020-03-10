// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Flocking.h"
#include "EnemyPawnController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/World.h"
#include "EnemyPawn.h"
#include "Kismet/KismetSystemLibrary.h"


UBTService_Flocking::UBTService_Flocking()
{
	bCreateNodeInstance = true;
}

void UBTService_Flocking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyPawnController* Controller = Cast<AEnemyPawnController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		AEnemyPawn* Pawn = Cast<AEnemyPawn>(Controller->GetPawn());

		if (Pawn)
		{
			if (Pawn->Neighbors.Num() > 0)
			{
				FVector CohesionComponent = FVector::ZeroVector;
				FVector SeparationComponent = FVector::ZeroVector;

				// Compute Cohesion Component Vector
				for (AEnemyPawn* Agent : Pawn->Neighbors)
				{
					if (Agent)
					{
						CohesionComponent += Agent->GetActorLocation() - Pawn->GetActorLocation();
					}
				}
				CohesionComponent /= Pawn->Neighbors.Num() * 100.0f;
				// Compute Separation Component Vector
				for (AActor* Agent : Pawn->Neighbors)
				{
					if (Agent)
					{
						FVector SeparationVector = Pawn->GetActorLocation() - Agent->GetActorLocation();
						SeparationComponent += SeparationVector.GetSafeNormal() / FMath::Abs(SeparationVector.Size() - 800);
					}
				}
				SeparationComponent *= (1.0f + Pawn->Neighbors.Num() / 5.0f) * 100.0f;
				Pawn->FlokingLocation = Pawn->GetActorLocation() + CohesionComponent + SeparationComponent;
				//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(Controller->FlokingLocationKeyID, Pawn->GetActorLocation() + CohesionComponent + SeparationComponent);
			}
		}



	}
}
