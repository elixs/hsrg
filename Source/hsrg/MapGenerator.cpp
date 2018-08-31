// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenerator.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Room.h"
#include "Path.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavMeshBoundsVolume.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meh"));
	//TestMeshComponent->RegisterComponent();
	//TestMeshComponent->SetupAttachment(RootComponent);
	//TestMeshComponent->SetRelativeLocation(FVector::ZeroVector);
	//TestMeshComponent->SetRelativeRotation(FQuat::Identity);
	//TestMeshComponent->SetStaticMesh(TestMesh);
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (RoomsAmount > MapWidth * MapHeight)
	{
		RoomsAmount = MapWidth * MapHeight;
	}

	//for (int32 i = 0; i < 20; ++i)
	//{
	//	for (int32 j = 0; j < 20; ++j)
	//	{
	//		UStaticMeshComponent *MyComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	//		MyComponent->RegisterComponent();

	//		MyComponent->SetStaticMesh(TestMesh);
	//		MyComponent->SetRelativeLocation(FVector(i * 100, j * 100, 0));
	//	}
	//}

	if (Room)
	{
		ARoom * TestRoom = GetWorld()->SpawnActor<ARoom>(Room, FVector(0.f, 0.f, -1000.f), FRotator::ZeroRotator);
		RoomSize = TestRoom->GetActorScale().X * TestRoom->Size;
		TestRoom->Destroy();
	}
	if (Path)
	{
		APath * TestPath = GetWorld()->SpawnActor<APath>(Path, FVector(0.f, 0.f, -1000.f), FRotator::ZeroRotator);
		PathSize = TestPath->GetActorScale().X *  TestPath->Size;
		TestPath->Destroy();
	}

	CreateRooms();

	CreatePaths();

	// Open Start Room

	ARoom* StartRoom = RoomsArray[FirstRoomPosition.X][FirstRoomPosition.Y];
	StartRoom->OpenAllAvailableGates();

	if (NavMesh)
	{
		//	NavMesh->GetRootComponent()->SetMobility(EComponentMobility::Stationary);
		NavMesh->SetActorRelativeLocation(FVector::ZeroVector);
		//float BlockSize = RoomSize + PathSize - 1;
		NavMesh->SetActorRelativeScale3D(FVector(MapWidth * RoomSize + (MapWidth - 1) * PathSize, MapHeight * RoomSize + (MapHeight - 1) * PathSize, 500.f));
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("///////////////////////////"));
		UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
		if (NavSys)
		{
			NavSys->OnNavigationBoundsUpdated(NavMesh);
		}
		//NavMesh->GetRootComponent()->UpdateBounds();
		//	NavMesh->GetRootComponent()->SetMobility(EComponentMobility::Static);
	}

	CreateEnemies();

	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("................."));
	//}

	//if (NavMesh)
	//{
	//	NavMesh->SetActorRelativeLocation(FVector::ZeroVector);
	//	float BlockSize = RoomSize + PathSize - 1;
	//	NavMesh->SetActorRelativeScale3D(FVector(BlockSize * MapWidth, BlockSize * MapHeight, 100.f));
	//}

	//GetWorld()->SpawnActor<ARoom>(Room, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
	//GetWorld()->SpawnActor<APath>(Path, FVector(RoomSize + PathSize, 0.f, 0.f), FRotator::ZeroRotator);
	//GetWorld()->SpawnActor<ARoom>(Room, FVector(RoomSize + 2 * PathSize + RoomSize, 0.f, 0.f), FRotator::ZeroRotator);

	//UStaticMeshComponent *MyComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	//MyComponent->RegisterComponent();

	//MyComponent->SetStaticMesh(TestMesh);
	//MyComponent->SetRelativeLocation(FVector(0, 0, 0));

	//UStaticMeshComponent *MyComponent2 = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	//MyComponent2->RegisterComponent();

	//MyComponent2->SetStaticMesh(TestMesh);

	//MyComponent2->SetRelativeLocation(FVector(100, 0, 0));

	//RoomsArray.Add(new Room(FVector(0, 0, 2), ERoomType::Default));

	//FString message = TEXT("Meh ") + RoomsArray[0]->Postition.ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
}

void AMapGenerator::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//TestMeshComponent->SetStaticMesh(TestMesh);

	//TestMeshComponent->RegisterComponent();
	//if (NavMesh)
	//{
	//	NavMesh->SetActorRelativeLocation(FVector::ZeroVector);
	//	float BlockSize = TestRoom->GetActorScale().X * TestRoom->Size + TestPath->GetActorScale().X *  TestPath->Size - 1;
	//	NavMesh->SetActorRelativeScale3D(FVector(BlockSize * MapWidth, BlockSize * MapHeight, 100.f));
	//}
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapGenerator::CreateRooms()
{
	for (int32 i = 0; i < MapHeight; ++i)
	{
		RoomsArray.Add(FRoomsArray());
		for (int32 j = 0; j < MapWidth; ++j)
		{
			RoomsArray[i].Add(nullptr);
		}
	}

	// Create first room at the center
	FirstRoomPosition.X = FMath::RoundToInt(MapHeight / 2);
	FirstRoomPosition.Y = FMath::RoundToInt(MapWidth / 2);
	RoomsArray[FirstRoomPosition.X][FirstRoomPosition.Y] = GetWorld()->SpawnActor<ARoom>(Room, FVector::ZeroVector, FRotator::ZeroRotator);
	RoomsArray[FirstRoomPosition.X][FirstRoomPosition.Y]->Initialize(ERoomType::Start);
	MakeTilesAvailable(FirstRoomPosition);

	//if (!RoomsArray[FirstRoomRow][FirstRoomColumn])
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("(/· - ·)/"));
	//}
	//if (FirstRoomRow - 1 > 0)
	//{
	//	AvailableTiles.Add(FVector2D(Fi))
	//}

	//auto meh  = GetWorld()->SpawnActor<ARoom>(Room, FVector::ZeroVector, FRotator::ZeroRotator);
	//RoomsArray[0][0] = meh;

	for (int32 i = 0; i < RoomsAmount - 1; ++i)
	{
		float BranchProbability = FMath::Lerp(BranchProbabilityStart, BranchProbabilityEnd, float(i) / (RoomsAmount - 1));

		FVector2D NewRoomPosition;
		bool bThereIsBranchTile = false;

		if (BranchProbability >= FMath::RandRange(0, 1))
		{
			for (FVector2D AvailableTile : AvailableTiles)
			{
				if (IsBranchTile(AvailableTile))
				{
					NewRoomPosition = AvailableTile;
					bThereIsBranchTile = true;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Branch"));
					break;
				}
			}
		}

		if (!bThereIsBranchTile)
		{
			NewRoomPosition = AvailableTiles[FSetElementId::FromInteger(FMath::RandRange(0, AvailableTiles.Num() - 1))];
			//UE_LOG(LogTemp, Error, TEXT("No hay branch"));
		}

		AvailableTiles.Remove(NewRoomPosition);

		//UE_LOG(LogTemp, Warning, TEXT("NewRoomPosition = %s"), *NewRoomPosition.ToString());

		//Create Room
		FVector2D DeltaPosition = (RoomSize + PathSize) * (NewRoomPosition - FirstRoomPosition);
		FVector RoomLocation = FVector(DeltaPosition.Y, DeltaPosition.X, 0.f);
		ARoom* NewRoom = GetWorld()->SpawnActor<ARoom>(Room, RoomLocation, FRotator::ZeroRotator);
		NewRoom->Initialize(ERoomType::Default);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Room created");
		RoomsArray[NewRoomPosition.X][NewRoomPosition.Y] = NewRoom;
		MakeTilesAvailable(NewRoomPosition);
	}
}

void AMapGenerator::CreatePaths()
{
	// BFS

	TQueue<FVector2D> Queue;
	TSet<FVector2D> Visited;

	Queue.Enqueue(FirstRoomPosition);

	while (!Queue.IsEmpty())
	{
		FVector2D Position;
		Queue.Dequeue(Position);
		int32 Row = Position.X;
		int32 Column = Position.Y;

		// Check neighbors and create paths

		if (Row - 1 > 0 && RoomsArray[Row - 1][Column])
		{
			FVector2D NeighborPosition = FVector2D(Row - 1, Column);
			if (!Visited.Contains(NeighborPosition))
			{
				Queue.Enqueue(NeighborPosition);
				//Create Path
				FVector2D DeltaPosition = (RoomSize + PathSize) * (NeighborPosition - FirstRoomPosition + FVector2D(0.5f, 0.f));
				FVector PathLocation = FVector(DeltaPosition.Y, DeltaPosition.X, 0.f);
				APath* NewPath = GetWorld()->SpawnActor<APath>(Path, PathLocation, FRotator::ZeroRotator);
				NewPath->EnableUp();
				RoomsArray[Row][Column]->Up = NewPath;
				RoomsArray[Row - 1][Column]->Down = NewPath;
				NewPath->First = RoomsArray[Row][Column];
				NewPath->Second = RoomsArray[Row - 1][Column];
			}
		}
		if (Row + 1 < MapHeight && RoomsArray[Row + 1][Column])
		{
			FVector2D NeighborPosition = FVector2D(Row + 1, Column);
			if (!Visited.Contains(NeighborPosition))
			{
				Queue.Enqueue(NeighborPosition);
				//Create Path
				FVector2D DeltaPosition = (RoomSize + PathSize) * (NeighborPosition - FirstRoomPosition - FVector2D(0.5f, 0.f));
				FVector PathLocation = FVector(DeltaPosition.Y, DeltaPosition.X, 0.f);
				APath* NewPath = GetWorld()->SpawnActor<APath>(Path, PathLocation, FRotator::ZeroRotator);
				NewPath->EnableDown();
				RoomsArray[Row][Column]->Down = NewPath;
				RoomsArray[Row + 1][Column]->Up = NewPath;
				NewPath->First = RoomsArray[Row][Column];
				NewPath->Second = RoomsArray[Row + 1][Column];
			}
		}
		if (Column - 1 > 0 && RoomsArray[Row][Column - 1])
		{
			FVector2D NeighborPosition = FVector2D(Row, Column - 1);
			if (!Visited.Contains(NeighborPosition))
			{
				Queue.Enqueue(NeighborPosition);
				//Create Path
				FVector2D DeltaPosition = (RoomSize + PathSize) * (NeighborPosition - FirstRoomPosition + FVector2D(0.f, 0.5f));
				FVector PathLocation = FVector(DeltaPosition.Y, DeltaPosition.X, 0.f);
				APath* NewPath = GetWorld()->SpawnActor<APath>(Path, PathLocation, FRotator::ZeroRotator);
				NewPath->EnableLeft();
				RoomsArray[Row][Column]->Left = NewPath;
				RoomsArray[Row][Column - 1]->Right = NewPath;
				NewPath->First = RoomsArray[Row][Column];
				NewPath->Second = RoomsArray[Row][Column - 1];
			}
		}
		if (Column + 1 < MapWidth && RoomsArray[Row][Column + 1])
		{
			FVector2D NeighborPosition = FVector2D(Row, Column + 1);
			if (!Visited.Contains(NeighborPosition))
			{
				Queue.Enqueue(NeighborPosition);
				//Create Path
				FVector2D DeltaPosition = (RoomSize + PathSize) * (NeighborPosition - FirstRoomPosition - FVector2D(0.f, 0.5f));
				FVector PathLocation = FVector(DeltaPosition.Y, DeltaPosition.X, 0.f);
				APath* NewPath = GetWorld()->SpawnActor<APath>(Path, PathLocation, FRotator::ZeroRotator);
				NewPath->EnableRight();
				RoomsArray[Row][Column]->Right = NewPath;
				RoomsArray[Row][Column + 1]->Left = NewPath;
				NewPath->First = RoomsArray[Row][Column];
				NewPath->Second = RoomsArray[Row][Column + 1];
			}
		}

		Visited.Add(Position);
	}
}

void AMapGenerator::MakeTilesAvailable(FVector2D Tile)
{
	int32 Row = Tile.X;
	int32 Column = Tile.Y;
	if (Row - 1 > 0 && !RoomsArray[Row - 1][Column])
	{
		AvailableTiles.Add(FVector2D(Row - 1, Column));
	}
	if (Row + 1 < MapHeight && !RoomsArray[Row + 1][Column])
	{
		AvailableTiles.Add(FVector2D(Row + 1, Column));
	}
	if (Column - 1 > 0 && !RoomsArray[Row][Column - 1])
	{
		AvailableTiles.Add(FVector2D(Row, Column - 1));
	}
	if (Column + 1 < MapWidth && !RoomsArray[Row][Column + 1])
	{
		AvailableTiles.Add(FVector2D(Row, Column + 1));
	}
	ShuffleTiles();
}

bool AMapGenerator::IsBranchTile(FVector2D Tile)
{
	int32 Row = Tile.X;
	int32 Column = Tile.Y;
	uint8 Neighbors = 0;
	//(LogTemp, Warning, TEXT("%s"), *Tile.ToString());
	if (Row - 1 > 0 && RoomsArray[Row - 1][Column])
	{
		++Neighbors;
	}
	if (Row + 1 < MapHeight && RoomsArray[Row + 1][Column])
	{
		++Neighbors;
	}
	if (Column - 1 > 0 && RoomsArray[Row][Column - 1])
	{
		++Neighbors;
	}
	if (Column + 1 < MapWidth && RoomsArray[Row][Column + 1])
	{
		++Neighbors;
	}
	//if (Row - 1 > 0 && Column - 1 > 0 && RoomsArray[Row - 1][Column - 1])
	//{
	//	++Neighbors;
	//}
	//if (Row - 1 > 0 && Column + 1 < MapWidth && RoomsArray[Row - 1][Column + 1])
	//{
	//	++Neighbors;
	//}
	//if (Row + 1 < MapHeight && Column - 1 > 0 && RoomsArray[Row + 1][Column - 1])
	//{
	//	++Neighbors;
	//}
	//if (Row + 1 < MapHeight && Column + 1 < MapWidth && RoomsArray[Row + 1][Column + 1])
	//{
	//	++Neighbors;
	//}

	//UE_LOG(LogTemp, Warning, TEXT("Neighbors = %i"), Neighbors);

	return Neighbors == 1;
}

void AMapGenerator::ShuffleTiles()
{
	AvailableTiles.Sort([](const FVector2D& A, const FVector2D& B)
	{
		return FMath::RandRange(0.f, 1.f) > 0.5;
	});
}

void AMapGenerator::CreateEnemies()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating enemies"));
	for (int32 i = 0; i < MapHeight; ++i)
	{
		for (int32 j = 0; j < MapWidth; ++j)
		{
			if (ARoom* Room = RoomsArray[i][j])
			{
				UE_LOG(LogTemp, Warning, TEXT("New enemies"));

				if (Room->Type == ERoomType::Default)
				{
					Room->LoadEnemies(FMath::RandRange(MinEnemies, MaxEnemies));
				}
			}
		}
	}
}