// Fill out your copyright notice in the Description page of Project Settings.

#include "Path.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavModifierComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Room.h"

// Sets default values
APath::APath()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Barriers

	Barriers = CreateDefaultSubobject<USceneComponent>(TEXT("Barriers"));
	Barriers->SetupAttachment(RootComponent);

	BarrierUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierUp"));
	BarrierUp->SetupAttachment(Barriers);
	BarrierUp->SetRelativeLocationAndRotation(FVector(0.f, -345.f, 87.f), FRotator(0.f, -90.f, 0.f));

	BarrierDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierDown"));
	BarrierDown->SetupAttachment(Barriers);
	BarrierDown->SetRelativeLocationAndRotation(FVector(0.f, 345.f, 87.f), FRotator(0.f, 90.f, 0.f));

	BarrierLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierLeft"));
	BarrierLeft->SetupAttachment(Barriers);
	BarrierLeft->SetRelativeLocationAndRotation(FVector(-345.0f, 0.f, 87.f), FRotator(0.f, 180.f, 0.f));

	BarrierRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierRight"));
	BarrierRight->SetupAttachment(Barriers);
	BarrierRight->SetRelativeLocationAndRotation(FVector(345.0f, 0.f, 87.f), FRotator(0.f, 0.f, 0.f));

	NavModifier = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));
	//NavModifier->SetupAttachment(RootComponent);
	//NavModifier->SetRelativeLocationAndRotation(FVector(345.0f, 0.f, 87.f), FRotator(0.f, 0.f, 0.f));

	OpenClosedGatesTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OpenClosedGates"));
	OpenClosedGatesTrigger->SetupAttachment(Barriers);
	OpenClosedGatesTrigger->SetBoxExtent(FVector(300.f, 300.f, 100.f));
	//OpenClosedGatesTrigger->OnComponentBeginOverlap.AddDynamic(this, &APath::OpenClosedGates);
}

void APath::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	NavModifier->FailsafeExtent = FVector(Size, Size, 100.f);
}

// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();

	OpenClosedGatesTrigger->OnComponentBeginOverlap.AddDynamic(this, &APath::OpenClosedGates);

}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APath::EnableUp()
{
	EnableVertical();
}

void APath::EnableDown()
{
	EnableVertical();
}

void APath::EnableLeft()
{
	EnableHorizontal();
}

void APath::EnableRight()
{
	EnableHorizontal();
}

void APath::EnableVertical()
{
	BarrierUp->ToggleVisibility();
	BarrierUp->SetCollisionProfileName(TEXT("NoCollision"));
	BarrierDown->ToggleVisibility();
	BarrierDown->SetCollisionProfileName(TEXT("NoCollision"));
}

void APath::EnableHorizontal()
{
	BarrierLeft->ToggleVisibility();
	BarrierLeft->SetCollisionProfileName(TEXT("NoCollision"));
	BarrierRight->ToggleVisibility();
	BarrierRight->SetCollisionProfileName(TEXT("NoCollision"));
}

void APath::OpenClosedGates(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger Open Gates"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PICKED UP!")));
	OpenClosedGatesTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (First)
	{
		TArray<AActor*> FirstGates;

		if (First->Up == this && First->bIsGateUpOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("F Up z %i"), First->GetActorLocation().Z);
			FirstGates.Add(First->GateUp);
		}
		if (First->Down == this && First->bIsGateDownOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("F Down z %i"), First->GetActorLocation().Z);
			FirstGates.Add(First->GateDown);
		}
		if (First->Left == this && First->bIsGateLeftOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("F Left z %i"), First->GetActorLocation().Z);
			FirstGates.Add(First->GateLeft);
		}
		if (First->Right == this && First->bIsGateRightOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("F Right z %i"), First->GetActorLocation().Z);
			FirstGates.Add(First->GateRight);
		}
		First->OpenGates(FirstGates);
	}
	if (Second)
	{
		TArray<AActor*> SecondGates;
		if (Second->Up == this && Second->bIsGateUpOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("S Up z %i"), Second->GetActorLocation().Z);
			SecondGates.Add(Second->GateUp);
		}
		if (Second->Down == this && Second->bIsGateDownOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("S Down z %i"), Second->GetActorLocation().Z);
			SecondGates.Add(Second->GateDown);
		}
		if (Second->Left == this && Second->bIsGateLeftOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("S Left z %i"), Second->GetActorLocation().Z);
			SecondGates.Add(Second->GateLeft);
		}
		if (Second->Right == this && Second->bIsGateRightOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("S Right z %i"), Second->Right->GetActorLocation().Z);
			SecondGates.Add(Second->GateRight);
		}
		Second->OpenGates(SecondGates);
	}
}

//void APath::OpenClosedGates()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Trigger Open Gates"));
//}