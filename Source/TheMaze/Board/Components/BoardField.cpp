// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardField.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogBoard);

bool UBoardField::SetKindOfField(FGameplayTag InKindOfField)
{
	if (!InKindOfField.IsValid())
	{
		UE_LOGFMT(LogBoard, Error, "UBoardField::SetKindOfField() - InKindOfField is Invalid");
		
		return false;
	}
	
	if (!FieldTextures.Contains(KindOfField))
	{
		UE_LOGFMT(LogBoard, Error, "UBoardField::SetKindOfField() - Can't find InKindOfField: {0} in FieldTextures", InKindOfField.ToString());
		
		return false;
	}		
		
	KindOfField = InKindOfField;
	
	UE_LOGFMT(LogBoard, VeryVerbose, "UBoardField::SetKindOfField() - Set KindOfField to: {0}", InKindOfField.ToString());
	
	if (!bIsHide)
		SetMaterialByTag(KindOfField);
	
	return true;
}

void UBoardField::SetIsHide(bool bInIsHide)
{
	if (bInIsHide == bIsHide)
	{
		UE_LOGFMT(LogBoard, Error, "UBoardField::SetIsHide() - bInIsHide is the same as bIsHide: {0}", bIsHide ? "TRUE" : "FALSE");
		
		return;
	}
	
	UE_LOGFMT(LogBoard, VeryVerbose, "UBoardField::SetIsHide() - Set bIsHide to: {0}", bIsHide ? "TRUE" : "FALSE");
	
	bIsHide = bInIsHide;
	
	SetMaterialByTag(bIsHide ? HideTag : KindOfField);		
}

void UBoardField::PostInitProperties()
{
	Super::PostInitProperties();
	
	SetMaterialByTag(bIsHide ? HideTag : KindOfField);
}

bool UBoardField::SetMaterialByTag(const FGameplayTag& Tag)
{
	if (!FieldTextures.Contains(Tag))
	{
		UE_LOGFMT(LogBoard, Error, "UBoardField::SetMaterialByTag() - Can't find Tag: {0} in FieldTextures", Tag.ToString());
		
		return false;
	}		

	const auto SoftTexture = FieldTextures[Tag];
	const auto Texture = SoftTexture.LoadSynchronous();
	if (!Texture)
	{
		UE_LOGFMT(LogBoard, Error, "UBoardField::SetMaterialByTag() - Loaded texture for {0} is null", Tag.ToString());
		
		return false;
	}
	
	SetMaterial(0, Texture);
	
	return true;
}
