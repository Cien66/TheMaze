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
	/**
	 * Call when update field
	 */
	UPROPERTY(BlueprintAssignable)
	FOnCheckedFieldDelegate OnCheckedField;

	/**
	 * Call when player stand on meat field
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerOnMetaDelegate OnPlayerOnMeta;

	/**
	 * Call when player back from invalid to last safe field 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStepBackDelegate OnPlayerStepBackDelegate;

	/**
	 * Check the field is correct to stay player on it or not 
	 * @param InBoardField field to check
	 * @return is valid field
	 */
	UFUNCTION(BlueprintCallable)
	bool CheckIsValidField(UBoardField* InBoardField);

	/**
	 * Set player pawn 
	 * @param InPlayerPawn Player pawn to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetPlayerPawn(APawn* InPlayerPawn);
	
	/**
	 * Set last safe field to can player back 
	 * @param InSafeField Safe field to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSafeField(UBoardField* InSafeField);
	
private:
	/**
	 * Return player pawn to last safe field position
	 */
	UFUNCTION()
	void SetPlayerStepBack() const;

	/**
	 * Set location and rotation of player pawn to safe last step
	 */
	UFUNCTION()
	void UpdateLastStepLocationAndRotation();

	/**
	 * Player pawn
	 */
	UPROPERTY()
	TWeakObjectPtr<APawn> PlayerPawn = nullptr;

	/**
	 * Last safe field to can player back
	 */
	UPROPERTY()
	TWeakObjectPtr<UBoardField> LastSafeField = nullptr;

	/**
	 * Last location where player can step back 
	 */
	UPROPERTY(VisibleAnywhere)
	FVector LastStepPlayerLocation = FVector::ZeroVector;

	/**
	 * Last rotation where player can step back 
	 */
	UPROPERTY(VisibleAnywhere)
	FRotator LastStepPlayerRotation = FRotator::ZeroRotator;
};
