// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ghost.generated.h"

UCLASS()
class GRAVEYARD_API AGhost : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGhost();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="player")
	ACharacter* Player; 

	UPROPERTY(EditAnywhere, Category="Spawner")
	UStaticMeshComponent* Body;

};
