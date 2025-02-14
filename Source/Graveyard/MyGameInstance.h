// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GRAVEYARD_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void AddScore();
	UFUNCTION(BlueprintCallable, Category="Timer")
	void StartGameTimer();
	UFUNCTION(BlueprintPure, Category="Score")
	int32 GetScore() const;
    UFUNCTION(BlueprintPure, Category="Timer")
    float GetTimeRemaining() const;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Score", meta=(AllowPrivateAccess="true"))
	int32 score=15;
	FTimerHandle EndGameTimerHandle;
	void EndGame();
};
