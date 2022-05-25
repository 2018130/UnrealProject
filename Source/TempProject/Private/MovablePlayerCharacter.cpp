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
#include "Components/SphereComponent.h"

AMovablePlayerCharacter::AMovablePlayerCharacter()
{
	Damage = 10;

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

	WeaponType = EWeaponType::RIFLE;
}

void AMovablePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = LagSpeed;
	isAttacking = false;
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

	PlayerInputComponent->BindAction("Zoomin", EInputEvent::IE_Pressed, ZoominComponent, &UZoominComponent::Zoom);
	PlayerInputComponent->BindAction("Zoomin", EInputEvent::IE_Released, ZoominComponent, &UZoominComponent::ZoomOut);

	PlayerInputComponent->BindAction("PickUp", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::PickUp);

	PlayerInputComponent->BindAction("Shop", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::Shop);

	PlayerInputComponent->BindAction("RifleMode", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::RifleMode);

	PlayerInputComponent->BindAction("GrenadeMode", EInputEvent::IE_Pressed, this, &AMovablePlayerCharacter::GrenadeMode);
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
		UGameplayStatics::PlaySoundAtLocation(this, ShootSound, this->GetActorLocation(), this->GetViewRotation());
		auto Con = GetController<ATestPlayerController>();

		FVector StartVector, EndVector;
		if (ZoominComponent->IsZoomMode()) {
			StartVector = GetFollowCamera()->GetComponentLocation();
			FVector Vec = FRotationMatrix(FRotator(Con->GetControlRotation().Pitch, Con->GetControlRotation().Yaw, Con->GetControlRotation().Roll)).GetUnitAxis(EAxis::X);
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

		if (UKismetSystemLibrary::LineTraceSingleForObjects(this, StartVector, EndVector,
			ObjectType, false, TArray<AActor*>(), EDrawDebugTrace::None,
			Hit, true))
		{
			if (ShootPointParticle != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, ShootPointParticle, Hit.Location);
			}

			auto Enemy = Cast<AAICharacter>(Hit.GetActor());
			if (Enemy != nullptr)
			{

				Enemy->TakeDamage(Damage, FDamageEvent(), this->GetController(), this);
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
		if(BulletCount >= 1000)
		{
			auto Grenade = GetWorld()->SpawnActor<AWeapon_GrenadeActor>(GrenadeActor, GetActorLocation() + 100, GetActorRotation());
			Grenade->SetOnwer(this);
			auto Con = GetController<ATestPlayerController>();
			FVector Vec = FRotationMatrix(FRotator(Con->GetControlRotation().Pitch, Con->GetControlRotation().Yaw, Con->GetControlRotation().Roll)).GetUnitAxis(EAxis::X);

			Grenade->GetMeshComponent()->AddForce(Vec * 100000 * Grenade->GetMeshComponent()->GetMass());

			AddBullet(-1000);
		}else
		{
			UKismetSystemLibrary::PrintString(this, "Requires 1000 bullets");
		}
	}
}

void AMovablePlayerCharacter::NotifyActorBeginOverlap(AActor* Otheractor)
{
	auto Bullet = Cast<AItemActor>(Otheractor);
	if (Bullet != nullptr) {
		auto MainWidget = GetController<ATestPlayerController>()->GetMainWidget();
		if (MainWidget != nullptr) {
			MainWidget->GetAskPickUpItemWidget()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMovablePlayerCharacter::NotifyActorEndOverlap(AActor* Otheractor)
{
	auto Bullet = Cast<AItemActor>(Otheractor);
	if (Bullet != nullptr) {
		auto MainWidget = GetController<ATestPlayerController>()->GetMainWidget();
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
}

void AMovablePlayerCharacter::GrenadeMode()
{
	WeaponType = EWeaponType::GRENADE;
}

float AMovablePlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Value = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(HP <= 0)
	{
		UGameplayStatics::OpenLevel(this, "Second_Scene");
	}

	return Value;
}

