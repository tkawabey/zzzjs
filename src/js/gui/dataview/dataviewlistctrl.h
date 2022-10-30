
#ifndef _WX_DATAVIEW_LIST_CTRL_H
#define _WX_DATAVIEW_LIST_CTRL_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewListCtrl : public ApiWrapper<DataViewListCtrl, wxDataViewListCtrl >
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewListCtrl)
				WXJS_DECLARE_DEL_PROP(wxDataViewListCtrl)
				WXJS_DECLARE_GET_PROP(wxDataViewListCtrl)
				WXJS_DECLARE_SET_PROP(wxDataViewListCtrl)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewListCtrl)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewListCtrl)

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
				WXJS_DECLARE_METHOD(itemToRow)
				WXJS_DECLARE_METHOD(rowToItem)




				static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);

				//WXJS_DECLARE_CONSTANT_MAP()
			};



		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_LIST_CTRL_H
