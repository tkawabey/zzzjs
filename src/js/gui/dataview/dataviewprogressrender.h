
#ifndef _WX_DATAVIEW_PROGRESS_RENDER_H
#define _WX_DATAVIEW_PROGRESS_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewProgressRenderer : public ApiWrapper<DataViewProgressRenderer, wxDataViewProgressRenderer >
			{
			public:
				
				WXJS_DECLARE_SET_STR_PROP(wxDataViewProgressRenderer )
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewProgressRenderer )
				WXJS_DECLARE_DESTRUCTOR(wxDataViewProgressRenderer )
				
				
			};


		}; // namespace dataview
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_PROGRESS_RENDER_H
