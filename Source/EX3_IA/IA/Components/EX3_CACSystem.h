#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_CACSystem.generated.h"

class ACharacter;
class AEX3_IAPawn;
class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_CACSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY() AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY() UBoxComponent* m_WeaponCollider = nullptr;

	UPROPERTY(VisibleAnywhere) TArray<ACharacter*> m_CharacterTouched = TArray<ACharacter*>();
	UPROPERTY(VisibleAnywhere) TArray<ACharacter*> m_CharacterToDamage = TArray<ACharacter*>();
	UPROPERTY(VisibleAnywhere) bool m_IsLightAttacking = false;
	UPROPERTY(VisibleAnywhere) bool m_IsHeavyAttacking = false;
	UPROPERTY(EditAnywhere) float m_PercentHeavyAttack = 50;
	UPROPERTY(EditAnywhere) float m_KnockbackForce = 300;

	UPROPERTY(VisibleAnywhere) bool m_CanDealDamage = false;
	UPROPERTY(VisibleAnywhere) bool m_WeaponTouchPlayer = false;

public:
	DECLARE_EVENT(UEX3_CACSystem, HeavyAttackCombo)
	HeavyAttackCombo onHeavyAttackCombo;

	DECLARE_EVENT(UEX3_CACSystem, LightAttackCombo)
	LightAttackCombo onLightAttackCombo;

	DECLARE_EVENT(UEX3_CACSystem, EndCombo)
	EndCombo onEndCombo;

public:
	FORCEINLINE HeavyAttackCombo* OnHeavyAttackCombo() { return &onHeavyAttackCombo; };
	FORCEINLINE LightAttackCombo* OnLightAttackCombo() { return &onLightAttackCombo; };
	FORCEINLINE EndCombo* OnEndCombo() { return &onEndCombo; };

	FORCEINLINE void SetHeavyAttacking(const bool _isHeavyAttacking) { m_IsHeavyAttacking = _isHeavyAttacking; };
	FORCEINLINE void SetLightAttacking(const bool _isLightAttacking) { m_IsLightAttacking = _isLightAttacking; };


public:	
	UEX3_CACSystem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void GetWeaponCollider();
	UFUNCTION()
	void OnWeaponColliderOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	void OnWeaponColliderEndOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	void ChooseTypeAttack();
	void Attack();

	void ActivateDamage(const bool _dealDamage);
	void ApplyDamage();

	void ResetCombo();
};
