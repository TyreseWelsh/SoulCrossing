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
	virtual void BeginPlay() override;

	//virtual void Possess(APawn* InPawn) override;

	virtual FMoveSignature* GetMoveDelegate() override;
	virtual FLookSignature* GetLookDelegate() override;
	virtual FJumpSignature* GetJumpDelegate() override;
	virtual FInteractSignature* GetInteractDelegate() override;
	virtual FUnPossessSignature* GetUnPossessDelegate() override;
	virtual FAbilitySignature* GetAbilityDelegate() override;

public:
	// INPUT
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UnPossessAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AbilityAction;

	void PressMove(const FInputActionValue& Value);
	void PressLook(const FInputActionValue& Value);
	void PressJump();
	void PressInteract(const FInputActionValue& Value);
	void PressUnPossess();
	void PressAbility();

private:
	FMoveSignature MoveDelegate;
	FLookSignature LookDelegate;
	FJumpSignature JumpDelegate;
	FInteractSignature InteractDelegate;
	FUnPossessSignature UnPossessDelegate;
	FAbilitySignature AbilityDelegate;
};