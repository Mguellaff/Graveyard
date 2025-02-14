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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AGhost> EnemyClass;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
private:
	AGhost* SpawnedEnemy = nullptr; 

	FTimerHandle SpawnTimerHandle;

	float delay = 5.0f;
	void SpawnEnemy();
	void SpawnEnemy_Internal();

	
	UPROPERTY(EditAnywhere, Category="Spawner")
	UStaticMeshComponent* MeshComponent;

};


