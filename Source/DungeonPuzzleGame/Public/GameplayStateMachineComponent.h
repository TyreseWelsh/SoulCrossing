// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "Delegates/Delegate.h"
#include "GameplayTagsClasses.h"
#include "GameplayStateMachineComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChangedSignature, const FGameplayTag&, NewStateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitStateSignature, const FGameplayTag&, StateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickStateSignature, float&, DeltaTime, const FGameplayTag&,StateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndStateSignature, const FGameplayTag&, StateTag);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class DUNGEONPUZZLEGAME_API UGameplayStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayStateMachineComponent();


	UPROPERTY(BlueprintAssignable)
	FInitStateSignature InitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FEndStateSignature EndStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FTickStateSignature TickStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FStateChangedSignature StateChangedDelegate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CurrentStateTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InitialStateTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayTag> StateHistory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxStateHistoryLength = 6;

	UFUNCTION(BlueprintCallable)
	bool SwitchState(FGameplayTag NewStateTag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bStateCanTick = false;

	void InitState();
	void TickState(float DeltaTime);
	void EndState();
};
