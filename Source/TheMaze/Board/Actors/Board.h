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
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<UBoardField*> GetFields() const {return Fields;}
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void BuildBoard();
		
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UFUNCTION()
	void ClearBoard();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBoardField> FieldClass;
	
	UPROPERTY(EditAnywhere)
	FInt32Point BoardSize;
	UPROPERTY(EditAnywhere)
	FVector2D SpaceBetweenFields;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<TObjectPtr<UBoardField>> Fields;
};
