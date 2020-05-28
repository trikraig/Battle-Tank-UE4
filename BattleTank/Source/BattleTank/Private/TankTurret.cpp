// Copyright Craig Palmer 2020


#include "TankTurret.h"

void UTankTurret::Rotate(const float& relativeSpeed)
{
	float speed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	//move the barrel the right amount this frame
	//given a max elevation speed, and the frame time.
	float rotationChange = speed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0,newRotation,0));
}

