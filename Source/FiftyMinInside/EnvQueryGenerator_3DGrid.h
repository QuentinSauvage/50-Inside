// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_SimpleGrid.h"
#include "EnvQueryGenerator_3DGrid.generated.h"

/**
 *
 */
UCLASS()
class FIFTYMININSIDE_API UEnvQueryGenerator_3DGrid : public UEnvQueryGenerator_SimpleGrid
{
	GENERATED_BODY()


		virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
};
