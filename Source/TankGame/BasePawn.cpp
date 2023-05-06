// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	// Only need the Yaw, avoids rotating the head of turret into the ground
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);  
	TurretMesh->SetWorldRotation(FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this), 5.f)
		); // Instead of setting the Look at Rotation, I interp between, avoids a stutter looking mouse is over center of turret head
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLoc = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRot = ProjectileSpawnPoint->GetComponentRotation();
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPointLoc, 25.f, 12, FColor::Blue, false, 3.f);
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLoc, ProjectileSpawnPointRot);
}






