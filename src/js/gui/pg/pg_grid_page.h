
#ifndef _WX_PG_GRID_PAGE_H_
#define _WX_PG_GRID_PAGE_H_

#include <wx/propgrid/property.h>
#include <wx/propgrid/manager.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class GridPage : public ApiWrapper<GridPage, wxPropertyGridPage>
			{
			public:
				

				WXJS_DECLARE_GET_PROP(wxPropertyGridPage)
				WXJS_DECLARE_SET_PROP(wxPropertyGridPage)
				WXJS_DECLARE_CONSTRUCTOR(wxPropertyGridPage)
				WXJS_DECLARE_DESTRUCTOR(wxPropertyGridPage)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_INDEX
					,	P_FIT_COLUMNS
					,	P_ROOT
					,	P_TOOL_ID
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(getSplitterPosition)
				WXJS_DECLARE_METHOD(setSplitterPosition)


				//-----------------------------------------------
				//	wxPropertyGridInterface
				//-----------------------------------------------
				WXJS_DECLARE_METHOD(append)
				WXJS_DECLARE_METHOD(appendIn)
				WXJS_DECLARE_METHOD(beginAddChildren)
				WXJS_DECLARE_METHOD(clear)
				WXJS_DECLARE_METHOD(clearSelection)
				WXJS_DECLARE_METHOD(clearModifiedStatus)
				WXJS_DECLARE_METHOD(collapse)
				WXJS_DECLARE_METHOD(collapseAll)
				WXJS_DECLARE_METHOD(changePropertyValue)
				WXJS_DECLARE_METHOD(deleteProperty)
				WXJS_DECLARE_METHOD(disableProperty)
				WXJS_DECLARE_METHOD(editorValidate)
				WXJS_DECLARE_METHOD(enableProperty)
				WXJS_DECLARE_METHOD(endAddChildren)
				WXJS_DECLARE_METHOD(expand)
				WXJS_DECLARE_METHOD(expandAll)
				WXJS_DECLARE_METHOD(getColumnProportion)
				WXJS_DECLARE_METHOD(getFirstChild)
				WXJS_DECLARE_METHOD(getProperty)
				//WXJS_DECLARE_METHOD(getPropertiesWithFlag) TODO...
				WXJS_DECLARE_METHOD(getPropertyAttribute)
				//WXJS_DECLARE_METHOD(getPropertyAttributes)  TODO...
				WXJS_DECLARE_METHOD(getPropertyBackgroundColour)
				WXJS_DECLARE_METHOD(getPropertyCategory)
				//WXJS_DECLARE_METHOD(getPropertyClientData) ... TODO,,,
				WXJS_DECLARE_METHOD(getPropertyByLabel)
				WXJS_DECLARE_METHOD(getPropertyByName)
				WXJS_DECLARE_METHOD(getPropertyEditor)
				WXJS_DECLARE_METHOD(getPropertyHelpString)
				WXJS_DECLARE_METHOD(getPropertyImage)
				WXJS_DECLARE_METHOD(getPropertyLabel)
				WXJS_DECLARE_METHOD(getPropertyName)
				WXJS_DECLARE_METHOD(getPropertyParent)
				WXJS_DECLARE_METHOD(getPropertyTextColour)
				WXJS_DECLARE_METHOD(getPropertyValidator)
				WXJS_DECLARE_METHOD(getPropertyValue)
				WXJS_DECLARE_METHOD(getPropertyValueAsArrayInt)
				WXJS_DECLARE_METHOD(getPropertyValueAsArrayString)
				WXJS_DECLARE_METHOD(getPropertyValueAsBool)
				WXJS_DECLARE_METHOD(getPropertyValueAsDateTime)
				WXJS_DECLARE_METHOD(getPropertyValueAsDouble)
				WXJS_DECLARE_METHOD(getPropertyValueAsInt)
				WXJS_DECLARE_METHOD(getPropertyValueAsLong)
				//WXJS_DECLARE_METHOD(getPropertyValueAsLongLong)
				WXJS_DECLARE_METHOD(getPropertyValueAsString)
				WXJS_DECLARE_METHOD(getPropertyValueAsULong)
				//WXJS_DECLARE_METHOD(getPropertyValueAsULongLong)
				WXJS_DECLARE_METHOD(getPropertyValues)
				//WXJS_DECLARE_METHOD(getVIterator) TODO...
				WXJS_DECLARE_METHOD(hideProperty)
				WXJS_DECLARE_METHOD(insert)
				WXJS_DECLARE_METHOD(isPropertyCategory)
				WXJS_DECLARE_METHOD(isPropertyEnabled)
				WXJS_DECLARE_METHOD(isPropertyExpanded)
				WXJS_DECLARE_METHOD(isPropertyModified)
				WXJS_DECLARE_METHOD(isPropertySelected)
				WXJS_DECLARE_METHOD(isPropertyShown)
				WXJS_DECLARE_METHOD(isPropertyValueUnspecified)
				WXJS_DECLARE_METHOD(limitPropertyEditing)
				//WXJS_DECLARE_METHOD(refreshGrid) TODO...
				WXJS_DECLARE_METHOD(removeProperty)
				WXJS_DECLARE_METHOD(replaceProperty)
				WXJS_DECLARE_METHOD(restoreEditableState)
				WXJS_DECLARE_METHOD(saveEditableState)
				WXJS_DECLARE_METHOD(setColumnProportion)
				WXJS_DECLARE_METHOD(setPropertyAttribute)
				WXJS_DECLARE_METHOD(setPropertyAttributeAll)
				WXJS_DECLARE_METHOD(setPropertyBackgroundColour)
				WXJS_DECLARE_METHOD(setPropertyCell)
				//WXJS_DECLARE_METHOD(setPropertyClientData) TODO...
				WXJS_DECLARE_METHOD(setPropertyColoursToDefault)
				WXJS_DECLARE_METHOD(setPropertyEditor)
				WXJS_DECLARE_METHOD(setPropertyLabel)
				WXJS_DECLARE_METHOD(setPropertyName)
				WXJS_DECLARE_METHOD(setPropertyReadOnly)
				WXJS_DECLARE_METHOD(setPropertyValueUnspecified)
				//WXJS_DECLARE_METHOD(setPropertyValues) TODO...
				WXJS_DECLARE_METHOD(setPropertyHelpString)
				WXJS_DECLARE_METHOD(setPropertyImage)
				WXJS_DECLARE_METHOD(setPropertyMaxLength)
				WXJS_DECLARE_METHOD(setPropertyTextColour)
				WXJS_DECLARE_METHOD(setPropertyValidator)
				WXJS_DECLARE_METHOD(setPropertyValue)
				WXJS_DECLARE_METHOD(setPropertyValueString)
				WXJS_DECLARE_METHOD(setPropVal)
				WXJS_DECLARE_METHOD(setValidationFailureBehavior)
				WXJS_DECLARE_METHOD(sort)
				WXJS_DECLARE_METHOD(sortChildren)
				WXJS_DECLARE_METHOD(refreshProperty)
				//WXJS_DECLARE_CONSTANT_MAP()
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_GRID_PAGE_H_
