// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

void AMinionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMinionPlayerController::PressJump);
	}
}

FJumpSignature* AMinionPlayerController::GetJumpDelegate()
{
	return &JumpDelegate;
}

void AMinionPlayerController::PressJump()
{
	if (JumpDelegate.IsBound())
	{
		JumpDelegate.Broadcast();
	}
}
