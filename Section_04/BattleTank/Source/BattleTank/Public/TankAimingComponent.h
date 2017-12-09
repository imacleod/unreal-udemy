#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Aiming state
UENUM()
enum class EFiringState : uint8
{
	Aiming, Locked, OutOfAmmo, Reloading
};

// Forward declaration, useful when reference to class is needed but not for inheritance or calling methods
class AProjectile;
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

	FVector AimDirection;

	UTankBarrel* Barrel = nullptr;

	virtual void BeginPlay() override;

	bool IsBarrelMoving();

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float LaunchSpeed = 4000;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category="Firing")
	int32 RoundsLeft = 3;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankTurret* Turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category="State")
	EFiringState FiringState = EFiringState::Reloading;

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Firing")
	void Fire();

	FVector GetAimDirection() const;

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category="Firing")
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
};
