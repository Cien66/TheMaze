// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BoardPathCreatorSubsystem.generated.h"


class UBoardField;
class ABoard;


USTRUCT()
struct FPathFindingStep
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoardField> Field;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoardField> LeftField;	
	UPROPERTY(VisibleAnywhere)
	bool bIsCheckLeftField = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoardField> RightField;
	UPROPERTY(VisibleAnywhere)
	bool bIsCheckRightField = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoardField> UpField;
	UPROPERTY(VisibleAnywhere)
	bool bIsCheckUpField = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoardField> DownField;
	UPROPERTY(VisibleAnywhere)
	bool bIsCheckDownField = false;
};
/**
 * 
 */
UCLASS()
class THEMAZE_API UBoardPathCreatorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RegisterBoard(const ABoard* InBoard);
	UFUNCTION(BlueprintCallable)
	void UnregisterBoard(const ABoard* InBoard);
	
	UFUNCTION(BlueprintCallable)
	void CreatePath(const ABoard* InBoard);
	
private:
	UFUNCTION()
	void GetFieldAroundIndex(int InIndex, const ABoard* InBoard, UBoardField*& InLeftField, UBoardField*& InRightField, UBoardField*& InUpField, UBoardField*& InDownField);
	
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<const ABoard>> Boards;
	
	
};
