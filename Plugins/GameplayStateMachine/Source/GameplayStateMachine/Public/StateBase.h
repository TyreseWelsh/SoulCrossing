// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEPLAYSTATEMACHINE_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanTickState = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanLoop = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StateDisplayName;


	virtual void OnEnterState(AActor* StateOwner) {};
	virtual void OnTickState() {};
	virtual void OnExitState() {};
};
