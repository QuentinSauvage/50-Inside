// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "BulletExplosion.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);
	
	Speed = 6000;

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->InitialSpeed = Speed;
	BulletMovement->MaxSpeed = Speed;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->ProjectileGravityScale = 0.f;

	Material = CreateDefaultSubobject<UMaterial>("Material");

	OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);
	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->SetMaterial(0, Cast<UMaterialInterface>(Material));
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this) {
		if (bSticky)
		{
			ABullet* Bullet = Cast<ABullet>(OtherActor);
			if (Bullet && BulletMovement->Velocity != FVector::ZeroVector) {
				Destroy();
			}
			BulletMovement->StopMovementImmediately();
			return;
		}
		APawn* Pawn = Cast<APawn>(OtherActor);
		if (Pawn) {
			float DamageDealed = UGameplayStatics::ApplyPointDamage(OtherActor, 10.0, GetActorLocation(), Hit, nullptr, this, DamageType);
		}
	}
	if (BulletExplosion)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		FTransform ExplosionTransform;
		ExplosionTransform.SetLocation(GetActorLocation());
		ABulletExplosion* Explosion = GetWorld()->SpawnActor <ABulletExplosion>(BulletExplosion, ExplosionTransform, SpawnParams);
		Explosion->Init(DamageType);
	}

	Destroy();
}

