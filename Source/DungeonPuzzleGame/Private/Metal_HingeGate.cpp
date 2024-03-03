// Fill out your copyright notice in the Description page of Project Settings.


#include "Metal_HingeGate.h"

void AMetal_HingeGate::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat ActivationProgress;
	ActivationProgress.BindUFunction(this, FName("ActivationUpdate"));

	FOnTimelineEvent ActivationFinishedEvent;
	ActivationFinishedEvent.BindUFunction(this, FName("ActivationFinished"));

	ActivationTimeline.AddInterpFloat(ActivationCurve, ActivationProgress);
	ActivationTimeline.SetTimelineFinishedFunc(ActivationFinishedEvent);

	GateStartPosition = GetActorLocation();
}

void AMetal_HingeGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActivationTimeline.TickTimeline(DeltaTime);
}

void AMetal_HingeGate::Activate_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Metal Gate Activated..."));

	bCanActivate = false;

	if (!bAlreadyActivated)
	{
		UE_LOG(LogTemp, Warning, TEXT("Play Gate Animation..."));
		ActivationTimeline.Play();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reverse Gate Animation..."));
		ActivationTimeline.Reverse();
	}
}

void AMetal_HingeGate::ActivationUpdate(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("Update Gate Position..."));

	float NewGateLocationZ = FMath::Lerp(GateStartPosition.Z, GateStartPosition.Z + GateZOffset, Alpha);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, NewGateLocationZ));
}

void AMetal_HingeGate::ActivationFinished()
{
	bAlreadyActivated = !bAlreadyActivated;
	bCanActivate = true;
	UE_LOG(LogTemp, Warning, TEXT("Activation finished: activated is now %b"), bAlreadyActivated);
}
