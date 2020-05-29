// Copyright Craig Palmer 2020

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
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
	if (!ensure(playerTank && controlledTank)) { return; }
	
	//Move towards the player
	MoveToActor( //TODO check radius is in cm
		playerTank,
		acceptanceRadius
	);
	//Aim towards the player
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(playerTank->GetActorLocation());
	aimingComponent->Fire();
	
}
