// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGrenade.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LooterShooter/Character/LSMonster.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

ALSGrenade::ALSGrenade()
{
 	PrimaryActorTick.bCanEverTick = true;

	GrenadeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = GrenadeMeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GRENADE(TEXT("/Game/Weapons/Grenade/Mesh/SM_grenade.SM_grenade"));
	if (SM_GRENADE.Succeeded())
	{
		GrenadeMeshComponent->SetStaticMesh(SM_GRENADE.Object);
	}
	GrenadeMeshComponent->SetCollisionProfileName(TEXT("Ragdoll"));	
	GrenadeMeshComponent->SetSimulatePhysics(true);
	GrenadeMeshComponent->SetEnableGravity(true);

	GrenadeMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("GRENADEMOVECOMP"));
	GrenadeMovementComponent->bRotationFollowsVelocity = true;
	GrenadeMovementComponent->bShouldBounce = true;

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_EXPLODE(TEXT("/Game/MilitaryWeapSilver/Sound/GrenadeLauncher/Cues/GrenadeLauncher_Explosion_Cue.GrenadeLauncher_Explosion_Cue"));
	if (SC_EXPLODE.Succeeded())
	{
		ExplodeSound = SC_EXPLODE.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_EXPLODE(TEXT("/Game/MilitaryWeapSilver/Sound/GrenadeLauncher/Wavs/GrenadeLauncher_Explosion03.GrenadeLauncher_Explosion03"));
	if (PS_EXPLODE.Succeeded())
	{
		ExplodeImpact = PS_EXPLODE.Object;
	}

	ExplodeParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EXPLODE"));
}

void ALSGrenade::Throw()
{
	if (GrenadeMovementComponent)
	{
		GrenadeMovementComponent->AddForce(GetActorForwardVector() * 30000.0f);
		GrenadeMovementComponent->InitialSpeed = 100000.0f;
		GrenadeMovementComponent->MaxSpeed = 10000000.0f;
	}
}

void ALSGrenade::Explode()
{
	TArray<FHitResult> OutHits;
	//FHitResult HitResult;

	/**
	 *  Sweep a shape against the world and return all initial overlaps using a specific channel (including blocking) if requested, then overlapping hits and then first blocking hit
	 *  Results are sorted, so a blocking hit (if found) will be the last element of the array
	 *  Only the single closest blocking result will be generated, no tests will be done after that
	 *  @param  OutHits         Array of hits found between ray and the world
	 *  @param  Start           Start location of the shape
	 *  @param  End             End location of the shape
	 *  @param  TraceChannel    The 'channel' that this ray is in, used to determine which components to hit
	 *  @param	CollisionShape	CollisionShape - supports Box, Sphere, Capsule
	 *  @param  Params          Additional parameters used for the trace
	 * 	@param 	ResponseParam	ResponseContainer to be used for this trace
	 *  @return TRUE if OutHits contains any blocking hit entries
	 */
	bool bIsHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		GetActorLocation(),
		GetActorLocation(),// + GetActorForwardVector() * 500.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(500.0f)
	);
	if (bIsHit)
	{
		for (FHitResult& HitResult : OutHits)
		{
			//FName HitName = FName(*(HitResult.GetActor()->GetName()));
			ALSMonster* Monster = Cast<ALSMonster>(HitResult.GetActor());
			if (Monster && Player)
			{
				FDamageEvent DamageEvent;
				HitResult.GetActor()->TakeDamage(100.0f, DamageEvent, Player->GetController(), Player);
				Monster->TakeDamage(100.0f, DamageEvent, Player->GetController(), Player);
			}
		}
	}

	if (ExplodeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation());

	}
	else
	{
		LSLOG(Warning, TEXT("NO t Sound"));
	}

	if (ExplodeImpact)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeImpact, GetActorTransform());
	}
	else
	{
		LSLOG(Warning, TEXT("NO t explode"));
	}


	Destroy();
}

void ALSGrenade::Init(APawn* Pawn)
{
	Player = Pawn;
}

void ALSGrenade::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			OnLifeTimerHandle,
			FTimerDelegate::CreateLambda([this]() -> void {
				ALSGrenade::Explode(); }),
				2.0f, // 폭발 시간
				false
		);
	}

	ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &ALSGrenade::OnBounce);
}

void ALSGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GrenadeMovementComponent)
	{
		GrenadeMovementComponent->AddForce(GetActorForwardVector() * 30000.0f);
	}
}

void ALSGrenade::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (BounceSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			BounceSound,
			GetActorLocation()
		);
	}
}



