// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minion.h"
#include "Strong.h"
#include "../DungeonPuzzleGame/Public/Heavy.h"
#include "Minion_Warrior.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API AMinion_Warrior : public AMinion, public IStrong, public IHeavy
{
	GENERATED_BODY()
	
};
