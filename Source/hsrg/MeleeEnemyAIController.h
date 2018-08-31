// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MeleeEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HSRG_API AMeleeEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	void FollowActor(AActor* Goal);
	
	
};
