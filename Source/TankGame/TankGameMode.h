// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TANKGAME_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();

private:
	class ATank* Tank;
	class ATankPlayerController* TankPlayerController;

	float StartDelay = 3.0f;

	void HandleGameStart();

	
};