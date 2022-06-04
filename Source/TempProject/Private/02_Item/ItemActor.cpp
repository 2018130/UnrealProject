// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/ItemActor.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void AItemActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	InitGenericItemInformation();
}
#endif

void AItemActor::InitGenericItemInformation()
{
	if (DataTable != nullptr) {
		const auto Info = DataTable->FindRow<FItemInformation>(ItemCode, "Cannot Find");

		if (Info != nullptr)
		{
			GenericItemInformation.ItemCode = Info->ItemCode;
			GenericItemInformation.ItemActorObject = Info->ItemActorObject;
			GenericItemInformation.ItemDescription = Info->ItemDescription;
			GenericItemInformation.ItemName = Info->ItemName;
		}
		/*
		switch (Info->ItemType)
		{
		case EItemType::WEAPON:
		{
			FWeapon* info = (FWeapon*)Info;
			if (GenericItemInformation.SharedPtr.IsValid() == false) {
				FWeapon* ItemInfo = new FWeapon(*info);
				GenericItemInformation.SharedPtr = MakeShareable(ItemInfo);
			}

			break;
		}
		case EItemType::CONSUME:
		{
			FConsume* info = (FConsume*)Info;
			if (GenericItemInformation.SharedPtr.IsValid() == false) {
				FConsume* ItemInfo = new FConsume(*info);
				GenericItemInformation.SharedPtr = MakeShareable(ItemInfo);
			}

			break;
		}
		}
		*/
	}
}