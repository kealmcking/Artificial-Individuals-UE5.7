// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Components/RadiantAIComponent.h"

// Sets default values for this component's properties
URadiantAIComponent::URadiantAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void URadiantAIComponent::BeginPlay()
{
	Super::BeginPlay();
}

URadiantPackageStack* URadiantAIComponent::GetMainStack() const {
	if (AIConfig) {
		return AIConfig->GetMainStack();
	}
	else {
		return MainStack;
	}
}

URadiantPackageStack* URadiantAIComponent::GetDefaultList() const {
	if (AIConfig) {
		return AIConfig->GetDefaultList();
	}
	else {
		return DefaultList;
	}
}

URadiantPackageStack* URadiantAIComponent::GetCombatOverrideList() const {
	if (AIConfig) {
		return AIConfig->GetCombatOverrideList();
	}
	else {
		return CombatOverrideList;
	}
}

URadiantPackageStack* URadiantAIComponent::GetSpectatorOverrideList() const {
	if (AIConfig) {
		return AIConfig->GetSpectatorOverrideList();
	}
	else {
		return SpectatorOverrideList;
	}
}

URadiantPackageStack* URadiantAIComponent::GetObserveDeadBodyOverrideList() const {
	if (AIConfig) {
		return AIConfig->GetObserveDeadBodyOverrideList();
	}
	else {
		return ObserveDeadBodyOverrideList;
	}
}

URadiantPackageStack* URadiantAIComponent::GetOverrideListForState(ERadiantOverrideState State) const {
	switch (State) {
		case ERadiantOverrideState::Combat:
			return GetCombatOverrideList();
		case ERadiantOverrideState::Spectator:
			return GetSpectatorOverrideList();
		case ERadiantOverrideState::ObserveDeadBody:
			return GetObserveDeadBodyOverrideList();
		default:
			return nullptr;
	}
}

URadiantPackage* URadiantAIComponent::GetCurrentPackage() const {
	return CurrentPackage;
}

void URadiantAIComponent::SetCurrentPackage(URadiantPackage* Package) {
	CurrentPackage = Package;
}

void URadiantAIComponent::SetCurrentOverrideState(ERadiantOverrideState State) {
	CurrentOverrideState = State;
}

ERadiantOverrideState URadiantAIComponent::GetCurrentOverrideState() const {
	return CurrentOverrideState;
}





