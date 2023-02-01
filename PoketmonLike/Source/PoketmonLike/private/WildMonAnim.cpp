// Fill out your copyright notice in the Description page of Project Settings.


#include "WildMonAnim.h"

UWildMonAnim::UWildMonAnim()
{
	CurrentPawnSpeed = 0.0f;
}

void UWildMonAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	CurrentPawnSpeed = Pawn->GetVelocity().Size();
}
