/* Copyright © Noé Perard-Gayot 2022. */

#include "Items/WHItem.h"
#include "Items/WHItemTableRow.h"


bool UWHItem::IsSame(const TObjectPtr<UWHItem>& OtherItem) const
{
	if (OtherItem.IsNull())
		return false;

	if (OtherItem.GetClass() != GetClass())
		return false;


	// TODO : Check each and every properties
	

	return true;
}
