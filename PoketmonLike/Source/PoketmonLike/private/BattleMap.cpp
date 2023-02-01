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

	if (spawnPoints[0])
	{
		auto wildmon = GetWorld()->SpawnActor<AWildMon>(spawnPoints[0]->GetActorLocation(), FRotator::ZeroRotator);
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

