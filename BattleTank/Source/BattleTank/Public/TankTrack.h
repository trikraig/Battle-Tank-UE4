// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
	float trackMaxDrivingForce{40000000};
	UFUNCTION(BlueprintCallable, Category = Input)
	void setThrottle(const float& throttle);
	
};
