// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinionStateBase.h"
#include "FloatMinionState.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API UFloatMinionState : public UMinionStateBase
{
	GENERATED_BODY()
	
	virtual void OnEnterState(AActor* OwnerRef) override;
	virtual void OnTickState() override;
	virtual void OnExitState() override;

	virtual void PressMove(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;
	virtual void PressJump() override;
	virtual void PressUnPossess() override;
	virtual void PressInteract(const FInputActionValue& Value);
	virtual void PressAbility() override;

	float OldGravityScale = 0;
};
