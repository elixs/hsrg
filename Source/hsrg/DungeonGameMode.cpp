// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DungeonGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MeleeEnemyCharacter.h"

ADungeonGameMode::ADungeonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


TArray<TSubclassOf<AMeleeEnemyCharacter>> ADungeonGameMode::GetEnemyTypes()
{
	return EnemyTypes;
}
