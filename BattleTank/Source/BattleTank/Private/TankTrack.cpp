// Copyright Craig Palmer 2020


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("test"));
	//calculate the slippage speed
	float slippageSpeed = FVector().DotProduct(GetRightVector(), GetComponentVelocity());
	//work out the required acceleration this frame to correct
	FVector correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
	//calculate and apply sideways force (F = m a)
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAcceleration / 2; //divide by 2 as two tracks
	tankRoot->AddForce(correctionForce);

}

void UTankTrack::setThrottle(const float& throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("moving forward %s"), *GetOwner()->GetName());
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("GROUND HIT TEST"));
}

