// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
void UMyGameInstance::AddScore()
{
	score-=1;
	if (score <= 0)
	{
		EndGame(true);
	};
}

int32 UMyGameInstance::GetScore() const
{
	return score;
}
void UMyGameInstance::StartGameTimer()
{
	const float TimerDuration = 60.0f;  
    
	GetWorld()->GetTimerManager().SetTimer(EndGameTimerHandle, [this]() { EndGame(false); }, TimerDuration, false);
}



void UMyGameInstance::EndGame(bool bWin)
{
	SetIsWin(bWin);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyGameInstance::OpenMenu, 2.0f, false);
}
void UMyGameInstance::OpenMenu()
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
void UMyGameInstance::SetIsWin(bool win)
{
	isWin=win;
}
FString UMyGameInstance::SetWinText(FString title)
{
	ShowWinText=true;
	winText=title;
	return winText;
}
