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
	// Planifie le spawn si ce n'est pas déjà fait
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy_Internal, delay, false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Spawn called"));
}

void ASpawner::SpawnEnemy_Internal()
{
	if (EnemyClass) 
	{
		FVector LocalOffset(0, 5, 0);
		FVector SpawnLocation = GetActorTransform().TransformPosition(LocalOffset);

		FRotator SpawnRotation = GetActorRotation();

		AGhost* SpawnedEnemy = GetWorld()->SpawnActor<AGhost>(EnemyClass, SpawnLocation, SpawnRotation);

		if (SpawnedEnemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Spawned Successfully!"));
		}
else
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy did not Spawn!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnemyClass is NULL! Assign it in the Editor."));
	}
}


