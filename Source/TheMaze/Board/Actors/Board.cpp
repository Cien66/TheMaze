// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "TheMaze/Board/Components/BoardField.h"
#include "Logging/StructuredLog.h"
#include "TheMaze/Board/Subsystems/BoardPathCreatorSubsystem.h"

ABoard::ABoard()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	if (const auto PathCreator = GetWorld() ? GetWorld()->GetSubsystem<UBoardPathCreatorSubsystem>() : nullptr)
		PathCreator->RegisterBoard(this);
}

void ABoard::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//ClearBoard();
	
	if (const auto PathCreator = GetWorld() ? GetWorld()->GetSubsystem<UBoardPathCreatorSubsystem>() : nullptr)
		PathCreator->UnregisterBoard(this);
	
	Super::EndPlay(EndPlayReason);
}

void ABoard::BuildBoard()
{
	ClearBoard();
	
	if (BoardSize.GetMin() <= 0 || BoardSize.GetMax() <= 0)
	{
		UE_LOGFMT(LogBoard, Error, "ABoard::BuildBoard() - Invalid board size: {0}", BoardSize.ToString());
		
		return;
	}
	
	if (FieldClass == nullptr)
	{
		UE_LOGFMT(LogBoard, Error, "ABoard::BuildBoard() - Field class is null!");
		
		return;
	}
	
	int BoardLenght = BoardSize.GetMin() * BoardSize.GetMax(); 
	for (int i = 0; i < BoardLenght; i++)
	{
		const int Row = i / BoardSize.GetMin();
		const int Column = i % BoardSize.GetMin();
		
		FString FieldName = "Field" + FString::FromInt(i);
		if (auto Field = NewObject<UBoardField>(this, FieldClass, *FieldName))
		{	
			Field->RegisterComponent();
			Field->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			Field->CreationMethod = EComponentCreationMethod::Instance;
			
			Fields.Add(Field);
			
			float LocationX = (Field->GetFieldSize().GetMin() + SpaceBetweenFields.GetMin()) * Column;
			float LocationY = (Field->GetFieldSize().GetMax() + SpaceBetweenFields.GetMax()) * Row;
			
			Field->SetRelativeLocation(FVector(LocationX, LocationY, GetActorLocation().Z));
		}
	}
}

void ABoard::ClearBoard()
{
	for (auto BoardField : Fields)
	{
		if (!BoardField) continue;
		BoardField->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);		
		BoardField->DestroyComponent();
	}
	
	Fields.Empty();
}


void ABoard::CovertIndexToRowAndColumn(int InIndex, int& OutRow, int& OutColumn) const
{
	OutRow = INDEX_NONE;
	OutColumn = INDEX_NONE;
	
	if (InIndex < 0 || InIndex >= GetFields().Num()) return;
	
	OutRow = InIndex / GetBoardSize().GetMin();
	OutColumn = InIndex % GetBoardSize().GetMin();	
}

int ABoard::ConvertRowAndColumnToIndex(int InRow, int InColumn) const
{
	if (InRow < 0 || InColumn < 0) return INDEX_NONE;
	
	const int Index = InRow * GetBoardSize().GetMin() + InColumn;
	
	return Index;
}