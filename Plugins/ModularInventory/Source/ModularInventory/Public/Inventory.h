// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


class IItem;
UCLASS( ClassGroup=(Custom), Abstract, Blueprintable, meta=(BlueprintSpawnableComponent) )
class MODULARINVENTORY_API UInventory : public UActorComponent{
	
	GENERATED_BODY()
	
	public:	
		UInventory();
		UInventory(const int StorageAmount);
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Items")
		TArray<FItemData> Slots;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Items")
		float MaxStorage;
	
	protected:
		virtual void BeginPlay() override;
		bool IsStackableAdd(FItemData ItemData, int& RestAmount);
		
	public:	
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		UFUNCTION(BlueprintCallable,BlueprintAuthorityOnly, Category="Inventory")
		bool TryAddItem(FItemData ItemData, int& RestAmount);
		UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
		bool TryRemoveItemWithTags(TArray<FItemData>& ItemSlots, FGameplayTagContainer ItemTags,int Amount = 1);
		UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
		bool TryRemoveItemAtIndex(FItemData& ItemData, int Index,int Amount = 1);
};
