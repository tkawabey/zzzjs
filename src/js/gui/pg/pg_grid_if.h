
#ifndef _WX_PG_GRID_IF_H_
#define _WX_PG_GRID_IF_H_

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
			class GridInterface : public ApiWrapper<GridInterface, wxPropertyGridInterface>
			{
			public:
				

				WXJS_DECLARE_GET_PROP(wxPropertyGridInterface)
				WXJS_DECLARE_SET_PROP(wxPropertyGridInterface)
				WXJS_DECLARE_CONSTRUCTOR(wxPropertyGridInterface)
				WXJS_DECLARE_DESTRUCTOR(wxPropertyGridInterface)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_SELECTED_PROPERTY
					,	P_SELECTION
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(append)
				static JSBool  impl_append(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(appendIn)
				static JSBool  impl_appendIn(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(beginAddChildren)
				static JSBool  impl_beginAddChildren(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(clear)
				static JSBool  impl_clear(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(clearSelection)
				static JSBool  impl_clearSelection(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(clearModifiedStatus)
				static JSBool  impl_clearModifiedStatus(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(collapse)
				static JSBool  impl_collapse(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(collapseAll)
				static JSBool  impl_collapseAll(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(changePropertyValue)
				static JSBool  impl_changePropertyValue(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(deleteProperty)
				static JSBool  impl_deleteProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(disableProperty)
				static JSBool  impl_disableProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(editorValidate)
				static JSBool  impl_editorValidate(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(enableProperty)
				static JSBool  impl_enableProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(endAddChildren)
				static JSBool  impl_endAddChildren(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(expand)
				static JSBool  impl_expand(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(expandAll)
				static JSBool  impl_expandAll(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getColumnProportion)
				static JSBool  impl_getColumnProportion(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getFirstChild)
				static JSBool  impl_getFirstChild(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getProperty)
				static JSBool  impl_getProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getPropertiesWithFlag) TODO...
				WXJS_DECLARE_METHOD(getPropertyAttribute)
				static JSBool  impl_getPropertyAttribute(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getPropertyAttributes)  TODO...
				WXJS_DECLARE_METHOD(getPropertyBackgroundColour)
				static JSBool  impl_getPropertyBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyCategory)
				static JSBool  impl_getPropertyCategory(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getPropertyClientData) ... TODO,,,
				WXJS_DECLARE_METHOD(getPropertyByLabel)
				static JSBool  impl_getPropertyByLabel(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyByName)
				static JSBool  impl_getPropertyByName(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyEditor)
				static JSBool  impl_getPropertyEditor(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyHelpString)
				static JSBool  impl_getPropertyHelpString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyImage)
				static JSBool  impl_getPropertyImage(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyLabel)
				static JSBool  impl_getPropertyLabel(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyName)
				static JSBool  impl_getPropertyName(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyParent)
				static JSBool  impl_getPropertyParent(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyTextColour)
				static JSBool  impl_getPropertyTextColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValidator)
				static JSBool  impl_getPropertyValidator(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValue)
				static JSBool  impl_getPropertyValue(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsArrayInt)
				static JSBool  impl_getPropertyValueAsArrayInt(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsArrayString)
				static JSBool  impl_getPropertyValueAsArrayString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsBool)
				static JSBool  impl_getPropertyValueAsBool(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsDateTime)
				static JSBool  impl_getPropertyValueAsDateTime(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsDouble)
				static JSBool  impl_getPropertyValueAsDouble(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsInt)
				static JSBool  impl_getPropertyValueAsInt(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsLong)
				static JSBool  impl_getPropertyValueAsLong(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getPropertyValueAsLongLong)
				WXJS_DECLARE_METHOD(getPropertyValueAsString)
				static JSBool  impl_getPropertyValueAsString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(getPropertyValueAsULong)
				static JSBool  impl_getPropertyValueAsULong(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getPropertyValueAsULongLong)
				WXJS_DECLARE_METHOD(getPropertyValues)
				static JSBool  impl_getPropertyValues(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getVIterator) TODO...
				WXJS_DECLARE_METHOD(hideProperty)
				static JSBool  impl_hideProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(insert)
				static JSBool  impl_insert(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertyCategory)
				static JSBool  impl_isPropertyCategory(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertyEnabled)
				static JSBool  impl_isPropertyEnabled(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertyExpanded)
				static JSBool  impl_isPropertyExpanded(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertyModified)
				static JSBool  impl_isPropertyModified(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertySelected)
				static JSBool  impl_isPropertySelected(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertyShown)
				static JSBool  impl_isPropertyShown(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(isPropertyValueUnspecified)
				static JSBool  impl_isPropertyValueUnspecified(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(limitPropertyEditing)
				static JSBool  impl_limitPropertyEditing(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(refreshGrid) TODO...
				WXJS_DECLARE_METHOD(removeProperty)
				static JSBool  impl_removeProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(replaceProperty)
				static JSBool  impl_replaceProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(restoreEditableState)
				static JSBool  impl_restoreEditableState(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(saveEditableState)
				static JSBool  impl_saveEditableState(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setColumnProportion)
				static JSBool  impl_setColumnProportion(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyAttribute)
				static JSBool  impl_setPropertyAttribute(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyAttributeAll)
				static JSBool  impl_setPropertyAttributeAll(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyBackgroundColour)
				static JSBool  impl_setPropertyBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyCell)
				static JSBool  impl_setPropertyCell(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(setPropertyClientData) TODO...
				WXJS_DECLARE_METHOD(setPropertyColoursToDefault)
				static JSBool  impl_setPropertyColoursToDefault(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyEditor)
				static JSBool  impl_setPropertyEditor(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyLabel)
				static JSBool  impl_setPropertyLabel(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyName)
				static JSBool  impl_setPropertyName(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyReadOnly)
				static JSBool  impl_setPropertyReadOnly(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyValueUnspecified)
				static JSBool  impl_setPropertyValueUnspecified(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(setPropertyValues) TODO...
				WXJS_DECLARE_METHOD(setPropertyHelpString)
				static JSBool  impl_setPropertyHelpString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyImage)
				static JSBool  impl_setPropertyImage(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyMaxLength)
				static JSBool  impl_setPropertyMaxLength(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyTextColour)
				static JSBool  impl_setPropertyTextColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyValidator)
				static JSBool  impl_setPropertyValidator(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyValue)
				static JSBool  impl_setPropertyValue(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropertyValueString)
				static JSBool  impl_setPropertyValueString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setPropVal)
				static JSBool  impl_setPropVal(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(setValidationFailureBehavior)
				static JSBool  impl_setValidationFailureBehavior(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(sort)
				static JSBool  impl_sort(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(sortChildren)
				static JSBool  impl_sortChildren(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				WXJS_DECLARE_METHOD(refreshProperty)
				static JSBool  impl_refreshProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p);
				//WXJS_DECLARE_METHOD(getIterator) TODO...
				//WXJS_DECLARE_METHOD(getFirst) TODO...

				//WXJS_DECLARE_CONSTANT_MAP()
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_GRID_IF_H_
