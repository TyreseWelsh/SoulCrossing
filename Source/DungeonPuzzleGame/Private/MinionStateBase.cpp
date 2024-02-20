// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionStateBase.h"
#include "../Minion.h"
#include "../MinionSoul.h"
#include "MinionPlayerController.h"
#include "GameplayStateManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"


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
}

void UMinionStateBase::PressMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("MOVE INPUT"));

	if (PlayerReference->GetController() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HAS CONTROLLER, SHOULD MOVE"));
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
	PlayerReference->Jump();
	PlayerReference->StateManagerComponent->SwitchStateByKey("InAir");
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