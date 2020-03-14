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

public:
	AFiftyMinInsideGameMode();

	UFUNCTION(BlueprintCallable, Category = Health)
	int GetTargetCounter();

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetTargetCounter(int NewTargetCounter);
	
	UFUNCTION(BlueprintCallable, Category = Health)
	int GetPickUpsCounter();
	
	UFUNCTION(BlueprintCallable, Category = Health)
	void SetPickUpsCounter(int NewPickUpsCounter);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = EndGame)
	void OnLevelCleared();
};



