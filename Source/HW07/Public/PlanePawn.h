// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlanePawn.generated.h"

struct FInputActionValue;

UCLASS()
class HW07_API APlanePawn : public ABasePawn
{
	GENERATED_BODY()
public:
	APlanePawn();

	UStaticMeshComponent* StaticMeshComp;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement")
	float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn|Movement")
	float ThrustAccel;


	UFUNCTION()
	void Rotate(const FInputActionValue& Value);
	UFUNCTION()
	void StartMove(const FInputActionValue& Value);
	UFUNCTION()
	void StopMove(const FInputActionValue& Value);



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	//FVector CurrentVelocity;
	FVector MoveInput;
	float MaxSpeedInAir;


};
