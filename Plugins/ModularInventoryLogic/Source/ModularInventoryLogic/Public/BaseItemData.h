// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "BaseItemData.generated.h"

UCLASS(Abstract, Blueprintable)
class MODULARINVENTORYLOGIC_API UBaseItemData : public UPrimaryDataAsset{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		UStaticMesh* Mesh;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		FText Name;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		UTexture* Icon;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		FGameplayTagContainer ItemType;
};
