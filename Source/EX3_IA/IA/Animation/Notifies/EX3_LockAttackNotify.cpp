#include "EX3_LockAttackNotify.h"

#include "EX3_IA/IA/Animation/EX3_IAAnimation.h"

void UEX3_LockAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UEX3_IAAnimation* _animInstance = Cast<UEX3_IAAnimation>(MeshComp->GetAnimInstance());
	if (!_animInstance) return;
	_animInstance->OnLockAI()->Broadcast(m_LockAI);
}