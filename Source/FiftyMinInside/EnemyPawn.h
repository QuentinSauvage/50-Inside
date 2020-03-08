// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

UCLASS(Config = Game)
class FIFTYMININSIDE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

		/** StaticMesh component that will be the visuals for our flying pawn */
		UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PlaneMesh;



	/** Maximum health*/
	UPROPERTY(EditAnywhere, Category = Health)
		float FullHealth;

	/** Remaining health*/
	UPROPERTY(EditAnywhere, Category = Health)
		float RemainingHealth;

	UPROPERTY(EditAnywhere, Category = Detection)
		class USphereComponent* NeighborTrigger;

public:
	/** Weapon Class*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armaments)
		TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = Armaments)
		 AWeapon* MainWeapon;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* Behavior;

	UPROPERTY(EditAnywhere, Category = Movement)
		float FullSpeed;

	FVector CurrentDirection;

	TArray<AEnemyPawn*> Neighbors;

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;

	void OnFire();

	void StopFire();

	void AddNeighbor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void RemoveNeighbor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = Health)
		void UpdateHealth(float HealthChange);

};
