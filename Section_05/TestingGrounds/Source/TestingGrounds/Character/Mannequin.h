#pragma once

#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class AGun;


UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

private:
	// Create a CameraComponent	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	AGun* Gun;

	// For first person view (arms seen only by self)
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AMannequin();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void PullTrigger();

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<class AGun> GunBlueprint;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};
