// Copyright Craig Palmer 2020
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
private:

    ATank* GetControlledTank() const;
    //Start the tank moving the barrel so shot would hit where crosshair intersects the world
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& hitLocation) const;
    bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
    bool GetLookVectorHitLocation(const FVector& lookDirection, FVector& hitLocation) const;
    UPROPERTY(EditAnywhere)
    float crosshairXLocation {0.5};
    UPROPERTY(EditAnywhere)
    float crosshairYLocation {0.33333};
    UPROPERTY(EditAnywhere)
    float lineTraceRange{ 1000000 };

    
};
