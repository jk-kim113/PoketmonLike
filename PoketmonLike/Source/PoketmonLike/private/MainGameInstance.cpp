// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

UMainGameInstance::UMainGameInstance()
{
	FString WildMonDataPath = TEXT("DataTable'/Game/GameData/WildMonData.WildMonData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WILDMON(*WildMonDataPath);
	WildMonTable = DT_WILDMON.Object;
}

FWildMonData* UMainGameInstance::GetWildMonData(int32 index)
{
	return WildMonTable->FindRow<FWildMonData>(*FString::FromInt(index), TEXT(""));
}
