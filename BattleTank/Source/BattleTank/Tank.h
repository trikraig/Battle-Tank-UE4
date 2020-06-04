// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
GENERATED_BODY()
public:
	//Called by the engine when Actor Damage is dealt
	virtual float TakeDamage (float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator,AActor* DamageCauser) override;
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;
private:
	ATank();
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 maxHealth{ 100 };
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 currentHealth = maxHealth;
};
