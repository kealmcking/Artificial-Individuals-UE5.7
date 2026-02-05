// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Packages/RadiantAIConfig.h"

URadiantPackageStack* URadiantAIConfig::GetMainStack() const
{
	return MainStack;
}

URadiantPackageStack* URadiantAIConfig::GetDefaultList() const
{
	return DefaultList;
}

URadiantPackageStack* URadiantAIConfig::GetCombatOverrideList() const
{
	return CombatOverrideList;
}

URadiantPackageStack* URadiantAIConfig::GetSpectatorOverrideList() const
{
	return SpectatorOverrideList;
}

URadiantPackageStack* URadiantAIConfig::GetObserveDeadBodyOverrideList() const
{
	return ObserveDeadBodyOverrideList;
}

URadiantPackageStack* URadiantAIConfig::GetOverrideListForState(ERadiantOverrideState State) const
{
	switch (State)
	{
		case ERadiantOverrideState::Combat:				return GetCombatOverrideList();
		case ERadiantOverrideState::Spectator:			return GetSpectatorOverrideList();
		case ERadiantOverrideState::ObserveDeadBody:	return GetObserveDeadBodyOverrideList();
		default:										return nullptr;
	}
}
