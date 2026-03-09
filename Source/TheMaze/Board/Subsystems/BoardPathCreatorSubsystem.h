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
	UFUNCTION(BlueprintCallable)
	void RegisterBoard(ABoard* InBoard);
	
	UFUNCTION(BlueprintCallable)
	TArray<int> CreatePath();
	
	UFUNCTION(BlueprintPure)
	ABoard* GetBoard() const {return Board;}
private:
	UFUNCTION()
	TArray<int> FindSteps( const TArray<int>& InLastSteps, const int& InMetaIndex);
	UFUNCTION()
	void GetFieldAroundIndex(int InIndex, int& OutLeftFieldIndex, int& OutRightFieldIndex, int& OutUpFieldIndex, int& OutDownFieldIndex) const;	
	UFUNCTION()
	bool CheckFieldStep(int InIndex, const TArray<int>& InCurrentStepIndexes, const TArray<int>& InFieldIndexesAround) const;
	
	UFUNCTION()
	int GetNextStepIndex(TArray<int> InFieldIndexesAround) const;
	
	UFUNCTION()
	FString GetIntArrayToString(const TArray<int>& InArray) const;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABoard> Board;
};
