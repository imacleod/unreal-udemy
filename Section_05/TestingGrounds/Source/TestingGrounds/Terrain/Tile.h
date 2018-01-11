#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;


UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Randomly generate and place level/tile props
	UFUNCTION(BlueprintCallable, Category="Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn=1, int MaxSpawn=1, float Radius=500, float MinScale=1, float MaxScale=1);

	UFUNCTION(BlueprintCallable, Category="Pool")
	void SetPool(UActorPool* ActorPool);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Scale);

	UActorPool* Pool;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
