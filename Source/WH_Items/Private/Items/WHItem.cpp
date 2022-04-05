/* Copyright © Noé Perard-Gayot 2022. */

#include "Items/WHItem.h"
#include "Items/WHItemTableRow.h"


bool UWHItem::IsSame(const TObjectPtr<UWHItem>& OtherItem) const
{
	if (OtherItem.IsNull())
		return false;

	if (OtherItem.GetClass() != GetClass())
		return false;

	if (OtherItem.Get()->ItemHandle != ItemHandle)
		return false;


	// TODO : Check each and every properties

	return true;
}

TOptional<FWHItemTableRow> UWHItem::GetItemRow() const
{
	if (const auto RowPtr = ItemHandle.GetRow<FWHItemTableRow>(nullptr))
	{
		return*RowPtr;
	}
	return FWHItemTableRow();
}
