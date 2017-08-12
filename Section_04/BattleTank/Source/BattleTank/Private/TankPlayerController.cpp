
#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location of location through crosshair
	// If linetrace hits landscape tell controlled tank to aim at this point
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

void ATankPlayerController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	AimTowardsCrosshair();
}
