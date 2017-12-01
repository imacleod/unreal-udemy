// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank track on ground..."));
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	// Primitive component allows for force application
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// Correct tank sideways slippage speed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CurrentAcceleration = SlippageSpeed / DeltaTime * GetRightVector(); // acceleration is meters per second squared
	FVector CorrectionAcceleration = -CurrentAcceleration;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // need mass from static mesh component
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // force = mass * acceleration, two tank tracks
	TankRoot->AddForce(CorrectionForce);
}
