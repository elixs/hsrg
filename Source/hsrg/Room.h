// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "Room.generated.h"

struct FNavigationRelevantData;

UENUM()
enum class ERoomType : uint8
{
	Start,
	Default,
	Chest,
	Boss
};

UCLASS()
class HSRG_API ARoom : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

public:
	class APath *Up, *Down, *Left, *Right;

	UPROPERTY(VisibleAnywhere)
	ERoomType Type = ERoomType::Default;

	void Initialize(ERoomType IntType);

	// Archs

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Archs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArchUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArchDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArchLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArchRight;

	// Barriers

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Barriers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierLeftUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierLeftDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierRightUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BarrierRightDown;

	// Gates

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	//class USceneComponent* Gates;

	UPROPERTY(EditAnywhere, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* GateMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class AStaticMeshActor* GateUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class AStaticMeshActor* GateDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class AStaticMeshActor* GateLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class AStaticMeshActor* GateRight;

	//Triggers

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GateUpTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GateDownTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GateLeftTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GateRightTrigger;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UPROPERTY(EditAnywhere)
	//class ULevelSequence* GateSequencer;


	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	//class UActorSequenceComponent* GateSequenceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence", meta = (AllowedClasses = "LevelSequence"))
	FSoftObjectPath GateOpenSequencePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence", meta = (AllowedClasses = "LevelSequence"))
	FSoftObjectPath GateCloseSequencePath;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence", meta = (AllowedClasses = "LevelSequence"))
	//class ALevelSequenceActor* GateSequenceActor;

	//class ULevelSequence* GateSequence;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence", meta = (AllowedClasses = "Static"))
	//FSoftObjectPath GateSequenceActor;

	// Enemies
	UPROPERTY(EditAnywhere)
	uint16 SpawnInnerRadius = 300;

	UPROPERTY(EditAnywhere)
	uint16 SpawnOuterRadius = 650;

	UPROPERTY(VisibleAnywhere)
	uint8 EnemyCount;

	void LoadEnemies(uint8 EnemyAmount);

	UFUNCTION()
	void EnemyDeath();

	void OpenGates(TArray<AActor*> Gates, bool bReverse = false);

	UFUNCTION()
	void CloseUp(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	UFUNCTION()
	void CloseDown(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	UFUNCTION()
	void CloseLeft(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	UFUNCTION()
	void CloseRight(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	bool bIsGateUpOn = true;
	bool bIsGateDownOn = true;
	bool bIsGateLeftOn = true;
	bool bIsGateRightOn = true;

	void OpenAllAvailableGates();

private:
	void DisableTriggers();


//public:
	// BEGIN INavRelevantInterface
	//virtual void GetNavigationData(FNavigationRelevantData& Data) const override;
	//virtual FBox GetNavigationBounds() const override;
	//virtual bool IsNavigationRelevant() const override;
	// END INavRelevantInterface

};
