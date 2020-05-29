// Copyright Craig Palmer 2020

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "Engine/World.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector& hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed); 
}

void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - lastFireTime) > reloadTimeInSeconds;
	if (barrel && isReloaded)
	{
		//Spawn projectile at socket location on the barrel
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}
