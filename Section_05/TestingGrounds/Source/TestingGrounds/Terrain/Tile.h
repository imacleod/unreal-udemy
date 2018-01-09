#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Randomly generate and place level/tile props
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool CastSphere(FVector Location, float Radius);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
