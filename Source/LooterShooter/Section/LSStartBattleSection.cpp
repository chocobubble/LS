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

    SetState(ESectionState::ESS_Complete);
}

void ALSStartBattleSection::SectionClear()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("stage1"));
}
