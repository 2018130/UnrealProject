// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_Weapon/Weapon_GrenadeActor.h"

#include "MovablePlayerCharacter.h"
#include "01_AI/AICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AWeapon_GrenadeActor::AWeapon_GrenadeActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
}

void AWeapon_GrenadeActor::BeginPlay()
{
	Super::BeginPlay();

	InitGenericItemInformation();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWeapon_GrenadeActor::Explosion, 3.0f, false);
}

void AWeapon_GrenadeActor::Explosion()
{
	TArray<FHitResult> Hits;

	if(UKismetSystemLibrary::SphereTraceMultiForObjects(this, GetActorLocation(), GetActorForwardVector() + GetActorLocation(), 300.f,
		ObjectType, false,TArray<AActor*>(), EDrawDebugTrace::None,
		Hits,  true))
	{
		for(int32 i = 0; i < Hits.Num(); i++)
		{
			if (player != nullptr) {
				float dam = ((FWeapon*)GenericItemInformation.SharedPtr.Get())->Damage + player->GetDamage();
				Cast<AAICharacter>(Hits[i].GetActor())->TakeDamage(dam, FDamageEvent(), player->GetController(), nullptr);
			}
		}
	}
	
	if(ExplosionParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, this->GetActorLocation());
	}
	if (ExplosionSound != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, ExplosionSound, this->GetActorLocation());
	}

	Destroy();
}

void AWeapon_GrenadeActor::InitGenericItemInformation()
{
	Super::InitGenericItemInformation();

	if (!GenericItemInformation.SharedPtr.IsValid())
	{
		auto ItemInfo = DataTable->FindRow<FWeapon>(ItemCode, "Cannot Find");
		if (ItemInfo != nullptr)
		{
			ItemInfo->ItemType = EItemType::WEAPON;
			FWeapon* Info = new FWeapon(*ItemInfo);
			GenericItemInformation.SharedPtr = MakeShareable(Info);
			UE_LOG(LogTemp, Log, TEXT("22222222-"));
		}
	}
}
