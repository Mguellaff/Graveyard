
#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Engine/World.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	// Récupère le joueur dans la scène
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn)
	{
		// Fait avancer le fantôme vers le joueur
		MoveToActor(PlayerPawn, 5.0f); // 5.0f correspond à la distance d'acceptation
	}
}