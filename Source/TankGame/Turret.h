// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public: 
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank; // Pointing to the tank class

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRange = 100.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.0f;
	void CheckFire();
	bool WithinRange();
};
