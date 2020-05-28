// Copyright Craig Palmer 2020


#include "TankTrack.h"

void UTankTrack::setThrottle(const float& throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("moving forward %s"), *GetOwner()->GetName());
}
