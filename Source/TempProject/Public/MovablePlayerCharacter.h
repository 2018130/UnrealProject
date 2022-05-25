// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovableCharacter.h"
#include "MovablePlayerCharacter.generated.h"

/**
 * 
 */

enum class EWeaponType
{
	RIFLE,
	GRENADE,
};

UCLASS()
class TEMPPROJECT_API AMovablePlayerCharacter : public AMovableCharacter
{
	GENERATED_BODY()

protected:

	AMovablePlayerCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
		float LagSpeed;
	UPROPERTY(EditAnywhere)
		float Range;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
		class UTimerComponent* TimerComponent;

	UPROPERTY(EditAnywhere)
		class UZoominComponent* ZoominComponent;

	UPROPERTY(EditAnywhere)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

	UPROPERTY(VisibleAnywhere)
		int32 BulletCount = 0;

	EWeaponType WeaponType;

	int32 Money;

	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void PickUp();

	virtual void Jump() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float ShootDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isAttacking;

	FTimerHandle ShootTimerHandle;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ShootPointParticle;

	UPROPERTY(EditAnywhere)
		UTexture* ShootedPointTexture;

	UPROPERTY(EditDefaultsOnly)
		USoundWave* ShootSound;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeapon_GrenadeActor> GrenadeActor;

public:

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking() { return isAttacking; }

	virtual void Attack() override;

	void StopAttack();

	void Shoot();

	USpringArmComponent* GetCameraBoom() { return CameraBoom; }

	UCameraComponent* GetFollowCamera() { return FollowCamera; }

	virtual void NotifyActorBeginOverlap(AActor* Otheractor) override;

	virtual void NotifyActorEndOverlap(AActor* Otheractor) override;

	void AddMoney(int32 Value);

	void AddBullet(int32 Value);

	float GetShootDelay() { return ShootDelay; }

	void SetShootDelay(float Value);

	void Shop();

	bool CheckMoney(int32 Value) { return Money >= Value; }

	void RifleMode();

	void GrenadeMode();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
