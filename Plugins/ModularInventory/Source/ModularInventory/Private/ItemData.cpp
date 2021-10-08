#include "ItemData.h"

FItemData::FItemData(): PrimaryItemData(nullptr), Amount(0){}

FItemData::FItemData(UPrimaryItemData* PrimaryItemData, const int Amount){
	this->PrimaryItemData = PrimaryItemData;
	this->Amount = Amount;
	this->ItemTags = PrimaryItemData->ItemType;
}
FItemData::FItemData(const FItemData& ItemData){
	this->PrimaryItemData = ItemData.PrimaryItemData;
	this->Amount = ItemData.Amount;
	this->ItemTags = PrimaryItemData->ItemType;
}
void FItemData::KeepTag(const FItemData& ItemSlot){
	this->PrimaryItemData = ItemSlot.PrimaryItemData;
	this->Amount = ItemSlot.Amount;
}
