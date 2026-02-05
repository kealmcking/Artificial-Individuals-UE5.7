// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Conditions/RadiantConditionSet.h"

bool URadiantConditionSet::Evaluate(float WorldTimeHours, FVector NPCLocation, UWorld* World) const {
	// Return false if any enabled check fails
	if (bCheckTime && !IsTimeValid(WorldTimeHours))
		return false;
	if (bCheckLocation && !IsLocationValid(NPCLocation, World))
		return false;
	return true;
}

bool URadiantConditionSet::IsTimeValid(float WorldTimeHours) const {
	if (TimeWindows.Num() == 0) {
		return true;
	}
	for (const FTimeWindow& Window : TimeWindows) {
		if (Window.Contains(WorldTimeHours)) {
			return true;
		}
	}
	return false;
}

bool URadiantConditionSet::IsLocationValid(FVector NPCLocation, UWorld* World) const {
	FVector TargetLocation = GetResolvedLocation(World);
	float DistanceSquared = FVector::DistSquared(NPCLocation, TargetLocation);
	return (DistanceSquared <= FMath::Square(LocationRadius)) || !bCheckLocation;
}

FVector URadiantConditionSet::GetResolvedLocation(UWorld* World) const
{
	if (LocationReference.IsValid()) {
		AActor* Actor = LocationReference.Get();
		if (Actor) {
			return Actor->GetActorLocation();
		}
	}
	return LocationFallback;
}
