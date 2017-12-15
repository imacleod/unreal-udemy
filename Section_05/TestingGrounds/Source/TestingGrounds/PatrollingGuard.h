#pragma once

#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
public:  // TODO: remove public or create getter
	UPROPERTY(EditInstanceOnly, Category="PatrolRoute")
	TArray<AActor*> PatrolPointsCPP;
};
