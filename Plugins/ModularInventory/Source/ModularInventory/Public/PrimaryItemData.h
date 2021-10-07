// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PrimaryItemData.generated.h"

class UGameplayEffect;
UCLASS(Abstract, Blueprintable)
class MODULARINVENTORY_API UPrimaryItemData : public UPrimaryDataAsset{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		UStaticMesh* Mesh;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		UGameplayEffect* GameplayEffect;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		FText Name;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		FText Description;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		UTexture2D* Icon;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
		FGameplayTagContainer ItemType;
};
