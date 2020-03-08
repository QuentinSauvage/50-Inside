// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawnController.h"
#include "EnemyPawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/GameplayStatics.h"

AEnemyPawnController::AEnemyPawnController() {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AEnemyPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyPawn* EPawn = Cast<AEnemyPawn>(InPawn);

	//Init Blackboard and start behavoir tree
	if (EPawn && EPawn->Behavior)
	{
		BlackboardComp->InitializeBlackboard(*EPawn->Behavior->BlackboardAsset);
		DirectionKeyID = BlackboardComp->GetKeyID("Direction");
		TargetKeyID = BlackboardComp->GetKeyID("Target");
		FlokingLocationKeyID = BlackboardComp->GetKeyID("FlokingLocation");
		BehaviorComp->StartTree(*EPawn->Behavior);
	}

}