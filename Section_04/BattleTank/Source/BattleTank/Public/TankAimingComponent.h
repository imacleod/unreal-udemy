// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Aiming state
UENUM()
enum class EFiringState : uint8
{
	Aiming, Locked, Reloading
};

// Forward declaration, useful when reference to class is needed but not for inheritance or calling methods
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	void MoveBarrelTowards(FVector AimDirection);

	UTankTurret* Turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category="State")
	EFiringState FiringState = EFiringState::Aiming;

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
};
