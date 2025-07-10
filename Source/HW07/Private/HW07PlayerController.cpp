// Fill out your copyright notice in the Description page of Project Settings.


#include "HW07PlayerController.h"
#include "HW07GameMode.h"
#include "EnhancedInputSubsystems.h"
#include "HumanPawn.h"
#include "PlanePawn.h"
#include "GameFramework/GameMode.h"
#include "EnhancedInputComponent.h"

AHW07PlayerController::AHW07PlayerController()
	: BaseInputMappingContext(nullptr),
	BaseSwitchToHuman(nullptr),
	BaseSwitchToPlane(nullptr), 
	HumanInputMappingContext(nullptr),
	HumanMoveAction(nullptr),
	HumanLookAction(nullptr),
	HumanJumpAction(nullptr),
	HumanSprintAction(nullptr), 
	PlaneInputMappingContext(nullptr),
	PlaneRotateAction(nullptr),
	PlaneMoveAction(nullptr)
{

}

void AHW07PlayerController::BeginPlay() 
{
	Super::BeginPlay();

	// Default HumanPawn 저장
	if (GetPawn()) 
	{
		DefaultPawn = GetPawn();
	}
	else 
	{
		DefaultPawn = nullptr;
	}

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) 
		{
			if (BaseInputMappingContext) 
			{
				Subsystem->AddMappingContext(BaseInputMappingContext, 0);
			}
		}
	}
	if (!InputComponent) 
	{
		InputComponent = NewObject<UEnhancedInputComponent>(this, TEXT("EnhancedInputComponent"));
		InputComponent->RegisterComponent();
		PushInputComponent(InputComponent);
	}
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		
		if (BaseSwitchToHuman)
		{
			EnhancedInput->BindAction(
				BaseSwitchToHuman,
				ETriggerEvent::Triggered,
				this,
				&AHW07PlayerController::SwitchToHuman
			);
		}
		if (BaseSwitchToPlane)
		{
			EnhancedInput->BindAction(
				BaseSwitchToPlane,
				ETriggerEvent::Triggered,
				this,
				&AHW07PlayerController::SwitchToPlane
			);
		}
	
	}
}


void AHW07PlayerController::OnPossess(APawn* InPawn) 
{
	Super::OnPossess(InPawn);

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) 
		{
			// 폰 전용 IMC 제거
			if (CurrentPawnMappingContext) 
			{
				Subsystem->RemoveMappingContext(CurrentPawnMappingContext);
			}

			if (Cast<AHumanPawn>(InPawn))
			{
				if (HumanInputMappingContext)
				{
					CurrentPawnMappingContext = HumanInputMappingContext;
				}
			}
			else if (Cast<APlanePawn>(InPawn))
			{
				if (PlaneInputMappingContext)
				{
					CurrentPawnMappingContext = PlaneInputMappingContext;
				}
			}
			else CurrentPawnMappingContext = nullptr;

			if (CurrentPawnMappingContext) 
			{
				Subsystem->AddMappingContext(CurrentPawnMappingContext, 1);
			}
		}
	}
}

void AHW07PlayerController::SwitchToHuman() 
{
	if (DefaultPawn) 
	{
		Possess(DefaultPawn);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find Default Pawn"));
	}
}
void AHW07PlayerController::SwitchToPlane()
{
	if (AHW07GameMode* GameMode = Cast<AHW07GameMode>(GetWorld()->GetAuthGameMode())) 
	{
		if (APlanePawn* PlaneInstance = GameMode->GetPlaneInstance()) 
		{
			Possess(PlaneInstance);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot find Plane Pawn"));
		}
	}
}
