// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Minion.h"
#include "Weak.h"
#include "Magic.h"

#include "Minion_Mage.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API AMinion_Mage : public AMinion, public IWeak, public IMagic
{
	GENERATED_BODY()
	
};
