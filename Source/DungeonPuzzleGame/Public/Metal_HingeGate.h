// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableObject.h"
#include "Components/TimelineComponent.h"

#include "Metal_HingeGate.generated.h"

class UCurveFloat;

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API AMetal_HingeGate : public AActivatableObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* ActivationCurve = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Activate_Implementation() override;

private:
	FTimeline ActivationTimeline;

	UFUNCTION()
	void ActivationUpdate(float Alpha);
	UFUNCTION()
	void ActivationFinished();

	FVector GateStartPosition;
	float GateZOffset = 400.f;
};
