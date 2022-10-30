
#ifndef _WX_DATAVIEW_CHOICE_BY_INDEX_RENDER_H
#define _WX_DATAVIEW_CHOICE_BY_INDEX_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewChoiceByIndexRenderer : public ApiWrapper<DataViewChoiceByIndexRenderer, wxDataViewChoiceByIndexRenderer>
			{
			public:		  
				WXJS_DECLARE_SET_STR_PROP(wxDataViewChoiceByIndexRenderer)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewChoiceByIndexRenderer)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewChoiceByIndexRenderer)
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_CHOICE_BY_INDEX_RENDER_H
