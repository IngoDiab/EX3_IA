#pragma once

#include "CoreMinimal.h"
#include "EX3_Transition.h"
#include "EX3_Chase_To_Wait.generated.h"

class UEX3_MovementSystem;

UCLASS()
class EX3_IA_API UEX3_Chase_To_Wait : public UEX3_Transition
{
	GENERATED_BODY()

	UPROPERTY() UEX3_MovementSystem* m_MoveSystem = nullptr;

public:
	void InitTransition(UEX3_Brain& _brain, UEX3_State& _nextState) override;

	void EnterTransition() const override;
	void ExitTransition() const override;

	bool CheckCondition() const override;
	
};
