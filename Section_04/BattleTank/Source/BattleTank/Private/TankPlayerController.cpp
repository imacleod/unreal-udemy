
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // Player may not be possessing tank during runtime
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation))
	{
		AimingComponent->AimAt(OutHitLocation);
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Required, unused
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}

/// Get world location of linetrace through crosshair, true on landscape hit
bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{
	// Find crosshair position in viewport coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project screen position to world direction
	FVector OutLookDirection;
	if (GetLookDirection(ScreenLocation, OutLookDirection))
	{
		// Linetrace along that look direction, check for hit up to max range
		GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
	}

	return true;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}
