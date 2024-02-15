// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Possessable.h"
#include "Minion.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class USphereComponent;

class AMinionSoul;

UCLASS()
class DUNGEONPUZZLEGAME_API AMinion : public ACharacter, public IPossessable
{
	GENERATED_BODY()

	// COMPONENTS
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlayerStaticMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlayerNoseMesh;

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
	UInputAction* UnPossessAction;

	//
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMinionSoul> BP_Soul;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possession, meta = (AllowPrivateAccess = "true"))
	bool bCanInput = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possession, meta = (AllowPrivateAccess = "true"))
	bool Possessing = false;

public:
	// Sets default values for this character's properties
	AMinion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Possessable interface functions
	int GetSoulCost_Implementation();
	void StoreSoulEnergy_Implementation(int EnergyToStore);
	void PossessThis_Implementation();

	//int GetStoredSoulEnergy() const { return StoredSoulEnergy; }
	//void StoreSoulEnergy(int newSoulEnergy) { StoredSoulEnergy = newSoulEnergy; }

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void UnPossess(const FInputActionValue& Value);

	int SoulCost = 1;
	int StoredSoulEnergy = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseMoveSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Possession", meta = (AllowPrivateAccess = "true"))
	bool Possessed = false;
};
