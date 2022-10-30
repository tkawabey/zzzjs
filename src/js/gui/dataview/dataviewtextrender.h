
#ifndef _WX_DATAVIEW_TEXT_RENDER_H
#define _WX_DATAVIEW_TEXT_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewTextRenderer : public ApiWrapper<DataViewTextRenderer, wxDataViewTextRenderer >
			{
			public:
				
				WXJS_DECLARE_SET_STR_PROP(wxDataViewTextRenderer )
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewTextRenderer )
				WXJS_DECLARE_DESTRUCTOR(wxDataViewTextRenderer )
				
				
			};


		}; // namespace dataview
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_ICON_TEXT_RENDER_H
