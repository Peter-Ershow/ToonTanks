// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
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

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction()
{
	if(DeathParticles)
	{
	UGameplayStatics::SpawnEmitterAtLocation(
		this,
		DeathParticles,
		GetActorLocation(),
		GetActorRotation());
	}
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
		this,
		DeathSound,
		GetActorLocation()
		);
	}
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh-> GetComponentLocation();

	//we only need to rotate yaw
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	
	TurretMesh->SetWorldRotation(
		//Rotate the turret with interpolation
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f
			));
}

void ABasePawn::Fire()
{
	if(ProjectileClass)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			SpawnPoint->GetComponentLocation(),
			SpawnPoint->GetComponentRotation()
			);

		Projectile->SetOwner(this);
	}
}

