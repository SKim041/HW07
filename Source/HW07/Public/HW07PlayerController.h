// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HW07PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class HW07_API AHW07PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHW07PlayerController();

	// Base IMC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Base")
	UInputMappingContext* BaseInputMappingContext;
	// Base IA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Base")
	UInputAction* BaseSwitchToHuman;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Base")
	UInputAction* BaseSwitchToPlane;
	// Human IMC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Human")
	UInputMappingContext* HumanInputMappingContext;
	// Human IA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Human")
	UInputAction* HumanMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Human")
	UInputAction* HumanLookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Human")
	UInputAction* HumanJumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Human")
	UInputAction* HumanSprintAction;

	// Plane IMC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Plane")
	UInputMappingContext* PlaneInputMappingContext;
	// Plane IA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Plane")
	UInputAction* PlaneRotateAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Plane")
	UInputAction* PlaneMoveAction;

	UFUNCTION()
	void SwitchToHuman();
	UFUNCTION()
	void SwitchToPlane();


protected:
	virtual void BeginPlay() override;	

	virtual void OnPossess(APawn* InPawn) override;

	UInputMappingContext* CurrentPawnMappingContext = nullptr;

	APawn* DefaultPawn;
};
