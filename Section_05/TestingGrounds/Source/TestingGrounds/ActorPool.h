#pragma once

#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<AActor*> Pool;

public:	
	// Sets default values for this component's properties
	UActorPool();

	void Add(AActor* ActorToAdd);

	AActor* Checkout();

	void Return(AActor* ActorToReturn);
};
