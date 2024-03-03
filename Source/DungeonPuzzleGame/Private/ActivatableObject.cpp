// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AActivatableObject::AActivatableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MainCollider"));
	MainCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	MainCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = MainCollider;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MainMesh->SetupAttachment(MainCollider);
}

// Called when the game starts or when spawned
void AActivatableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActivatableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AActivatableObject::CanActivate_Implementation()
{
	return bCanActivate;
}

void AActivatableObject::Activate_Implementation()
{
	// Activation Code: Implementation will change depending on the derived classes implementation
	UE_LOG(LogTemp, Warning, TEXT("Base Activatable Object - Activate Implementation"));
}
