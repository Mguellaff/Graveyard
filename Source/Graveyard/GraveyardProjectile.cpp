// Copyright Epic Games, Inc. All Rights Reserved.

#include "GraveyardProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ghost.h"
#include "Components/SphereComponent.h"

AGraveyardProjectile::AGraveyardProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGraveyardProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f; 


	InitialLifeSpan = 1.0f;
}

void AGraveyardProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this))  // Vérifie que l'autre acteur n'est pas ce projectile
	{
		// Vérifie si l'acteur touché possède le tag "Ghost"
		if (OtherActor->ActorHasTag("Ghost"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("has ghost"));
		
			// Appelle la méthode TakeHit() sur le Ghost pour gérer la réduction de vie et la destruction
			AGhost* Ghost = Cast<AGhost>(OtherActor);
			if (Ghost)
			{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("is ghost"));
				Ghost->TakeHit();  // Appelle TakeHit pour réduire la vie et ajouter au score
				UE_LOG(LogTemp, Warning, TEXT("Projectile a touché un Ghost !"));
				Destroy();  // Détruit le projectile
			}
		}
		// Vérifie si le composant touche un objet physique
		else if (OtherComp && OtherComp->IsSimulatingPhysics())
		{
			// Applique une impulsion à l'objet physique
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			Destroy();  // Détruit le projectile
		}
	}
}



