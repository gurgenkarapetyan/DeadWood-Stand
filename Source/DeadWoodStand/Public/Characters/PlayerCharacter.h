// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class DEADWOODSTAND_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	/** Movement input handlers */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void ToggleCrouch();

private:
	void EnableStaminaRecovery();
	
protected:
	/** Mapping context and actions */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;
		
	/** Spring arm that positions the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
private:
	float WalkSpeed;
	float SprintSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (AllowPrivateAccess))
	float MaxStamina = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess))
	float CurrentStamina = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (AllowPrivateAccess))
	float StaminaDrainRate = 25.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (AllowPrivateAccess))
	float StaminaRecoveryRate = 15.f;
	
	bool bIsSprinting;
	
	FTimerHandle StaminaRecoveryTimerHandle;
	
	bool bCanRecoverStamina = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float StaminaRecoveryDelay = 7.f;
};
