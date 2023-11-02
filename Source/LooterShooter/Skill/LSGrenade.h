// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSGrenade.generated.h"


UCLASS()
class LOOTERSHOOTER_API ALSGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSGrenade();

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* GrenadeMesh;

};
