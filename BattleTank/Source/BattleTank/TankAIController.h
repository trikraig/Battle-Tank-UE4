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
private:
    //min distance ai to player
    float acceptanceRadius{ 50 };
    void AimTowardsPlayer();
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
