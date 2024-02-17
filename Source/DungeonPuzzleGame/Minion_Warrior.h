// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minion.h"
#include "Strong.h"
#include "Minion_Warrior.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API AMinion_Warrior : public AMinion, public IStrong
{
	GENERATED_BODY()
	

public:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsPushing = false;
};
