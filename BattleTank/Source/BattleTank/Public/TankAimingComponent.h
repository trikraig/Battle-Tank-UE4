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
	Locked,
	OutOfAmmo
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

	EFiringStatus GetFiringState() const;
	UFUNCTION(BluePrintCallable, Category = "Firing")
	int GetAmmoRemaining() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringStatus firingStatus{ EFiringStatus::Reloading };

private:
	UTankBarrel* barrel{ nullptr };
	UTankTurret* turret{ nullptr };

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void MoveBarrelTowards();
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int ammoRemaining {3};

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed{ 4000 };

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds{ 3 };

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;
		
	double lastFireTime{ 0 };

	FVector aimDirection{ 0 };



};
