#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyAIController.h"
#include "Components/SphereComponent.h"
#include "MyGameInstance.h"
#include "Sound/SoundBase.h"

#include "NiagaraSystem.h" 
#include "Particles/ParticleSystem.h"  
#include "Ghost.generated.h"

UCLASS()
class GRAVEYARD_API AGhost : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGhost();
	virtual void Tick(float DeltaTime) override;

	void TakeHit();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	void DestroyAndPlaySound();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void Destroyed() override;
private:
	FVector MoveDirection;
	float Speed = 300.f;

	UPROPERTY(EditAnywhere, Category="player")
	ACharacter* Player; 

	UPROPERTY(EditAnywhere, Category="Spawner")
	UStaticMeshComponent* Body;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 600.0f;  
	UMyGameInstance* GameInstance;
	int32 health=3;

	UPROPERTY(EditAnywhere)
	float DamageRadius = 100.0f; 

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* DeathVFX;
};
