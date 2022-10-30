
#ifndef _WX_DATAVIEW_ITEM_H
#define _WX_DATAVIEW_ITEM_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewItem : public ApiWrapper<DataViewItem, wxDataViewItem>
			{
			public:
				WXJS_DECLARE_GET_PROP(wxDataViewItem)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewItem)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewItem)
				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_ISOK
				};
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_ITEM_H
