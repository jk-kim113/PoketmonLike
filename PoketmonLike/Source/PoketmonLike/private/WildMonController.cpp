// Fill out your copyright notice in the Description page of Project Settings.


#include "WildMonController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WildMon.h"

const FName AWildMonController::HomePosKey(TEXT("HomePos"));
const FName AWildMonController::PatrolPosKey(TEXT("PatrolPos"));

AWildMonController::AWildMonController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/BB_WildMon.BB_WildMon'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_WildMon.BT_WildMon'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AWildMonController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		
		RunBT(true);
	}
}

void AWildMonController::RunBT(bool isActive)
{
	if (isActive)
	{
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("!!!!"));
		}
	}
	else
	{
		BrainComponent->StopLogic(TEXT("Battle"));
	}
}
