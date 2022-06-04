// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/01_Consume/Consume_ItemActor.h"

#include "Components/SphereComponent.h"

AConsume_ItemActor::AConsume_ItemActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = StaticMeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	
}

void AConsume_ItemActor::BeginPlay()
{
	Super::BeginPlay();

	InitGenericItemInformation();
}

float AConsume_ItemActor::GetRecoverHP()
{
	if (GenericItemInformation.SharedPtr.IsValid())
	{
		FConsume* ItemInfo = (FConsume*)GenericItemInformation.SharedPtr.Get();
		return ItemInfo->RecoverHP;
	}
	return 0;
}

float AConsume_ItemActor::GetRecoverMP()
{
	if (GenericItemInformation.SharedPtr.IsValid())
	{
		FConsume* ItemInfo = (FConsume*)GenericItemInformation.SharedPtr.Get();
		return ItemInfo->RecoverMP;
	}
	return 0;
}

void AConsume_ItemActor::InitGenericItemInformation()
{
	Super::InitGenericItemInformation();

	if(!GenericItemInformation.SharedPtr.IsValid())
	{
		auto ItemInfo = DataTable->FindRow<FConsume>(ItemCode, "Cannot Find");
		if(ItemInfo != nullptr)
		{
			ItemInfo->ItemType = EItemType::CONSUME;
			FConsume* Info = new FConsume(*ItemInfo);
			GenericItemInformation.SharedPtr = MakeShareable(Info);
			UE_LOG(LogTemp, Log, TEXT("2222222222"));
		}
	}
}
