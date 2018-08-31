// Fill out your copyright notice in the Description page of Project Settings.

#include "NewNavRelevantComponent.h"

UNewNavRelevantComponent::UNewNavRelevantComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Bounds = FBox(FVector(-1148.f, -1148, -100.f), FVector(1148.f, 1148.f, 500.f));
}


