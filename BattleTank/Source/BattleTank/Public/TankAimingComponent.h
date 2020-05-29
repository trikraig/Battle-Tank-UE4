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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel* barrelToSet);
	void SetTurretReference(UTankTurret* turretToSet);
	void AimAt(const FVector& hitLocation, const float& launchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingStatus{ EFiringStatus::Aiming };

private:
	UTankBarrel* barrel{ nullptr };
	void MoveBarrelTowards(const FVector& aimDirection);
	UTankTurret* turret{ nullptr };

};
