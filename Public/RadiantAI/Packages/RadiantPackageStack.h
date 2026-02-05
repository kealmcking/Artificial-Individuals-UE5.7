// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RadiantPackage.h"
#include "RadiantPackageStack.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALRADIANTAI_API URadiantPackageStack : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stack")
	TArray<TObjectPtr<URadiantPackage>> Packages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stack")
	FName StackName;


public:
	const TArray<TObjectPtr<URadiantPackage>>& GetPackages() const;

	int32 Num() const;

	URadiantPackage* GetPackageAt(int32 Index) const;

	bool IsEmpty() const;
	
};
