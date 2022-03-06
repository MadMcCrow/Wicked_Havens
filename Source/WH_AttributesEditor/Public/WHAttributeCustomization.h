/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

struct FWHAttributeName;
class SWHAttributeNameWidget;

/**
 *	@class FWHAttributeCustomization
 *	Editor Property customisation for attribute Values
 *	@see @struct FWHAttributeName
 *	@see @class SWHAttributeNameWidget
 */
class FWHAttributeCustomization : public IPropertyTypeCustomization, public FEditorUndoClient
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable( new FWHAttributeCustomization );
	}


	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;
	virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;

private:
	/**
	 * Handle to the actual Property being edited (ie the attribute)
	 */
	TSharedPtr<IPropertyHandle> AttributePropertyHandle;

	// Called when changed Attribute Name part of Attribute
	void OnAttributeNameChanged(TSharedPtr<FWHAttributeName> NewName, ESelectInfo::Type Arg) const;

	// Called when changed Attribute Name part of Attribute
	void OnAttributeValueChanged(TSharedPtr<FWHAttributeName> NewName, ESelectInfo::Type Arg) const;

};
