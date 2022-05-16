// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/AICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "MovablePlayerCharacter.h"
#include "MyAIController.h"
#include "TestPlayerController.h"
#include "98_Widget/AIProgressBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName("EnemyPreset");

	Dying = false;

	HPBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidgetComp"));
	HPBarWidgetComp->SetupAttachment(RootComponent);
	HPBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComp->SetVisibility(false);

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

}


// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::Attack()
{
	//task에서 진행하고 있습니다.
}

float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(!Dying)
	{
		if (HPBarWidgetComp != nullptr)
		{
			HPBarWidgetComp->SetVisibility(true);
			auto HPBarWidget = Cast<UAIProgressBarWidget>(HPBarWidgetComp->GetWidget());
			if (HPBarWidget != nullptr) {
				float per = HP / MaxHP;
				HPBarWidget->SetProgressBar(per);
			}
		}

		if (HP <= 0) {
			Dying = true;
			GetCapsuleComponent()->SetCollisionProfileName("Spectator");
			GetCharacterMovement()->StopActiveMovement();
			auto Player = EventInstigator->GetPawn<AMovablePlayerCharacter>();
			if (Player != nullptr)
			{
				Player->AddMoney(FMath::RandRange(10, 100));
			}

			auto controller = this->GetController<AMyAIController>();
			if (controller != nullptr)
			{
				controller->GetBrainComponent()->StopLogic("Death");
			}

			FTimerHandle TimerHandle;
			auto Time = 5.f;
			if (DeathAsset != nullptr)
			{
				GetMesh()->PlayAnimation(DeathAsset, false);
			}
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AAICharacter::Death, Time);
		}
	}
	
	return Damage;
}

void AAICharacter::Death()
{
	Destroy();
}
