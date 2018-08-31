// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Public/AI/NavigationModifier.h"
#include "Runtime/Engine/Public/AI/NavigationOctree.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavAreas/NavArea_Null.h"
#include "MeleeEnemyCharacter.h"
#include "DungeonGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/MovieScene/Public/MovieSceneSequencePlayer.h"
//#include "UObject/SoftObjectPath.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPath.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "PlayerCharacter.h"

// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Archs

	Archs = CreateDefaultSubobject<USceneComponent>(TEXT("Archs"));
	Archs->SetupAttachment(RootComponent);

	ArchUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchUp"));
	ArchUp->SetupAttachment(Archs);
	ArchUp->SetRelativeLocationAndRotation(FVector(0.f, -1093.f, 0.f), FRotator(0.f, 0.f, 0.f));
	ArchUp->SetRelativeScale3D(FVector(2.5f));

	ArchDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchDown"));
	ArchDown->SetupAttachment(Archs);
	ArchDown->SetRelativeLocationAndRotation(FVector(0.f, 1093.f, 0.f), FRotator(0.f, 180.f, 0.f));
	ArchDown->SetRelativeScale3D(FVector(2.5f));

	ArchLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchLeft"));
	ArchLeft->SetupAttachment(Archs);
	ArchLeft->SetRelativeLocationAndRotation(FVector(-1093.f, 0.f, 0.f), FRotator(0.f, -90.f, 0.f));
	ArchLeft->SetRelativeScale3D(FVector(2.5f));

	ArchRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArchRight"));
	ArchRight->SetupAttachment(Archs);
	ArchRight->SetRelativeLocationAndRotation(FVector(1093.f, 0.f, 0.f), FRotator(0.f, 90.f, 0.f));
	ArchRight->SetRelativeScale3D(FVector(2.5f));

	// Barriers

	Barriers = CreateDefaultSubobject<USceneComponent>(TEXT("Barriers"));
	Barriers->SetupAttachment(RootComponent);

	BarrierLeftUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierLeftUp"));
	BarrierLeftUp->SetupAttachment(Barriers);
	BarrierLeftUp->SetRelativeLocationAndRotation(FVector(-735.5f, -735.5f, 87.f), FRotator(0.f, -135.f, 0.f));
	BarrierLeftUp->SetRelativeScale3D(FVector(1.f, 1.402f, 1.f));

	BarrierLeftDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierLeftDown"));
	BarrierLeftDown->SetupAttachment(Barriers);
	BarrierLeftDown->SetRelativeLocationAndRotation(FVector(-735.5f, 735.5f, 87.f), FRotator(0.f, 135.f, 0.f));
	BarrierLeftDown->SetRelativeScale3D(FVector(1.f, 1.402f, 1.f));

	BarrierRightUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierRightUp"));
	BarrierRightUp->SetupAttachment(Barriers);
	BarrierRightUp->SetRelativeLocationAndRotation(FVector(735.5f, -735.5f, 87.f), FRotator(0.f, -45.f, 0.f));
	BarrierRightUp->SetRelativeScale3D(FVector(1.f, 1.402f, 1.f));

	BarrierRightDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierRightDown"));
	BarrierRightDown->SetupAttachment(Barriers);
	BarrierRightDown->SetRelativeLocationAndRotation(FVector(735.5f, 735.5f, 87.f), FRotator(0.f, 45.f, 0.f));
	BarrierRightDown->SetRelativeScale3D(FVector(1.f, 1.402f, 1.f));

	// Gates

	//Gates = CreateDefaultSubobject<USceneComponent>(TEXT("Gates"));
	//Gates->SetupAttachment(RootComponent);

	//GateUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateUp"));
	//GateUp->SetupAttachment(ArchUp);
	//GateUp->SetRelativeLocationAndRotation(FVector(0.f, -1093.5f, 0.f), FRotator(0.f, 0.f, 0.f));
	//GateUp->SetRelativeScale3D(FVector(2.5f));

	//GateDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateDown"));
	//GateDown->SetupAttachment(ArchDown);
	//GateDown->SetRelativeLocationAndRotation(FVector(0.f, 1093.f, 0.f), FRotator(0.f, 180.f, 0.f));
	//GateDown->SetRelativeScale3D(FVector(2.5f));

	//GateLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateLeft"));
	//GateLeft->SetupAttachment(ArchLeft);
	//GateLeft->SetRelativeLocationAndRotation(FVector(-1093.f, 0.f, 0.f), FRotator(0.f, -90.f, 0.f));
	//GateLeft->SetRelativeScale3D(FVector(2.5f));

	//GateRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateRight"));
	//GateRight->SetupAttachment(ArchRight);
	//GateRight->SetRelativeLocationAndRotation(FVector(1093.f, 0.f, 0.f), FRotator(0.f, 90.f, 0.f));
	//GateRight->SetRelativeScale3D(FVector(2.5f));

	//DrawDebugPoint(GetWorld(), FVector(0.f, 0.f, 300.f), 200, FColor(52, 220, 239), true);

	//FBox TestBox = FBox(FVector(-1148.f, -1148, -100.f), FVector(1148.f, 1148.f, 500.f));

	//DrawDebugBox(GetWorld(), TestBox.GetCenter(), TestBox.GetExtent(), FColor::Red, true, -1.f, 0, 10.f);
	//DrawDebugBox(GetWorld(), TestBox.GetCenter(), TestBox.GetExtent(), FColor::Green);

	//FStringAssetReference SequenceName("/Game/Sequences/GateOpening.GateOpening'");
	//ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());

	//LevelSequencePlaye = ObjectInitializer.CreateDefaultSubobject<ULevelSequencePlayer>(this, LevelScriptStatics::CinematicSequencePlayername);

	//GateSequenceComponent = CreateDefaultSubobject<UActorSequenceComponent>(TEXT("GateSequenceComponent"));

	GateUpTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GateUpTrigger"));
	GateUpTrigger->SetupAttachment(ArchUp);
	GateUpTrigger->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
	GateUpTrigger->SetBoxExtent(FVector(250.f, 25.f, 100.f));

	GateDownTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GateDownTrigger"));
	GateDownTrigger->SetupAttachment(ArchDown);
	GateDownTrigger->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
	GateDownTrigger->SetBoxExtent(FVector(250.f, 25.f, 100.f));

	GateLeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GateLeftTrigger"));
	GateLeftTrigger->SetupAttachment(ArchLeft);
	GateLeftTrigger->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
	GateLeftTrigger->SetBoxExtent(FVector(250.f, 25.f, 100.f));

	GateRightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GateRightTrigger"));
	GateRightTrigger->SetupAttachment(ArchRight);
	GateRightTrigger->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
	GateRightTrigger->SetBoxExtent(FVector(250.f, 25.f, 100.f));
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	//DrawDebugBox(GetWorld(), TestBox.GetCenter(), TestBox.GetExtent(), FColor::Red, true, -1.f, 0, 10.f);

	//DrawDebugPoint(GetWorld(), FVector(0.f, 0.f, 300.f), 200, FColor(52, 220, 239), true);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("meh"));

	GateUpTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::CloseUp);
	GateDownTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::CloseDown);
	GateLeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::CloseLeft);
	GateRightTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::CloseRight);
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoom::Destroyed()
{
	if (GateUp)
	{
		GateUp->Destroy();
	}
	if (GateDown)
	{
		GateDown->Destroy();
	}
	if (GateLeft)
	{
		GateLeft->Destroy();
	}
	if (GateRight)
	{
		GateRight->Destroy();
	}
	Super::Destroyed();
}

void ARoom::Initialize(ERoomType IntType)
{
	Type = IntType;

	TArray<UStaticMeshComponent*> Comps;

	GateUp = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(0.f, -1100.f, 0.f) + GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	GateUp->GetComponents(Comps);
	if (Comps.Num() > 0 && GateMesh)
	{
		UStaticMeshComponent* FoundComp = Comps[0];
		FoundComp->SetStaticMesh(GateMesh);
	}
	GateUp->SetActorRelativeScale3D(FVector(2.5f));
	GateUp->SetMobility(EComponentMobility::Movable);
	//GateUp->SetActorEnableCollision(false);

	GateDown = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(0.f, 1100.f, 0.f) + GetActorLocation(), FRotator(0.f, 180.f, 0.f));
	GateDown->GetComponents(Comps);
	if (Comps.Num() > 0 && GateMesh)
	{
		UStaticMeshComponent* FoundComp = Comps[0];
		FoundComp->SetStaticMesh(GateMesh);
	}
	GateDown->SetActorRelativeScale3D(FVector(2.5f));
	GateDown->SetMobility(EComponentMobility::Movable);
	//GateDown->SetActorEnableCollision(false);

	GateLeft = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(-1100.f, 0.f, 0.f) + GetActorLocation(), FRotator(0.f, -90.f, 0.f));
	GateLeft->GetComponents(Comps);
	if (Comps.Num() > 0 && GateMesh)
	{
		UStaticMeshComponent* FoundComp = Comps[0];
		FoundComp->SetStaticMesh(GateMesh);
	}
	GateLeft->SetActorRelativeScale3D(FVector(2.5f));
	GateLeft->SetMobility(EComponentMobility::Movable);
	//GateLeft->SetActorEnableCollision(false);

	GateRight = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(1100.f, 0.f, 0.f) + GetActorLocation(), FRotator(0.f, 90.f, 0.f));
	GateRight->GetComponents(Comps);
	if (Comps.Num() > 0 && GateMesh)
	{
		UStaticMeshComponent* FoundComp = Comps[0];
		FoundComp->SetStaticMesh(GateMesh);
	}
	GateRight->SetActorRelativeScale3D(FVector(2.5f));
	GateRight->SetMobility(EComponentMobility::Movable);
	//GateRight->SetActorEnableCollision(false);

	if (Type == ERoomType::Start)
	{
		DisableTriggers();
		//if (Up)
		//{
		//	GateUp->Destroy();
		//}
		//if (Down)
		//{
		//	GateDown->Destroy();
		//}
		//if (Left)
		//{
		//	GateLeft->Destroy();
		//}
		//if (Right)
		//{
		//	GateRight->Destroy();
		//}
	}
}

void ARoom::LoadEnemies(uint8 EnemyAmount)
{
	EnemyCount = EnemyAmount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Enemies " + FString::FromInt(EnemyAmount));
	if (ADungeonGameMode* DGM = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode()))
	{
		TArray<TSubclassOf<AMeleeEnemyCharacter>> EnemyTypes = DGM->GetEnemyTypes();
		if (EnemyTypes.Num())
		{
			for (uint8 i = 0; i < EnemyAmount; ++i)
			{
				TSubclassOf<AMeleeEnemyCharacter> Enemy = EnemyTypes[FMath::RandRange(0, EnemyTypes.Num() - 1)];
				// Spawn enemy on random point of the radius
				UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
				if (NavSys)
				{
					FVector2D RandomPosition = FMath::RandPointInCircle(SpawnInnerRadius);
					RandomPosition = RandomPosition + RandomPosition.GetSafeNormal()*(SpawnOuterRadius - SpawnInnerRadius);
					FVector SpawnLocation = FVector(RandomPosition, 90.f) + GetActorLocation();
					//NavSys->GetRandomPointInNavigableRadius(GetActorLocation(), SpawnRadius, SpawnLocation);
					//UE_LOG(LogTemp, Warning, TEXT("Actor Location = %s"), *GetActorLocation().ToString());
					//UE_LOG(LogTemp, Warning, TEXT("Spawn Location = %s"), *SpawnLocation.ToString());
					AMeleeEnemyCharacter* NewEnemy = GetWorld()->SpawnActor<AMeleeEnemyCharacter>(Enemy, SpawnLocation, FRotator::ZeroRotator);
					NewEnemy->SpawnDefaultController();
					FScriptDelegate Delegate;
					Delegate.BindUFunction(this, "EnemyDeath");
					NewEnemy->OnDestroyed.Add(Delegate);
					//NewEnemy->OnDeathDelegate.Add(Delegate);
				}
			}
		}
	}
}

void ARoom::EnemyDeath()
{
	--EnemyCount;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Enemy death"));
	if (!EnemyCount)
	{
		OpenAllAvailableGates();
	}
}

void ARoom::OpenGates(TArray<AActor*> Gates, bool bReverse)
{
	ULevelSequence* GateSequence;
	if (bReverse)
	{
		GateSequence = Cast<ULevelSequence>(GateCloseSequencePath.TryLoad());
	}
	else
	{
		GateSequence = Cast<ULevelSequence>(GateOpenSequencePath.TryLoad());
	}

	if (GateSequence)
	{
		FMovieSceneSequencePlaybackSettings Settings = FMovieSceneSequencePlaybackSettings();
		if (bReverse)
		{
			Settings.PlayRate = 10.f;
		}
		else
		{
			Settings.PlayRate = 2.f;
		}
		ALevelSequenceActor* OutActor;
		ULevelSequencePlayer* Player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), GateSequence, Settings, OutActor);
		TArray<FMovieSceneBinding> Bindings = GateSequence->MovieScene->GetBindings();
		if (Bindings.Num() > 0)
		{
			FMovieSceneBinding Binding = Bindings[0];
			FMovieSceneObjectBindingID BindingID = FMovieSceneObjectBindingID(Binding.GetObjectGuid(), MovieSceneSequenceID::Root);
			OutActor->SetBinding(BindingID, Gates);
		}
		if (Player)
		{
			Player->Play();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Couldn't find a player"));
		}
	}
}

void ARoom::CloseUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		DisableTriggers();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trigger Up")));
		TArray<AActor*> Gates;
		Gates.Add(GateUp);
		OpenGates(Gates, true);
	}
}

void ARoom::CloseDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		DisableTriggers();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trigger Down")));
		TArray<AActor*> Gates;
		Gates.Add(GateDown);
		OpenGates(Gates, true);
	}
}

void ARoom::CloseLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		DisableTriggers();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trigger Left")));
		TArray<AActor*> Gates;
		Gates.Add(GateLeft);
		OpenGates(Gates, true);
	}
}

void ARoom::CloseRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		DisableTriggers();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trigger Right")));
		TArray<AActor*> Gates;
		Gates.Add(GateRight);
		OpenGates(Gates, true);
	}
}

void ARoom::OpenAllAvailableGates()
{
	TArray<AActor*> Gates;
	if (Up)
	{
		Gates.Add(GateUp);
		bIsGateUpOn = false;
	}
	if (Down)
	{
		Gates.Add(GateDown);
		bIsGateDownOn = false;
	}
	if (Left)
	{
		Gates.Add(GateLeft);
		bIsGateLeftOn = false;
	}
	if (Right)
	{
		Gates.Add(GateRight);
		bIsGateRightOn = false;
	}
	OpenGates(Gates);
}

void ARoom::DisableTriggers()
{
	GateUpTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GateDownTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GateLeftTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GateRightTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//void ARoom::GetNavigationData(FNavigationRelevantData& Data) const
//{
	//FBox TestBox = FBox(FVector(-1148.f, -1148, -100.f), FVector(1148.f, 1148.f, 500.f));
	//FAreaNavModifier Test = FAreaNavModifier(TestBox, FVector(0.f), UNavigationSystem::GetDefaultWalkableArea());
	//FAreaNavModifier Test = FAreaNavModifier(FBox::BuildAABB(FVector(0.f,0.f,150.f), FVector(2296.f, 2296.f, 500.f)), GetOwner()->GetTransform(), UNavigationSystem::GetDefaultWalkableArea());
	//FAreaNavModifier Test = FAreaNavModifier(FBox::BuildAABB(FVector(200.f,0.f,0.f), FVector(200.f, 200.f, 500.f)), GetTransform(), UNavArea_Null::StaticClass());

	//Data.Modifiers.Add(Test);
	//Data.Bounds = FBox(FVector(-1148.f, -1148, -100.f), FVector(1148.f, 1148.f, 500.f));
	//Data.Modifiers.CreateAreaModifiers(NavBox, UNavigationSystem::GetDefaultObstacleArea());
	//Data.Modifiers.CreateAreaModifiers(NavBox, UNavArea_Null::StaticClass());
//}

//FBox ARoom::GetNavigationBounds() const
//{
//	return NavBox->CalcBounds(GetOwner()->GetTransform()).GetBox();
//}
//
//bool ARoom::IsNavigationRelevant() const
//{
//	return true;
//}