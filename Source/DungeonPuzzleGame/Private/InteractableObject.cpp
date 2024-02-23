// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "../Minion.h"

#include "Activatable.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObject::Interact_Implementation(AMinion* InteractingSkeleton)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base Interact Implementation"));
	for (AActor* obj : ActivatableObjects)
	{
		UE_LOG(LogTemp, Warning, TEXT("Looping through activatable objects if they exist"));

		if (IActivatable* ActivatableInterface = Cast<IActivatable>(obj))
		{
			if (ActivatableInterface->Execute_CanActivate(obj))
			{
				ActivatableInterface->Execute_Activate(obj);
			}
		}
	}
}

bool AInteractableObject::IsInteractable_Implementation()
{
	return bCanInteract;
}
