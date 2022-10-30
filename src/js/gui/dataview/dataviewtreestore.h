
#ifndef _WX_DATAVIEW_TREE_STORE_H
#define _WX_DATAVIEW_TREE_STORE_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewTreeStore : public ApiWrapper<DataViewTreeStore, wxDataViewTreeStore>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewTreeStore)
				WXJS_DECLARE_DEL_PROP(wxDataViewTreeStore)
				WXJS_DECLARE_GET_PROP(wxDataViewTreeStore)
				WXJS_DECLARE_SET_PROP(wxDataViewTreeStore)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewTreeStore)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_ColumnCount 
					,	P_asDefaultCompare 
				};

				WXJS_DECLARE_METHOD_MAP()
				//WXJS_DECLARE_METHOD(addNotifier)
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
				WXJS_DECLARE_METHOD(prependContainer)
				WXJS_DECLARE_METHOD(prependItem)
				WXJS_DECLARE_METHOD(setItemData)
				WXJS_DECLARE_METHOD(setItemExpandedIcon)
				WXJS_DECLARE_METHOD(setItemIcon)

//				WXJS_DECLARE_CONSTANT_MAP()
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_TREE_STORE_H
