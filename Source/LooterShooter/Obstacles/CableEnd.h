// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableEnd.generated.h"

UCLASS()
class LOOTERSHOOTER_API ACableEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	ACableEnd();

	FTimerHandle DestoryTimerHandle = { };

	UFUNCTION()
	void DestoryCableEnd();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Timer")
	float DestoryTime = 4.0f;
};
