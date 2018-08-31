// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "Path.generated.h"

UCLASS()
class HSRG_API APath : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APath();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	class ARoom *First, *Second;

	// Barriers

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Barriers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* OpenClosedGatesTrigger;

	void EnableUp();
	void EnableDown();
	void EnableLeft();
	void EnableRight();
	void EnableVertical();
	void EnableHorizontal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Navigation, meta = (AllowPrivateAccess = "true"))
	class UNavModifierComponent* NavModifier;

	UFUNCTION()
	void OpenClosedGates(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	//UFUNCTION()
	//void OpenClosedGates();

};
