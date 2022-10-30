
#ifndef _WX_DATAVIEW_TOGGLE_RENDER_H
#define _WX_DATAVIEW_TOGGLE_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewToggleRenderer : public ApiWrapper<DataViewToggleRenderer, wxDataViewToggleRenderer  >
			{
			public:
				
				WXJS_DECLARE_SET_STR_PROP(wxDataViewToggleRenderer )
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewToggleRenderer )
				WXJS_DECLARE_DESTRUCTOR(wxDataViewToggleRenderer )
				
				
			};


		}; // namespace dataview
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_TOGGLE_RENDER_H
