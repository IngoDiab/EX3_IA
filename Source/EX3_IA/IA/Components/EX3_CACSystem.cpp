#include "EX3_CACSystem.h"

#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"

#include "Components/BoxComponent.h" 	
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UEX3_CACSystem::UEX3_CACSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEX3_CACSystem::BeginPlay()
{
	Super::BeginPlay();
	GetWeaponCollider();
}

void UEX3_CACSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 
	//ApplyDamage();
}

void UEX3_CACSystem::GetWeaponCollider()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	if (!m_Owner)return;
	m_WeaponCollider = m_Owner->GetWeaponCollider();
	if (!m_WeaponCollider)return;
	m_WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &UEX3_CACSystem::OnWeaponColliderOverlap);
	m_WeaponCollider->OnComponentEndOverlap.AddDynamic(this, &UEX3_CACSystem::OnWeaponColliderEndOverlap);
}

void UEX3_CACSystem::OnWeaponColliderOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	ACharacter* _character = Cast<ACharacter>(_otherActor);
	if (!_character)return;
	m_CharacterToDamage.Add(_character);
	/*if (!m_CanDealDamage) return;
	ACharacter* _character = Cast<ACharacter>(_otherActor);
	if (!_character)return;
	const FVector _knockbackForce = _character->GetActorForwardVector() * -100 + _character->GetActorUpVector() * 200;
	_character->LaunchCharacter(_knockbackForce, true, true);*/
}

void UEX3_CACSystem::OnWeaponColliderEndOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	ACharacter* _character = Cast<ACharacter>(_otherActor);
	if (!_character)return;
	m_CharacterToDamage.Remove(_character);
}

void UEX3_CACSystem::ChooseTypeAttack()
{
	const float _randomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 100);
	if (_randomNumber <= m_PercentHeavyAttack)
		m_IsHeavyAttacking = true;
	else
		m_IsLightAttacking = true;
}

void UEX3_CACSystem::Attack()
{
	if (m_IsLightAttacking) onLightAttackCombo.Broadcast();
	else if (m_IsHeavyAttacking) onHeavyAttackCombo.Broadcast();
}

void UEX3_CACSystem::ActivateDamage(const bool _dealDamage)
{
	m_CanDealDamage = _dealDamage;
	if (_dealDamage) return;
	m_CharacterToDamage.Empty();
	m_CharacterTouched.Empty();
}

void UEX3_CACSystem::ApplyDamage()
{
	if (!m_CanDealDamage || !m_Owner || m_CharacterToDamage.Num() == 0) return;
	for (ACharacter* _character : m_CharacterToDamage) 
	{
		FVector _knockbackForce = _character->GetActorLocation() - m_Owner->GetActorLocation();
		_knockbackForce.Normalize();
		_knockbackForce *= m_KnockbackForce;
		_character->LaunchCharacter(_knockbackForce, true, true);
	}
}

void UEX3_CACSystem::ResetCombo()
{
	onEndCombo.Broadcast();
}

