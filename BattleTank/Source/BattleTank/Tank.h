// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
GENERATED_BODY()
public:
	ATank();
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AimAt(const FVector& hitLocation);
	UFUNCTION(BluePrintCallable, Category = Firing)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* tankAimingComponent{ nullptr };

private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed{ 4000 };
	double lastFireTime{ 0 };
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds{ 3 };
	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile> projectileBlueprint;
	UTankBarrel* barrel = nullptr; //TODO remove

};
