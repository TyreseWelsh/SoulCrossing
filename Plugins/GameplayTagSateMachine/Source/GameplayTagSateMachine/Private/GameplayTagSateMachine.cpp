// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagSateMachine.h"

#define LOCTEXT_NAMESPACE "FGameplayTagSateMachineModule"

void FGameplayTagSateMachineModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGameplayTagSateMachineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameplayTagSateMachineModule, GameplayTagSateMachine)