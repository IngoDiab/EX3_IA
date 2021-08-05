#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_Brain.generated.h"

class AEX3_IAPawn;
class UEX3_IAAnimation;
class UEX3_FSM;
class UEX3_DetectionSystem;
class UEX3_MovementSystem;
class UEX3_CACSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_Brain : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY(EditAnywhere) UEX3_IAAnimation* m_Animations = nullptr;

	UPROPERTY(EditAnywhere) UEX3_FSM* m_FSM = nullptr;
	UPROPERTY(EditAnywhere) UEX3_DetectionSystem* m_DetectionSystem = nullptr;
	UPROPERTY(EditAnywhere) UEX3_MovementSystem* m_MovementSystem = nullptr;
	UPROPERTY(EditAnywhere) UEX3_CACSystem* m_CACSystem = nullptr;

public:
	DECLARE_EVENT(UEX3_Brain, UpdateBrain)
	UpdateBrain onUpdateBrain;

public:	
	UEX3_Brain();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE UpdateBrain* OnUpdateBrain() { return &onUpdateBrain; };

	FORCEINLINE UEX3_FSM* GetFSM() { return m_FSM; };
	FORCEINLINE UEX3_DetectionSystem* GetDetectionSystem() { return m_DetectionSystem; };
	FORCEINLINE UEX3_MovementSystem* GetMovementSystem() { return m_MovementSystem; };
	FORCEINLINE UEX3_CACSystem* GetCACSystem() { return m_CACSystem; };

public:
	void CreateComponents();
	void InitOwner();
	void InitAnimation();
	void AttachComponentsToOwner();

	void InitEventsComponents();
	void InitBrainEvents();
	void InitDetectionEvents();
	void InitMovementEvents();
	void InitCACEvents();
	void InitAnimationsNotifyEvents();

	UFUNCTION()
	void ActivateDamage(const bool _dealDamage);
	UFUNCTION()
	void LockAI(const bool _lockAI);
	UFUNCTION()
	void EndCombo();
};
