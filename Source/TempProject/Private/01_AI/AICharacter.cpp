// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/AICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "MovablePlayerCharacter.h"
#include "MyAIController.h"
#include "TestPlayerController.h"
#include "02_Item/00_Weapon/Weapon_ItemActor.h"
#include "02_Item/01_Consume/Consume_ItemActor.h"
#include "98_Widget/AIProgressBarWidget.h"
#include "98_Widget/MainWidget.h"
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

	ConstructorHelpers::FObjectFinder<UAnimBlueprint>AnimBPAsset(
		TEXT("AnimBlueprint'/Game/00_Workspace/01_Item/00_Weapon/Rifle_AnimBP.Rifle_AnimBP'"));
	WeaponAnimBPAsset = AnimBPAsset.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage>StunMontageAsset(
		TEXT("AnimMontage'/Game/00_Workspace/00_AI/Stun_Idle_Retargeted_Montage.Stun_Idle_Retargeted_Montage'"));
	StunMontage = StunMontageAsset.Object;
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
	float Dam = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(!Dying)
	{
		if(Hit_ReactMontage != nullptr)
		{
			
			float time = GetMesh()->GetAnimInstance()->Montage_Play(Hit_ReactMontage, HitReactionRate, EMontagePlayReturnType::Duration);
			if (GetCharacterMovement()->MaxWalkSpeed != 0) {
				MaxSPD = GetCharacterMovement()->MaxWalkSpeed;
			}
			GetCharacterMovement()->MaxWalkSpeed = 0;

			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AAICharacter::StopFrozen, time);
		}

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

			int32 Sniffling = FMath::RandRange(1, 20);
			switch (Sniffling)
			{
			case 1:
				if(HPPotionObj != nullptr)
				{
					GetWorld()->SpawnActor<AConsume_ItemActor>(HPPotionObj, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
				}
				break;
			case 2:
				if (MPPotionObj != nullptr)
				{
					GetWorld()->SpawnActor<AConsume_ItemActor>(MPPotionObj, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
				}
				break;
			case 3:
				if (HPPotionObj != nullptr)
				{
					GetWorld()->SpawnActor<AConsume_ItemActor>(HPPotionObj, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
				}
				if (MPPotionObj != nullptr)
				{
					FVector SpawnLocation = GetActorLocation();
					SpawnLocation.Y += 40;
					SpawnLocation.X += 40;
					GetWorld()->SpawnActor<AConsume_ItemActor>(MPPotionObj, SpawnLocation, FRotator::ZeroRotator, FActorSpawnParameters());
				}
				break;
			}

			auto Player = EventInstigator->GetPawn<AMovablePlayerCharacter>();
			if (Player != nullptr)
			{
				Player->AddMoney(FMath::RandRange(10, 100));
				auto TargetController = Player->GetController<ATestPlayerController>();
				if (TargetController != nullptr)
				{
					float Value = this->GetMaxHP() + this->Damage * 100;
					TargetController->GetMainWidget()->AddScore(Value);
				}
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

void AAICharacter::StopFrozen()
{
	if(!GetMesh()->GetAnimInstance()->Montage_IsPlaying(Hit_ReactMontage))
	{
		GetCharacterMovement()->MaxWalkSpeed = 700;
	}
}

void AAICharacter::Stun()
{
	if(StunMontage != nullptr)
	{
		if(IsAttacking)
		{
			IsAttacking = false;
		}
		float time = GetMesh()->GetAnimInstance()->Montage_Play(StunMontage, 0.5, EMontagePlayReturnType::Duration);
		GetController<AAIController>()->GetBrainComponent()->StopLogic("Stuned");

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AAICharacter::StunEnd, time);
	}
}

void AAICharacter::StunEnd()
{
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(StunMontage)) {
		GetController<AAIController>()->RunBehaviorTree(BehaviorTree);
	}
}
