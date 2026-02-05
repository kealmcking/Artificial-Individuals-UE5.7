// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadiantTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTimeWindow
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EndHour;

	bool Contains(float TimeHours) const {
		if (StartHour > EndHour) {
			return TimeHours >= StartHour || TimeHours < EndHour;
		}
		else if (StartHour <= EndHour) {
			return TimeHours >= StartHour && TimeHours < EndHour;
		}

		return false;
	}

};

UENUM(BlueprintType)
enum ERadiantPackageType
{
	Sleep,
	Eat,
	Sandbox,
	Patrol,
	Travel,
	UseObject
};

UENUM(BlueprintType)
enum ERadiantOverrideState {
	None,
	Combat,
	Spectator,
	ObserveDeadBody
};