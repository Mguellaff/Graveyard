// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"
#include "MyGameInstance.h"
UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AGraveyardCharacter* Character = Cast<AGraveyardCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
	
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance)
	{
		GameInstance->StartGameTimer();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Timer démarré depuis AMoon !"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance est null dans AMoon::BeginPlay"));
	}
}
