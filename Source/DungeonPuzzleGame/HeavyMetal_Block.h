// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DungeonPuzzleGame/Public/InteractableObject.h"
#include "../DungeonPuzzleGame/Public/Heavy.h"
#include "../DungeonPuzzleGame/Public/Pushable.h"
#include "HeavyMetal_Block.generated.h"

class AMinion;
class UBoxComponent;
class UStaticMeshComponent;
class UPhysicsConstraintComponent;
class USceneComponent;

UCLASS()
class DUNGEONPUZZLEGAME_API AHeavyMetal_Block : public AInteractableObject, public IHeavy, public IPushable
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

	virtual void Interact_Implementation(AMinion* InteractingSkeleton) override;
	virtual bool IsInteractable_Implementation() override;
	void StartPush_Implementation(AMinion* InteractingMinion);
	void StopPush_Implementation();
	bool GetPushable_Implementation();

private:
	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	//UBoxComponent* BlockCollider;

	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	//UStaticMeshComponent* PlaceholderMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* PushableArea;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UPhysicsConstraintComponent* PushConstraint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractionPoint1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractionPoint2;

	bool bPushable = false;
};
