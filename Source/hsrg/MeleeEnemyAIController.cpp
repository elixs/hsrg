// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeEnemyAIController.h"

void AMeleeEnemyAIController::FollowActor(AActor* Goal)
{
	MoveToActor(Goal, 5);
}