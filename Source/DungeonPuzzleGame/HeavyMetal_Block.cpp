// Fill out your copyright notice in the Description page of Project Settings.


#include "HeavyMetal_Block.h"

#include "Strong.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Minion.h"

// Sets default values
AHeavyMetal_Block::AHeavyMetal_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockCollider"));
	BlockCollider->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	BlockCollider->SetLinearDamping(4.f);
	BlockCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BlockCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = BlockCollider;

	PlaceholderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderMesh"));
	PlaceholderMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	PlaceholderMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlaceholderMesh->SetupAttachment(BlockCollider);
}

// Called when the game starts or when spawned
void AHeavyMetal_Block::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeavyMetal_Block::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeavyMetal_Block::Interact_Implementation(AMinion* InteractingSkeleton)
{
	if (IStrong* StrongInterface = Cast<IStrong>(InteractingSkeleton))
	{
		UE_LOG(LogTemp, Error, TEXT("INteract with heavy"));
		BlockCollider->SetSimulatePhysics(true);
	}
}