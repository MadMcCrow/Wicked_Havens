 /* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeValueWidget.h"
#include "DetailLayoutBuilder.h"
#include "SEnumCombo.h"
#include "SSearchableComboBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "SPinTypeSelector.h"

#define LOCTEXT_NAMESPACE "SWHAttributeValueWidget"



void SWHAttributeValueWidget::Construct(const FArguments& InArgs)
{
	EditedAttributeValue = InArgs._AtributeValue;
	OnTypeSelectionChange = InArgs._OnTypeSelectionChange;

	bool bTypePicker = InArgs._bShowTypeSelector.Get();

}

void SWHAttributeValueWidget::CommitValue()
{
	OnTypeSelectionChange.ExecuteIfBound(MakeShared<FWHAttributeValue>(EditedAttributeValue.Get()));
}

 TSharedRef<SWidget> SWHAttributeValueWidget::MakeValueEntryWidget()
 {
	return SNullWidget::NullWidget;
 }


#undef LOCTEXT_NAMESPACE
