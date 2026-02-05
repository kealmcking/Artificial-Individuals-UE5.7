// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RadiantAI/Components/RadiantAIComponent.h"
#include "RadiantAI/Evaluation/RadiantPackageStackEvaluator.h"
#include "RadiantAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRADIANTAI_API ARadiantAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void PerformEvaluation();
	void WriteToBlackboard(URadiantPackage* Package);
	bool ShouldSkipEvaluationForLOD() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardData> BlackboardAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Evaluation", meta =(ClampMin = "0.1"))
	float EvaluationInterval = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Evaluation", meta = (ClampMin = "0.0"))
	float LODDistanceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LOD")
	bool bEnableLOD = false;

	FTimerHandle EvaluationTimerHandle;
	TObjectPtr<URadiantAIComponent> CachedAIComponent;
	FRadiantPackageStackEvaluator Evaluator;

public:
	UFUNCTION(BlueprintCallable, Category = "Radiant AI")
	void SetOverrideState(ERadiantOverrideState NewState);

	ERadiantOverrideState GetOverrideState() const;

	UFUNCTION(BlueprintCallable, Category = "Radiant AI")
	void ForceEvaluate();

	URadiantPackage* GetCurrentPackage() const;
	
};
