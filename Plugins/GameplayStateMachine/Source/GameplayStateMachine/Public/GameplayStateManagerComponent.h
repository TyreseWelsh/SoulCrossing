// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateBase.h"
#include "GameplayStateManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYSTATEMACHINE_API UGameplayStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayStateManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State Machine")
	FString InitialState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State Machine")							// States character can be in
	TMap<FString, TSubclassOf<UStateBase>> AvailableStates;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State Machine")
	bool bDebug = false;

	UPROPERTY(BlueprintReadOnly)																		// Array of previous states with size up to max state length
	TArray<UStateBase*> StateHistory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State Machine Debug")
	int StateHistoryLength;
	int MaxStateHistoryLength = 6;
	UPROPERTY(BlueprintReadOnly)
	UStateBase* CurrentState = nullptr;

	UPROPERTY()
	TMap<FString, UStateBase*> StateMap;


	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchStateByKey(FString NewStateKey);

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchState(UStateBase* NewState);

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void InitStateManager();

private:
	bool bCanTickState = false;
	void InitStates();
};
