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
	JumpImpulse = 500.0f;
	DecelerationRate = 10.0f;

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


	if(bIsJumping)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentVelocity: %s"), *CurrentVelocity.ToString());
		CurrentVelocity += Gravity * DeltaTime;
	}
	AddActorLocalOffset(CurrentVelocity * DeltaTime, true);
	// xy 감속
	FVector XYVel = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0);
	FVector ZVel = FVector(0, 0, CurrentVelocity.Z);
	CurrentVelocity = FMath::VInterpTo(XYVel, FVector::ZeroVector, DeltaTime, DecelerationRate) + ZVel;
	if (IsOnGround())
	{
		UE_LOG(LogTemp, Warning, TEXT("false"));

		bIsJumping = false;
		//CurrentVelocity = FVector::ZeroVector;
		CurrentVelocity.Z = 0.0;
	}
}

void AHumanPawn::Move(const FInputActionValue& Value) 
{
	if (!Controller) return;
	MoveInput = Value.Get<FVector2D>();
	if (!MoveInput.IsNearlyZero()) 
	{
		//// Z 값 무시
		//FVector MoveOffset = FVector(MoveInput.X, MoveInput.Y, 0.0f) * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
		//AddActorLocalOffset(MoveOffset, true);

		CurrentVelocity.X = MoveInput.X * MoveSpeed;
		CurrentVelocity.Y = MoveInput.Y * MoveSpeed;
	}
}
void AHumanPawn::StartJump(const FInputActionValue& Value)
{
	if (!bIsJumping) 
	{
		bIsJumping = true;
		CurrentVelocity.Z = JumpImpulse;
	}
}
void AHumanPawn::StopJump(const FInputActionValue& Value)
{
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
