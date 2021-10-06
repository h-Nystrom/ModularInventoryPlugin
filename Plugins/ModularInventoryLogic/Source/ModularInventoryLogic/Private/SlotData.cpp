#include "SlotData.h"

#include "BaseItemData.h"

FSlotData::FSlotData(): Amount(0){ }
FSlotData::FSlotData(const TSubclassOf<UBaseItemData> BaseItemData, const int Amount){
	BaseItemDataRef = BaseItemData;
	this->Amount = Amount;
	this->ItemTags = BaseItemData.GetDefaultObject()->ItemType;
}
