// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Component/TimerComponent.h"

#include "MovablePlayerCharacter.h"
#include "TestPlayerController.h"
#include "98_Widget/TimerUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UTimerComponent::UTimerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Time = MaxTime;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTimerComponent::UpdateTime, 1.0f, true);
}

void UTimerComponent::UpdateTime()
{
	auto player = Cast<AMovablePlayerCharacter>(GetOwner());
	auto Controller = Cast<ATestPlayerController>(player->GetController());
	if (Controller != nullptr) {
		auto TimerWidget = Controller->GetTimerWidget();

		if (Time < 1)
		{
			FText EndStr = FText::FromString("TheEnd");
			TimerWidget->SetTimeText(EndStr);
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		else
		{
			Time--;
			TimerWidget->SetTimeText(Time);
		}
	}
}


