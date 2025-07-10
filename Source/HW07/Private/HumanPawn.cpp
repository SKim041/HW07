// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPawn.h"
#include "EnhancedInputComponent.h"
#include "HW07PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"


AHumanPawn::AHumanPawn() 
{
	NormalSpeed = 600.0f;
	MoveSpeed = NormalSpeed;
	SprintMultiplier = 1.7f;
	MouseSensitivity = 1.0f;
}

void AHumanPawn::BeginPlay() 
{
	Super::BeginPlay();
}

void AHumanPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		if (AHW07PlayerController* PlayerController = Cast<AHW07PlayerController>(GetController())) 
		{
			if (PlayerController->HumanMoveAction) 
			{
				EnhancedInput->BindAction(
					PlayerController->HumanMoveAction,
					ETriggerEvent::Triggered,
					this,
					&AHumanPawn::Move
				);
			}
			if (PlayerController->HumanLookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HumanLookAction,
					ETriggerEvent::Triggered,
					this,
					&AHumanPawn::Look
				);
			}
			if (PlayerController->HumanJumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HumanJumpAction,
					ETriggerEvent::Triggered,
					this,
					&AHumanPawn::StartJump
				);
			}
			if (PlayerController->HumanJumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HumanJumpAction,
					ETriggerEvent::Completed,
					this,
					&AHumanPawn::StopJump
				);
			}
			if (PlayerController->HumanSprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HumanSprintAction,
					ETriggerEvent::Triggered,
					this,
					&AHumanPawn::StartSprint
				);
			}
			if (PlayerController->HumanSprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HumanSprintAction,
					ETriggerEvent::Completed,
					this,
					&AHumanPawn::StopSprint
				);
			}
		}
	}
}

// Called every frame
void AHumanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHumanPawn::Move(const FInputActionValue& Value) 
{
	if (!Controller) return;
	MoveInput = Value.Get<FVector2D>();
	if (!MoveInput.IsNearlyZero()) 
	{
		// Z °ª ¹«½Ã
		FVector MoveOffset = FVector(MoveInput.X, MoveInput.Y, 0.0f) * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalOffset(MoveOffset, true);
	}
}
void AHumanPawn::StartJump(const FInputActionValue& Value)
{
	bIsJumping = true;
	if (IsOnGround()) 
	{
		
	}
}
void AHumanPawn::StopJump(const FInputActionValue& Value)
{
	bIsJumping = false;
}
void AHumanPawn::Look(const FInputActionValue& Value)
{
	LookInput = Value.Get<FVector2D>();

	FRotator SpringArmRotation = SpringArmComp->GetRelativeRotation();
	SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch + LookInput.Y * MouseSensitivity, -70.0f, 70.0f);

	SpringArmComp->SetRelativeRotation(SpringArmRotation);
	AddActorLocalRotation(FRotator(0, LookInput.X * MouseSensitivity, 0));
}
void AHumanPawn::StartSprint(const FInputActionValue& Value)
{
	bIsSprinting = true;
	MoveSpeed = NormalSpeed * SprintMultiplier;
}
void AHumanPawn::StopSprint(const FInputActionValue& Value)
{
	bIsSprinting = false;
	MoveSpeed = NormalSpeed;
}
