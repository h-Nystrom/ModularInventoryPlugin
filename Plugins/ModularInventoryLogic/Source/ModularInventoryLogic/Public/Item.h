// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotData.h"
#include "UObject/Interface.h"
#include "Item.generated.h"

UINTERFACE(BlueprintType)
class UItem : public UInterface{
	GENERATED_BODY()
};

class MODULARINVENTORYLOGIC_API IItem{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item")
		UBaseItemData* GetItem();
};
