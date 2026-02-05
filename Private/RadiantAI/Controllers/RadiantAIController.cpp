// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiantAI/Controllers/RadiantAIController.h"
#include "RadiantAI/Core/RadiantWorldTimeSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

void ARadiantAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr)
		return;

	CachedAIComponent = InPawn->FindComponentByClass<URadiantAIComponent>();

	if (CachedAIComponent == nullptr)
		return;

	UBlackboardComponent* BBComp = GetBlackboardComponent();
	if (BlackboardAsset != nullptr)
		UseBlackboard(BlackboardAsset, BBComp);

	if (BehaviorTreeAsset != nullptr)
		RunBehaviorTree(BehaviorTreeAsset);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ARadiantAIController::PerformEvaluation);
	GetWorldTimerManager().SetTimer(
		EvaluationTimerHandle,
		TimerDelegate,
		EvaluationInterval,
		true
	);

	PerformEvaluation();
}

void ARadiantAIController::OnUnPossess()
{
	GetWorldTimerManager().ClearTimer(EvaluationTimerHandle);

	CachedAIComponent = nullptr;

	Super::OnUnPossess();

}

void ARadiantAIController::PerformEvaluation()
{
	if (CachedAIComponent == nullptr)
		return;

	if (bEnableLOD && ShouldSkipEvaluationForLOD())
		return;

	URadiantWorldTimeSubsystem* TimeSubsystem = GetWorld()->GetSubsystem<URadiantWorldTimeSubsystem>();
	if (TimeSubsystem == nullptr)
		return;
	float WorldTimeHours = TimeSubsystem->GetCurrentTimeHours();

	APawn* MyPawn = GetPawn();
	if (MyPawn == nullptr)
		return;

	FVector NPCLocation = MyPawn->GetActorLocation();

	ERadiantOverrideState CurrentOverrideState = CachedAIComponent->GetCurrentOverrideState();

	FRadiantEvaluatorParams Params;
	Params.MainStack = CachedAIComponent->GetMainStack();
	Params.DefaultList = CachedAIComponent->GetDefaultList();
	Params.OverrideList = CachedAIComponent->GetOverrideListForState(CurrentOverrideState);
	Params.OverrideState = CurrentOverrideState;
	Params.WorldTimeHours = WorldTimeHours;
	Params.NPCLocation = NPCLocation;
	Params.World = GetWorld();

	URadiantPackage* SelectedPackage = Evaluator.Evaluate(Params);

	// Check if the package actually changed
	URadiantPackage* PreviousPackage = CachedAIComponent->GetCurrentPackage();
	bool bPackageChanged = (SelectedPackage != PreviousPackage);

	CachedAIComponent->SetCurrentPackage(SelectedPackage);

	WriteToBlackboard(SelectedPackage);

	// If package changed, restart the behavior tree to pick up new target
	if (bPackageChanged)
	{
		UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(GetBrainComponent());
		if (BTComp)
		{
			BTComp->RestartTree();
		}
	}
}

void ARadiantAIController::WriteToBlackboard(URadiantPackage* Package)
{
	UBlackboardComponent* BB = GetBlackboardComponent();

	if (BB == nullptr)
		return;

	if (Package != nullptr) {
		ERadiantPackageType PackageType = Package->GetPackageType();
		const FRadiantPackageParams& Params = Package->GetParams();

		BB->SetValueAsEnum(FName("PackageType"), static_cast<uint8>(PackageType));
		BB->SetValueAsName(FName("CurrentPackage"), Package->GetFName());

		FVector TargetLocation = Params.TargetLocation;
		AActor* TargetActor = Params.TargetActor.Get();
		
		if (TargetActor != nullptr) {
			TargetLocation = TargetActor->GetActorLocation();
		}

		BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);

		BB->SetValueAsObject(FName("TargetActor"), Params.TargetActor.Get());

		BB->SetValueAsFloat(FName("WanderRadius"), Params.Radius);
	} else {
		BB->SetValueAsEnum(FName("PackageType"), static_cast<uint8>(ERadiantPackageType::Sandbox));
		BB->SetValueAsName(FName("CurrentPackage"), "Sandbox | No Package");
		BB->SetValueAsVector(FName("TargetLocation"), GetPawn()->GetActorLocation());
		BB->SetValueAsObject(FName("TargetActor"), nullptr);
		BB->SetValueAsFloat(FName("WanderRadius"), 0.0f);
	}
		
}

bool ARadiantAIController::ShouldSkipEvaluationForLOD() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC == nullptr)
		return false;

	APawn* PlayerPawn = PC->GetPawn();
	if (PlayerPawn == nullptr)
		return false;

	APawn* MyPawn = GetPawn();
	if (MyPawn == nullptr)
		return false;

	float Distance = FVector::Dist(MyPawn->GetActorLocation(), PlayerPawn->GetActorLocation());

	return Distance > LODDistanceThreshold;

}

void ARadiantAIController::SetOverrideState(ERadiantOverrideState NewState)
{
	if (CachedAIComponent == nullptr)
		return;

	CachedAIComponent->SetCurrentOverrideState(NewState);

	ForceEvaluate();
}

ERadiantOverrideState ARadiantAIController::GetOverrideState() const
{
	if (CachedAIComponent == nullptr)
		return ERadiantOverrideState::None;

	return CachedAIComponent->GetCurrentOverrideState();
}

void ARadiantAIController::ForceEvaluate() {
	PerformEvaluation();
}

URadiantPackage* ARadiantAIController::GetCurrentPackage() const {
	if (CachedAIComponent == nullptr)
		return nullptr;

	return CachedAIComponent->GetCurrentPackage();
}
