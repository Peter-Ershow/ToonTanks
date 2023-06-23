// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
	
protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components",meta=(AllowPrivateAccess))
	class UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components",meta=(AllowPrivateAccess))
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components",meta=(AllowPrivateAccess))
	UStaticMeshComponent *TurretMesh;
	
	UPROPERTY(EditAnywhere)
	USceneComponent *SpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category= "Death")
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category= "Death")
	class USoundBase* DeathSound;

};
