

#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"

void ABaseCharacter::ChangeView()
{
	if (ViewSetting == ECameraViewPoints::TP)
	{
		ChangeToFPView();
	}
	else
	{
		ChangeToTPView();
	}
}

void ABaseCharacter::ChangeToFPView()
{
	TPCamera->SetActive(false);
	FPCamera->SetActive(true);
	// 카메라 위치 조정
	SpringArm->TargetArmLength = 0.f;

	// 카메라가 arm에 의해 회전하지 않음
	SpringArm->bUsePawnControlRotation = false;

	FPCamera->bUsePawnControlRotation = true;
	FRotator CameraRotation = FRotator(270.f, 0.f, 90.f);
	FPCamera->SetRelativeRotation(CameraRotation);

	GetMesh()->SetOwnerNoSee(true);

	ViewSetting = ECameraViewPoints::FP;

}

void ABaseCharacter::ChangeToTPView()
{
	FPCamera->SetActive(false);
	TPCamera->SetActive(true);
	//카메라 위치 조정
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	TPCamera->SetupAttachment(SpringArm); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	TPCamera->SetRelativeLocation(CameraDefaultLocation);

	GetMesh()->SetOwnerNoSee(false);
	ViewSetting = ECameraViewPoints::TP;
}

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	DefaultSpeed = GetCharacterMovement()->MaxWalkSpeed;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));


	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	TPCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SpringArm->bUsePawnControlRotation = true;

	TPCamera->SetupAttachment(SpringArm); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	TPCamera->SetRelativeLocation(CameraDefaultLocation);

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetMesh(), FName("head"));

	GetMesh()->SetOwnerNoSee(false);
	ViewSetting = ECameraViewPoints::TP;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInput{ Cast<UEnhancedInputComponent>(PlayerInputComponent) };
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Input_OnLookMouse);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Input_OnLook);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Input_OnMove);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &ABaseCharacter::Input_OnSprint);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &ABaseCharacter::Input_OnSprint_End);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Started, this, &ABaseCharacter::Input_OnWalk);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Completed, this, &ABaseCharacter::Input_OnWalk_End);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Input_OnJump);
		EnhancedInput->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Input_OnViewMode);
	}


}

void ABaseCharacter::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	const auto Value{ ActionValue.Get<FVector2D>() };

	AddControllerPitchInput(Value.Y * LookUpMouseSensitivity);
	AddControllerYawInput(Value.X * LookRightMouseSensitivity);

}

void ABaseCharacter::Input_OnLook(const FInputActionValue& ActionValue)
{
	const auto Value{ ActionValue.Get<FVector2D>() };

	AddControllerPitchInput(Value.Y * LookUpRate);
	AddControllerYawInput(Value.X * LookRightRate);

}

void ABaseCharacter::Input_OnMove(const FInputActionValue& ActionValue)
{
	// input is a Vector2D
	FVector2D MovementVector = ActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void ABaseCharacter::Input_OnSprint(const FInputActionValue& ActionValue)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ABaseCharacter::Input_OnSprint_End(const FInputActionValue& ActionValue)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}


void ABaseCharacter::Input_OnWalk(const FInputActionValue& ActionValue)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ABaseCharacter::Input_OnWalk_End(const FInputActionValue& ActionValue)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
}



void ABaseCharacter::Input_OnJump(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		Jump();
	}
	else
	{
		StopJumping();
	}

}

void ABaseCharacter::Input_OnViewMode(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		ChangeView();
	}
}

