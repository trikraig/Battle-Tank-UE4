// Copyright Craig Palmer 2020

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{	
	int32 damagePoints = FMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp<int32>(damagePoints,0, maxHealth);
	currentHealth -= damageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Damage amount: %f"), DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Damage to apply: %f"), damageToApply);
	return damageToApply;
}
