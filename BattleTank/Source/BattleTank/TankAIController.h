// Copyright Craig Palmer 2020
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "TankAIController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
    GENERATED_BODY()
private:
    ATank* controlledTank{ nullptr };
    ATank* playerTank{ nullptr };
    //min distance ai to player
    float acceptanceRadius{ 300 };
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
