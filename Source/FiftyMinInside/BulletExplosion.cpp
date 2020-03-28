// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletExplosion.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABulletExplosion::ABulletExplosion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Collision->InitSphereRadius(100.f);
	Collision->SetCollisionProfileName("Trigger");
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABulletExplosion::OnOverlapBegin);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MaterialInstance = CreateDefaultSubobject<UMaterialInterface>("Material");
}

void ABulletExplosion::Init(TSubclassOf<UDamageType> BulletDamageType, float DamageValue)
{
	DamageType = BulletDamageType;
	DamageAmount = DamageValue;
}

// Called when the game starts or when spawned
void ABulletExplosion::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(TimeToLive);
	Mesh->SetMaterial(0, Cast<UMaterialInterface>(MaterialInstance));
}

// Called every frame
void ABulletExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ExplosionScale = Collision->GetRelativeScale3D();
	Collision->SetRelativeScale3D(ExplosionScale + (MaxExplosion - ExplosionScale) * DeltaTime);
}

void ABulletExplosion::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {
		APawn* Pawn = Cast<APawn>(OtherActor);
		if (Pawn) {
			float DamageDealed = UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, GetActorLocation(), SweepResult, nullptr, this, DamageType);
		}
	}
}