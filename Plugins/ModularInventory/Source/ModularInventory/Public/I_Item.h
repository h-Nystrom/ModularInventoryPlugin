// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PrimaryItemData.h"
#include "UObject/Interface.h"
#include "I_Item.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UI_Item : public UInterface{
	GENERATED_BODY()
};

/**
 * 
 */
class MODULARINVENTORY_API II_Item{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item")
	FGameplayTag GetItemTags();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item")
	bool TrySetItemData(UPrimaryItemData* PrimaryItemData, bool SimulatePhysics);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item")
	UPrimaryItemData* GetItemData();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item")
	bool TrySetItemMaterial(UMaterialInstance* ItemMaterial);
};
