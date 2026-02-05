// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadiantAI/Core/RadiantTypes.h"
#include "UObject/Class.h"
#include "RadiantConditionSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALRADIANTAI_API URadiantConditionSet : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTimeWindow> TimeWindows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<AActor> LocationReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LocationFallback;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
	float LocationRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCheckTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCheckLocation;

public:
	bool Evaluate(float WorldTimeHours, FVector NPCLocation, UWorld* World) const;

	bool IsTimeValid(float WorldTimeHours) const;

	bool IsLocationValid(FVector NPCLocation, UWorld* World) const;

	FVector GetResolvedLocation(UWorld* World) const;
	
};
