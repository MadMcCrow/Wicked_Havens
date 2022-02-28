/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"


struct FWHAttributeName;


class SWHAttributeNameWidget : public SWidget
{
public:
	//DECLARE_DELEGATE_OneParam(FOnAttributeNameChanged, FWHAttributeName);

	SLATE_BEGIN_ARGS(SWHAttributeNameWidget)
		: _AtributeName(FWHAttributeName())
		{
			_Visibility = EVisibility::SelfHitTestInvisible;
		}
		SLATE_ARGUMENT(FWHAttributeName, AtributeName)
		//SLATE_EVENT(FOnAttributeNameChanged, OnAttributeNameChanged)

	SLATE_END_ARGS()
	
public:

	void Construct(const FArguments& InArgs);

private:

	FName InternalName;
	FGuid InternalGUID;

	void OnTextSelectionChanged(const FText &NewText);

	FGuid GetAttributeNameGuid() const;
	//FOnAttributeNameChanged, OnAttributeNameChanged
};