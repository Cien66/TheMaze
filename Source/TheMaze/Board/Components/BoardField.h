// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/StaticMeshComponent.h"
#include "BoardField.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBoard, Log, All)
/**
 * Field of board 
 * Apply color by kind of field or hide 
 */
UCLASS()
class THEMAZE_API UBoardField : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	/*
	 *Set new kind of field and call update material by tag if not hide
	 *@param InKindOfField - new kind of field */
	UFUNCTION(BlueprintCallable)
	bool SetKindOfField(FGameplayTag InKindOfField);

	/**
	 * Return kind of field
	 * @return Kind of field this object in gameplay tag
	 */
	UFUNCTION(BlueprintPure)
	FGameplayTag GetKindOfField() const { return KindOfField; }

	/**
	 * Set field as hide or not,
	 * call update material by hide tag if true or kind of field if not hide  
	 * @param bInIsHide flag of field is hide 
	 */
	UFUNCTION(BlueprintCallable)
	void SetIsHide(bool bInIsHide);
	
	/**
	 * Return status of field is hide
	 * @return flag of field is hide 
	 */
	UFUNCTION(BlueprintPure)
	bool GetIsHide() const { return bIsHide;}

	/**
	 * Return size of field by weight and high
	 * @return size of field 
	 */
	UFUNCTION(BlueprintPure)
	FVector2D GetFieldSize() const {return FieldSize;}

	/**
	 * 
	 * @return Map off all possible status for this field and their textures
	 */
	UFUNCTION(BlueprintPure)
	TMap<FGameplayTag, TSoftObjectPtr<UMaterial>> GetFieldTextures() {return FieldTextures;}
	
protected:
	virtual void PostInitProperties() override;
	
private:
	/**
	 * Update material by tag
	 * @param Tag to change material
	 * @return material is changed by tag
	 */
	UFUNCTION()
	bool SetMaterialByTag(const FGameplayTag& Tag);

	/**
	 * Defined size of field
	 */
	UPROPERTY(EditAnywhere)
	FVector2D FieldSize;

	/**
	 * Defined kind of field e.g. valid, meta, start, invalid
	 */
	UPROPERTY(EditAnywhere)
	FGameplayTag KindOfField;

	/**
	 * Defined status of field is hide or not
	 */
	UPROPERTY(EditAnywhere)
	bool bIsHide = true;

	/**
	 * Defined hide tag for material
	 */
	UPROPERTY(EditAnywhere)
	FGameplayTag HideTag;

	/**
	 * Defined material by kind of field and hide tag
	 */
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, TSoftObjectPtr<UMaterial>> FieldTextures;
};
