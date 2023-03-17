// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMap.h"
#include "WildMon.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABattleMap::ABattleMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(TEXT("/Engine/MapTemplates/SM_Template_Map_Floor"));
	if (SM_SQUARE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_SQUARE.Object);
	}

	Mesh->SetWorldScale3D(FVector(6.0f, 6.0f, 1.0f));
}

// Called when the game starts or when spawned
void ABattleMap::BeginPlay()
{
	Super::BeginPlay();
	
	FindSpawnPoints();

	for (int n = 0; n < spawnPoints.Num(); n++)
	{
		if (spawnPoints[n])
		{
			int num = FMath::RandRange(2, 4);

			for (int m = 0; m < num; m++)
			{
				float randX = FMath::RandRange(-800.0f, 800.0f);
				float randY = FMath::RandRange(-800.0f, 800.0f);
				auto wildmon = GetWorld()->SpawnActor<AWildMon>(spawnPoints[n]->GetActorLocation() + FVector(randX, randY, 0), FRotator::ZeroRotator);
				wildmon->SetWildMonInfor(n + 1);
			}
		}
	}
}

// Called every frame
void ABattleMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleMap::FindSpawnPoints()
{
	TArray<class AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	for (auto spawn : allActors)
	{
		if (spawn->GetName().Contains(TEXT("BP_WildMonSpawnpoint")))
		{
			spawnPoints.Add(spawn);
		}
	}
}

