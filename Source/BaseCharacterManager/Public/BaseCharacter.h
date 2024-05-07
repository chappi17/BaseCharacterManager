// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;


// ĳ���� ����
UENUM()
enum class ECameraViewPoints :uint8
{
	FP UMETA(DisplayName = "FirstPerson"),
	TP UMETA(DisplayName = "ThirdPerson")
};

UCLASS()
class BASECHARACTERMANAGER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


protected:

	// ī�޶� ����
	// 3��Ī ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	TObjectPtr<UCameraComponent> TPCamera;
	
	// 1��Ī ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	TObjectPtr<UCameraComponent> FPCamera;

	// ������ ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	ECameraViewPoints ViewSetting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	FVector CameraDefaultLocation;
	// ~ī�޶� ����

	// Input ����
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> LookMouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> WalkAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> JumpAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSetting", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ViewModeAction;
	// ~Input ����

	// ȭ�� ȸ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookUpMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookRightMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookUpRate{90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookRightRate{240.0f};
	// ~ȭ�� ȸ�� ����

	// �⺻ Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed{ 200.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed{ 600.0f };

	//~�⺻ Movement Speed

	// �þ� ���� ���
	UFUNCTION(BlueprintCallable, Category = "Camera View Point")
	void ChangeView();

	UFUNCTION()
	void ChangeToFPView();
	
	UFUNCTION()
	void ChangeToTPView();

public:
	ABaseCharacter();

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Input_OnLookMouse(const FInputActionValue& ActionValue);

	void Input_OnLook(const FInputActionValue& ActionValue);

	void Input_OnMove(const FInputActionValue& ActionValue);

	void Input_OnSprint(const FInputActionValue& ActionValue);
	
	void Input_OnSprint_End(const FInputActionValue& ActionValue);
	

	void Input_OnWalk(const FInputActionValue& ActionValue);
	
	void Input_OnWalk_End(const FInputActionValue& ActionValue);

	void Input_OnJump(const FInputActionValue& ActionValue);

	void Input_OnViewMode(const FInputActionValue& ActionValue);




};
