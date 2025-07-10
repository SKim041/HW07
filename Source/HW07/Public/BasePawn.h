// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class HW07_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pawn|Component")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Component")
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pawn|Component")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pawn|Component")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement")
	float MaxFallSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement")
	float MouseSensitivity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Movement")
	FVector Gravity = FVector(0.0f, 0.0f, -980.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsOnGround();

};
