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
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//So that first fire is after initial reload
	lastFireTime = GetWorld()->GetTimeSeconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ammoRemaining <= 0)
	{
		firingStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}

	
}


void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	barrel = barrelToSet;
	turret = turretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return firingStatus;
}

int32 UTankAimingComponent::GetAmmoRemaining() const
{
	return ammoRemaining;
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
	if (bHaveAimSolution)
	{
		aimDirection = outLaunchVelocity.GetSafeNormal(); //Turns into a unit vector
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::Fire()
{
	if (firingStatus == EFiringStatus::Locked || firingStatus == EFiringStatus::Aiming)
	{

		if (!ensure(barrel)) { return; }
		if (!ensure(projectileBlueprint)) { return; }

		UE_LOG(LogTemp, Warning, TEXT("Firing Status: %i"), firingStatus);
		//Spawn projectile at socket location on the barrel
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = GetWorld()->GetTimeSeconds();
		ammoRemaining--;			
	}
}


void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(barrel &&turret)) { return; }
	// Work out difference between current barrel rotation and aim direction
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;
	barrel->Elevate(deltaRotator.Pitch); 
	//Always yaw the shortest way
	if (FMath::Abs(deltaRotator.Yaw) < 180)
	{
		turret->Rotate(deltaRotator.Yaw);
	}
	else
	{
		turret->Rotate(-deltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(barrel)) { return false; }
	return !(barrel->GetForwardVector().Equals(aimDirection, 0.01));
}

