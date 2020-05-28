// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 *  Driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BluePrintCallable, Category = "Setup")
	void Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);
	UFUNCTION(BluePrintCallable, Category = "Movement")
	void IntendMoveForward(const float& amountThrow);
	UFUNCTION(BluePrintCallable, Category = "Movement")
	void IntendTurnRight(const float& amountThrow);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;

};
