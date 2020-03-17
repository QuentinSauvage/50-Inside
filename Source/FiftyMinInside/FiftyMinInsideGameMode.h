// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FiftyMinInsideGameMode.generated.h"

UCLASS(MinimalAPI)
class AFiftyMinInsideGameMode : public AGameModeBase
{
	GENERATED_BODY()

	int TargetCounter;
	int PickUpsCounter;
	bool EnemiesMode;

public:
	AFiftyMinInsideGameMode();

	UFUNCTION(BlueprintCallable, Category = Objectives)
	int GetTargetCounter();

	UFUNCTION(BlueprintCallable, Category = Objectives)
	void SetTargetCounter(int NewTargetCounter);
	
	UFUNCTION(BlueprintCallable, Category = Objectives)
	int GetPickUpsCounter();
	
	UFUNCTION(BlueprintCallable, Category = Objectives)
	void SetPickUpsCounter(int NewPickUpsCounter);

	UFUNCTION(BlueprintCallable, Category = Objectives)
	void SetLevelMode(bool Mode);

	UFUNCTION(BlueprintCallable, Category = Objectives)
	bool GetLevelMode();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = EndGame)
	void OnLevelCleared();
};



