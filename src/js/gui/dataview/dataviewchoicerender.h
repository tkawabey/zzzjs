
#ifndef _WX_DATAVIEW_CHOICE_RENDER_H
#define _WX_DATAVIEW_CHOICE_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewChoiceRenderer : public ApiWrapper<DataViewChoiceRenderer, wxDataViewChoiceRenderer>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewChoiceRenderer)
				WXJS_DECLARE_DEL_PROP(wxDataViewChoiceRenderer)
				WXJS_DECLARE_GET_PROP(wxDataViewChoiceRenderer)
				WXJS_DECLARE_SET_STR_PROP(wxDataViewChoiceRenderer)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewChoiceRenderer)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewChoiceRenderer)
				
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
#endif //_WX_DATAVIEW_CHOICE_RENDER_H
