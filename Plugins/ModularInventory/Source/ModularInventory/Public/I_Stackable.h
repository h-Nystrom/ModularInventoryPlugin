// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Stackable.generated.h"

UINTERFACE(BlueprintType)
class UI_Stackable : public UInterface{
	GENERATED_BODY()
};

class MODULARINVENTORY_API II_Stackable{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	int GetMaxStack();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	int GetCurrentAmount();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, BlueprintAuthorityOnly)
	void SetCurrentAmount(int Amount);
};
