/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
//#include "WHAttributeCustomization.generated.h"


class FWHAttributeNameCustomization : public IPropertyTypeCustomization, public FEditorUndoClient
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable( new FWHAttributeNameCustomization );
	}


	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;
	virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;

private:
	/**
	 * Handle to the actual Property being edited (ie the attribute)
	 */
	TSharedPtr<IPropertyHandle> AttributeNamePropertyHandle;

	/** The Attribute names */
	TArray<TSharedPtr<FString>> AttributeNamesStrings;

	/** Called when list of attributes change */
	void UpdateFromAttributeList();

	/** Get GUID to display */
	FText GetAttributeGUID() const;

	void OnAttributeChanged(TSharedPtr<FString, ESPMode::Fast> String, ESelectInfo::Type Arg) const;

};
