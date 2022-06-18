// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MovableCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class AMovableCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedMP, class AMovableCharacter*, Character);

UCLASS()
class TEMPPROJECT_API AMovableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMovableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		UChildActorComponent* WeaponActorComponent;

	UPROPERTY(EditAnywhere)
		float HP;
	UPROPERTY(EditAnywhere)
		float MaxHP;
	UPROPERTY(EditAnywhere)
		float MP;
	UPROPERTY(EditAnywhere)
		float MaxMP;
	UPROPERTY(EditAnywhere)
		float Damage;
public:

	UPROPERTY(EditAnywhere)
		FOnChangedHP OnChangedHP;
	UPROPERTY(EditAnywhere)
		FOnChangedMP OnChangedMP;

	UFUNCTION(BlueprintCallable)
		void AddHP(float Value);

	void AddMP(float Value);

	float GetHP() { return HP; }
	float GetMP() { return MP; }
	float GetMaxHP() { return MaxHP; }
	float GetMaxMP() { return MaxMP; }

	virtual void Attack() {};

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void AddDamage(float Value) { Damage += Value; }

	void AddMaxHP(float Value) { MaxHP += Value; }

	void AddMaxMP(float Value) { MaxMP += Value; }
	float GetDamage() { return Damage; }

	UChildActorComponent* GetWeaponActorComponent() { return WeaponActorComponent; }
};
