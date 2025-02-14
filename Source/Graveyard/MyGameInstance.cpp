// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
void UMyGameInstance::AddScore()
{
	score-=1;
	if (score <= 0)
	{
		UMyGameInstance::EndGame();
	};
}

int32 UMyGameInstance::GetScore() const
{
	return score;
}
void UMyGameInstance::StartGameTimer()
{
	const float TimerDuration = 60.0f;  

	GetWorld()->GetTimerManager().SetTimer(EndGameTimerHandle, this, &UMyGameInstance::EndGame, TimerDuration, false);
}


void UMyGameInstance::EndGame()
{
    UGameplayStatics::OpenLevel(this, FName("bp_menu"));
}

float UMyGameInstance::GetTimeRemaining() const
{
	if (GetWorld()->GetTimerManager().IsTimerActive(EndGameTimerHandle))
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(EndGameTimerHandle);
	}
    
	return 0.0f;
}