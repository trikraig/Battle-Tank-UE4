// Copyright Craig Palmer 2020

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(const float& amountThrow)
{
	if (leftTrack && rightTrack)
	{
		leftTrack->setThrottle(amountThrow);
		rightTrack->setThrottle(amountThrow);
	}
}

void UTankMovementComponent::IntendTurnRight(const float& amountThrow)
{
	if (!leftTrack || !rightTrack)
	{
		leftTrack->setThrottle(amountThrow);
		rightTrack->setThrottle(-amountThrow);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//no need to call super as replacing the functionality
	FVector tankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	IntendMoveForward(FVector::DotProduct(tankFoward, aiForwardIntention));
	IntendTurnRight((FVector::CrossProduct(tankFoward, aiForwardIntention)).Z);
}

