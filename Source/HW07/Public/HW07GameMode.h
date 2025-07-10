// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HW07GameMode.generated.h"

class APlanePawn;

/**
 * 
 */
UCLASS()
class HW07_API AHW07GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AHW07GameMode();
	UFUNCTION(BlueprintPure, Category = "Plane")
	APlanePawn* GetPlaneInstance() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<APlanePawn> PlanePawnClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	FTransform PlaneSpawnTransform;

	
private:
	UPROPERTY()
	TObjectPtr<APlanePawn> PlaneInstance;
};
