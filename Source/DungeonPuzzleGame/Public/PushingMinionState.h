// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinionStateBase.h"
#include "PushingMinionState.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API UPushingMinionState : public UMinionStateBase
{
	GENERATED_BODY()
	
	virtual void OnEnterState(AActor* OwnerRef) override;
	virtual void OnTickState() override;
	virtual void OnExitState() override;

	virtual void PressMove(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void PressJump();
	virtual void PressUnPossess();
	virtual void PressInteract(const FInputActionValue& Value);
};
