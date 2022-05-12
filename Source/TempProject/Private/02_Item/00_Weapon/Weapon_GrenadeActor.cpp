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
	auto Info = DataTable->FindRow<FWeapon>(ItemCode, "Cannot Find");

	InitGenericItemInformation();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWeapon_GrenadeActor::Explosion, 3.0f, false);
}

#if WITH_EDITOR
void AWeapon_GrenadeActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	InitGenericItemInformation();
}
#endif

void AWeapon_GrenadeActor::InitGenericItemInformation()
{
	auto Info = DataTable->FindRow<FWeapon>(ItemCode, "Cannot Find");

	if (Info != nullptr)
	{
		GenericItemInformation.ItemCode = Info->ItemCode;
		GenericItemInformation.ItemActorObject = Info->ItemActorObject;
		GenericItemInformation.ItemDescription = Info->ItemDescription;
		GenericItemInformation.ItemName = Info->ItemName;

		if (GenericItemInformation.SharedPtr.IsValid() == false) {
			FWeapon* ItemInfo = new FWeapon(*Info);
			GenericItemInformation.SharedPtr = MakeShareable(ItemInfo);
		}
	}
}

void AWeapon_GrenadeActor::Explosion()
{
	TArray<FHitResult> Hits;

	if(UKismetSystemLibrary::SphereTraceMultiForObjects(this, GetActorLocation(), GetActorForwardVector() + GetActorLocation(), 300.f, ObjectType, false,TArray<AActor*>(), EDrawDebugTrace::ForDuration,
		Hits,  true))
	{
		for(int32 i = 0; i < Hits.Num(); i++)
		{
			if (player != nullptr) {
				float dam = ((FWeapon*)GenericItemInformation.SharedPtr.Get())->Damage + player->GetDamage();
				Cast<AAICharacter>(Hits[i].GetActor())->TakeDamage(dam, FDamageEvent(), player->GetController(), nullptr);
				UKismetSystemLibrary::PrintString(this, FString::FormatAsNumber(dam));
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
