// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Component/ZoominComponent.h"

#include <string>

#include "98_Widget/ZoomTargetPointWidget.h"
#include "MovablePlayerCharacter.h"
#include "TestPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UZoominComponent::UZoominComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	IsZoomIn = false;
	// ...
}


// Called when the game starts
void UZoominComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}



void UZoominComponent::Zoom()
{
	auto Player = GetOwner<AMovablePlayerCharacter>();
	if (Player != nullptr)
	{
		auto CameraBoom = Player->GetCameraBoom();
		auto Camera = Player->GetFollowCamera();
		if (CameraBoom != nullptr && Camera != nullptr)
		{
			CameraBoom->TargetArmLength -= 500;

			FVector CamRocation = Camera->GetRelativeLocation();
			CamRocation.X += XVal;
			CamRocation.Y += YVal;
			CamRocation.Z += ZVal;
			Camera->SetRelativeLocation(CamRocation);

			auto Controller = Player->GetController<ATestPlayerController>();
			if (Controller != nullptr)
			{
				Controller->GetZoomTargetPointWidget()->SetVisibility(ESlateVisibility::Visible);
				//Player->GetCharacterMovement()->bOrientRotationToMovement = false;
				Player->GetCharacterMovement()->MaxWalkSpeed -= 300;
				IsZoomIn = true;
			}
		}
	}
}

void UZoominComponent::ZoomOut()
{
	auto Player = GetOwner<AMovablePlayerCharacter>();
	if (Player != nullptr)
	{
		auto CameraBoom = Player->GetCameraBoom();
		auto Camera = Player->GetFollowCamera();
		if (CameraBoom != nullptr && Camera != nullptr)
		{
			CameraBoom->TargetArmLength += 500;

			FVector Rocation = Camera->GetRelativeLocation();
			Rocation.X -= XVal;
			Rocation.Y -= YVal;
			Rocation.Z -= ZVal;
			Camera->SetRelativeLocation(Rocation);

			auto Controller = Player->GetController<ATestPlayerController>();
			if (Controller != nullptr)
			{
				Controller->GetZoomTargetPointWidget()->SetVisibility(ESlateVisibility::Hidden);
				Player->GetCharacterMovement()->bOrientRotationToMovement = true;
				Player->GetCharacterMovement()->MaxWalkSpeed += 300;
				IsZoomIn = false;
			}
		}
	}
}

