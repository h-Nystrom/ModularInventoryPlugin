// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

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
		bool IsStackableAdd(AActor* ActorItem, UPrimaryItemData* ItemData);
		
	public:	
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		UFUNCTION(BlueprintCallable,BlueprintAuthorityOnly, Category="Inventory")
		bool TryAddItem(AActor* ActorItem);
		UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
		bool TryRemoveItemWithTags(TArray<FItemData>& ItemSlots, FGameplayTagContainer ItemTags,int Amount);
};
