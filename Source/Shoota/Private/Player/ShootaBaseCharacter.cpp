// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShootaBaseCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AShootaBaseCharacter::AShootaBaseCharacter()
{
	// Default size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->bUsePawnControlRotation = true;

	FPSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonSkeletalMesh"));
	FPSkeletalMesh->SetupAttachment(FPCameraComponent);
	FPSkeletalMesh->SetOnlyOwnerSee(true);
	FPSkeletalMesh->CastShadow = false;
	FPSkeletalMesh->bCastDynamicShadow = false;
}

// Called when the game starts or when spawned
void AShootaBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// Called every frame
void AShootaBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootaBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement action handling
		EnhancedInputComponent->BindAction(
			MoveAction, ETriggerEvent::Triggered,
			this, &AShootaBaseCharacter::Move);

		// Look up action handling
		EnhancedInputComponent->BindAction(
			LookAction, ETriggerEvent::Triggered,
			this, &AShootaBaseCharacter::Look);

		// Jump action handling
		EnhancedInputComponent->BindAction(
			JumpAction, ETriggerEvent::Triggered,
			this, &ACharacter::Jump);

		EnhancedInputComponent->BindAction(
			JumpAction, ETriggerEvent::Completed,
			this, &ACharacter::StopJumping);
	}
}

void AShootaBaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AShootaBaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookUpVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		AddControllerYawInput(LookUpVector.X);
		AddControllerPitchInput(LookUpVector.Y);
	}
}

