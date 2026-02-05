// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Packages/RadiantPackageStack.h"

URadiantPackage* URadiantPackageStack::GetPackageAt(int32 Index) const
{
	if (Packages.IsValidIndex(Index))
	{
		return Packages[Index];
	}
	return nullptr;
}

bool URadiantPackageStack::IsEmpty() const
{
	return Packages.Num() == 0;
}

const TArray<TObjectPtr<URadiantPackage>>& URadiantPackageStack::GetPackages() const
{
	return Packages;
}

int32 URadiantPackageStack::Num() const
{
	return Packages.Num();
}