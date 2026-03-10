// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class UBoardField;

UCLASS()
class THEMAZE_API ABoard : public AActor
{
	GENERATED_BODY()

public:
	ABoard();

	/**
	 * Generate board and update fields
	 */
	UFUNCTION(BlueprintCallable, CallInEditor)
	void BuildBoard();

	/**
	 * 
	 * @return all fields in board 
	 */
	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<UBoardField*> GetFields() const {return Fields;}

	/**
	 * 
	 * Convert field index to row and column where the field is 
	 * @param InIndex Index of field in array
	 * @param OutRow Row where the field is
	 * @param OutColumn Column where the field is 
	 */
	UFUNCTION(BlueprintCallable)
	void CovertIndexToRowAndColumn(int InIndex, int& OutRow, int& OutColumn) const;

	/**
	 * Convert row and column to index of field in array
	 * @param InRow where the field is
	 * @param InColumn where the field is
	 * @return Index of field in array
	 */
	UFUNCTION(BlueprintPure)
	int ConvertRowAndColumnToIndex(int InRow, int InColumn) const;

	/**
	 * 
	 * @return Size of board by count of rows and columns
	 */
	FORCEINLINE FInt32Point GetBoardSize() const {return BoardSize;}
	
protected:
	/**
	 * Register board to path creator subsystem
	 */
	virtual void BeginPlay() override;
	/**
	 * Unregister board from path creator subsystem
	 */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	/**
	 * Clear board and all fields
	 */
	UFUNCTION()
	void ClearBoard();

	/**
	 * class of field to create board
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBoardField> FieldClass;

	/**
	 * Board size by rows and columns
	 */
	UPROPERTY(EditAnywhere)
	FInt32Point BoardSize;
	/**
	 * Space between fields
	 */
	UPROPERTY(EditAnywhere)
	FVector2D SpaceBetweenFields;

	/**
	 * Array of fields in board
	 */
	UPROPERTY(VisibleInstanceOnly)
	TArray<TObjectPtr<UBoardField>> Fields;
};
