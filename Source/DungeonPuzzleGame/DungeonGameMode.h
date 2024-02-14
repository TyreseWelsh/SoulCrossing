// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OverlordController.h"
#include "DungeonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPUZZLEGAME_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	UClass* PlayerPawnClass = AOverlordController::StaticClass();
};
