// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MeleeEnemyCharacter.generated.h"

//DECLARE_MULTICAST_DELEGATE(FDeathDelegate)
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS(config=Game)
class HSRG_API AMeleeEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn Sensing for AI control*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensor;

	UFUNCTION()
	void OnSeePawn(APawn *OtherPawn);

public:
	// Sets default values for this character's properties
	AMeleeEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void BeginDestroy() override;

public:
	/** Returns PawnSensingComponent subobject **/
	FORCEINLINE class UPawnSensingComponent* GetPawnSensing() const { return PawnSensor; }

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool bAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool bIsHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic)
	int HitPoints= 5;

	//UPROPERTY(BlueprintAssignable)
	//FDeathDelegate OnDeathDelegate;
	
};
