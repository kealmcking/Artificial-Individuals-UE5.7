// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Evaluation/RadiantPackageStackEvaluator.h"

URadiantPackage* FRadiantPackageStackEvaluator::Evaluate(const FRadiantEvaluatorParams& Params)
{
	if (Params.OverrideState != ERadiantOverrideState::None) {
		const URadiantPackageStack* OverrideList = Params.OverrideList;
		if (OverrideList != nullptr) {
			URadiantPackage* Result = EvaluateStack(OverrideList, Params.WorldTimeHours, Params.NPCLocation, Params.World);
			if (Result != nullptr)
				return Result;
		}
	}

	if (Params.MainStack != nullptr) {
		URadiantPackage* Result = EvaluateStack(Params.MainStack, Params.WorldTimeHours, Params.NPCLocation, Params.World);
		if (Result != nullptr)
			return Result;
	}

	if (Params.DefaultList != nullptr) {
		URadiantPackage* Result = EvaluateStack(Params.DefaultList, Params.WorldTimeHours, Params.NPCLocation, Params.World);
		if (Result != nullptr)
			return Result;
	}

	return nullptr;
}

URadiantPackage* FRadiantPackageStackEvaluator::EvaluateStack(const URadiantPackageStack* Stack, float WorldTimeHours, FVector NPCLocation, UWorld* World) const
{
	for (URadiantPackage* Package : Stack->GetPackages()) {
		if (IsPackageValid(Package, WorldTimeHours, NPCLocation, World)) {
			return Package;
		}
	}

	return nullptr;
}

bool FRadiantPackageStackEvaluator::IsPackageValid(const URadiantPackage* Package, float WorldTimeHours, FVector NPCLocation, UWorld* World) const
{
	if (Package == nullptr)
		return false;

	if (!Package->IsTimeValid(WorldTimeHours))
		return false;

	// LocationRadius <= 0 means "don't check location" (valid anywhere)
	float LocationRadius = Package->GetLocationRadius();
	if (LocationRadius > 0.f)
	{
		FVector LocationTarget = Package->GetLocationTarget(World);
		if (FVector::Dist(NPCLocation, LocationTarget) > LocationRadius)
			return false;
	}
	
	return true;
}
