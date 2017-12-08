#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Override engine method for use in AI pathfinding
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ForwardThrowRequired = FVector::DotProduct(AIForwardIntention, TankForwardVector);
	FVector RightThrowRequired = FVector::CrossProduct(AIForwardIntention, TankForwardVector);
	IntendMoveForward(ForwardThrowRequired);
	IntendTurnRight(RightThrowRequired.Z);
}
