// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float MaxElevationDegrees = 40;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float MinElevationDegrees = 0;

public:
	// -1 is min downward speed, +1 is max
	void Elevate(float RelativeSpeed);
};
