#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


/**
* Patrol route used by AI
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

private:	
	UPROPERTY(EditInstanceOnly, Category="PatrolRoute")
	TArray<AActor*> PatrolPoints;

public:
	TArray<AActor*> GetPatrolPoints() const;
};
