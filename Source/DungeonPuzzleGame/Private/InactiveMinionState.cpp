// Fill out your copyright notice in the Description page of Project Settings.


#include "InactiveMinionState.h"
#include "../Minion.h"
#include "EnhancedInputSubsystems.h"
#include "MinionPlayerController.h"

// CANNOT DO ANY ACTIONS IN THE INACTIVE STATE, PURELY FOR THE VISUAL AND SEPARATION

void UInactiveMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (PlayerReference->GetController())
	{
		if (AMinionPlayerController* MinionController = Cast<AMinionPlayerController>(PlayerReference->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MinionController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(MinionController->DefaultMappingContext);
			}
		}
	}
}

void UInactiveMinionState::OnTickState()
{
}

void UInactiveMinionState::OnExitState()
{
}

void UInactiveMinionState::PressMove(const FInputActionValue& Value)
{
}

void UInactiveMinionState::Look(const FInputActionValue& Value)
{
}

void UInactiveMinionState::PressJump()
{
}

void UInactiveMinionState::PressUnPossess()
{
}
