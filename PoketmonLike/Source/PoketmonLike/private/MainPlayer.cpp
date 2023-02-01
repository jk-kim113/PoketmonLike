// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	springArmComp->SetupAttachment(RootComponent);
	tpsCamComp->SetupAttachment(springArmComp);

	springArmComp->TargetArmLength = 400.0f;
	springArmComp->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	springArmComp->bUsePawnControlRotation = true;
	springArmComp->bInheritPitch = true;
	springArmComp->bInheritRoll = true;
	springArmComp->bInheritYaw = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MAINPLAYER_ANIM(TEXT("AnimBlueprint'/Game/Animations/ABP_MainPlayer.ABP_MainPlayer_C'"));

	if (MAINPLAYER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MAINPLAYER_ANIM.Class);
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MainPlayer"));
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMainPlayer::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMainPlayer::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainPlayer::LookUp);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AMainPlayer::InputRun);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &AMainPlayer::InputRun);
}

void AMainPlayer::UpDown(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AMainPlayer::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AMainPlayer::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AMainPlayer::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void AMainPlayer::InputRun()
{	
	if (GetCharacterMovement()->MaxWalkSpeed > walkSpeed)
	{
		GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	}
}