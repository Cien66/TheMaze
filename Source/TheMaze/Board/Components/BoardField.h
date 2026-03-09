// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/StaticMeshComponent.h"
#include "BoardField.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBoard, Log, All)
/**
 * Field of board 
 * when actor stand by on, field check own status and change color 
 */
UCLASS()
class THEMAZE_API UBoardField : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool SetKindOfField(FGameplayTag InKindOfField);
	UFUNCTION(BlueprintPure)
	FGameplayTag GetKindOfField() const { return KindOfField; }
	
	
	UFUNCTION(BlueprintCallable)
	void SetIsHide(bool bInIsHide);
	UFUNCTION(BlueprintPure)
	bool GetIsHide() const { return bIsHide;}
	
	UFUNCTION(BlueprintPure)
	FVector2D GetFieldSize() const {return FieldSize;}

	UFUNCTION(BlueprintPure)
	TMap<FGameplayTag, TSoftObjectPtr<UMaterial>> GetFieldTextures() {return FieldTextures;}
	
protected:
	virtual void PostInitProperties() override;
	
private:
	UFUNCTION()
	bool SetMaterialByTag(const FGameplayTag& Tag);
	
	UPROPERTY(EditAnywhere)
	FVector2D FieldSize;
		
	UPROPERTY(EditAnywhere)
	FGameplayTag KindOfField;
	
	UPROPERTY(EditAnywhere)
	bool bIsHide = true;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag HideTag;	
	
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, TSoftObjectPtr<UMaterial>> FieldTextures;
};
