
#ifndef _WX_DATAVIEW_MODEL_H
#define _WX_DATAVIEW_MODEL_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewModel : public ApiWrapper<DataViewModel, wxDataViewModel>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewModel)
				WXJS_DECLARE_DEL_PROP(wxDataViewModel)
				WXJS_DECLARE_GET_PROP(wxDataViewModel)
				WXJS_DECLARE_SET_PROP(wxDataViewModel)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewModel)

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
				WXJS_DECLARE_METHOD(changeValue)
				WXJS_DECLARE_METHOD(cleared)
				WXJS_DECLARE_METHOD(compare)
				WXJS_DECLARE_METHOD(getAttr)
				WXJS_DECLARE_METHOD(isEnabled)
				WXJS_DECLARE_METHOD(getChildren)
				WXJS_DECLARE_METHOD(getColumnType)
				WXJS_DECLARE_METHOD(getParent)
				WXJS_DECLARE_METHOD(getValue)
				WXJS_DECLARE_METHOD(hasContainerColumns)
				WXJS_DECLARE_METHOD(hasValue)
				WXJS_DECLARE_METHOD(isContainer)
				WXJS_DECLARE_METHOD(itemAdded)
				WXJS_DECLARE_METHOD(itemChanged)
				WXJS_DECLARE_METHOD(itemDeleted)
				WXJS_DECLARE_METHOD(itemsAdded)
				WXJS_DECLARE_METHOD(itemsChanged)
				WXJS_DECLARE_METHOD(itemsDeleted)
				WXJS_DECLARE_METHOD(resort)
				WXJS_DECLARE_METHOD(setValue)
				WXJS_DECLARE_METHOD(valueChanged)
				WXJS_DECLARE_METHOD(isListModel)
				WXJS_DECLARE_METHOD(isVirtualListModel)
				
//				WXJS_DECLARE_CONSTANT_MAP()
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_MODEL_H
