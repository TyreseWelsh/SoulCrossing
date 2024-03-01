// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pushable.generated.h"

class AMinion;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPushable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONPUZZLEGAME_API IPushable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartPush(AMinion* InteractingMinion);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopPush();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetPushable();
};