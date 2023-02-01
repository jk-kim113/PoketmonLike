// Fill out your copyright notice in the Description page of Project Settings.


#include "WildMon.h"
#include "WildMonFSM.h"
#include "WildMonController.h"
#include "Components/CapsuleComponent.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWildMon::AWildMon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UWildMonFSM>(TEXT("FSM"));

	AIControllerClass = AWildMonController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("WildMon"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

// Called when the game starts or when spawned
void AWildMon::BeginPlay()
{
	Super::BeginPlay();
}

void AWildMon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AWildMon::OnCharacterOverlap);
}

// Called every frame
void AWildMon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWildMon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWildMon::SetWildMonInfor(int32 index)
{
	auto MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (nullptr != MainGameInstance)
	{	
		WildMonMeshToLoad.SetPath(MainGameInstance->GetWildMonData(index)->MeshLocation);
		WildMonAnimToLoad.SetPath(MainGameInstance->GetWildMonData(index)->AnimLocation);

		MeshStreamingHandle = MainGameInstance->StreamableManager.RequestAsyncLoad(WildMonMeshToLoad, FStreamableDelegate::CreateUObject(this, &AWildMon::OnMeshLoadCompleted));

		WildMonAnim = MainGameInstance->StreamableManager.LoadSynchronous(WildMonAnimToLoad);
		
		if (nullptr != WildMonAnim)
		{
			GetMesh()->SetAnimInstanceClass(WildMonAnim.Get());
		}
	}
}

void AWildMon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("sdjkfdklfs"));
}

void AWildMon::OnMeshLoadCompleted()
{
	class USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(MeshStreamingHandle->GetLoadedAsset());
	MeshStreamingHandle.Reset();
	if (nullptr != AssetLoaded)
	{
		GetMesh()->SetSkeletalMesh(AssetLoaded);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
}

