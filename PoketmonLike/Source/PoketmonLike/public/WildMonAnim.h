// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WildMonAnim.generated.h"

/**
 * 
 */
UCLASS()
class POKETMONLIKE_API UWildMonAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UWildMonAnim();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
};
