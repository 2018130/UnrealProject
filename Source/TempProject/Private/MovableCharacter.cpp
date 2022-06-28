// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableCharacter.h"

#include "02_Item/00_Weapon/Weapon_ItemActor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMovableCharacter::AMovableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponActorComponent"));
	WeaponActorComponent->SetupAttachment(GetMesh(), "WeaponSocket");

}

// Called when the game starts or when spawned
void AMovableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMovableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovableCharacter::AddHP(float Value)
{
	float NewHP = FMath::Clamp(Value + HP, 0, MaxHP);
	HP = NewHP;
	OnChangedHP.Broadcast(this);
}

void AMovableCharacter::AddMP(float Value)
{
	float NewMP = FMath::Clamp(Value + MP, 0, MaxMP);
	MP = NewMP;
	OnChangedMP.Broadcast(this);
}

float AMovableCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	this->AddHP(-DamageAmount);

	return DamageAmount;
}


