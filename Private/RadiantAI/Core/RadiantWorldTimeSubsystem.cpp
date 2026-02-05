// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Core/RadiantWorldTimeSubsystem.h"

TStatId URadiantWorldTimeSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(URadiantWorldTimeSubsystem, STATGROUP_Tickables);
}

bool URadiantWorldTimeSubsystem::IsTickable() const
{
	return true;
}

void URadiantWorldTimeSubsystem::Tick(float DeltaTime)
{
	CurrentTimeHours += DeltaTime / TimeScale;
	CurrentTimeHours = FMath::Fmod(CurrentTimeHours, 24.0f);

	if (CurrentTimeHours < 0.0f) {
		CurrentTimeHours += 24.0f;
	}
	
	int32 Hours = FMath::FloorToInt(CurrentTimeHours);
	int32 Minutes = FMath::FloorToInt((CurrentTimeHours - Hours) * 60.0f);

	int32 TempDayIndex = DayIndex;
	if (Hours == 0 && Minutes == 0 && TempDayIndex == DayIndex) {
		TempDayIndex = DayIndex + 1;
	}

	DayIndex = TempDayIndex;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			0.f,
			FColor::Green,
			FString::Printf(TEXT("Current Day: %d \nCurrent Time: %02d:%02d"), DayIndex, Hours, Minutes)
		);
	}
}

float URadiantWorldTimeSubsystem::GetCurrentTimeHours() const
{
	return CurrentTimeHours;
}

int URadiantWorldTimeSubsystem::GetDayIndex() const
{
	return DayIndex;
}

void URadiantWorldTimeSubsystem::SetTimeScale(float RealSecondsPerGameHour) {
	TimeScale = RealSecondsPerGameHour;
}

void URadiantWorldTimeSubsystem::SetTime(float Hours) {
	CurrentTimeHours = Hours;
}
