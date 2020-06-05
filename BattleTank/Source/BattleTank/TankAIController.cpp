// Copyright Craig Palmer 2020

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!possessedTank) { return; }
		//TODO Subscribe our local method to tanks death event.
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	//Death of Tank
	//DetachFromControllerPendingDestroy();
	auto pawn = GetPawn();
	if (pawn)
	{
		pawn->DetachFromControllerPendingDestroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("AI Tank Destroyed"));
	//Call an explosion on the tank and destroy?
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

void ATankAIController::AimTowardsPlayer()
{
	auto controlledTank = GetPawn();
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(playerTank && controlledTank)) { return; } //TODO - Will fail when player tank is destroyed
	//Move towards the player
	MoveToActor(playerTank,acceptanceRadius);
	//Aim towards the player
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(playerTank->GetActorLocation());
	if (aimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		aimingComponent->Fire();
	}
}

