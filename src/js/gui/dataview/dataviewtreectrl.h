
#ifndef _WX_DATAVIEW_TREE_CTRL_H
#define _WX_DATAVIEW_TREE_CTRL_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewTreeCtrl : public ApiWrapper<DataViewTreeCtrl, wxDataViewTreeCtrl>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewTreeCtrl)
				WXJS_DECLARE_DEL_PROP(wxDataViewTreeCtrl)
				WXJS_DECLARE_GET_PROP(wxDataViewTreeCtrl)
				WXJS_DECLARE_SET_PROP(wxDataViewTreeCtrl)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewTreeCtrl)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewTreeCtrl)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_IMAGE_LIST
					,   P_STORE
					,	P_ColumnCount
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
				WXJS_DECLARE_METHOD(appendContainer)
				WXJS_DECLARE_METHOD(appendItem)
				WXJS_DECLARE_METHOD(deleteAllItems)
				WXJS_DECLARE_METHOD(deleteChildren)
				WXJS_DECLARE_METHOD(deleteItem)
				WXJS_DECLARE_METHOD(getChildCount)
				WXJS_DECLARE_METHOD(getItemData)
				WXJS_DECLARE_METHOD(getItemExpandedIcon)
				WXJS_DECLARE_METHOD(getItemIcon)
				WXJS_DECLARE_METHOD(getItemText)
				WXJS_DECLARE_METHOD(getNthChild)
				WXJS_DECLARE_METHOD(insertContainer)
				WXJS_DECLARE_METHOD(insertItem)
				WXJS_DECLARE_METHOD(isContainer)
				WXJS_DECLARE_METHOD(prependContainer)
				WXJS_DECLARE_METHOD(prependItem)
				WXJS_DECLARE_METHOD(setItemData)
				WXJS_DECLARE_METHOD(setItemExpandedIcon)
				WXJS_DECLARE_METHOD(setItemIcon)
				WXJS_DECLARE_METHOD(setItemText)


				static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);

				//WXJS_DECLARE_CONSTANT_MAP()
			};



		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_TREE_CTRL_H
