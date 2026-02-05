// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RadiantAI/Core/RadiantTypes.h"
#include "RadiantPackage.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FRadiantPackageParams {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radiant Package Params")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radiant Package Params")
	TSoftObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radiant Package Params", meta = (ClampMin = "0.0"))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radiant Package Params")
	TSoftObjectPtr<AActor> PatrolPath;

};

UCLASS(BlueprintType)
class UNREALRADIANTAI_API URadiantPackage : public UDataAsset
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Radiant Package")
	TEnumAsByte<ERadiantPackageType> PackageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package")
	TArray<FTimeWindow> Schedule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package")
	TSoftObjectPtr<AActor> LocationReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package")
	FVector LocationFallback;

	// LocationRadius <= 0 means "don't check location" (valid anywhere)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package", meta = (ClampMin = "0.0"))
	float LocationRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package")
	FRadiantPackageParams Params;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package")
	bool bMustComplete;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radiant Package")
	bool bOncePerDay;

public:
	ERadiantPackageType GetPackageType() const { return static_cast<ERadiantPackageType>(PackageType); }

	const TArray<FTimeWindow>& GetSchedule() const { return Schedule; }

	bool IsTimeValid(float TimeHours) const { 
		if (Schedule.Num() == 0) {
			return true;
		}

		for (FTimeWindow Window : Schedule) {
			if (Window.Contains(TimeHours)) {
				return true;
			}
		}
		return false;
	}

	FVector GetLocationTarget(UWorld* World) const { 
		AActor* Actor = LocationReference.Get();
		if (Actor)
			return Actor->GetActorLocation();
		else
			return LocationFallback;
		
	};

	float GetLocationRadius() const { return LocationRadius; }

	const FRadiantPackageParams& GetParams() const { return Params; }
	
};
