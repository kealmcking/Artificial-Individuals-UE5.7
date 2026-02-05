// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadiantPackageStack.h"
#include "Engine/DataAsset.h"
#include "RadiantAIConfig.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRADIANTAI_API URadiantAIConfig : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stacks")
	TObjectPtr<URadiantPackageStack> MainStack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stacks")
	TObjectPtr<URadiantPackageStack> DefaultList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists")
	TObjectPtr<URadiantPackageStack> CombatOverrideList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists")
	TObjectPtr<URadiantPackageStack> SpectatorOverrideList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists")
	TObjectPtr<URadiantPackageStack> ObserveDeadBodyOverrideList;

public:
	URadiantPackageStack* GetMainStack() const;
	URadiantPackageStack* GetDefaultList() const;
	URadiantPackageStack* GetCombatOverrideList() const;
	URadiantPackageStack* GetSpectatorOverrideList() const;
	URadiantPackageStack* GetObserveDeadBodyOverrideList() const;
	URadiantPackageStack* GetOverrideListForState(ERadiantOverrideState State) const;
	
};
