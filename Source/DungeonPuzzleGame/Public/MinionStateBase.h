// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "MinionStateBase.generated.h"

class AMinion;
class IMinionPlayerControllerInterface;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API UMinionStateBase : public UStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	AMinion* PlayerReference = nullptr;
	IMinionPlayerControllerInterface* PlayerController = nullptr;
	AActor* InteractedObject = nullptr;

	virtual void OnEnterState(AActor* OwnerRef) override;
	virtual void OnTickState() override;
	virtual void OnExitState() override;

	virtual void PressMove(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void PressJump();
	virtual void PressUnPossess();
	virtual void PressInteract(const FInputActionValue& Value);
	virtual void PressAbility();
};
