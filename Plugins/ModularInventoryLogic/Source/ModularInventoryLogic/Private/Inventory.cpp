// Fill out your copyright notice in the Description page of Project Settings.
#include "Inventory.h"

#include "BaseItemData.h"
#include "Item.h"
#include "Stackable.h"
#include "Net/UnrealNetwork.h"

//TODO: Bug test and Refactor code..


UInventory::UInventory(){
	PrimaryComponentTick.bCanEverTick = true;
}

UInventory::UInventory(const int StorageAmount){
	MaxStorage = StorageAmount;
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventory::BeginPlay(){
	Super::BeginPlay();
}

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventory, Slots);
	DOREPLIFETIME(UInventory, MaxStorage);
}

void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventory::TryAddItem(AActor* ItemActor){
    if(ItemActor == nullptr || !ItemActor->Implements<UItem>()){
		UE_LOG(LogTemp,Error,TEXT("Error: BaseItemData is null or not an Item"));
		return false;
	}
    const auto BaseItemData = IItem::Execute_GetItem(ItemActor);
	if(BaseItemData == nullptr)
		return false;
	if(IsStackableAdd(ItemActor, BaseItemData))
		return true;		
	if(Slots.Num() >= MaxStorage){
		UE_LOG(LogTemp,Display,TEXT("Inventory is full!"));
		return false;
	}
	Slots.Add(FSlotData(BaseItemData->GetClass(), 1));
	return true;
}
bool UInventory::TryRemoveItemWithTags(TArray<FSlotData>& ItemSlots, const FGameplayTagContainer ItemTags, const int Amount){
	if(Slots.IsEmpty() || Amount == 0){
		UE_LOG(LogTemp,Error,TEXT("Error: Slots or TagContainer is empty or Amount <= 0!"));
		return false;
	}
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
			ItemSlots.Add(FSlotData(Slots[i].BaseItemDataRef, MaxRemoveAmount));
			Slots[i].Amount -= MaxRemoveAmount;
			AmountToRemove -= MaxRemoveAmount;
	}
	return ItemSlots.IsEmpty();
}

bool UInventory::TryRemoveItemAtIndex(FSlotData& ItemSlots, const int Index, const int Amount){
	if(Slots.IsEmpty() || Slots.Num() < Index+1 || Slots[Index].BaseItemDataRef == nullptr){
		UE_LOG(LogTemp,Error,TEXT("Error: Item is out of range or null!"));
		return false;
	}
	if(Slots[Index].BaseItemDataRef->Implements<UStackable>()){
		if(Amount <= 0){
			UE_LOG(LogTemp,Display,TEXT("Stackable Item.Amount == 0!"));
			return false;
		}
		const auto MaxRemoveAmount = Slots[Index].Amount - Amount;
		if(MaxRemoveAmount <= 0){
			ItemSlots = Slots[Index];
			Slots.RemoveAt(Index);
			return true;
		}
		ItemSlots = FSlotData(Slots[Index].BaseItemDataRef, MaxRemoveAmount);
		Slots[Index].Amount -= MaxRemoveAmount;
		return true;
	}
	ItemSlots = Slots[Index];
	Slots.RemoveAt(Index);
	return true;
}
bool UInventory::IsStackableAdd(AActor* ItemActor, const UBaseItemData* BaseItemData){
	if(!ItemActor->Implements<UStackable>())
		return false;
	const auto MaxStack = IStackable::Execute_GetMaxStack(ItemActor);
	auto Amount = IStackable::Execute_GetCurrentAmount(ItemActor);
	if(Amount <= 0){
		UE_LOG(LogTemp,Display,TEXT("Stackable Item.Amount == 0!"));
		return false;
	}
	for (int i = 0; i < Slots.Num(); i++){
		if(GetTypeHash(Slots[i].BaseItemDataRef->GetClass()) == GetTypeHash(BaseItemData->GetClass())){
			if(Slots[i].Amount >= MaxStack)
				continue;
			UE_LOG(LogTemp, Display,TEXT("Found an item to add too!"))
			const auto MaxAmount = MaxStack - Slots[i].Amount;
			if(MaxAmount >= Amount){
				Slots[i].Amount += Amount;
				return true;
			}
			Amount -= MaxAmount;
		}
	}
	if(Slots.Num() >= MaxStorage){
		UE_LOG(LogTemp,Display,TEXT("Inventory is full!"));
		IStackable::Execute_SetCurrentAmount(ItemActor, Amount);
		return true;
	}
	Slots.Add(FSlotData(BaseItemData->GetClass(), Amount));
	return true;
}

