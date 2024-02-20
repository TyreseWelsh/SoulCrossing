// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void AMinionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	//{
	//	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//}
}

void AMinionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMinionPlayerController::PressMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMinionPlayerController::PressLook);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMinionPlayerController::PressJump);							// Start jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMinionPlayerController::PressJump);						// Stop jumping
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMinionPlayerController::PressInteract);						// Regular interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMinionPlayerController::PressInteract);					// Most likely held interact
		
		EnhancedInputComponent->BindAction(UnPossessAction, ETriggerEvent::Triggered, this, &AMinionPlayerController::PressUnPossess);
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Triggered, this, &AMinionPlayerController::PressAbility);
	}
}

FMoveSignature* AMinionPlayerController::GetMoveDelegate()
{
	return &MoveDelegate;
}

FLookSignature* AMinionPlayerController::GetLookDelegate()
{
	return &LookDelegate;
}

FJumpSignature* AMinionPlayerController::GetJumpDelegate()
{
	return &JumpDelegate;
}

FInteractSignature* AMinionPlayerController::GetInteractDelegate()
{
	return &InteractDelegate;
}

FUnPossessSignature* AMinionPlayerController::GetUnPossessDelegate()
{
	return &UnPossessDelegate;
}

FAbilitySignature* AMinionPlayerController::GetAbilityDelegate()
{
	return &AbilityDelegate;
}

void AMinionPlayerController::PressMove(const FInputActionValue& Value)
{
	if (MoveDelegate.IsBound())
	{
		MoveDelegate.Broadcast(Value);
	}
}

void AMinionPlayerController::PressLook(const FInputActionValue& Value)
{
	if (LookDelegate.IsBound())
	{
		LookDelegate.Broadcast(Value);
	}
}

// When this action is called, this function is called and broadcasts a message outwards to anything that has the JumpDelegate bound (which would be the current player state if we can jump in that state)
// Then the function in that state that is bound to the jump delegate is called which is whatever jump function is written in that state which will obviously depend on what state it is.
void AMinionPlayerController::PressJump()
{
	if (JumpDelegate.IsBound())
	{
		JumpDelegate.Broadcast();
	}
}

void AMinionPlayerController::PressInteract(const FInputActionValue& Value)
{
	if (InteractDelegate.IsBound())
	{
		InteractDelegate.Broadcast(Value);
	}
}

void AMinionPlayerController::PressUnPossess()
{
	if (UnPossessDelegate.IsBound())
	{
		UnPossessDelegate.Broadcast();
	}
}

void AMinionPlayerController::PressAbility(const FInputActionValue& Value)
{
	if (AbilityDelegate.IsBound())
	{
		AbilityDelegate.Broadcast(Value);
	}
}
