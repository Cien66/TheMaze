// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBoardCheckerSubsystem.h"

#include "TheMaze/Board/Components/BoardField.h"
#include "TheMaze/Board/Settings/BoardDeveloperSettings.h"

bool UPlayerBoardCheckerSubsystem::CheckIsValidField(UBoardField* InBoardField) 
{
	if (!InBoardField)
	{
		UE_LOGFMT(LogBoard, Error, "UPlayerBoardCheckerSubsystem::CheckIsValidField - Field is null!");
		
		SetPlayerStepBack();
		
		return false;
	}
	
	const auto BoardSetting = GetDefault<UBoardDeveloperSettings>();
	if (!BoardSetting)
	{
		UE_LOGFMT(LogBoard, Error, "UPlayerBoardCheckerSubsystem::CheckIsValidField - Can't find setting!");
		
		return false;
	}
	
	const auto KindOfField = InBoardField->GetKindOfField();
	
	InBoardField->SetIsHide(false);
	
	if (KindOfField == BoardSetting->StartFieldTag || KindOfField == BoardSetting->ValidFieldTag)
	{				
		UE_LOGFMT(LogBoard, Error, "UPlayerBoardCheckerSubsystem::CheckIsValidField - Field {0} is valid!", InBoardField->GetName());
		
		UpdateLastStepLocationAndRotation();
		
		OnCheckedField.Broadcast(InBoardField, KindOfField);
		
		LastSafeField = InBoardField;
		
		return true;
	}
	
	if (KindOfField == BoardSetting->MetaFieldTag)
	{
		UE_LOGFMT(LogBoard, Error, "UPlayerBoardCheckerSubsystem::CheckIsValidField - Field {0} is meta!", InBoardField->GetName());
		
		UpdateLastStepLocationAndRotation();
		
		LastSafeField = InBoardField;
		
		OnCheckedField.Broadcast(InBoardField, KindOfField);
		
		OnPlayerOnMeta.Broadcast();
		
		return true;
	}
	
	SetPlayerStepBack();
	
	OnPlayerStepBackDelegate.Broadcast(LastSafeField.Get(), InBoardField);
	
	return false;
}

void UPlayerBoardCheckerSubsystem::SetPlayerPawn(APawn* InPlayerPawn)
{
	PlayerPawn = InPlayerPawn;
	
	UpdateLastStepLocationAndRotation();	
}

void UPlayerBoardCheckerSubsystem::SetSafeField(UBoardField* InSafeField)
{
	LastSafeField = InSafeField;
}

void UPlayerBoardCheckerSubsystem::SetPlayerStepBack() const
{
	if (PlayerPawn.IsValid())
		PlayerPawn->SetActorLocationAndRotation(LastStepPlayerLocation, LastStepPlayerRotation);	
}

void UPlayerBoardCheckerSubsystem::UpdateLastStepLocationAndRotation()
{
	if (PlayerPawn.IsValid())
	{
		LastStepPlayerLocation = PlayerPawn->GetActorLocation();
		LastStepPlayerRotation = PlayerPawn->GetActorRotation();
	}
}
