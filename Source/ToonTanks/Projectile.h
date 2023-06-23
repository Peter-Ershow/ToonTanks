// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category= "Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category= "Combat")
	class UParticleSystemComponent* TrailParticles;
	
	UPROPERTY(EditAnywhere, Category= "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category= "Combat")
	USoundBase* HitSound;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
