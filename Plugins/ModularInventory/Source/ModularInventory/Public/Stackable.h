// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Stackable.generated.h"

UINTERFACE(BlueprintType)
class UStackable : public UInterface{
	GENERATED_BODY()
};

class MODULARINVENTORY_API IStackable{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	int GetMaxStack();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	int GetCurrentAmount();
	UFUNCTION(BlueprintImplementableEvent, BlueprintAuthorityOnly, BlueprintCallable)
	void SetCurrentAmount(int Amount);
};
