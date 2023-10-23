// Fill out your copyright notice in the Description page of Project Settings.

#include "LSAmmo.h"
#include "GameFramework/ProjectileMovementComponent.h"

ALSAmmo::ALSAmmo()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));

	FString AssetPath = TEXT("/Game/LS/Meshes/SM_Ammo.SM_Ammo");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_AMMO(*AssetPath);
	if (SM_AMMO.Succeeded())
	{
		Mesh->SetStaticMesh(SM_AMMO.Object);
	}
	else 
	{
		LSLOG_S(Warning);
	}
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ALSAmmo::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(OnLifeTimerHandle,
		FTimerDelegate::CreateLambda([this]() -> void {
			Destroy();
		}), 0.5f, false);
}

void ALSAmmo::Fire(FVector Dir)
{
	ProjectileMovement->InitialSpeed = 100000.f;
	ProjectileMovement->AddForce(Dir * 1000.0f);
	ProjectileMovement->MaxSpeed = 200000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	FireDir = Dir;
}

void ALSAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProjectileMovement->AddForce(FireDir * 100000.0f);
}

