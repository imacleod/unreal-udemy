// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

// Forward declarations
class UProjectileMovementComponent;


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float Speed);

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
