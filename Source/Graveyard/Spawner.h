// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ghost.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class GRAVEYARD_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	FTimerHandle SpawnTimerHandle;

	float delay = 2.0f;
	void SpawnEnemy();
	void SpawnEnemy_Internal();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AGhost> EnemyClass; // Classe de l'ennemi à spawn

	UPROPERTY(EditAnywhere, Category="Spawner")
	UStaticMeshComponent* MeshComponent;

};
