// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "HeavyMetal_Block.generated.h"

class AMinion;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class DUNGEONPUZZLEGAME_API AHeavyMetal_Block : public AActor, public IInteractable
{
	GENERATED_BODY()


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

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BlockCollider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlaceholderMesh;

};
