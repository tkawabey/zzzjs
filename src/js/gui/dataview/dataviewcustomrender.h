
#ifndef _WX_DATAVIEW_CUSTOM_RENDER_H
#define _WX_DATAVIEW_CUSTOM_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewCustomRenderer : public ApiWrapper<DataViewCustomRenderer, wxDataViewCustomRenderer>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewCustomRenderer)
				WXJS_DECLARE_DEL_PROP(wxDataViewCustomRenderer)
				WXJS_DECLARE_GET_PROP(wxDataViewCustomRenderer)
				WXJS_DECLARE_SET_STR_PROP(wxDataViewCustomRenderer)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewCustomRenderer)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewCustomRenderer)
				
				  WXJS_DECLARE_METHOD_MAP()
				  WXJS_DECLARE_METHOD(getChoice )

				/**
				* Property Ids.
				*/
				enum
				{
						P_Choices
				};
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_CUSTOM_RENDER_H
