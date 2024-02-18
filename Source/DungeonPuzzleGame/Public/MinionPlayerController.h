// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MinionPlayerControllerInterface.h"
#include "MinionPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API AMinionPlayerController : public APlayerController, public IMinionPlayerControllerInterface
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;

	virtual FJumpSignature* GetJumpDelegate() override;

public:
	// INPUT
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;


	void PressJump();

private:
	FJumpSignature JumpDelegate;
};
