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
	void AimAt(const FVector& hitLocation);
	UFUNCTION(BluePrintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingStatus{ EFiringStatus::Locked };

private:
	UTankBarrel* barrel{ nullptr };
	void MoveBarrelTowards(const FVector& aimDirection);
	UTankTurret* turret{ nullptr };
	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed{ 4000 };

};
