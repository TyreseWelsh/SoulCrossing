// Fill out your copyright notice in the Description page of Project Settings.


#include "HeavyMetal_Block.h"

#include "Strong.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "Minion.h"


// Sets default values
AHeavyMetal_Block::AHeavyMetal_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockCollider"));
	BlockCollider->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	BlockCollider->SetMassOverrideInKg(NAME_None, 700.f);
	BlockCollider->SetLinearDamping(4.f);
	BlockCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BlockCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = BlockCollider;

	PlaceholderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderMesh"));
	PlaceholderMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	PlaceholderMesh->SetLinearDamping(0.0f);
	PlaceholderMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlaceholderMesh->SetupAttachment(BlockCollider);

	PushableArea = CreateDefaultSubobject<UBoxComponent>(TEXT("PushArea"));
	PushableArea->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	PushableArea->SetLinearDamping(0.f);
	PushableArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PushableArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PushableArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	PushableArea->SetupAttachment(PlaceholderMesh);

	PushConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PushConstraint"));
	PushConstraint->ComponentName1.ComponentName = FName(TEXT("PlaceholderMesh"));
	PushConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PushConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PushConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	PushConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PushConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PushConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PushConstraint->SetupAttachment(PlaceholderMesh);
}

// Called when the game starts or when spawned
void AHeavyMetal_Block::BeginPlay()
{
	Super::BeginPlay();

	PushableArea->OnComponentBeginOverlap.AddDynamic(this, &AHeavyMetal_Block::BeginOverlap);
	PushableArea->OnComponentEndOverlap.AddDynamic(this, &AHeavyMetal_Block::EndOverlap);
}

// Called every frame
void AHeavyMetal_Block::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeavyMetal_Block::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APawn>(OtherActor)->GetController())							// If actor possesses a controller (active player skeleton)
	{
		bPushable = true;
	}
}

void AHeavyMetal_Block::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APawn>(OtherActor)->GetController())
	{
		bPushable = false;
	}
}

void AHeavyMetal_Block::Interact_Implementation(AMinion* InteractingSkeleton)
{
	//if (IStrong* StrongInterface = Cast<IStrong>(InteractingSkeleton))
	//{
	//	UE_LOG(LogTemp, Error, TEXT("INteract with heavy"));
	//	BlockCollider->SetSimulatePhysics(true);
	//}
}

void AHeavyMetal_Block::StartPush_Implementation()
{
	BlockCollider->SetSimulatePhysics(true);
}

void AHeavyMetal_Block::StopPush_Implementation()
{
	BlockCollider->SetSimulatePhysics(false);
}

bool AHeavyMetal_Block::GetPushable_Implementation()
{
	return bPushable;
}
