// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Engine/Scene.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	RootComponent = Floor;



}

void ATile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (UStaticMesh* FloorMesh = Floor->GetStaticMesh())
	{
		// The bounding box should be a square and the mesh pivot must be on the center
		FVector BoundingBoxSize = FloorMesh->GetBoundingBox().GetSize();

		Size = FMath::TruncToInt(BoundingBoxSize.X);
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}