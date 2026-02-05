// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RadiantWorldTimeSubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALRADIANTAI_API URadiantWorldTimeSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;

private:
	float CurrentTimeHours = 0.0;
	int DayIndex = 0;
	float TimeScale = 180.f;
	float StartTimeHours = 0.0f;

public:
	UFUNCTION(BlueprintPure, Category = "Time")
	float GetCurrentTimeHours() const;

	UFUNCTION(BlueprintPure, Category = "Time")
	int GetDayIndex() const;

	void SetTimeScale(float RealSecondsPerGameHour);
	void SetTime(float Hours);
};
