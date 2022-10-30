
#ifndef _WX_PG_GRID_MANAGER_H_
#define _WX_PG_GRID_MANAGER_H_

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
			class GridManager : public ApiWrapper<GridManager, wxPropertyGridManager>
			{
			public:
				static void InitClass(JSContext* cx,
									JSObject* obj,
									JSObject* proto);
				
				
				WXJS_DECLARE_ADD_PROP(wxPropertyGridManager)
				WXJS_DECLARE_DEL_PROP(wxPropertyGridManager)
				WXJS_DECLARE_GET_PROP(wxPropertyGridManager)
				WXJS_DECLARE_SET_PROP(wxPropertyGridManager)
				WXJS_DECLARE_CONSTRUCTOR(wxPropertyGridManager)
				WXJS_DECLARE_DESTRUCTOR(wxPropertyGridManager)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_GRID
					,	P_CURRENT_PAGE
					,	P_PAGE_COUNT
					,	P_SELECTED_PAGE
					,	P_SELECTED_PROPERTY
					,	P_SELECTION
					,	P_TOOLBAR
					,	P_IS_ANY_MODIFIED
					,	P_IS_FROZEN
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(create)
				WXJS_DECLARE_METHOD(addPage)
				WXJS_DECLARE_METHOD(clear)
				WXJS_DECLARE_METHOD(clearPage)
				WXJS_DECLARE_METHOD(commitChangesFromEditor)
				WXJS_DECLARE_METHOD(enableCategories)
				WXJS_DECLARE_METHOD(ensureVisible)
				WXJS_DECLARE_METHOD(getColumnCount)
				WXJS_DECLARE_METHOD(getDescBoxHeight)
				//WXJS_DECLARE_METHOD(getVIterator)	TODO...
				WXJS_DECLARE_METHOD(getPage)
				WXJS_DECLARE_METHOD(getPageByName)
				//WXJS_DECLARE_METHOD(getPageByState)	TODO...
				WXJS_DECLARE_METHOD(getPageName)
				WXJS_DECLARE_METHOD(getPageRoot)
				WXJS_DECLARE_METHOD(insertPage)
				WXJS_DECLARE_METHOD(isPageModified)
				WXJS_DECLARE_METHOD(isPropertySelected)
				WXJS_DECLARE_METHOD(removePage)
				WXJS_DECLARE_METHOD(selectPage)
				WXJS_DECLARE_METHOD(selectProperty)
				WXJS_DECLARE_METHOD(setColumnCount)
				WXJS_DECLARE_METHOD(setColumnTitle)
				WXJS_DECLARE_METHOD(setDescription)
				WXJS_DECLARE_METHOD(setDescBoxHeight)
				WXJS_DECLARE_METHOD(setSplitterLeft)
				WXJS_DECLARE_METHOD(setPageSplitterLeft)
				WXJS_DECLARE_METHOD(setPageSplitterPosition)
				WXJS_DECLARE_METHOD(setSplitterPosition)
				WXJS_DECLARE_METHOD(showHeader)
				

				//-----------------------------------------------
				//	wxPropertyGridInterface
				//-----------------------------------------------
				WXJS_DECLARE_METHOD(append)
				WXJS_DECLARE_METHOD(appendIn)
				WXJS_DECLARE_METHOD(beginAddChildren)
				//WXJS_DECLARE_METHOD(clear) ... same function defined avobe.
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
				//WXJS_DECLARE_METHOD(isPropertySelected) ... same function defined avobe.
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
				static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
			};
		
		

			class GridManagerEventHandler : public EventConnector<wxPropertyGridManager>
					, public wxEvtHandler
			{
			public:
				void OnSelected(wxPropertyGridEvent &event);
				void OnChanged(wxPropertyGridEvent &event);
				void OnChanging(wxPropertyGridEvent &event);
				void OnHighLighted(wxPropertyGridEvent &event);
				void OnRightClick(wxPropertyGridEvent &event);
				void OnDoubleClick(wxPropertyGridEvent &event);
				void OnItemCollapsed(wxPropertyGridEvent &event);
				void OnItemExpanded(wxPropertyGridEvent &event);
				void OnLabelEditBegin(wxPropertyGridEvent &event);
				void OnLabelEditEnding(wxPropertyGridEvent &event);
				void OnColBeginDrag(wxPropertyGridEvent &event);
				void OnColDragging(wxPropertyGridEvent &event);
				void OnColEndDrag(wxPropertyGridEvent &event);


				static void InitConnectEventMap();
			private:
				static void ConnectSelected(wxPropertyGridManager *p, bool connect);
				static void ConnectChanged(wxPropertyGridManager *p, bool connect);
				static void ConnectChanging(wxPropertyGridManager *p, bool connect);
				static void ConnectHighLighted(wxPropertyGridManager *p, bool connect);
				static void ConnectRightClick(wxPropertyGridManager *p, bool connect);
				static void ConnectDoubleClick(wxPropertyGridManager *p, bool connect);
				static void ConnectItemCollapsed(wxPropertyGridManager *p, bool connect);
				static void ConnectItemExpanded(wxPropertyGridManager *p, bool connect);
				static void ConnectLabelEditBegin(wxPropertyGridManager *p, bool connect);
				static void ConnectLabelEditEnding(wxPropertyGridManager *p, bool connect);
				static void ConnectColBeginDrag(wxPropertyGridManager *p, bool connect);
				static void ConnectColDragging(wxPropertyGridManager *p, bool connect);
				static void ConnectColEndDrag(wxPropertyGridManager *p, bool connect);



			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_GRID_MANAGER_H_
