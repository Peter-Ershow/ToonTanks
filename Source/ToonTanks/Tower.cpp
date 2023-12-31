// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(InFireRange()) {
		// Find the distance to the tank
		// check if in range
		// is so, rotate toward a tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank, APawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true
		);
}

void ATower::CheckFireCondition()
{
	if(Tank && InFireRange() && Tank->bAlive) {
		// Find the distance to the tank
		// check if in range
		// is so, fire a bullet
		Fire();
	}
}

bool ATower::InFireRange() const
{
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		return Distance <= FireRange;
	}
	return false;
}

