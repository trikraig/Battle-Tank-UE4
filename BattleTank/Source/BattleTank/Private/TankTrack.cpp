// Copyright Craig Palmer 2020


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	//aka Simulation Generation Hit Events in Collision section. Keeps getting unset when compile C++.
	SetNotifyRigidBodyCollision(true);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("on hit"));
	DriveTracks();
	ApplySidewaysForce();
	currentThrottle = 0;
}

void UTankTrack::SetThrottle(const float& throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTracks()
{
	FVector forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	//calculate the slippage speed
	float slippageSpeed = FVector().DotProduct(GetRightVector(), GetComponentVelocity());
	//work out the required acceleration this frame to correct
	FVector correctionAcceleration = -slippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	//calculate and apply sideways force (F = m a)
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAcceleration / 2; //divide by 2 as two tracks
	tankRoot->AddForce(correctionForce);
}


