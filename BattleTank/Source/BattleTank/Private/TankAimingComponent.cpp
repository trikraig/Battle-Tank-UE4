// Copyright Craig Palmer 2020

#include "..\Public\TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	barrel = barrelToSet;
	turret = turretToSet;
}

void UTankAimingComponent::AimAt(const FVector& hitLocation)
{
	if (!ensure(barrel)) { return; }
	FVector outLaunchVelocity(0);
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	));
	if(bHaveAimSolution)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal(); //Turns into a unit vector
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - lastFireTime) > reloadTimeInSeconds;
	if (!ensure(barrel && projectileBlueprint)) { return; }
	if (isReloaded)
	{
		//Spawn projectile at socket location on the barrel
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}


void UTankAimingComponent::MoveBarrelTowards(const FVector& aimDirection)
{
	if (!ensure(barrel &&turret)) { return; }
	// Work out difference between current barrel rotation and aim direction
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;
	turret->Rotate(deltaRotator.Yaw);
	barrel->Elevate(deltaRotator.Pitch); 
}

