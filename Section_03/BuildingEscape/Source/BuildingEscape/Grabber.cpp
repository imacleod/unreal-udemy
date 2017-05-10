// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Initialize input
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

// Draw red trace line to visualize player reach length
void UGrabber::DrawDebugLineTrace()
{
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);
}

/// Confirm required components are attached
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandleComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found PhysicsHandleComponent for %s"), *(GetOwner()->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing PhysicsHandleComponent for %s"), *(GetOwner()->GetName()));
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Construct query parameters for simple collision
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Line trace/ray cast out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	/// Debug hit detection
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
	return HitResult;
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("UGrabber grab"));

	/// Attempt line trace to reach actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// On successful hit attach physics handle
	if (ActorHit) {
		PhysicsHandleComponent->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("UGrabber release"));
	PhysicsHandleComponent->ReleaseComponent();
}

/// InputComponent is attached at runtime
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found InputComponent for %s"), *(GetOwner()->GetName()));

		/// Bind input actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing InputComponent for %s"), *(GetOwner()->GetName()));
	}
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UpdatePlayerViewPoint();

	LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * PlayerReach);

	if (PhysicsHandleComponent->GrabbedComponent) {
		PhysicsHandleComponent->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::UpdatePlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
}
