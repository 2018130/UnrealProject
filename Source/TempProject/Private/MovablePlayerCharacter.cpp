// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMovablePlayerCharacter::AMovablePlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	//true->화면 안돌아감,디폴트 false->좌우 30도정도까진 돌아감
	//CameraBoom->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	this->bUseControllerRotationYaw = false;
}

void AMovablePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMovablePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMovablePlayerCharacter::MoveRight);
}

void AMovablePlayerCharacter::MoveForward(float Value)
{
		FRotator ControllerRotate = Controller->GetControlRotation();

		FVector Vector = FRotationMatrix(
			FRotator(0 ,ControllerRotate.Yaw, 0)).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Vector, Value);
	
}

void AMovablePlayerCharacter::MoveRight(float Value)
{
		FRotator ControllerRotate = Controller->GetControlRotation();

		FVector Vector = FRotationMatrix(
			FRotator(0, ControllerRotate.Yaw, 0)).GetUnitAxis(EAxis::Y);

		AddMovementInput(Vector, Value);
	
}
