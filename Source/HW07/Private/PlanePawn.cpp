// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanePawn.h"
#include "EnhancedInputComponent.h"
#include "HW07PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

APlanePawn::APlanePawn() 
{
	NormalSpeed = 600.0f;
	MaxSpeed = 1000.0f;
	MaxSpeedInAir = MaxSpeed * 0.5;
	MouseSensitivity = 1.0f;
	// ���� ���ӵ�
	ThrustAccel = 2000.0f;
	DecelerationRate = 1.0f;
	CurrentVelocity = FVector::ZeroVector;
}

void APlanePawn::BeginPlay() 
{
	Super::BeginPlay();
}

void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		if (AHW07PlayerController* PlayerController = Cast<AHW07PlayerController>(GetController())) 
		{
			if (PlayerController->PlaneMoveAction) 
			{
				EnhancedInput->BindAction(
					PlayerController->PlaneMoveAction,
					ETriggerEvent::Triggered,
					this,
					&APlanePawn::StartMove
				);
			}
			if (PlayerController->PlaneMoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->PlaneMoveAction,
					ETriggerEvent::Completed,
					this,
					&APlanePawn::StopMove
				);
			}
			if (PlayerController->PlaneRotateAction)
			{
				EnhancedInput->BindAction(
					PlayerController->PlaneRotateAction,
					ETriggerEvent::Triggered,
					this,
					&APlanePawn::Rotate
				);
			}
		}
	}
}

void APlanePawn::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	// �����̸� Z �ӵ� �ʱ�ȭ
	if (IsOnGround()) 
	{
		CurrentVelocity.Z = 0;
	}
	if (!MoveInput.IsNearlyZero()) 
	{
		// ThrustAccel : ���� ���ӵ�
		// MoveDirection : �̵� ����
		FVector MoveDirection = GetActorForwardVector() * MoveInput.X
			+ GetActorRightVector() * MoveInput.Y
			+ GetActorUpVector() * MoveInput.Z;
		// ���� ����
		MoveDirection = MoveDirection.GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("UpVector: %s"), *GetActorUpVector().ToString());

		// ���� �ӵ�
		CurrentVelocity += MoveDirection * ThrustAccel * DeltaTime;
		if (IsOnGround()) 
		{
			CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(MaxSpeed);
		}
		else 
		{
			CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(MaxSpeedInAir);
		}
	}
	else 
	{
		// xy ����
		FVector XYVel = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0);
		FVector ZVel = FVector(0, 0, CurrentVelocity.Z);
		CurrentVelocity = FMath::VInterpTo(XYVel, FVector::ZeroVector, DeltaTime, DecelerationRate) + ZVel;
	}
	// �߷� ���ӵ� ������ ���� �ӵ�
	CurrentVelocity += Gravity * DeltaTime;

	// �����̰� �Ʒ� ���� �ӵ��� ���� �ӵ� 0 �ʱ�ȭ
	if (IsOnGround() && MoveInput.Z <= 0.0f)
	{
		CurrentVelocity.Z = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("CurrentVelocity: %s"), *(CurrentVelocity.ToString()));

	SetActorLocation(GetActorLocation() + CurrentVelocity * DeltaTime);
}

void APlanePawn::Rotate(const FInputActionValue& Value) 
{
	FVector RotateInput = Value.Get<FVector>()*MouseSensitivity;

	AddActorLocalRotation(FRotator(RotateInput.Y, RotateInput.X, RotateInput.Z), true);
}

void APlanePawn::StartMove(const FInputActionValue& Value) 
{
	if (!Controller) return;

	MoveInput = Value.Get<FVector>();
	UE_LOG(LogTemp, Warning, TEXT("Moveinput: %s"), *(MoveInput.ToString()));

}
void APlanePawn::StopMove(const FInputActionValue& Value)
{
	MoveInput = FVector::ZeroVector;
}