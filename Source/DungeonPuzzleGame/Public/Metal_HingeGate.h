// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableObject.h"
#include "Metal_HingeGate.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API AMetal_HingeGate : public AActivatableObject
{
	GENERATED_BODY()
	
public:
	virtual void Activate_Implementation() override;

//private:
//	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
//	bool CanActivate = true;
};
