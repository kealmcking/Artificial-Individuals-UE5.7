// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RadiantAI/Packages/RadiantAIConfig.h"
#include "RadiantAI/Packages/RadiantPackage.h"
#include "RadiantAI/Packages/RadiantPackageStack.h"
#include "RadiantAIComponent.generated.h"


UCLASS(BlueprintType, ClassGroup = ("RadiantAI"), meta = (BlueprintSpawnableComponent))
class UNREALRADIANTAI_API URadiantAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadiantAIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TObjectPtr<URadiantAIConfig> AIConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stacks", meta = (EditCondition = "AIConfig == nullptr"))
	TObjectPtr<URadiantPackageStack> MainStack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stacks", meta = (EditCondition = "AIConfig == nullptr"))
	TObjectPtr<URadiantPackageStack> DefaultList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists", meta = (EditCondition = "AIConfig == nullptr"))
	TObjectPtr<URadiantPackageStack> CombatOverrideList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists", meta = (EditCondition = "AIConfig == nullptr"))
	TObjectPtr<URadiantPackageStack> SpectatorOverrideList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists", meta = (EditCondition = "AIConfig == nullptr"))
	TObjectPtr<URadiantPackageStack> ObserveDeadBodyOverrideList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Override Lists", meta = (EditCondition = "AIConfig == nullptr"))
	TObjectPtr<URadiantPackage> CurrentPackage;
	
	UPROPERTY(BlueprintReadOnly, Category = "Runtime")
	TEnumAsByte<ERadiantOverrideState> CurrentOverrideState;

public:
	URadiantPackageStack* GetMainStack() const;
	URadiantPackageStack* GetDefaultList() const;
	URadiantPackageStack* GetCombatOverrideList() const;
	URadiantPackageStack* GetSpectatorOverrideList() const;
	URadiantPackageStack* GetObserveDeadBodyOverrideList() const;

	URadiantPackageStack* GetOverrideListForState(ERadiantOverrideState State) const;

	void SetCurrentPackage(URadiantPackage* Package);

	URadiantPackage* GetCurrentPackage() const;

	void SetCurrentOverrideState(ERadiantOverrideState State);

	ERadiantOverrideState GetCurrentOverrideState() const;
};
