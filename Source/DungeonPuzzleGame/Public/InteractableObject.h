// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interactable.h"
#include "Lightweight.h"
#include "InteractableObject.generated.h"

class AMinion;
class UBoxComponent;
class UStaticMeshComponent;
class UActorComponent;
class USceneComponent;

UCLASS()
class DUNGEONPUZZLEGAME_API AInteractableObject : public AActor, public IInteractable, public ILightweight
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> ActivatableObjects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* MainCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	TArray<USceneComponent*> InteractionPoints;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AMinion* InteractingMinion);
	virtual bool IsInteractable_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanInteract = true;
};
