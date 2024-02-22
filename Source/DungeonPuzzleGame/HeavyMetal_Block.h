// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "../DungeonPuzzleGame/Public/Heavy.h"
#include "../DungeonPuzzleGame/Public/Pushable.h"
#include "HeavyMetal_Block.generated.h"

class AMinion;
class UBoxComponent;
class UStaticMeshComponent;
class UPhysicsConstraintComponent;

UCLASS()
class DUNGEONPUZZLEGAME_API AHeavyMetal_Block : public AActor, public IInteractable, public IHeavy, public IPushable
{
	GENERATED_BODY()

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Sets default values for this actor's properties
	AHeavyMetal_Block();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AMinion* InteractingSkeleton);
	void StartPush_Implementation();
	void StopPush_Implementation();
	bool GetPushable_Implementation();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BlockCollider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlaceholderMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* PushableArea;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* PushConstraint;

	bool bPushable = false;
};
