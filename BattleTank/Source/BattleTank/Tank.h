// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
GENERATED_BODY()
public:
	ATank();
	//Called by the engine when Actor Damage is dealt
	virtual float TakeDamage
	(float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator,AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 maxHealth{ 100 };
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 currentHealth = maxHealth;
};
