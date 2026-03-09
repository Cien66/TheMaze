// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "BoardDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, Const/*, meta = (DisplayName = "Board Developer Settings")*/)
class THEMAZE_API UBoardDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere)
	FGameplayTag MetaFieldTag;
	UPROPERTY(Config, EditAnywhere)
	FGameplayTag StartFieldTag;
	UPROPERTY(Config, EditAnywhere)
	FGameplayTag ValidFieldTag;
};
