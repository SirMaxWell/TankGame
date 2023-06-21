// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WithinRange())
	{
		// if within range, rotate to face the tank
		RotateTurret(Tank->GetActorLocation());
	}
	
}


void ATurret::BeginPlay()
{
	Super::BeginPlay();

	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFire, FireRate, true);

}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();

	
}

void ATurret::CheckFire()
{
	if (Tank == nullptr)
	{
		return;
	}
	if (WithinRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATurret::WithinRange()
{
	if (Tank) // if tank not null 
	{
		// Finds the distance between the tank and turret
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// Checks to see if the tank is within range 
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

