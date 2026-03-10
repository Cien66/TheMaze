// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BoardPathCreatorSubsystem.generated.h"


class UBoardField;
class ABoard;



/**
 * 
 */
UCLASS()
class THEMAZE_API UBoardPathCreatorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	/**
	 * Register board to create path
	 * @param InBoard board to register
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterBoard(ABoard* InBoard);

	/**
	 * 
	 * @param InBoard to create from subsytem
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterBoard(ABoard* InBoard);

	/**
	 * Generate path from start to meta - invalid, not working, not impact in project 
	 * @return list of field with correct path form start to meta 
	 */
	UFUNCTION(BlueprintCallable)
	TArray<int> CreatePath();

	/**
	 * 
	 * @return board
	 */
	UFUNCTION(BlueprintPure)
	ABoard* GetBoard() const {return Board;}
private:
	/**
	 * Find next step to meta field around last step
	 * @param InLastSteps List of step from start to current field
	 * @param InMetaIndex Index of meat field in array
	 * @return List of step from start to this field
	 */
	UFUNCTION()
	TArray<int> FindSteps( const TArray<int>& InLastSteps, const int& InMetaIndex);

	/**
	 * Looking for field around center field - if out of board return INDEX_NONE to field 
	 * @param InIndex Index of center field in array to looking for field around 
	 * @param OutLeftFieldIndex left field around center field
	 * @param OutRightFieldIndex right field around center field
	 * @param OutUpFieldIndex up field around center field
	 * @param OutDownFieldIndex down field around center field
	 */
	UFUNCTION()
	void GetFieldAroundIndex(int InIndex, int& OutLeftFieldIndex, int& OutRightFieldIndex, int& OutUpFieldIndex, int& OutDownFieldIndex) const;

	/**
	 * Check the field if only one valid field around it
	 * @param InIndex Index of field to check
	 * @param InCurrentStepIndexes 
	 * @param InFieldIndexesAround 
	 * @return 
	 */
	UFUNCTION()
	bool CheckFieldStep(int InIndex, const TArray<int>& InCurrentStepIndexes, const TArray<int>& InFieldIndexesAround) const;

	/**
	 * Get random index in field around center field
	 * @param InFieldIndexesAround  indexes of around field 
	 * @return random index of around field to next step
	 */
	UFUNCTION()
	int GetNextStepIndex(TArray<int> InFieldIndexesAround) const;

	/**
	 * Convert array of int to string e.g 1, 2, 3
	 * @param InArray to convert to string
	 * @return Return string of array
	 */
	UFUNCTION()
	FString GetIntArrayToString(const TArray<int>& InArray) const;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABoard> Board;
};
