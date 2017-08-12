
#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		// If linetrace hits landscape tell controlled tank to aim at this point
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Debugging
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay..."));
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController GetControlledTank: None"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController GetControlledTank: %s"), *(controlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Required, unused
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

/// Get world location of linetrace through crosshair, true on landscape hit
bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{
	// Find crosshair position in viewport coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project screen position to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController GetSightRayHitLocation: %s"), *(LookDirection.ToString()));
	}

	// Linetrace along that look direction, check for hit up to max range

	return true;
}

void ATankPlayerController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	AimTowardsCrosshair();
}
