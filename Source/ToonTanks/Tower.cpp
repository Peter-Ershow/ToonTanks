// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		
		// Find the distance to the tank
		// check if in range
		// is so, rotate toward a tank

		if(Distance<FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank, APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}