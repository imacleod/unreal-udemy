// Fill out your copyright notice in the Description page of Project Settings.

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
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO: prevent doubled speed from multiple controller inputs
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO: prevent doubled speed from multiple controller inputs
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Override engine method for use in AI pathfinding
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float ForwardThrowRequired = FVector::DotProduct(AIForwardIntention, TankForwardVector);
	IntendMoveForward(ForwardThrowRequired);
}
