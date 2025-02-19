// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"

#include "MyGameInstance.h"
AGhost::AGhost()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = Body;
	
	Tags.Add("Ghost");

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(DamageRadius);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnOverlapBegin);


	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMyAIController::StaticClass();

}

void AGhost::BeginPlay()
{
	Super::BeginPlay();

	MoveDirection = FVector(FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f), 0.f);
	MoveDirection.Normalize();

	if (Body)
	{
		Body->SetSimulatePhysics(true);
		Body->SetPhysicsLinearVelocity(MoveDirection * Speed);
	}
}

void AGhost::Destroyed()
{
	Super::Destroyed();

	
}

void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    
	if (PlayerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("Le fantôme suit le joueur"));
	}
	
}


// Called to bind functionality to input
void AGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGhost::TakeHit()
{
    // Vérifie si la vie est déjà inférieure ou égale à zéro pour éviter de décrementer plusieurs fois
    if (health > 0)
    {
        health -= 1;  // Réduit la vie
    	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("health reduced"));
		
        if (health <= 0)
        {
            // Assure-toi que GameInstance est bien initialisé
            if (!GameInstance) // Si GameInstance n'a pas été initialisé, le faire ici
            {
                GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
            }

            if (GameInstance)
            {
                // Appelle AddScore sur GameInstance pour ajouter un point
                GameInstance->AddScore();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("GameInstance est null dans TakeHit"));
            }

            DestroyAndPlaySound();
        }
    }
}
void AGhost::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
		if (PlayerCharacter)
		{
			Destroy();
		}
	}
}

void AGhost::DestroyAndPlaySound()
{
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathVFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathVFX, GetActorLocation());
	}
	Destroy();
}