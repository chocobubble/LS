// Fill out your copyright notice in the Description page of Project Settings.

#include "LSBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

ALSBullet::ALSBullet()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BULLET(TEXT("/Game/LS/Meshes/SM_Ammo.SM_Ammo"));
	if (SM_BULLET.Succeeded())
	{
		Mesh->SetStaticMesh(SM_BULLET.Object);
		Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));

	BulletTracerComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TRACER"));
	BulletTracerComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SM_TRACER(TEXT("/Game/MilitaryWeapSilver/FX/P_AssaultRifle_Tracer_01.P_AssaultRifle_Tracer_01"));
	if (SM_TRACER.Succeeded())
	{
		BulletTracer = SM_TRACER.Object;
	}

	if (BulletTracerComponent && BulletTracer)
	{
		BulletTracerComponent->SetTemplate(BulletTracer);
	}

   
}

void ALSBullet::BeginPlay()
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

void ALSBullet::Fire()
{
	/*
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = 100000.0f;
		ProjectileMovement->AddForce(Dir * 1000.0f);
		ProjectileMovement->MaxSpeed = 200000.0f;
		ProjectileMovement->ProjectileGravityScale = 0.0f;
	} 
	FireDir = Dir;
	*/

	if (ProjectileMovement)
	{
		//InitialVelocity = GetActorForwardVector() * BulletInitialSpeed;
	}
}

void ALSBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileMovement)
	{
		ProjectileMovement->AddForce(GetActorForwardVector() * 100000.0f);
	}
}

