
#ifndef _WX_DATAVIEW_DATE_RENDER_H
#define _WX_DATAVIEW_DATE_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewDateRenderer : public ApiWrapper<DataViewDateRenderer, wxDataViewDateRenderer>
			{
			public:
				
				WXJS_DECLARE_SET_STR_PROP(wxDataViewDateRenderer)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewDateRenderer)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewDateRenderer)
				
				
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_DATE_RENDER_H
