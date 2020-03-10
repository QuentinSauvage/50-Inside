// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_FlockingLocation.h"
#include "EnemyPawn.h"
#include "GameFramework/Controller.h"
#include "AISystem.h"
#include "VisualLogger/VisualLogger.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"


void UEnvQueryContext_FlockingLocation::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AEnemyPawn* QueryOwner = Cast<AEnemyPawn>(QueryInstance.Owner.Get());
	if (QueryOwner)
	{
		UEnvQueryItemType_Point::SetContextHelper(ContextData, QueryOwner->FlokingLocation);
	}
}