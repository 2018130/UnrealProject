// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlayerCharacter.h"

#include "TestPlayerController.h"
#include "00_Component/TimerComponent.h"
#include "98_Widget/TimerUserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMovablePlayerCharacter::AMovablePlayerCharacter()
{

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;

	//true->화면 안돌아감,디폴트 false->좌우 30도정도까진 돌아감
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//true->카메라가 조종되어버림, 디폴트 false
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TimerComponent = CreateDefaultSubobject<UTimerComponent>(TEXT("TimerComponent"));
}

void AMovablePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = LagSpeed;
}

void AMovablePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMovablePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMovablePlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
}

void AMovablePlayerCharacter::MoveForward(float Value)
{
	FRotator ControllerRotate = Cast<ATestPlayerController>(GetController())->GetControlRotation();

	FVector Vector = FRotationMatrix(
		FRotator(0, ControllerRotate.Yaw, 0)).GetUnitAxis(EAxis::X);

	AddMovementInput(Vector, Value);
}

void AMovablePlayerCharacter::MoveRight(float Value)
{
	FRotator ControllerRotate = Cast<ATestPlayerController>(GetController())->GetControlRotation();

	FVector Vector = FRotationMatrix(
		FRotator(0, ControllerRotate.Yaw, 0)).GetUnitAxis(EAxis::Y);

	AddMovementInput(Vector, Value);
}
