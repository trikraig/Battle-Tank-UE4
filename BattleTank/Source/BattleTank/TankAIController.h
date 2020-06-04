// Copyright Craig Palmer 2020
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Controls aiming and movement of AI tanks
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
    GENERATED_BODY()

protected:
    //min distance ai to player
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float acceptanceRadius{ 8000 };

private:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    void AimTowardsPlayer();

    virtual void SetPawn(APawn* InPawn) override;

    UFUNCTION()
    void OnPossessedTankDeath();
};
