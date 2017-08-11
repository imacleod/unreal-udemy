
#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Debugging
	UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay..."));
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController GetControlledTank: None"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController GetControlledTank: %s"), *(controlledTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
