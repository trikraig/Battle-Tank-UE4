// Copyright Craig Palmer 2020


#include "TankBarrel.h"

void UTankBarrel::Elevate(const float& relativeSpeed)
{
	float speed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	float elevationChange = speed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float elevation = FMath::Clamp<float>(rawNewElevation, minElevationInDegrees, maxElevationInDegrees);
	SetRelativeRotation(FRotator(elevation, 0, 0));
}
