// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

/// Correct tank sideways slippage
void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// Acceleration is meters per second squared
	FVector CurrentAcceleration = SlippageSpeed / DeltaTime * GetRightVector(); 
	FVector CorrectionAcceleration = -CurrentAcceleration;

	// Cast to static mesh component in order to get mass
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); 

	// Force = mass * acceleration, halve force since there are two tank tracks
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; 
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// Add OnHit event via code instead of blueprint
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	// Primitive component allows for force application
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}
