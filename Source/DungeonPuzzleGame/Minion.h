// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Possessable.h"
#include "Minion.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FEnhancedInputActionEventBinding;
class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class UGameplayStateManagerComponent;
class UAnimMontage;

class AMinionSoul;

UCLASS()
class DUNGEONPUZZLEGAME_API AMinion : public ACharacter, public IPossessable
{
	GENERATED_BODY()

	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Possession, meta = (AllowPrivateAccess = "true"))
	USphereComponent* PossessionRadius;

	// INPUT
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UnPossessAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* PossessionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possession, meta = (AllowPrivateAccess = "true"))
	bool bCanInput = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possession, meta = (AllowPrivateAccess = "true"))
	bool Possessing = false;


	void NewJump();

	UFUNCTION()
	void MontageBeginBlendOut(UAnimMontage* Montage, bool bInterrupted);

public:
	// Sets default values for this character's properties
	AMinion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FEnhancedInputActionEventBinding* JumpActionBinding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AbilityAction;

public:
	//
	UPROPERTY(EditAnywhere, Category = SoulBlueprint, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMinionSoul> BP_Soul;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UCameraComponent* GetCamera() { return PlayerCamera; }

	// Possessable interface functions
	int GetSoulCost_Implementation();
	void StoreSoulEnergy_Implementation(int EnergyToStore);
	void PossessThis_Implementation(FRotator ControllerRotation);

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void UnPossess(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine, meta = (AllowPrivateAccess = "true"))
	UGameplayStateManagerComponent* StateManagerComponent;

	int SoulCost = 1;
	int StoredSoulEnergy = 0;
	float InteractionDistance = 125.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseMoveSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possession, meta = (AllowPrivateAccess = "true"))
	bool Possessed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bInteracting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bPushing = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bHovering = false;
	float HoverTimer = 0.f;
	const float MAX_HOVER_TIME = 2.f;

private:



};
