/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

struct FWHAttributeName;
class SWHAttributeNameWidget;

/**
 *	@class FWHAttributeNameCustomization
 *	Editor Property customisation for attribute name
 *	@see @struct FWHAttributeName
 *	@see @class SWHAttributeNameWidget
 */
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

	// Called when changed Attribute
	void OnAttributeChanged(TSharedPtr<FWHAttributeName> NewName, ESelectInfo::Type Arg) const;

};
