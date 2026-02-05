#pragma once

#include "CoreMinimal.h"
#include "RadiantAI/Packages/RadiantPackage.h"
#include "RadiantAI/Packages/RadiantPackageStack.h"
#include "RadiantPackageStackEvaluator.generated.h"

USTRUCT()
struct FRadiantEvaluatorParams
{
	GENERATED_BODY()

public:
	const URadiantPackageStack* MainStack;
	const URadiantPackageStack* DefaultList;
	const URadiantPackageStack* OverrideList;
	const URadiantPackageStack* CombatOverrideList;
	const URadiantPackageStack* SpectatorOverrideList;
	const URadiantPackageStack* ObserveDeadBodyOverrideList;

	ERadiantOverrideState OverrideState;
	float WorldTimeHours;
	FVector NPCLocation;
	UWorld* World;
};

USTRUCT()
struct UNREALRADIANTAI_API FRadiantPackageStackEvaluator
{
	GENERATED_BODY()
public:
	URadiantPackage* Evaluate(const FRadiantEvaluatorParams& Params);
	URadiantPackage* EvaluateStack(
		const URadiantPackageStack* Stack, 
		float WorldTimeHours, 
		FVector NPCLocation, 
		UWorld* World
	) const;

	bool IsPackageValid(
		const URadiantPackage* Package, 
		float WorldTimeHours, 
		FVector NPCLocation, 
		UWorld* World
	) const;

};
