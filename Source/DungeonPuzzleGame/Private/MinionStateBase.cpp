// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionStateBase.h"
#include "../Minion.h"
#include "../MinionSoul.h"
#include "MinionPlayerController.h"
#include "GameplayStateManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../Interactable.h"
#include "Weak.h"
#include "Lightweight.h"
#include "../Strong.h"
#include "Heavy.h"
#include "Pushable.h"
#include "Activatable.h"

void UMinionStateBase::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	// Saving reference to the players character
	if (!PlayerReference)
	{
		PlayerReference = Cast<AMinion>(OwnerRef);
	}

	// Saving reference to the player controller
	if (!PlayerController)
	{
		PlayerController = Cast<IMinionPlayerControllerInterface>(UGameplayStatics::GetPlayerController(this, 0));
	}

	if (PlayerController)
	{
		PlayerController->GetMoveDelegate()->AddUObject(this, &UMinionStateBase::PressMove);
		PlayerController->GetLookDelegate()->AddUObject(this, &UMinionStateBase::Look);
		PlayerController->GetJumpDelegate()->AddUObject(this, &UMinionStateBase::PressJump);
		PlayerController->GetUnPossessDelegate()->AddUObject(this, &UMinionStateBase::PressUnPossess);
		PlayerController->GetInteractDelegate()->AddUObject(this, &UMinionStateBase::PressInteract);

	}
	
}

void UMinionStateBase::OnTickState()
{
	Super::OnTickState();
}

void UMinionStateBase::OnExitState()
{
	Super::OnExitState();

	PlayerController->GetMoveDelegate()->RemoveAll(this);
	PlayerController->GetLookDelegate()->RemoveAll(this);
	PlayerController->GetJumpDelegate()->RemoveAll(this);
	PlayerController->GetUnPossessDelegate()->RemoveAll(this);
	PlayerController->GetInteractDelegate()->RemoveAll(this);
}

void UMinionStateBase::PressMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (PlayerReference->GetController() != nullptr)
	{
		const FRotator Rotation = PlayerReference->GetController()->GetControlRotation();						// Rotation of forward facing pawn
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);					// By default unreal uses X as the forward vector so we are getting that based on the pawns Yaw rotation

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);						// By default unreal uses Y as the right vector direction so we are also getting that

		PlayerReference->AddMovementInput(ForwardDirection, MovementVector.Y);									// Adding input values Y value to get forward/backward movement since that is what the values translate to
		PlayerReference->AddMovementInput(RightDirection, MovementVector.X);									// Adding input values X value to get right/left movement ^
	}
}

void UMinionStateBase::Look(const FInputActionValue& Value)
{
	FVector LookAxisVector = Value.Get<FVector>();																// Getting the input value as a FVector which we store

	if (PlayerReference->GetController() != nullptr)
	{
		PlayerReference->AddControllerYawInput(LookAxisVector.X);												// Add the input values to the pawns Yaw and Pitch
		PlayerReference->AddControllerPitchInput(LookAxisVector.Y);												//
	}
}

void UMinionStateBase::PressJump()
{
	if (PlayerReference->GetClass()->ImplementsInterface(UHeavy::StaticClass()) == false)
	{
		PlayerReference->Jump();
		PlayerReference->StateManagerComponent->SwitchStateByKey("InAir");
	}
}

void UMinionStateBase::PressUnPossess()
{
	PlayerReference->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
	PlayerReference->Possessed = false;

	PlayerReference->StateManagerComponent->SwitchStateByKey("Inactive");

	AMinionSoul* playerSoul = GetWorld()->SpawnActor<AMinionSoul>(PlayerReference->BP_Soul, PlayerReference->GetActorTransform());
	if (playerSoul != nullptr)
	{
		playerSoul->SetSoulEnergy(PlayerReference->StoredSoulEnergy);
		PlayerReference->GetController()->Possess(playerSoul);
	}
}

void UMinionStateBase::PressInteract(const FInputActionValue& Value)
{
	FHitResult Hit;
	float TraceLength = 125.f;

	// Creating line trace when interact button is pressed to check if there is any interactable object in distance of the player
	FVector TraceStartPos(PlayerReference->GetActorLocation());
	float TraceEndPosX(TraceStartPos.X + (PlayerReference->GetActorForwardVector().X * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().Y)));
	float TraceEndPosY(TraceStartPos.Y + (PlayerReference->GetActorForwardVector().Y * (TraceLength * PlayerReference->GetMesh()->GetRelativeScale3D().X)));
	FVector TraceEndPos(TraceEndPosX, TraceEndPosY, PlayerReference->GetActorLocation().Z);

	PlayerReference->GetWorld()->LineTraceSingleByChannel(Hit, TraceStartPos, TraceEndPos, ECollisionChannel::ECC_Visibility);

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("INTERACTING WITH OBJECT!"));
		if(IInteractable* InteractInterface = Cast<IInteractable>(Hit.GetActor()))
		{
			if (InteractInterface->Execute_IsInteractable(Hit.GetActor()))													// Check if the interactable object is currently interactable
			{
				// Interactions for when the player character is "Weak" and the interactable object is "Lightweight"
				if (PlayerReference->GetClass()->ImplementsInterface(UWeak::StaticClass())
					&& Hit.GetActor()->GetClass()->ImplementsInterface(ULightweight::StaticClass()))
				{
					if (Cast<IPushable>(Hit.GetActor())->Execute_GetPushable(Hit.GetActor()))										// If interactable object is pushable
					{
						PlayerReference->StateManagerComponent->SwitchStateByKey("Pushing");
						return;
					}

					PlayerReference->StateManagerComponent->SwitchStateByKey("Interacting");											// If the player is weak, interactable object is lightweight but is not pushable, switch to the normal interaction state
				}
				// Interactions for when the player character is "Strong" and the interactable object is "Heavy"
				else if (PlayerReference->GetClass()->ImplementsInterface(UStrong::StaticClass())
					&& Hit.GetActor()->GetClass()->ImplementsInterface(UHeavy::StaticClass()))
				{
					if (Cast<IPushable>(Hit.GetActor())->Execute_GetPushable(Hit.GetActor()))										// If interactable object is pushable
					{
						PlayerReference->StateManagerComponent->SwitchStateByKey("Pushing");
						return;
					}

					PlayerReference->StateManagerComponent->SwitchStateByKey("Interacting");											// If the player is strong, interactable object is heavy but is not pushable, switch to the normal interaction state
				}
			}
		}
	}
}