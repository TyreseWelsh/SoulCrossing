// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "../Minion.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Activatable.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting up main object collider
	MainCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MainCollider"));
	MainCollider->SetBoxExtent(FVector(75.f, 75.f, 75.f));
	MainCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	MainCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = MainCollider;

	// Setting up object mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetupAttachment(MainCollider);


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
