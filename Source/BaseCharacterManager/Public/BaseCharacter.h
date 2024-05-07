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


// 캐릭터 시점
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

	// 카메라 세팅
	// 3인칭 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	TObjectPtr<UCameraComponent> TPCamera;
	
	// 1인칭 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	TObjectPtr<UCameraComponent> FPCamera;

	// 스프링 암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	ECameraViewPoints ViewSetting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	FVector CameraDefaultLocation;
	// ~카메라 세팅

	// Input 세팅
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
	// ~Input 세팅

	// 화면 회전 세팅
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookUpMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookRightMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookUpRate{90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputSetting", Meta = (ClampMin = 0))
	float LookRightRate{240.0f};
	// ~화면 회전 세팅

	// 기본 Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed{ 200.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed{ 600.0f };

	//~기본 Movement Speed

	// 시야 변경 기능
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
