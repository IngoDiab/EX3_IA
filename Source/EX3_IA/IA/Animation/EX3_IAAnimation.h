#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EX3_IAAnimation.generated.h"

UCLASS()
class EX3_IA_API UEX3_IAAnimation : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsLightAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_IsHeavyAttacking = false;

public:
	FORCEINLINE void SetIsMoving(const bool _isMoving) { m_IsMoving = _isMoving; };
	FORCEINLINE void SetIsLightAttacking(const bool _isLightAttacking) { m_IsLightAttacking = _isLightAttacking; };
	FORCEINLINE void SetIsHeavyAttacking(const bool _isHeavyAttacking) { m_IsHeavyAttacking = _isHeavyAttacking; };

public:
	#pragma region ActivateDamage
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateDamage, bool, _activateDamage);
	UPROPERTY(BlueprintCallable)
		FActivateDamage onActivateDamage;

	FORCEINLINE FActivateDamage* OnActivateDamage() { return &onActivateDamage; };
	#pragma endregion

	#pragma region LockAI
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLockAI, bool, _lockAI);
	UPROPERTY(BlueprintCallable)
		FLockAI onLockAI;

	FORCEINLINE FLockAI* OnLockAI() { return &onLockAI; };
	#pragma endregion

	#pragma region EndCombo
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndComboDelegate);
	UPROPERTY(BlueprintCallable)
		FEndComboDelegate onEndComboDelegate;

	FORCEINLINE FEndComboDelegate* OnEndComboDelegate() { return &onEndComboDelegate; };
	#pragma endregion
};
