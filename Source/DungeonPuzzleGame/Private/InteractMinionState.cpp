// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractMinionState.h"
#include "../Minion.h"
#include "GameplayStateManagerComponent.h"

#include "../Interactable.h"

void UInteractMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (PlayerReference)
	{
		// NOTE: MIGHT WANT TO WHACK THIS TRACE IN A FUNCTION AT SOME POINT
		FHitResult Hit;
		float TraceLength = PlayerReference->InteractionDistance;

		FVector TraceStartPos(PlayerReference->GetActorLocation());
		float TraceEndPosX(TraceStartPos.X + (PlayerReference->GetActorForwardVector().X * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().Y)));
		float TraceEndPosY(TraceStartPos.Y + (PlayerReference->GetActorForwardVector().Y * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().X)));
		FVector TraceEndPos(TraceEndPosX, TraceEndPosY, PlayerReference->GetActorLocation().Z);

		PlayerReference->GetWorld()->LineTraceSingleByChannel(Hit, TraceStartPos, TraceEndPos, ECollisionChannel::ECC_Visibility);
		InteractedObject = Hit.GetActor();

		PlayerReference->bInteracting = true;
	}
}

void UInteractMinionState::OnTickState()
{
	Super::OnTickState();
	PlayerReference->StateManagerComponent->SwitchStateByKey("Idle");
}

void UInteractMinionState::OnExitState()
{
	Super::OnExitState();

	PlayerReference->bInteracting = false;
	InteractedObject = nullptr;
}

void UInteractMinionState::PressMove(const FInputActionValue& Value)
{
}

void UInteractMinionState::Look(const FInputActionValue& Value)
{
}

void UInteractMinionState::PressJump()
{
}

void UInteractMinionState::PressUnPossess()
{
}

void UInteractMinionState::PressInteract(const FInputActionValue& Value)
{
}

void UInteractMinionState::PressAbility()
{
}
