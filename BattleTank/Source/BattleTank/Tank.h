// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
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

	UFUNCTION(BluePrintCallable, Category = Firing)
	void Fire();

private:

	//TODO Remove when copy firing to aiming component.

	double lastFireTime{ 0 };
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds{ 3 };
	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile> projectileBlueprint;
	UTankBarrel* barrel = nullptr; //TODO remove

};
