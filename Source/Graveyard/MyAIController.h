// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GRAVEYARD_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	public:
    	virtual void BeginPlay() override;
    	virtual void Tick(float DeltaTime) override;
    
    private:
    	APawn* PlayerPawn;
};
