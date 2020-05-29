// Copyright Craig Palmer 2020

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	controlledTank = Cast<ATank>(GetPawn());
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (ensure (playerTank && controlledTank))
	{
		//Move towards the player
		MoveToActor( //TODO check radius is in cm
			playerTank,
			acceptanceRadius
			);
		//Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());
		//controlledTank->Fire();
	}
}

