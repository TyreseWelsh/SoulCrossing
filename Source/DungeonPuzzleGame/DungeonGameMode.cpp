// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameMode.h"

void ADungeonGameMode::InitGameState()
{
	Super::InitGameState();

	// Setting default pawn class which will be the players pawn class
	DefaultPawnClass = PlayerPawnClass;
}