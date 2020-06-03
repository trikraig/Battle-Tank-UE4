// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(const float& speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* projectileMovementComponent{ nullptr };

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UParticleSystemComponent* launchBlast = nullptr;


};
