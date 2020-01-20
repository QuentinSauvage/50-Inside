// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FiftyMinInsideGameMode.h"
#include "FiftyMinInsidePawn.h"

AFiftyMinInsideGameMode::AFiftyMinInsideGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AFiftyMinInsidePawn::StaticClass();
}
