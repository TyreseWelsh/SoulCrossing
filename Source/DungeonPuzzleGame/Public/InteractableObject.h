// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interactable.h"
#include "InteractableObject.generated.h"

class AMinion;

UCLASS()
class DUNGEONPUZZLEGAME_API AInteractableObject : public AActor, public IInteractable
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AMinion* InteractingSkeleton);
	virtual bool IsInteractable_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanInteract = true;
};
