// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AGraveyardCharacter;
class UMyGameInstance;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVEYARD_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AGraveyardProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Sounds")
	USoundBase* ReloadSound;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(AGraveyardCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category="Ammo")
	int32 GetNumberOfBullet() const { return NumberOfBullet; }

	UFUNCTION(BlueprintCallable, Category="Ammo")
	void SetNumberOfBullet(int32 NewNumberOfBullet)
	{
		NumberOfBullet = NewNumberOfBullet;
		MaxBullet-=NewNumberOfBullet;
		if(MaxBullet<0)
			MaxBullet=0;
	}

	UFUNCTION(BlueprintCallable, Category="Ammo")
	int32 GetMaxBullet() const { return MaxBullet; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=(BlueprintProtected="true"))
	int32 NumberOfBullet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta=(BlueprintProtected="true"))
	int32 MaxBullet;
	
	void MinusOneBullet();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Reload")
	FString ReloadText;
	
	UFUNCTION(BlueprintCallable, Category="Ammo")
	FString GetReloadText() const { return ReloadText; }

	UFUNCTION(BlueprintCallable, Category="Ammo")
	void SetReloadText(FString newReloadText){ReloadText=newReloadText;}
	
protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	AGraveyardCharacter* Character;
	void Reload();
	void FinishReload();
	
	
	FTimerHandle ReloadTimerHandle;
	

	

	bool canShoot=true;
};
