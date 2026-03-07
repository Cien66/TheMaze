// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPathCreatorSubsystem.h"
#include "../Actors/Board.h"

void UBoardPathCreatorSubsystem::RegisterBoard(const ABoard* InBoard)
{
	Boards.Add(InBoard);
	
	CreatePath(InBoard);
}

void UBoardPathCreatorSubsystem::UnregisterBoard(const ABoard* InBoard)
{
	Boards.Remove(InBoard);
}

void UBoardPathCreatorSubsystem::CreatePath(const ABoard* InBoard)
{
	if (!InBoard) return;
	
	const auto Fields = InBoard->GetFields();
	if (Fields.Num() < 2) return;
	
	
	int StartIndex = FMath::RandRange(0, Fields.Num() - 1);
	int MetaIndex = FMath::RandRange(0, Fields.Num() - 1);
	
	if (StartIndex == MetaIndex)
		MetaIndex = (MetaIndex + 1) % Fields.Num();
	
	TArray<UBoardField*> Steps;
	UBoardField* CurrentField = nullptr; 
	do
	{
		Steps.Add(Fields[StartIndex]);
	} while (CurrentField != Fields[MetaIndex]);
}

void UBoardPathCreatorSubsystem::GetFieldAroundIndex(int InIndex, const ABoard* InBoard, UBoardField*& InLeftField, UBoardField*& InRightField, UBoardField*& InUpField, UBoardField*& InDownField)
{
	if (!InBoard || InIndex < 0 || InIndex >= InBoard->GetFields().Num()) return;
	
	int ColumnIndex = -1;
	int RowIndex = -1;
	
	InBoard->CovertIndexToRowAndColumn(InIndex, RowIndex, ColumnIndex);
	
	if (ColumnIndex < 0 || RowIndex < 0) return;
	
	const auto LeftIndex = InBoard->ConvertRowAndColumnToIndex(RowIndex, ColumnIndex - 1);
	const auto RightIndex = InBoard->ConvertRowAndColumnToIndex(RowIndex, ColumnIndex + 1);
	const auto UpIndex = InBoard->ConvertRowAndColumnToIndex(RowIndex + 1, ColumnIndex);
	const auto DownIndex = InBoard->ConvertRowAndColumnToIndex(RowIndex, ColumnIndex - 1);
	
	InLeftField = LeftIndex >= 0 && LeftIndex < InBoard->GetFields().Num() ? InBoard->GetFields()[LeftIndex] : nullptr;
	InRightField = RightIndex >= 0 && RightIndex < InBoard->GetFields().Num() ? InBoard->GetFields()[RightIndex] : nullptr;
	InUpField = UpIndex >= 0 && UpIndex < InBoard->GetFields().Num() ? InBoard->GetFields()[UpIndex] : nullptr;
	InDownField = DownIndex >= 0 && DownIndex < InBoard->GetFields().Num() ? InBoard->GetFields()[DownIndex] : nullptr;
}


