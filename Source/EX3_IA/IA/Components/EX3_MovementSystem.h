#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_MovementSystem.generated.h"

class AEX3_IAPawn;
class UEX3_Brain;
class AAIController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_MovementSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) AAIController* m_Controller = nullptr;
	UPROPERTY(VisibleAnywhere) AEX3_IAPawn* m_Owner = nullptr;

	UPROPERTY(VisibleAnywhere) FVector m_PosToMove = FVector(0);
	UPROPERTY(VisibleAnywhere) TArray<FVector> m_Path;
	UPROPERTY(EditAnywhere) bool m_CanMove = true;
	UPROPERTY(EditAnywhere) bool m_CanRotate = true;
	UPROPERTY(EditAnywhere) float m_SpeedRotate = 1000;
	UPROPERTY(EditAnywhere) float m_MinDist = 100;

public:
	DECLARE_EVENT(UEX3_MovementSystem, MovingToPos)
	MovingToPos onMoveToPos;
	
	DECLARE_EVENT(UEX3_MovementSystem, PosReached)
	PosReached onPosReached;

public:	
	UEX3_MovementSystem();

protected:
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE MovingToPos* OnMoveToPos() { return &onMoveToPos; };
	FORCEINLINE PosReached* OnPosReached() { return &onPosReached; };
	FORCEINLINE void SetPosToMove(const FVector _pos) { m_PosToMove = _pos; };
	FORCEINLINE void SetCanMove(const bool _canMove) { m_CanMove = _canMove; };
	FORCEINLINE void SetCanRotate(const bool _canRotate) { m_CanRotate = _canRotate; };
	FORCEINLINE void SetMinDist(const float _minDist) { m_MinDist = _minDist; };

public:
	void InitComponent();
	bool IsAtPos();

	void UpdateMovementSystem();

	void MoveToPos();
	void RotateToPos();

	void GoToPos();
	void Stop();
};
