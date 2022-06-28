// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlayerCharacter.h"

#include "ShopWidget.h"
#include "02_Item/Item_BulletActor.h"
#include "98_Widget/MainWidget.h"
#include "98_Widget/AskPickUpItemWidget.h"

#include "TestPlayerController.h"
#include "00_Component/TimerComponent.h"
#include "00_Component/ZoominComponent.h"
#include "01_AI/AICharacter.h"
#include "98_Widget/BulletCountWidget.h"
#include "98_Widget/ShowGetMoneyWidget.h"
#include "98_Widget/TimerUserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/App.h"
#include "Particles/ParticleSystem.h"
#include "02_Item/00_Weapon/Weapon_GrenadeActor.h"
#include "02_Item/01_Consume/Consume_ItemActor.h"
#include "03_GameInstance/MyGameInstance.h"
#include "98_Widget/ZoomTargetPointWidget.h"
#include "Components/SphereComponent.h"

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

	ZoominComponent = CreateDefaultSubobject<UZoominComponent>(TEXT("ZoominComponent"));

	const ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(
		TEXT("ParticleSystem'/Game/MilitaryWeapSilver/FX/P_Impact_Stone_Large_01.P_Impact_Stone_Large_01'"));
	ShootPointParticle = ParticleAsset.Object;

	const ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(
		TEXT("SoundWave'/Game/MilitaryWeapSilver/Sound/Rifle/Wavs/RifleA_Fire01.RifleA_Fire01'"));
	ShootSound = SoundAsset.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage>StunMontageAsset(
		TEXT("AnimMontage'/Game/00_Workspace/02_Animation/Q_Ability_Montage.Q_Ability_Montage'"));
	Ability_Stun_Montage = StunMontageAsset.Object;
}

void AMovablePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = LagSpeed;
	isAttacking = false;
}

void AMovablePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMovablePlayerCharacter::InitGIVariableToLocal()
{
	auto GI = GetGameInstance<UMyGameInstance>();
	if (GI != nullptr) {
		auto Con = GetController<ATestPlayerController>();
		if(Con != nullptr)
		{
			Con->GetMainWidget()->AddScore(GI->GetGI_Score());
			AddBullet(GI->GetGI_BulletCount());
			AddMoney(GI->GetGI_Money());
			SetShootDelay(GI->GetGI_ShootDelay());
			
			AddMaxHP(GI->GetGI_MaxHP());
			AddHP(GI->GetGI_HP());
			AddMaxMP(GI->GetGI_MaxMP());
			AddMP(GI->GetGI_MP());
			AddDamage(GI->GetGI_Damage());
		}
	}
}

void AMovablePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMovablePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMovablePlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMovablePlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMovablePlayerCharacter::StopAttack);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMovablePlayerCharacter::Jump);


	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMovablePlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMovablePlayerCharacter::StopRun);


	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::Roll);

	PlayerInputComponent->BindAction("Zoomin", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::Zoom);
	PlayerInputComponent->BindAction("Zoomin", EInputEvent::IE_Released, this, &AMovablePlayerCharacter::ZoomOut);

	PlayerInputComponent->BindAction("PickUp", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::PickUp);

	PlayerInputComponent->BindAction("Shop", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::Shop);

	PlayerInputComponent->BindAction("RifleMode", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::RifleMode);

	PlayerInputComponent->BindAction("GrenadeMode", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::GrenadeMode);

	PlayerInputComponent->BindAction("Ability_Stun", EInputEvent::IE_Released, this, &AMovablePlayerCharacter::Ability_Stun);
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

void AMovablePlayerCharacter::PickUp()
{
	TArray<AActor*> Hits;
	GetOverlappingActors(Hits);
	for (int i = 0; i < Hits.Num(); i++) {
		if (Hits[i]->IsA<AItem_BulletActor>()) {
			AddBullet(30);
			Hits[i]->Destroy();
			return;
		}

		if(Hits[i]->IsA<AConsume_ItemActor>())
		{
			auto Potion = Cast<AConsume_ItemActor>(Hits[i]);
			AddHP(Potion->GetRecoverHP());
			AddMP(Potion->GetRecoverMP());
			Hits[i]->Destroy();
			return;
		}
	}
}

void AMovablePlayerCharacter::Jump()
{
	Super::Jump();
}

void AMovablePlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!ZoominComponent->IsZoomMode()) {
		FVector StartVector = GetMesh()->GetSocketLocation("weapon_l");
		FRotator Rot = GetMesh()->GetSocketRotation("lowerarm_l");
		Rot.Pitch -= 8;
		FVector RotVector = FRotationMatrix(FRotator(Rot.Pitch, Rot.Yaw, Rot.Roll)).GetUnitAxis(EAxis::X);
		FVector EndVector = RotVector * Range + StartVector;
		DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Red);
	}else
	{
		auto Con = GetController<ATestPlayerController>();
		auto Rotation = GetActorRotation();
		Rotation.Yaw = Controller->GetControlRotation().Yaw;
		SetActorRotation(Rotation);
	}

	if(IsRunning)
	{
		AddMP(-5 * DeltaSeconds);
	}
}

void AMovablePlayerCharacter::Attack()
{
	if (GetController<ATestPlayerController>()->GetMainWidget()->GetShopWidget()->GetVisibility() == ESlateVisibility::Hidden) {
		GetCharacterMovement()->MaxWalkSpeed -= 100;
		if (BulletCount <= 0) {
			return;
		}
		isAttacking = true;
		Shoot();
		GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AMovablePlayerCharacter::Shoot, ShootDelay, true);
	}
}

void AMovablePlayerCharacter::StopAttack()
{
	if (GetController<ATestPlayerController>()->GetMainWidget()->GetShopWidget()->GetVisibility() == ESlateVisibility::Hidden) {
		isAttacking = false;
		GetCharacterMovement()->MaxWalkSpeed += 100;
		GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	}
}

void AMovablePlayerCharacter::Shoot()
{ 
	if (BulletCount <= 0 || GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) {
		return;
	}

	if (WeaponType == EWeaponType::RIFLE) {
		if (AttackMontage != nullptr) {
			GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage, 1 / ShootDelay);
		}

		AddBullet(-1);
		SpreadZoomInWidget();

		UGameplayStatics::PlaySoundAtLocation(this, ShootSound, this->GetActorLocation(), this->GetViewRotation());
		auto Con = GetController<ATestPlayerController>();

		FVector StartVector, EndVector;
		if (ZoominComponent->IsZoomMode()) {
			StartVector = GetFollowCamera()->GetComponentLocation();
			float RandRate = FMath::RandRange(-RandCorrectRate, RandCorrectRate);
			FVector Vec = FRotationMatrix(FRotator(Con->GetControlRotation().Pitch + RandRate, Con->GetControlRotation().Yaw + RandRate, Con->GetControlRotation().Roll)).GetUnitAxis(EAxis::X);
			EndVector = Vec * Range + StartVector;
		}
		else
		{
			StartVector = GetMesh()->GetSocketLocation("weapon_l");
			FRotator Rot = GetMesh()->GetSocketRotation("lowerarm_l");
			Rot.Pitch -= 8;
			FVector RotVector = FRotationMatrix(FRotator(Rot.Pitch, Rot.Yaw, Rot.Roll)).GetUnitAxis(EAxis::X);
			EndVector = RotVector * Range + StartVector;
		}

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartVector, EndVector, ECC_Visibility))
		{
			UKismetSystemLibrary::PrintString(this, Hit.BoneName.ToString());
			if (ShootPointParticle != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, ShootPointParticle, Hit.Location);
			}

			auto Enemy = Cast<AAICharacter>(Hit.GetActor());
			if (Enemy != nullptr)
			{
				float lastDamage = Damage;

				if (Hit.BoneName == "head") {
					lastDamage *= 2;
					Enemy->CriticalHit();
				}

				Enemy->TakeDamage(lastDamage, FDamageEvent(), this->GetController(), this);
			}
		}

		if (Con != nullptr)
		{
			FRotator Rot = Con->GetControlRotation();
			Rot.Yaw += FMath::RandRange(-0.5f, 0.5f);
			Rot.Pitch += FMath::RandRange(0.f, 1.f);

			Con->SetControlRotation(Rot);
		}
	}else if(WeaponType == EWeaponType::GRENADE)
	{
		if(BulletCount >= 10)
		{
			auto Grenade = GetWorld()->SpawnActor<AWeapon_GrenadeActor>(GrenadeActor, GetActorLocation() + 100, GetActorRotation());
			Grenade->SetOnwer(this);
			auto Con = GetController<ATestPlayerController>();
			FVector Vec = FRotationMatrix(FRotator(Con->GetControlRotation().Pitch, Con->GetControlRotation().Yaw, Con->GetControlRotation().Roll)).GetUnitAxis(EAxis::X);

			Grenade->GetMeshComponent()->AddForce(Vec * 100000 * Grenade->GetMeshComponent()->GetMass());

			AddBullet(-10);
		}else
		{
			UKismetSystemLibrary::PrintString(this, "Requires 10 bullets");
		}
	}
}

void AMovablePlayerCharacter::SpreadZoomInWidget()
{
	auto Con = GetController<ATestPlayerController>();
	if(Con != nullptr)
	{
		Con->GetZoomTargetPointWidget()->Spread();
	}
}

void AMovablePlayerCharacter::NotifyActorBeginOverlap(AActor* Otheractor)
{
	auto MainWidget = GetController<ATestPlayerController>()->GetMainWidget();
	if (MainWidget != nullptr) {
		if(Otheractor->IsA<AItemActor>())
			MainWidget->GetAskPickUpItemWidget()->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMovablePlayerCharacter::NotifyActorEndOverlap(AActor* Otheractor)
{
	auto Con = GetController<ATestPlayerController>();
	if (Con != nullptr) {
		auto MainWidget = Con->GetMainWidget();
		if (MainWidget != nullptr) {
			MainWidget->GetAskPickUpItemWidget()->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AMovablePlayerCharacter::AddMoney(int32 Value)
{
	Money += Value;
	auto Con = GetController<ATestPlayerController>();
	if(Con != nullptr)
	{
		Con->GetMainWidget()->GetShowGetMoneyWidget()->SetMoneyTextBlock(Money);
	}
}

void AMovablePlayerCharacter::AddBullet(int32 Value)
{
	BulletCount += Value;
	if (BulletCount < 0) BulletCount = 0;

	auto MainWidget = GetController<ATestPlayerController>()->GetMainWidget();
	if(MainWidget!= nullptr)
	{
		MainWidget->GetBulletCountWidget()->SetTextBlock_BulletCount(BulletCount);
	}
}

void AMovablePlayerCharacter::SetShootDelay(float Value)
{
	if(Value < 0.06)
	{
		UKismetSystemLibrary::PrintString(this, "Current maximum attack speed");
		return;
	}

	ShootDelay = Value;
}

void AMovablePlayerCharacter::Shop()
{
	auto Con = GetController<ATestPlayerController>();
	if (Con != nullptr) {

		auto MainWidget = Con->GetMainWidget();
		if (MainWidget != nullptr) {

			auto ShopWidget = MainWidget->GetShopWidget();
			if (ShopWidget->GetVisibility() == ESlateVisibility::Hidden)
			{
				Con->SetInputMode(FInputModeGameAndUI());
				Con->SetShowMouseCursor(true);
				ShopWidget->SetVisibility(ESlateVisibility::Visible);
			}else
			{
				Con->SetInputMode(FInputModeGameOnly());
				Con->SetShowMouseCursor(false);
				ShopWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void AMovablePlayerCharacter::RifleMode()
{
	WeaponType = EWeaponType::RIFLE;
	GetController<ATestPlayerController>()->GetMainWidget()->SetWeaponType(FText::FromString("RIFLE"));
}

void AMovablePlayerCharacter::GrenadeMode()
{
	WeaponType = EWeaponType::GRENADE;
	GetController<ATestPlayerController>()->GetMainWidget()->SetWeaponType(FText::FromString("GRENADE"));
}

float AMovablePlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Value = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(HP <= 0)
	{
		UGameplayStatics::OpenLevel(this, "Template_Default");
	}

	return Value;
}

void AMovablePlayerCharacter::Ability_Stun()
{
	if(Ability_Stun_Montage != nullptr && !GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		if (MP >= 20) {
			AddMP(-20);
			float time = GetMesh()->GetAnimInstance()->Montage_Play(Ability_Stun_Montage);
			GetController<ATestPlayerController>()->SetIgnoreMoveInput(true);

			FVector EndVector = GetActorForwardVector() * 50 + GetActorLocation();
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery;
			ObjectTypeQuery.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
			TArray<FHitResult> Hits;

			if (UKismetSystemLibrary::SphereTraceMultiForObjects(this, GetActorLocation(),
				EndVector, 800, ObjectTypeQuery, false,
				TArray<AActor*>(), EDrawDebugTrace::ForDuration,
				Hits, true))
			{
				for (int32 i = 0; i < Hits.Num(); i++)
				{
					if (Hits[i].GetActor()->IsA<AAICharacter>())
					{
						UKismetSystemLibrary::PrintString(this, Hits[i].GetActor()->GetName());
						auto AI = Cast<AAICharacter>(Hits[i].GetActor());

						AI->Stun();
					}
				}
			}
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AMovablePlayerCharacter::AbilityEnd, time);
		}
	}
}

void AMovablePlayerCharacter::AbilityEnd()
{
	GetController<ATestPlayerController>()->SetIgnoreMoveInput(false);
}

void AMovablePlayerCharacter::Run()
{
	if (MP > 0) {
		GetCharacterMovement()->MaxWalkSpeed += 200;
		IsRunning = true;
	}
}

void AMovablePlayerCharacter::StopRun()
{
	if (GetCharacterMovement()->MaxWalkSpeed == 800) {
		GetCharacterMovement()->MaxWalkSpeed -= 200;
		IsRunning = false;
	}
}

void AMovablePlayerCharacter::Roll()
{
	if (RollMontage != nullptr && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(RollMontage)) {
		if (MP >= 5) {
			AddMP(-5);
			GetMesh()->HideBoneByName("weapon_l", EPhysBodyOp::PBO_MAX);
			float time = GetMesh()->GetAnimInstance()->Montage_Play(RollMontage, 1.0f, EMontagePlayReturnType::Duration);

			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AMovablePlayerCharacter::RollEnd, time);
		}
	}
}

void AMovablePlayerCharacter::RollEnd()
{
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(RollMontage)) {
		GetMesh()->UnHideBoneByName("weapon_l");
	}
}

void AMovablePlayerCharacter::Zoom()
{
	ZoominComponent->Zoom();
}

void AMovablePlayerCharacter::ZoomOut()
{
	ZoominComponent->ZoomOut();
}

//
