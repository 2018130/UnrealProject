// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_Weapon/Weapon_ItemActor.h"

AWeapon_ItemActor::AWeapon_ItemActor()
{

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;
}
