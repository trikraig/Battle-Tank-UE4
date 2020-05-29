// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called when the game starts
	virtual void BeginPlay() override;
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(const FVector& hitLocation);
	UFUNCTION(BluePrintCallable, Category = "Firing")
	void Fire();
	UFUNCTION(BluePrintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingStatus{ EFiringStatus::Locked };

private:
	UTankBarrel* barrel{ nullptr };
	UTankTurret* turret{ nullptr };
	
	void MoveBarrelTowards(const FVector& aimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed{ 4000 };

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds{ 3 };

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;
		
	double lastFireTime{ 0 };

};
