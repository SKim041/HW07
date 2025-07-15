// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "HumanPawn.generated.h"

struct FInputActionValue;
UCLASS()
class HW07_API AHumanPawn : public ABasePawn
{
	GENERATED_BODY()
public:
	AHumanPawn();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement");
	float SprintMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement")
	float JumpImpulse;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector2D MoveInput;
	FVector2D LookInput;
	bool bIsJumping = false;
	bool bIsSprinting = false;
	//FVector CurrentVelocity;
	float MoveSpeed;
};
