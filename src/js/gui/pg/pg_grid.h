
#ifndef _WX_PG_GRID_H_
#define _WX_PG_GRID_H_

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
			class Grid : public ApiWrapper<Grid, wxPropertyGrid>
			{
			public:
				static void InitClass(JSContext* cx,
									JSObject* obj,
									JSObject* proto);
				

				WXJS_DECLARE_GET_PROP(wxPropertyGrid)
				WXJS_DECLARE_SET_PROP(wxPropertyGrid)
				WXJS_DECLARE_CONSTRUCTOR(wxPropertyGrid)
				WXJS_DECLARE_DESTRUCTOR(wxPropertyGrid)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_FIT_COLUMNS
					,	P_LABEL_EDITOR
					,	P_PANEL
					,	P_CAPTION_BACKGROUND_COLOR
					,	P_CAPTION_FONT
					,	P_CAPTION_FOREGROUND_COLOR
					,	P_CELL_BACKGROUND_COLOR
					,	P_CELL_DISABLED_TEXT_COLOR
					,	P_CELL_TEXT_COLOR
					,	P_COLUMN_COUNT
					,	P_EMPTY_SPACE_COLOR
					,	P_FONT_HIGHT
					,	P_GRID
					,	P_LINE_COLOR
					,	P_MARGIN_COLOR
					,	P_ROOT
					,	P_ROW_HEIGHT
					,	P_SELECTED_PROPERTY
					,	P_SELECTION
					,	P_SELECTION_BACKGROUND_COLOR
					,	P_SELECTION_FOREGROUND_COLOR
					,	P_SORT_FUNC	// TODO...
					,	P_EDIT_TEXT_CTRL
					,	P_UNSPECIFIED_VALUE_APPEARANCE
					,	P_VERTICAL_SPACING
					,	P_IS_ANY_MODIFIED
					,	P_IS_EDITOR_FOCUSED
					,	P_IS_FROZEN
					,	P_CAPTION_TEXT_COLOR
					,	P_CURRENT_CATEGORY
					,	P_SELECTION_TEXT_COLOR
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(create)
				WXJS_DECLARE_METHOD(addActionTrigger)
				WXJS_DECLARE_METHOD(addToSelection)
				WXJS_DECLARE_METHOD(beginLabelEdit)
				WXJS_DECLARE_METHOD(changePropertyValue)
				WXJS_DECLARE_METHOD(centerSplitter)
				WXJS_DECLARE_METHOD(clear)
				WXJS_DECLARE_METHOD(clearActionTriggers)
				WXJS_DECLARE_METHOD(dedicateKey)
				WXJS_DECLARE_METHOD(enableCategories)
				WXJS_DECLARE_METHOD(endLabelEdit)
				WXJS_DECLARE_METHOD(ensureVisible)
				WXJS_DECLARE_METHOD(getImageRect)
				WXJS_DECLARE_METHOD(getImageSize)
				WXJS_DECLARE_METHOD(getLastItem)
				WXJS_DECLARE_METHOD(getSplitterPosition)
				WXJS_DECLARE_METHOD(getUnspecifiedValueText)
				WXJS_DECLARE_METHOD(hitTest)
				WXJS_DECLARE_METHOD(makeColumnEditable)
				WXJS_DECLARE_METHOD(onTLPChanging)
				WXJS_DECLARE_METHOD(refreshEditor)
				WXJS_DECLARE_METHOD(refreshProperty)
				WXJS_DECLARE_METHOD(resetColours)
				WXJS_DECLARE_METHOD(resetColumnSizes)
				WXJS_DECLARE_METHOD(removeFromSelection)
				WXJS_DECLARE_METHOD(selectProperty)
				WXJS_DECLARE_METHOD(setSplitterPosition)
				WXJS_DECLARE_METHOD(setSplitterLeft)


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
				//WXJS_DECLARE_METHOD(changePropertyValue) ... same function defined avobe.
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
				//WXJS_DECLARE_METHOD(refreshProperty) ... same function defined avobe.


				//WXJS_DECLARE_CONSTANT_MAP()
				static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
			};
		
		

			class GridEventHandler : public EventConnector<wxPropertyGrid>
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
				static void ConnectSelected(wxPropertyGrid *p, bool connect);
				static void ConnectChanged(wxPropertyGrid *p, bool connect);
				static void ConnectChanging(wxPropertyGrid *p, bool connect);
				static void ConnectHighLighted(wxPropertyGrid *p, bool connect);
				static void ConnectRightClick(wxPropertyGrid *p, bool connect);
				static void ConnectDoubleClick(wxPropertyGrid *p, bool connect);
				static void ConnectItemCollapsed(wxPropertyGrid *p, bool connect);
				static void ConnectItemExpanded(wxPropertyGrid *p, bool connect);
				static void ConnectLabelEditBegin(wxPropertyGrid *p, bool connect);
				static void ConnectLabelEditEnding(wxPropertyGrid *p, bool connect);
				static void ConnectColBeginDrag(wxPropertyGrid *p, bool connect);
				static void ConnectColDragging(wxPropertyGrid *p, bool connect);
				static void ConnectColEndDrag(wxPropertyGrid *p, bool connect);



			};
		
		
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_GRID_H_
