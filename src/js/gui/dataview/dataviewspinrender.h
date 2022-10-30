
#ifndef _WX_DATAVIEW_SPIN_RENDER_H
#define _WX_DATAVIEW_SPIN_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewSpinRenderer : public ApiWrapper<DataViewSpinRenderer, wxDataViewSpinRenderer>
			{
			public:
				
				WXJS_DECLARE_SET_STR_PROP(wxDataViewSpinRenderer)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewSpinRenderer)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewSpinRenderer)
				
				
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_CHOICE_RENDER_H
