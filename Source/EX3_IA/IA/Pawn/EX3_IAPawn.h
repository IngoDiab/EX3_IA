#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EX3_IAPawn.generated.h"

class UEX3_Brain;

class UCapsuleComponent;
class UBoxComponent;
class UArrowComponent;
class UFloatingPawnMovement;

UCLASS()
class EX3_IA_API AEX3_IAPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) UEX3_Brain* m_Brain = nullptr;
	UPROPERTY(EditAnywhere) USceneComponent* m_EyesLocation = nullptr;

	UPROPERTY(EditAnywhere) UCapsuleComponent* m_CapsuleComponent = nullptr;
	UPROPERTY(EditAnywhere) UBoxComponent* m_WeaponCollider = nullptr;
	UPROPERTY(EditAnywhere) UArrowComponent* m_ArrowComponent = nullptr;
	UPROPERTY(EditAnywhere) USkeletalMeshComponent* m_Mesh = nullptr;
	UPROPERTY(EditAnywhere) UFloatingPawnMovement* m_PawnMovement = nullptr;

	//FIX RM
	UPROPERTY(EditAnywhere) bool needRotateRM = true;

public:
	AEX3_IAPawn();

	void PostInitProperties() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE UEX3_Brain* GetBrain() const { return m_Brain; };
	FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return m_Mesh; };
	FORCEINLINE USceneComponent* GetEyesLocation() const { return m_EyesLocation; };
	FORCEINLINE UBoxComponent* GetWeaponCollider() const { return m_WeaponCollider; };

public:
	void CreateBrain();
	void CreateComponents();
	void CreateComponentsRelativeToCapsule();
	void CreateComponentsRelativeToMesh();

	void Gravity();

	void RootMotion();
	float GetScaledCapsuleHalfHeight() const;
};
