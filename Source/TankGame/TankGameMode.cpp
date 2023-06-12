// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "TankPlayerController.h"


void ATankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (Tank->GetTankPlayerController())
		{
			//Tank->DisableInput(Tank->GetTankPlayerController());
			//Tank->GetTankPlayerController()->bShowMouseCursor = false;
			TankPlayerController->SetPlayerEnabledState(false);
		}
		
	}
	else if (ATurret* DestoryedTower = Cast<ATurret>(DeadActor))
	{
		DestoryedTower->HandleDestruction();
	}
}

void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
