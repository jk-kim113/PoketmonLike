// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WildMonFSM.generated.h"


UENUM(BlueprintType)
enum class EWildMonState : uint8
{
	Idle,
	Move,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POKETMONLIKE_API UWildMonFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWildMonFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EWildMonState mState = EWildMonState::Idle;

	void IdleState();
	void MoveState();
		
	UPROPERTY()
	class AWildMon* me;

};
