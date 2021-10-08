// Fill out your copyright notice in the Description page of Project Settings.
#include "Inventory.h"

#include "I_Item.h"
#include "I_Stackable.h"
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

bool UInventory::TryAddItem(AActor* ActorItem){
	if(ActorItem == nullptr || !ActorItem->Implements<UI_Item>()){
  		UE_LOG(LogTemp, Display,TEXT("Null or doesn't implement I_Item!"));
		return false;
	}
	const auto ItemData = II_Item::Execute_GetItemData(ActorItem);
	if(IsStackableAdd(ActorItem, ItemData))
		return true;		
	if(Slots.Num() >= MaxStorage)
		return false;
	Slots.Add(FItemData(ItemData, 1));
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
	return !ItemSlots.IsEmpty();
}
bool UInventory::IsStackableAdd(AActor* ActorItem, UPrimaryItemData* ItemData){
	if(!ActorItem->Implements<UI_Stackable>())
		return false;
	//TODO: Test code...
	const auto MaxStack = II_Stackable::Execute_GetMaxStack(ActorItem);
	auto Amount =  II_Stackable::Execute_GetCurrentAmount(ActorItem);
	for (int i = 0; i < Slots.Num(); i++){
		if(GetTypeHash(Slots[i].PrimaryItemData->GetClass()) == GetTypeHash(ItemData)){
			if(Slots[i].Amount >= MaxStack)
				continue;
			UE_LOG(LogTemp, Display,TEXT("Found an item to add too!"));//TODO: Remove!
			const auto MaxAmount = MaxStack - Slots[i].Amount;
			if(MaxAmount >= Amount){
				Slots[i].Amount += Amount;
				return true;
			}
			Amount -= MaxAmount;
		}
	}
	if(Slots.Num() >= MaxStorage){
		II_Stackable::Execute_SetCurrentAmount(ActorItem,Amount);
		return false;
	}
	Slots.Add(FItemData(ItemData, Amount));
	return true;
}

