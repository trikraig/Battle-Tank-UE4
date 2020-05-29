// Copyright Craig Palmer 2020

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //ensures the preexisting code executes in the parent class.
	ATank* controlledTank = GetControlledTank();
	auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (aimingComponent)
	{
		FoundAimingComponent(aimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller can't find aiming component at begin player"));
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Player Tick Test &s"), *GetControlledTank()->GetName());
	AimTowardsCrosshair();
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) 	{return;}
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	//Find the crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation(viewportSizeX*crosshairXLocation, viewportSizeY*crosshairYLocation);
	//De-project the screen position of the crosshair to a world direction / convert crosshair screen position to a world space direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection) && GetLookVectorHitLocation(lookDirection, hitLocation))
	{
		return true;
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
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
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


