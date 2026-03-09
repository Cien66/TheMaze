// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPathCreatorSubsystem.h"
#include "../Actors/Board.h"
#include "TheMaze/Board/Components/BoardField.h"
#include "TheMaze/Board/Settings/BoardDeveloperSettings.h"

void UBoardPathCreatorSubsystem::RegisterBoard(ABoard* InBoard)
{
	Board = InBoard;
	
	//CreatePath();
}

TArray<int> UBoardPathCreatorSubsystem::CreatePath()
{
	if (!Board) return {};
	
	const auto Fields = Board->GetFields();
	if (Fields.Num() < 2) {};
		
	int StartIndex = FMath::RandRange(0, Fields.Num() - 1);
	int MetaIndex = FMath::RandRange(0, Fields.Num() - 1);
	
	if (StartIndex == MetaIndex)
		MetaIndex = (MetaIndex + 1) % Fields.Num();
	
	if (StartIndex == INDEX_NONE || MetaIndex == INDEX_NONE) return {};
	
	const auto Path = FindSteps({StartIndex}, MetaIndex);
	if (Path.IsEmpty()) return Path;
	
	if (const auto BoardSettings = GetDefault<UBoardDeveloperSettings>())
	{
		for (const int IndexField : Path)
			if (auto BoardField = Board->GetFields()[IndexField])
				BoardField->SetKindOfField(BoardSettings->ValidFieldTag);
			
		if (auto StartField = Board->GetFields()[StartIndex])
			StartField->SetKindOfField(BoardSettings->StartFieldTag);
		
		if (auto MetaField = Board->GetFields()[MetaIndex])
			MetaField->SetKindOfField(BoardSettings->MetaFieldTag);
	}
	
	return Path;
}

TArray<int> UBoardPathCreatorSubsystem::FindSteps(const TArray<int>& InLastSteps, const int& InMetaIndex)
{
	if (InLastSteps.IsEmpty()) return InLastSteps;
	
	const int CurrentIndex = InLastSteps.Last();
	
	TArray<int> CurrentSteps = InLastSteps;
	int LeftFieldIndex = INDEX_NONE;
	int RightFieldIndex = INDEX_NONE;
	int UpFieldIndex = INDEX_NONE;
	int DownFieldIndex = INDEX_NONE;
	
	GetFieldAroundIndex(CurrentIndex, LeftFieldIndex, RightFieldIndex, UpFieldIndex, DownFieldIndex);
	
	TArray<int> FieldIndexesAround = {LeftFieldIndex, RightFieldIndex, UpFieldIndex, DownFieldIndex};
	FieldIndexesAround.RemoveAll([](const int& InValue){return InValue == INDEX_NONE;});
	
	while (!CurrentSteps.Contains(InMetaIndex) && !FieldIndexesAround.IsEmpty())
	{
		int NextStepIndex = GetNextStepIndex(FieldIndexesAround);
		
		if (CheckFieldStep(NextStepIndex,InLastSteps, FieldIndexesAround))
		{
			CurrentSteps.Add(NextStepIndex);
			
			CurrentSteps = FindSteps(CurrentSteps, InMetaIndex);
			if (CurrentSteps.Contains(InMetaIndex))
				return CurrentSteps;
				
			CurrentSteps.Remove(NextStepIndex);			
		}
			
		FieldIndexesAround.Remove(NextStepIndex);
	}
	
	return CurrentSteps;
}

void UBoardPathCreatorSubsystem::GetFieldAroundIndex(int InIndex, int& OutLeftFieldIndex, int& OutRightFieldIndex, int& OutUpFieldIndex, int& OutDownFieldIndex) const
{
	if (!Board || InIndex < 0 || InIndex >= Board->GetFields().Num()) return;
	
	int ColumnIndex = INDEX_NONE;
	int RowIndex = INDEX_NONE;
	
	Board->CovertIndexToRowAndColumn(InIndex, RowIndex, ColumnIndex);
	
	if (ColumnIndex < 0 || RowIndex < 0) return;
	
	OutLeftFieldIndex = Board->ConvertRowAndColumnToIndex(RowIndex, ColumnIndex - 1);
	OutRightFieldIndex = Board->ConvertRowAndColumnToIndex(RowIndex, ColumnIndex + 1);
	OutUpFieldIndex = Board->ConvertRowAndColumnToIndex(RowIndex + 1, ColumnIndex);
	OutDownFieldIndex = Board->ConvertRowAndColumnToIndex(RowIndex - 1, ColumnIndex);
}

bool UBoardPathCreatorSubsystem::CheckFieldStep(int InIndex, const TArray<int>& InCurrentStepIndexes, const TArray<int>& InFieldIndexesAround) const
{
	UE_LOGFMT(LogBoard, Log, "UBoardPathCreatorSubsystem::CheckFieldStep - START");
	
	if (!Board || InIndex < 0 || InIndex >= Board->GetFields().Num()) 
	{	
		UE_LOGFMT(LogBoard, Log, "UBoardPathCreatorSubsystem::CheckFieldStep - InIndex: {0} is out of range: {1}", InIndex, Board->GetFields().Num());
		
		return false;
	}
		
	if (InCurrentStepIndexes.Contains(InIndex)) return false;
		
	int FoundSteps = 0;
	for (const auto FieldIndexAround : InFieldIndexesAround)
	{
		if (!InCurrentStepIndexes.Contains(FieldIndexAround)) continue;
		
		UE_LOGFMT(LogBoard, Log, "UBoardPathCreatorSubsystem::CheckFieldStep - FieldIndexAround: {0} is contains in InCurrentStepIndexes: {1}", FieldIndexAround, GetIntArrayToString(InCurrentStepIndexes));
		
		FoundSteps++;
		if (FoundSteps >= 2)
		{
			UE_LOGFMT(LogBoard, Log, "UBoardPathCreatorSubsystem::CheckFieldStep - Two or more index around {0} is contains in InCurrentStepIndexes: {1}", InIndex, GetIntArrayToString(InCurrentStepIndexes));
		
			return false;
		}
	}
	
	UE_LOGFMT(LogBoard, Log, "UBoardPathCreatorSubsystem::CheckFieldStep - Index  {0} correct index in path: {1}", InIndex, GetIntArrayToString(InCurrentStepIndexes));
	
	UE_LOGFMT(LogBoard, Log, "UBoardPathCreatorSubsystem::CheckFieldStep - END");
	return true;	
}

int UBoardPathCreatorSubsystem::GetNextStepIndex(TArray<int> InFieldIndexesAround) const
{	
	if (InFieldIndexesAround.IsEmpty()) return INDEX_NONE;
	
	int RandomIndex = FMath::RandRange(0, InFieldIndexesAround.Num() - 1);
	
	return InFieldIndexesAround[RandomIndex];
}

FString UBoardPathCreatorSubsystem::GetIntArrayToString(const TArray<int>& InArray) const
{
	FString ResultString;
	for (const auto Item : InArray)
		ResultString += FString::FromInt(Item) + ", ";
	
	return ResultString;
}
