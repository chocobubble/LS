// Fill out your copyright notice in the Description page of Project Settings.

#include "LSAmmo.h"
#include "GameFramework/ProjectileMovementComponent.h"

ALSAmmo::ALSAmmo()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_AMMO(TEXT("/Game/LS/Meshes/SM_Ammo.SM_Ammo"));
	if (SM_AMMO.Succeeded() && Mesh)
	{
		Mesh->SetStaticMesh(SM_AMMO.Object);
		Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void ALSAmmo::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		OnLifeTimerHandle,
		FTimerDelegate::CreateLambda([this]() -> void {
			Destroy();}),
		0.5f, 
		false
	);
}

void ALSAmmo::Fire(const FVector& Dir)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = 100000.0f;
		ProjectileMovement->AddForce(Dir * 1000.0f);
		ProjectileMovement->MaxSpeed = 200000.0f;
		ProjectileMovement->ProjectileGravityScale = 0.0f;
	} 
	FireDir = Dir;
}

void ALSAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileMovement)
	{
		ProjectileMovement->AddForce(FireDir * 100000.0f);
	}
}

