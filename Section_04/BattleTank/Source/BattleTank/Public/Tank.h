// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class AProjectile;
class UTankBarrel;
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

	// TODO: remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float ReloadTimeInSeconds = 3;

public:
	UFUNCTION(BlueprintCallable, Category="Firing")
	void Fire();
};
