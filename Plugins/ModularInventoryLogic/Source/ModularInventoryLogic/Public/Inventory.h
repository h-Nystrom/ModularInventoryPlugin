// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SlotData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


class IItem;
UCLASS( ClassGroup=(Custom), Abstract, Blueprintable, meta=(BlueprintSpawnableComponent) )
class MODULARINVENTORYLOGIC_API UInventory : public UActorComponent{
	
	GENERATED_BODY()
	
	public:	
		UInventory();
		UInventory(const int StorageAmount);
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Items")
		TArray<FSlotData> Slots;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Items")
		float MaxStorage;
	
	protected:
		virtual void BeginPlay() override;
		bool IsStackableAdd(AActor* ItemActor, const UBaseItemData* BaseItemData);
		
	public:	
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		UFUNCTION(BlueprintCallable,BlueprintAuthorityOnly, Category="Inventory")
		bool TryAddItem(AActor* ItemActor);
		UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
		bool TryRemoveItemWithTags(TArray<FSlotData>& ItemSlots, FGameplayTagContainer ItemTags,int Amount = 1);
		UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
		bool TryRemoveItemAtIndex(FSlotData& ItemSlots, int Index,int Amount = 1);
};
