// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class AProjectile;
class UTankAimingComponent;
class UTankBarrel;
class UTankMovementComponent;
class UTankTurret;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// Local barrel reference for spawning projectiles (lesson 150)
	UTankBarrel* Barrel = nullptr; // TODO: remove after finishing aiming component refactor

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float ReloadTimeInSeconds = 3;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Input")
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Input")
	UTankMovementComponent* TankMovementComponent = nullptr;

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Firing")
	void Fire();
};
