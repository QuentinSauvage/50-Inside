// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FiftyMinInsideGameMode.h"
#include "FiftyMinInsidePawn.h"

AFiftyMinInsideGameMode::AFiftyMinInsideGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AFiftyMinInsidePawn::StaticClass();
	EnemiesMode = false;
	TargetCounter = 0;
	PickUpsCounter = 0;

}

int AFiftyMinInsideGameMode::GetTargetCounter()
{
	return TargetCounter;
}

void AFiftyMinInsideGameMode::SetTargetCounter(int NewTargetCounter)
{
	TargetCounter += NewTargetCounter;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), TargetCounter));
	if (!TargetCounter)
	{
		this->OnLevelCleared();
	}
}

int AFiftyMinInsideGameMode::GetPickUpsCounter()
{
	return PickUpsCounter;
}

void AFiftyMinInsideGameMode::SetPickUpsCounter(int NewPickUpsCounter)
{
	PickUpsCounter += NewPickUpsCounter;
}

void AFiftyMinInsideGameMode::SetLevelMode(bool Mode)
{
	EnemiesMode = Mode;
}

bool AFiftyMinInsideGameMode::GetLevelMode()
{
	return EnemiesMode;
}