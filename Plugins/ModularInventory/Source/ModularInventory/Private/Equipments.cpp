// Fill out your copyright notice in the Description page of Project Settings.
#include "Equipments.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UEquipments::UEquipments(){PrimaryComponentTick.bCanEverTick = true;}
UEquipments::UEquipments(const int StorageAmount){this->MaxStorage = StorageAmount;}
void UEquipments::BeginPlay(){Super::BeginPlay();}

void UEquipments::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEquipments, EquipmentSlots);
}

void UEquipments::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UEquipments::TryAddItemToSlot(const FGameplayTagContainer ItemTags){
	if(ItemTags.IsEmpty() || EquipmentSlots.IsEmpty())
		return false;
	const auto TargetItemIndex = FindIndexFromTags(ItemTags);
	if(TargetItemIndex == -1)
		return false;
	for (int i = 0; i < EquipmentSlots.Num(); i++){
		if(ItemTags != EquipmentSlots[i].ItemTags)
			continue;
		if(EquipmentSlots[i].PrimaryItemData != nullptr)
			Slots.Add(FItemData(EquipmentSlots[i]));
		EquipmentSlots[i].KeepTag(Slots[TargetItemIndex]);
		Slots.RemoveAt(TargetItemIndex);
		return true;
	}
	return false;
}

bool UEquipments::UnEquipItemFromSlotWithTags(const FGameplayTagContainer EquipmentSlotTags){
	for (int i = 0; i < EquipmentSlots.Num(); i++){
		if(EquipmentSlotTags.HasAny(EquipmentSlots[i].ItemTags))
			continue;
		if(EquipmentSlots[i].PrimaryItemData == nullptr){
			Slots.Add(EquipmentSlots[i]);
			EquipmentSlots[i].PrimaryItemData = nullptr;
			return true;
		}
	}
	return false;
}
int UEquipments::FindIndexFromTags(const FGameplayTagContainer ItemTags){
	for (int i = 0; i < Slots.Num(); i++){
		if(ItemTags != Slots[i].ItemTags)
			continue;
		return i;
	}
	return -1;
}

