// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WildMon.generated.h"

UCLASS()
class POKETMONLIKE_API AWildMon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWildMon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UWildMonFSM* fsm;

	void SetWildMonInfor(int32 index);

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnMeshLoadCompleted();

	FSoftObjectPath WildMonMeshToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> MeshStreamingHandle;

	FSoftObjectPath WildMonAnimToLoad = FSoftObjectPath(nullptr);
	TAssetPtr<class UClass> WildMonAnim;
};
