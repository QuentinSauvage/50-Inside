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

	UPROPERTY(EditAnywhere, Category = Health)
		class USoundBase* HitSound;

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

	FVector FlokingLocation;

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;

	void OnFire();

	void StopFire();

	UFUNCTION(BlueprintCallable, Category = Overlap)
		void AddNeighbor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = Overlap)
		void RemoveNeighbor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	USoundBase* GetHitSound();

	bool CanFireTo(AActor* Other);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Armaments)
		void DropAmmo();

	UFUNCTION(BlueprintImplementableEvent, Category = Armaments)
		void DropRocket();

	UFUNCTION(BlueprintImplementableEvent, Category = Health)
		void DropHealth();

	UFUNCTION(BlueprintCallable, Category = Health)
		void UpdateHealth(float HealthChange);

	UFUNCTION(BlueprintImplementableEvent, Category = Objectives)
		void UpdateGameCounter();
};
