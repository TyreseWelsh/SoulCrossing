// Fill out your copyright notice in the Description page of Project Settings.


#include "PushingMinionState.h"
#include "../Minion.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "GameplayStateManagerComponent.h"

#include "Pushable.h"

void UPushingMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (PlayerReference)
	{
		FHitResult Hit;
		float TraceLength = 125.f;

		FVector TraceStartPos(PlayerReference->GetActorLocation());
		float TraceEndPosX(TraceStartPos.X + (PlayerReference->GetActorForwardVector().X * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().Y)));
		float TraceEndPosY(TraceStartPos.Y + (PlayerReference->GetActorForwardVector().Y * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().X)));
		FVector TraceEndPos(TraceEndPosX, TraceEndPosY, PlayerReference->GetActorLocation().Z);

		PlayerReference->GetWorld()->LineTraceSingleByChannel(Hit, TraceStartPos, TraceEndPos, ECollisionChannel::ECC_Visibility);
		InteractedObject = Hit.GetActor();

		PlayerReference->bPushing = true;
		PlayerReference->GetCharacterMovement()->bOrientRotationToMovement = false;
		PlayerReference->SetActorRotation(InteractedObject->GetActorRotation());

		if (IPushable* PushableInterface = Cast<IPushable>(InteractedObject))
		{
			PushableInterface->Execute_StartPush(InteractedObject);
		}
	}
}

void UPushingMinionState::OnTickState()
{
	Super::OnTickState();
}

void UPushingMinionState::OnExitState()
{
	Super::OnExitState();

	PlayerReference->bPushing = false;
	PlayerReference->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (IPushable* PushableInterface = Cast<IPushable>(InteractedObject))
	{
		PushableInterface->Execute_StopPush(InteractedObject);
	}

	InteractedObject = nullptr;
}

void UPushingMinionState::PressMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (PlayerReference->GetController())
	{
		if (MovementVector.X != 0.f || MovementVector.Y < 0.f)
		{
			PlayerReference->StateManagerComponent->SwitchStateByKey("Idle");
		}
		else
		{
			const FRotator Rotation = PlayerReference->GetController()->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			PlayerReference->AddMovementInput(PlayerReference->GetActorForwardVector(), MovementVector.Y);
		}
	}
}

void UPushingMinionState::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void UPushingMinionState::PressJump()
{
	Super::PressJump();
}

void UPushingMinionState::PressUnPossess()
{
}

void UPushingMinionState::PressInteract(const FInputActionValue& Value)
{
}