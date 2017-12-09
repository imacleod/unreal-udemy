#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

// Currently depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		// Subscribe to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);
	UpdateViewPoint();

	// Aim towards player, fire if player is visible and locked on
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (bIsPlayerVisible(AimingComponent) && AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

bool ATankAIController::bIsPlayerVisible(UTankAimingComponent* AimingComponent)
{
	FVector LineTraceEnd = PossessedTankLocation + (AimingComponent->GetAimDirection() * LineTraceRange);
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetPawn()); // Ignore possessed tank

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PossessedTankLocation,
		LineTraceEnd,
		ECollisionChannel::ECC_Pawn,
		TraceParams)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ATankAIController::UpdateViewPoint()
{
	this->GetPlayerViewPoint(PossessedTankLocation, PossessedTankRotation);
}
