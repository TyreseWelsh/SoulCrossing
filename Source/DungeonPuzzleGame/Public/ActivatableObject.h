// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "ActivatableObject.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class DUNGEONPUZZLEGAME_API AActivatableObject : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivatableObject();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* MainCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MainMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bAlreadyActivated = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual bool CanActivate_Implementation();
	virtual void Activate_Implementation();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bCanActivate = true;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//bool bActivated = false;
};