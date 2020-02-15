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

	UPROPERTY(EditAnywhere, Category = Armaments)
	class AWeapon* MainWeapon;

	/** Maximum health*/
	UPROPERTY(EditAnywhere, Category = Health)
		float FullHealth;

	/** Remaining health*/
	UPROPERTY(EditAnywhere, Category = Health)
		float RemainingHealth;

public:
	/** Weapon Class*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armaments)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* Behavior;

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;

	void OnFire();

	void StopFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	void UpdateHealth(float HealthChange);

};
