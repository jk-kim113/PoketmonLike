// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WildMonController.generated.h"

/**
 * 
 */
UCLASS()
class POKETMONLIKE_API AWildMonController : public AAIController
{
	GENERATED_BODY()
	
public:
	AWildMonController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;

	void RunBT(bool isActive);

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
