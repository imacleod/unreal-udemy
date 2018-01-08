#include "TestingGrounds.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	PlaceActors();
}

void ATile::PlaceActors()
{
	// Assuming 4000 x 4000 tile with origin in center of back barrier
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	for (size_t i = 0; i < 10; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		UE_LOG(LogTemp, Warning, TEXT("Random point: %s"), *SpawnPoint.ToString());
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
