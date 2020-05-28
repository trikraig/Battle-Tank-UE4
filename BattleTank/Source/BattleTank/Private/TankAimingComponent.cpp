// Copyright Craig Palmer 2020


//#include "TankAimingComponent.h"
#include "..\Public\TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}



void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	if (!barrelToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("No barrel reference set!"));
		return;
	}
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	if (!turretToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("No turre reference set!"));
		return;
	}
	turret = turretToSet;
}

void UTankAimingComponent::AimAt(const FVector& hitLocation, const float& launchSpeed)
{
	if (!barrel) {
		UE_LOG(LogTemp, Error, TEXT("No barrel Found"));
		return; 
	
	}
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

void UTankAimingComponent::MoveBarrelTowards(const FVector& aimDirection)
{
	// Work out difference between current barrel rotation and aim direction
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;
	turret->Rotate(deltaRotator.Yaw);
	barrel->Elevate(deltaRotator.Pitch); 
}

