// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleMinionState.h"
#include "../Minion.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayStateManagerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MinionPlayerController.h"


void UIdleMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (PlayerReference->GetController())
	{
		AMinionPlayerController* MinionController = Cast<AMinionPlayerController>(PlayerReference->GetController());

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MinionController->GetLocalPlayer()))
		{
			if (!Subsystem->HasMappingContext(MinionController->DefaultMappingContext))
			{
				Subsystem->AddMappingContext(MinionController->DefaultMappingContext, 0);

				MinionController->SetupInputComponent();
			}
		}
	}
}

void UIdleMinionState::OnTickState()
{
	Super::OnTickState();

	if (PlayerReference != nullptr)
	{
		if (PlayerReference->GetCharacterMovement()->Velocity.Z != 0)
		{
			PlayerReference->StateManagerComponent->SwitchStateByKey("InAir");
		}
	}
}

void UIdleMinionState::OnExitState()
{
	Super::OnExitState();
}

void UIdleMinionState::PressMove(const FInputActionValue& Value)
{
	Super::PressMove(Value);
}

void UIdleMinionState::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void UIdleMinionState::PressJump()
{
	Super::PressJump();
}

void UIdleMinionState::PressUnPossess()
{
	Super::PressUnPossess();
}
