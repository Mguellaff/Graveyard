// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	// Création et attachement du maillage statique
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Si le timer n'est pas déjà actif, on appelle SpawnEnemy
	if (!GetWorld()->GetTimerManager().IsTimerActive(SpawnTimerHandle))
	{
		SpawnEnemy();
	}
}

void ASpawner::SpawnEnemy()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy_Internal, delay, false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Spawn called"));
}

void ASpawner::SpawnEnemy_Internal()
{
	if (SpawnedEnemy)
	{
		SpawnedEnemy->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Old enemy destroyed!"));
	}

	if (EnemyClass)
	{
		FVector LocalOffset(
			FMath::RandRange(-250, 250),
			FMath::RandRange(-250, 250),
			FMath::RandRange(0, 500)
		);

		FVector SpawnLocation = GetActorLocation() + LocalOffset;
		FRotator SpawnRotation = GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Créer un nouvel ennemi et stocker son pointeur
		SpawnedEnemy = GetWorld()->SpawnActor<AGhost>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (SpawnedEnemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Enemy Spawned Successfully at: %s"), *SpawnLocation.ToString()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy did not spawn!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnemyClass is NULL! Assign it in the Editor."));
	}
}


void ASpawner::OnSpawn_Implementation() {}



