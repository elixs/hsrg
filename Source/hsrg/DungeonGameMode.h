// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonGameMode.generated.h"

UCLASS(minimalapi)
class ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADungeonGameMode();

	// TODO Use Game Instance?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	TArray<TSubclassOf<class AMeleeEnemyCharacter>> EnemyTypes;

	TArray<TSubclassOf<class AMeleeEnemyCharacter>> GetEnemyTypes();
};



