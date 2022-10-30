
#ifndef _WX_DATAVIEW_CTRL_H
#define _WX_DATAVIEW_CTRL_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewCtrl : public ApiWrapper<DataViewCtrl, wxDataViewCtrl>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewCtrl)
				WXJS_DECLARE_DEL_PROP(wxDataViewCtrl)
				WXJS_DECLARE_GET_PROP(wxDataViewCtrl)
				WXJS_DECLARE_SET_PROP(wxDataViewCtrl)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewCtrl)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewCtrl)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_ColumnCount
					,	P_ExpanderColumn
					,	P_CurrentItem
					,	P_CurrentColumn
					,	P_Indent
					,	P_Model
					,	P_SelectedItemsCount
					,	P_Selection
					,	P_Selections
					,	P_SortingColumn
					,	P_SortingColumns
					,	P_HasSelection 
					,	P_IsMultiColumnSortAllowed 
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(create)
				WXJS_DECLARE_METHOD(allowMultiColumnSort)
				WXJS_DECLARE_METHOD(appendColumn)
				WXJS_DECLARE_METHOD(prependColumn)
				WXJS_DECLARE_METHOD(insertColumn )
				WXJS_DECLARE_METHOD(associateModel)
				WXJS_DECLARE_METHOD(clearColumns)
				WXJS_DECLARE_METHOD(collapse)
				WXJS_DECLARE_METHOD(deleteColumn)
				WXJS_DECLARE_METHOD(editItem)
				WXJS_DECLARE_METHOD(enableDragSource)
				WXJS_DECLARE_METHOD(enableDropTarget)
				WXJS_DECLARE_METHOD(ensureVisible)
				WXJS_DECLARE_METHOD(expand)
				WXJS_DECLARE_METHOD(expandAncestors)
				WXJS_DECLARE_METHOD(getColumn)
				WXJS_DECLARE_METHOD(getColumnPosition)
				WXJS_DECLARE_METHOD(getItemRect)
				WXJS_DECLARE_METHOD(hitTest)
				WXJS_DECLARE_METHOD(isExpanded)
				WXJS_DECLARE_METHOD(isSelected)
				WXJS_DECLARE_METHOD(select)
				WXJS_DECLARE_METHOD(selectAll)
				WXJS_DECLARE_METHOD(unselect)
				WXJS_DECLARE_METHOD(unselectAll)
				WXJS_DECLARE_METHOD(setRowHeight)
				WXJS_DECLARE_METHOD(toggleSortByColumn)

				WXJS_DECLARE_METHOD(appendBitmapColumn)
				WXJS_DECLARE_METHOD(prependBitmapColumn)
				WXJS_DECLARE_METHOD(appendDateColumn)
				WXJS_DECLARE_METHOD(prependDateColumn )
				WXJS_DECLARE_METHOD(appendIconTextColumn)
				WXJS_DECLARE_METHOD(prependIconTextColumn)
				WXJS_DECLARE_METHOD(appendProgressColumn)
				WXJS_DECLARE_METHOD(prependProgressColumn)
				WXJS_DECLARE_METHOD(appendTextColumn)
				WXJS_DECLARE_METHOD(prependTextColumn)
				WXJS_DECLARE_METHOD(appendToggleColumn)
				WXJS_DECLARE_METHOD(prependToggleColumn)


				static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
				static JSBool innerAppendXXXColumn(int method, 
								   JSContext *cx, 
								   unsigned argc, 
								   JS::Value *vp);
				//WXJS_DECLARE_CONSTANT_MAP()
			};


			class DataViewEventHandler : public EventConnector<wxDataViewCtrl>
				, public wxEvtHandler
			{
			public:
				// Events
				void OnSelectChange(wxDataViewEvent &event);
				void OnItemActivated(wxDataViewEvent &event);
				void OnItemStartEditing(wxDataViewEvent &event);
				void OnItemEndingStated(wxDataViewEvent &event);
				void OnItemEndingDone(wxDataViewEvent &event);
				void OnItemCollapsing(wxDataViewEvent &event);
				void OnItemCollapsed(wxDataViewEvent &event);
				void OnItemExpanding(wxDataViewEvent &event);
				void OnItemExpanded(wxDataViewEvent &event);
				void OnItemValueChanged(wxDataViewEvent &event);
				void OnItemContextMenu(wxDataViewEvent &event);
				void OnColumnHeaderClick(wxDataViewEvent &event);
				void OnColumnHeaderRightClick(wxDataViewEvent &event);
				void OnColumnSorted(wxDataViewEvent &event);
				void OnColumnReOrdered(wxDataViewEvent &event);
				void OnItemBeginDrag(wxDataViewEvent &event);
				void OnItemDropPossible(wxDataViewEvent &event);
				void OnItemDrop(wxDataViewEvent &event);

				static void InitConnectEventMap();
				
			private:
			
				static void ConnectSelectChange(wxDataViewCtrl *p, bool connect);
				static void ConnectItemActivated(wxDataViewCtrl *p, bool connect);
				static void ConnectItemStartEditing(wxDataViewCtrl *p, bool connect);
				static void ConnectItemEndingStated(wxDataViewCtrl *p, bool connect);
				static void ConnectItemEndingDone(wxDataViewCtrl *p, bool connect);
				static void ConnectItemCollapsing(wxDataViewCtrl *p, bool connect);
				static void ConnectItemCollapsed(wxDataViewCtrl *p, bool connect);
				static void ConnectItemExpanding(wxDataViewCtrl *p, bool connect);
				static void ConnectItemExpanded(wxDataViewCtrl *p, bool connect);
				static void ConnectItemValueChanged(wxDataViewCtrl *p, bool connect);
				static void ConnectItemContextMenu(wxDataViewCtrl *p, bool connect);
				static void ConnectColumnHeaderClick(wxDataViewCtrl *p, bool connect);
				static void ConnectColumnHeaderRightClick(wxDataViewCtrl *p, bool connect);
				static void ConnectColumnSorted(wxDataViewCtrl *p, bool connect);
				static void ConnectColumnReOrdered(wxDataViewCtrl *p, bool connect);
				static void ConnectItemBeginDrag(wxDataViewCtrl *p, bool connect);
				static void ConnectItemDropPossible(wxDataViewCtrl *p, bool connect);
				static void ConnectItemDrop(wxDataViewCtrl *p, bool connect);
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_CTRL_H
