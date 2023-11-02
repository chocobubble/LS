// Fill out your copyright notice in the Description page of Project Settings.


#include "LSStartBattleSection.h"
#include "Kismet/GameplayStatics.h"

void ALSStartBattleSection::BeginPlay()
{
    Super::BeginPlay();
}

void ALSStartBattleSection::BattleStart()
{
    Super::BattleStart();

    SetState(ESectionState::COMPLETE);
}

void ALSStartBattleSection::SectionClear()
{
    Super::SectionClear();

    UGameplayStatics::OpenLevel(GetWorld(), TEXT("step4"));
}