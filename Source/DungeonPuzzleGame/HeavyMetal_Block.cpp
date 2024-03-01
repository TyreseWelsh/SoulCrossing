// Fill out your copyright notice in the Description page of Project Settings.


#include "HeavyMetal_Block.h"

#include "Strong.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SceneComponent.h"

#include "Minion.h"


// Sets default values
AHeavyMetal_Block::AHeavyMetal_Block()
{
	MainCollider->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	MainCollider->SetMassOverrideInKg(NAME_None, 200.f);
	MainCollider->SetLinearDamping(12.f);

	Mesh->SetRelativeScale3D(FVector(6.f, 6.f, 6.f));
	Mesh->SetLinearDamping(0.0f);

	PushableArea = CreateDefaultSubobject<UBoxComponent>(TEXT("PushArea"));
	PushableArea->SetBoxExtent(FVector(60.f, 10.f, 10.f));
	PushableArea->SetLinearDamping(0.f);
	PushableArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PushableArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PushableArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	PushableArea->SetupAttachment(Mesh);

	PushConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PushConstraint"));
	PushConstraint->ComponentName1.ComponentName = FName(TEXT("PlaceholderMesh"));
	PushConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PushConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PushConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	PushConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PushConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PushConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PushConstraint->SetupAttachment(Mesh);

	InteractionPoint1 = CreateDefaultSubobject<USceneComponent>(TEXT("InteractionPoint1"));
	InteractionPoint1->SetupAttachment(MainCollider);

	InteractionPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("InteractionPoint2"));
	InteractionPoint2->SetupAttachment(MainCollider);

	InteractionPoints.Add(InteractionPoint1);
	InteractionPoints.Add(InteractionPoint2);
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

}

bool AHeavyMetal_Block::IsInteractable_Implementation()
{
	return bCanInteract;
}

void AHeavyMetal_Block::StartPush_Implementation(AMinion* InteractingMinion)
{
	if (InteractionPoints.Num() > 0)
	{
		USceneComponent* ClosestInteractionPoint = InteractionPoints[0];

		for (USceneComponent* CurrentInteractionPoint : InteractionPoints)
		{
			FVector CurrentPointWorldLocation = GetActorLocation() + CurrentInteractionPoint->GetRelativeLocation();
			FVector ClosestPointWorldLocation = GetActorLocation() + ClosestInteractionPoint->GetRelativeLocation();

			double DistanceToCurrentPoint = FVector::Distance(InteractingMinion->GetActorLocation(), CurrentPointWorldLocation);
			double DistanceToClosestPoint = FVector::Distance(InteractingMinion->GetActorLocation(), ClosestPointWorldLocation);

			if (DistanceToCurrentPoint < DistanceToClosestPoint)
			{
				ClosestInteractionPoint = CurrentInteractionPoint;
			}
		}

		FVector NewMinionLocation = FVector(GetActorLocation().X + ClosestInteractionPoint->GetRelativeLocation().X, GetActorLocation().Y, InteractingMinion->GetActorLocation().Z);
		FRotator NewMinionRotation = GetActorRotation().Add(0, ClosestInteractionPoint->GetRelativeRotation().Yaw, 0);
		
		InteractingMinion->SetActorLocation(NewMinionLocation, false, (FHitResult*)nullptr, ETeleportType::TeleportPhysics);
		InteractingMinion->SetActorRotation(NewMinionRotation, ETeleportType::TeleportPhysics);
	}


	MainCollider->SetSimulatePhysics(true);
}

void AHeavyMetal_Block::StopPush_Implementation()
{
	MainCollider->SetSimulatePhysics(false);
}

bool AHeavyMetal_Block::GetPushable_Implementation()
{
	return bPushable;
}
