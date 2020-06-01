// Copyright Craig Palmer 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// Called when the game starts
	virtual void BeginPlay() override;
	UTankTrack();
	//Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
	float trackMaxDrivingForce{40000000};
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(const float& throttle);
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void DriveTracks();
	void ApplySidewaysForce();
	float currentThrottle{ 0 };
};
