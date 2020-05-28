// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Rotate(const float& relativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond{ 25 };
};
