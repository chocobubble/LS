// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryComponent.h"
#include "LSWeaponDefinition.h"

// Sets default values for this component's properties
ULSInventoryComponent::ULSInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

// later delete
	ULSWeaponDefinition* WeaponDefinition1 = NewObject<ULSWeaponDefinition>();
	WeaponDefinition1->SetWeaponDefinitionData(EWeaponType::RIFLE, 1);
	
	

	WeaponList.Add(WeaponDefinition1); 
	// ...
	
}

/*
// Called every frame
void ULSInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

