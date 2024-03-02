// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableObject.h"

// Sets default values
AActivatableObject::AActivatableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	return CanActivate;
}

void AActivatableObject::Activate_Implementation()
{
	// Activation Code: Implementation will change depending on the derived classes implementation
	UE_LOG(LogTemp, Warning, TEXT("Base Activatable Object - Activate Implementation"));
}
