
#ifndef _WX_DATAVIEW_ICON_TEXT_RENDER_H
#define _WX_DATAVIEW_ICON_TEXT_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewIconTextRenderer : public ApiWrapper<DataViewIconTextRenderer, wxDataViewIconTextRenderer >
			{
			public:
				
				WXJS_DECLARE_SET_STR_PROP(wxDataViewIconTextRenderer )
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewIconTextRenderer )
				WXJS_DECLARE_DESTRUCTOR(wxDataViewIconTextRenderer )
				
				
			};


		}; // namespace dataview
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_ICON_TEXT_RENDER_H
