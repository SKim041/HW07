// Fill out your copyright notice in the Description page of Project Settings.


#include "HW07GameMode.h"
#include "HW07PlayerController.h"
#include "HumanPawn.h"
#include "PlanePawn.h"


AHW07GameMode::AHW07GameMode() 
{
	DefaultPawnClass = AHumanPawn::StaticClass();
	PlayerControllerClass = AHW07PlayerController::StaticClass();
	PlaneInstance = nullptr;
}

void AHW07GameMode::BeginPlay() 
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld()) 
	{
		PlaneInstance = World->SpawnActor<APlanePawn>(PlanePawnClass, PlaneSpawnTransform);
	}
}

APlanePawn* AHW07GameMode::GetPlaneInstance() const 
{
	return PlaneInstance;
}
