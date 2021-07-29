// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EX3_IAAnimation.generated.h"

/**
 * 
 */
UCLASS()
class EX3_IA_API UEX3_IAAnimation : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsLightAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsHeavyAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int m_NumberAttackInRow = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsHit = false;

public:
	FORCEINLINE void SetIsMoving(const bool _isMoving) { m_IsMoving = _isMoving; };
	FORCEINLINE void SetIsLightAttacking(const bool _isLightAttacking) { m_IsLightAttacking = _isLightAttacking; };
	FORCEINLINE void SetIsHeavyAttacking(const bool _isHeavyAttacking) { m_IsHeavyAttacking = _isHeavyAttacking; };
	FORCEINLINE void SetIsHit(const bool _isHit) { m_IsHit = _isHit; };

	FORCEINLINE void IncreaseCombo() { m_NumberAttackInRow++; };
	FORCEINLINE void ResetCombo() { m_NumberAttackInRow = 0; };

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndComboDelegate);
	UPROPERTY(BlueprintCallable)
		FEndComboDelegate onEndComboDelegate;

	DECLARE_EVENT(UEX3_IAAnimation, EndCombo);
	EndCombo onEndCombo;

	FORCEINLINE FEndComboDelegate* OnEndComboDelegate() { return &onEndComboDelegate; };
	FORCEINLINE EndCombo* OnEndCombo() { return &onEndCombo; };
	UFUNCTION() void EndCombo();
	
};
