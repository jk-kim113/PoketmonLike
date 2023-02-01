// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MainGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FWildMonData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FWildMonData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString MeshLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString AnimLocation;
};

/**
 * 
 */
UCLASS()
class POKETMONLIKE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance();

	FWildMonData* GetWildMonData(int32 index);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
	class UDataTable* WildMonTable;
};
