// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractMinionState.h"
#include "../Minion.h"

void UInteractMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (PlayerReference)
	{
		// NOTE: MIGHT WANT TO WHACK THIS IN A FUNCTION AT SOME POINT
		FHitResult Hit;
		float TraceLength = PlayerReference->InteractionDistance;

		FVector TraceStartPos(PlayerReference->GetActorLocation());
		float TraceEndPosX(TraceStartPos.X + (PlayerReference->GetActorForwardVector().X * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().Y)));
		float TraceEndPosY(TraceStartPos.Y + (PlayerReference->GetActorForwardVector().Y * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().X)));
		FVector TraceEndPos(TraceEndPosX, TraceEndPosY, PlayerReference->GetActorLocation().Z);

		PlayerReference->GetWorld()->LineTraceSingleByChannel(Hit, TraceStartPos, TraceEndPos, ECollisionChannel::ECC_Visibility);
		InteractedObject = Hit.GetActor();

		// TODO: LOOK THROUGH PUSHING MINION STATE AND DO SIMILAR HERE
	}
}

void UInteractMinionState::OnTickState()
{
	Super::OnTickState();
}

void UInteractMinionState::OnExitState()
{
	Super::OnExitState();
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
