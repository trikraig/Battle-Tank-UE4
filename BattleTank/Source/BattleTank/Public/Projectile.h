// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(const float& speed);

private:
	UProjectileMovementComponent* projectileMovementComponent{ nullptr };

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UParticleSystemComponent* launchBlast = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UParticleSystemComponent* impactBlast = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	URadialForceComponent* explosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay{ 2.f };

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();

};
