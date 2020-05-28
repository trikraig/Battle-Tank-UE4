// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	
	void Elevate(const float& degreesPerSecond);
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDegreesPerSecond{ 5 };
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxElevationInDegrees{ 40 }; 
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float minElevationInDegrees{ 0 }; 
	
};
