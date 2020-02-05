// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Radius = 180.f;

	SphereCollision = CreateDefaultSubobject< USphereComponent>(TEXT("Trigger"));
	SphereCollision->InitSphereRadius(Radius);
	SphereCollision->SetCollisionProfileName("Trigger");
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);
	SetRootComponent(SphereCollision);

	Material = CreateDefaultSubobject<UMaterial>("Material");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMaterial(0, Material);

}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 20, FColor::Purple, false, -1, 0, 1);
}

void APickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {
		APawn* Pawn = Cast<APawn>(OtherActor);
		if (Pawn) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("PickUp!"));
			//if(Pawn->CanCollect())
			Destroy();
		}
	}
}

