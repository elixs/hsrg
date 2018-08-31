// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeEnemyCharacter.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "hsrg/PlayerCharacter.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "MeleeEnemyAIController.h"
#include "Runtime/Core/Public/Math/Vector.h"

// Sets default values
AMeleeEnemyCharacter::AMeleeEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create a pawn sensor
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));
}

// Called when the game starts or when spawned
void AMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMeleeEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMeleeEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//void AMeleeEnemyCharacter::BeginDestroy()
//{
//	Super::BeginDestroy();
//	UE_LOG(LogTemp, Warning, TEXT("Broadcast"));
//	OnDeathDelegate.Broadcast();
//}

void AMeleeEnemyCharacter::OnSeePawn(APawn *OtherPawn)
{
	FString message = TEXT("Saw Actor ") + OtherPawn->GetName();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	PawnSensor->SetPeripheralVisionAngle(180.f);

	// TODO: game-specific logic
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherPawn))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::SanitizeFloat(FVector::Dist(GetTransform().GetLocation(), Player->GetTransform().GetLocation())));

		if (AMeleeEnemyAIController* Controller = Cast<AMeleeEnemyAIController>(GetController()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::FromInt(Player->HitPoints));
			if (Player->HitPoints <= 0)
			{
				bAttack = false;
				Controller->StopMovement();
			}
			else
			{
				float Distance = FVector::Dist(GetTransform().GetLocation(), Player->GetTransform().GetLocation());
				if (bIsHit || HitPoints == 0)
				{
					bAttack = false;
					Controller->StopMovement();
				}
				else
				{
					if (Distance <= 200.f)
					{
						Controller->StopMovement();
						bAttack = true;
					}
					else if (Distance <= 700.f)
					{
						bAttack = false;
						Controller->MoveToActor(Player, 5.f);
					}
					else
					{
						Controller->StopMovement();
						PawnSensor->SetPeripheralVisionAngle(90.f);
					}
				}
			}
		}
	}
}

void AMeleeEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensor->OnSeePawn.AddDynamic(this, &AMeleeEnemyCharacter::OnSeePawn);
}