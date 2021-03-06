#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EX3_Transition.generated.h"

class UEX3_State;
class UEX3_Brain;
class UEX3_FSM;

UCLASS(ABSTRACT)
class EX3_IA_API UEX3_Transition : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY() UEX3_Brain* m_Brain;
	UPROPERTY() UEX3_FSM* m_FSM;
	UPROPERTY(VisibleAnywhere) UEX3_State* m_NextState;

public:
	FORCEINLINE UEX3_State* GetNextState() const { return m_NextState; };

public:
	virtual void InitTransition(UEX3_Brain& _brain, UEX3_State& _nextState);

	virtual void EnterTransition() const PURE_VIRTUAL(UEX3_Transition::EnterTransition, );
	virtual void ExitTransition() const PURE_VIRTUAL(UEX3_Transition::ExitTransition, );

	virtual bool CheckCondition() const PURE_VIRTUAL(UEX3_Transition::CheckCondition, return false;);
};
