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
	UE_LOG(LogTemp, Warning, TEXT("Tank death :/"));
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(ControlledTank && PlayerTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards player, fire if locked on
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}
