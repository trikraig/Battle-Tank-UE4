// Copyright Craig Palmer 2020

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //ensures the preexisting code executes in the parent class.
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }
	FoundAimingComponent(aimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		//Subscribe our local method to tanks death event.
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Tank Destroyed"));
	StartSpectatingOnly();
	//Get enemy tanks to stop?
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!(GetPawn())) { return; } // e.g. if not possessing so not using ensure
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		aimingComponent->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	//Find the crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);
	//De-project the screen position of the crosshair to a world direction / convert crosshair screen position to a world space direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		return GetLookVectorHitLocation(lookDirection, hitLocation);
	}
	//Missed 
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& lookDirection, FVector& hitLocation) const
{
	//Line trace out in Look Direction by Range
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (lookDirection * lineTraceRange);
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Camera))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector worldLocation; //will be discarded.
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, lookDirection))
	{
		return true;
	}
	//GetLookDirection failed
	UE_LOG(LogTemp, Error, TEXT("GetLookDirection not found in TankPlayerController"));
	return false;
}


