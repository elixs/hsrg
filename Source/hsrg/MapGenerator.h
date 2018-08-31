// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"


USTRUCT()
struct FRoomsArray
{
	GENERATED_BODY()
public:

	TArray<class ARoom*> Rooms;

	class ARoom*& operator[] (int32 i)
	{
		return Rooms[i];
	}

	void Add(class ARoom* Room)
	{
		Rooms.Add(Room);
	}
};

UCLASS()
class HSRG_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	UStaticMesh* TestMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARoom> Room;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APath> Path;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent *TestMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MapWidth = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MapHeight = 7;

	UPROPERTY(EditAnywhere)
	uint16 RoomsAmount = 10;

	UPROPERTY(EditAnywhere)
	uint8 MinEnemies = 1;

	UPROPERTY(EditAnywhere)
	uint8 MaxEnemies = 1;

	uint16 RoomSize = 100;

	uint16 PathSize = 50;


	TArray<FRoomsArray> RoomsArray;

	UPROPERTY(EditAnywhere)
	float BranchProbabilityStart = 0.2;

	UPROPERTY(EditAnywhere)
	float BranchProbabilityEnd = 0.05;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ANavMeshBoundsVolume* NavMesh;

private:
	void CreateRooms();

	void CreatePaths();


	void MakeTilesAvailable(FVector2D Tile);

	bool IsBranchTile(FVector2D Tile);

	void ShuffleTiles();

	TSet<FVector2D> AvailableTiles;

	FVector2D FirstRoomPosition;
	
	void CreateEnemies();

};
