// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatMinionState.h"
#include "../Minion.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayStateManagerComponent.h"

#include "Magic.h"

void UFloatMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (PlayerReference)
	{
		OldGravityScale = PlayerReference->GetCharacterMovement()->GravityScale;
		PlayerReference->GetCharacterMovement()->GravityScale = 0;

		PlayerReference->GetCharacterMovement()->Velocity.Z = 0;
		PlayerReference->bHovering = true;
	}
}

void UFloatMinionState::OnTickState()
{
	Super::OnTickState();

	if (PlayerReference)
	{
		PlayerReference->HoverTimer += GetWorld()->DeltaTimeSeconds;
		UE_LOG(LogTemp, Warning, TEXT("Hovertimer = %f"), PlayerReference->HoverTimer);
		if (PlayerReference->HoverTimer >= PlayerReference->MAX_HOVER_TIME)
		{
			PlayerReference->StateManagerComponent->SwitchStateByKey("InAir");
		}
	}
}

void UFloatMinionState::OnExitState()
{
	Super::OnExitState();

	PlayerReference->GetCharacterMovement()->GravityScale = OldGravityScale;
	PlayerReference->bHovering = false;
}

void UFloatMinionState::PressMove(const FInputActionValue& Value)
{
	Super::PressMove(Value);
}

void UFloatMinionState::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void UFloatMinionState::PressJump()
{
}

void UFloatMinionState::PressUnPossess()
{
}

void UFloatMinionState::PressInteract(const FInputActionValue& Value)
{
}

void UFloatMinionState::PressAbility()
{
	if (PlayerReference != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SHOULD STOP HOVER"));
		if (PlayerReference->GetClass()->ImplementsInterface(UMagic::StaticClass()))
		{
			PlayerReference->StateManagerComponent->SwitchStateByKey("InAir");
		}
	}
}
