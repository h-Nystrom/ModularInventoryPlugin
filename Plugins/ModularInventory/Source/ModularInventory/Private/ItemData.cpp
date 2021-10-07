#include "ItemData.h"
#include "PrimaryItemData.h"

FItemData::FItemData(): Amount(0){ }
FItemData::FItemData(const TSubclassOf<UPrimaryItemData> PrimaryItemData, const int Amount){
	this->PrimaryItemData = PrimaryItemData;
	this->Amount = Amount;
	this->ItemTags = PrimaryItemData.GetDefaultObject()->ItemType;
}
