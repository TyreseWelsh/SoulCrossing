// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputActionValue.h"
#include "MinionPlayerControllerInterface.generated.h"

//DECLARE_MULTICAST_DELEGATE(FInactiveSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FMoveSignature, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_OneParam(FLookSignature, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE(FJumpSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FInteractSignature, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE(FUnPossessSignature);
DECLARE_MULTICAST_DELEGATE(FAbilitySignature);


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMinionPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONPUZZLEGAME_API IMinionPlayerControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	// Pure function denoted by = 0, does not have an implementation and is solely used to inherit from
	//virtual FInactiveSignature* GetInactiveDelegate() = 0;
	virtual FMoveSignature* GetMoveDelegate() = 0;
	virtual FLookSignature* GetLookDelegate() = 0;
	virtual FJumpSignature* GetJumpDelegate() = 0;																	
	virtual FInteractSignature* GetInteractDelegate() = 0;
	virtual FUnPossessSignature* GetUnPossessDelegate() = 0;
	virtual FAbilitySignature* GetAbilityDelegate() = 0;
};