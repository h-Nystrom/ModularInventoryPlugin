// Fill out your copyright notice in the Description page of Project Settings.
#include "Inventory.h"
#include "Stackable.h"
#include "Net/UnrealNetwork.h"

//TODO: Bug test and Refactor code...


UInventory::UInventory(){PrimaryComponentTick.bCanEverTick = true;}

UInventory::UInventory(const int StorageAmount){
	MaxStorage = StorageAmount;
	PrimaryComponentTick.bCanEverTick = true;
}
void UInventory::BeginPlay() {Super::BeginPlay();}

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventory, Slots);
	DOREPLIFETIME(UInventory, MaxStorage);
}

void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventory::TryAddItem(const FItemData ItemData, int& RestAmount){
    if(ItemData.Amount <= 0 || ItemData.PrimaryItemData == nullptr)
		return false;
	if(IsStackableAdd(ItemData, RestAmount))
		return true;		
	if(Slots.Num() >= MaxStorage)
		return false;
	Slots.Add(FItemData(ItemData.PrimaryItemData, ItemData.Amount));
	return true;
}

bool UInventory::TryRemoveItemWithTags(TArray<FItemData>& ItemSlots, const FGameplayTagContainer ItemTags, const int Amount){
	if(Slots.IsEmpty() || Amount == 0)
		return false;
	auto AmountToRemove = Amount;
	for(int i = 0; i < Slots.Num(); i++){
		if(AmountToRemove <= 0)
			break;
		if(Slots[i].ItemTags != ItemTags)
			continue;
			const auto MaxRemoveAmount = Slots[i].Amount - Amount;
			if(MaxRemoveAmount <= 0){
				ItemSlots.Add(Slots[i]);
				AmountToRemove -= Slots[i].Amount;
				Slots.RemoveAt(i);
				--i;
				continue;
			}
			ItemSlots.Add(FItemData(Slots[i].PrimaryItemData, MaxRemoveAmount));
			Slots[i].Amount -= MaxRemoveAmount;
			AmountToRemove -= MaxRemoveAmount;
	}
	return ItemSlots.IsEmpty();
}

bool UInventory::TryRemoveItemAtIndex(FItemData& ItemData, const int Index, const int Amount){
	if(Amount <= 0 || Slots.IsEmpty() || Slots.Num() < Index+1 || Slots[Index].PrimaryItemData == nullptr)
		return false;
	if(Slots[Index].PrimaryItemData->Implements<UStackable>()){
		if(Amount <= 0)
			return false;
		const auto MaxRemoveAmount = Slots[Index].Amount - Amount;
		if(MaxRemoveAmount <= 0){
			ItemData = Slots[Index];
			Slots.RemoveAt(Index);
			return true;
		}
		ItemData = FItemData(Slots[Index].PrimaryItemData, MaxRemoveAmount);
		Slots[Index].Amount -= MaxRemoveAmount;
		return true;
	}
	ItemData = Slots[Index];
	Slots.RemoveAt(Index);
	return true;
}
bool UInventory::IsStackableAdd(FItemData ItemData, int& RestAmount){
	if(!ItemData.PrimaryItemData->Implements<UStackable>())
		return false;
	const auto MaxStack = IStackable::Execute_GetMaxStack(ItemData.PrimaryItemData);
	
	for (int i = 0; i < Slots.Num(); i++){
		if(GetTypeHash(Slots[i].PrimaryItemData->GetClass()) == GetTypeHash(ItemData.PrimaryItemData->GetClass())){
			if(Slots[i].Amount >= MaxStack)
				continue;
			UE_LOG(LogTemp, Display,TEXT("Found an item to add too!"));//TODO: Remove!
			const auto MaxAmount = MaxStack - Slots[i].Amount;
			if(MaxAmount >= ItemData.Amount){
				Slots[i].Amount += ItemData.Amount;
				return true;
			}
			ItemData.Amount -= MaxAmount;
		}
	}
	RestAmount = ItemData.Amount;
	return false;
}

