// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.h"
#include "ItemData.h"
#include "Equipments.generated.h"


UCLASS(ClassGroup=(Custom), Abstract, Blueprintable, meta=(BlueprintSpawnableComponent))
class MODULARINVENTORY_API UEquipments : public UInventory{
	GENERATED_BODY()
	int FindIndexFromTags(const FGameplayTagContainer ItemTags);
public:
	// Sets default values for this component's properties
	UEquipments();
	UEquipments(const int StorageAmount);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Equipments")
	TArray<FItemData> EquipmentSlots;

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	bool TryAddItemToSlot(FGameplayTagContainer ItemTags);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	bool UnEquipItemFromSlotWithTags(FGameplayTagContainer EquipmentSlotTags);
};
