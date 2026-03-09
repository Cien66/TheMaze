// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "PlayerBoardCheckerSubsystem.generated.h"

class UBoardField;
/**
 * 
 */
UCLASS()
class THEMAZE_API UPlayerBoardCheckerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckedFieldDelegate, const UBoardField*, InBoardField, const FGameplayTag&, InKindOfField);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStepBackDelegate, const UBoardField*, InLastSafeBoardField, const UBoardField*, InCheckedBoardField);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerOnMetaDelegate);
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnCheckedFieldDelegate OnCheckedField;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerOnMetaDelegate OnPlayerOnMeta;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStepBackDelegate OnPlayerStepBackDelegate;
	
	UFUNCTION(BlueprintCallable)
	bool CheckIsValidField(UBoardField* InBoardField);
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerPawn(APawn* InPlayerPawn);
	
	UFUNCTION(BlueprintCallable)
	void SetSafeField(UBoardField* InSafeField);
	
private:
	UFUNCTION()
	void SetPlayerStepBack() const;
	UFUNCTION()
	void UpdateLastStepLocationAndRotation();
	
	UPROPERTY()
	TWeakObjectPtr<APawn> PlayerPawn = nullptr;
	
	UPROPERTY()
	TWeakObjectPtr<UBoardField> LastSafeField = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	FVector LastStepPlayerLocation = FVector::ZeroVector;;
	UPROPERTY(VisibleAnywhere)
	FRotator LastStepPlayerRotation = FRotator::ZeroRotator;
};
