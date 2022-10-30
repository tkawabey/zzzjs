
#ifndef _WX_DATAVIEW_BITMAP_RENDER_H
#define _WX_DATAVIEW_BITMAP_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewBitmapRenderer : public ApiWrapper<DataViewBitmapRenderer, wxDataViewBitmapRenderer>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewBitmapRenderer)
				WXJS_DECLARE_DEL_PROP(wxDataViewBitmapRenderer)
				WXJS_DECLARE_SET_STR_PROP(wxDataViewBitmapRenderer)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewBitmapRenderer)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewBitmapRenderer)


				/**
				* Property Ids.
				*/
				enum
				{
						P_Alignment 
					,	P_EllipsizeMode 
					,	P_Mode 
					,	P_Owner
					,	P_VALUE
					,	P_VariantType
					,	P_HasEditorCtrl
				};
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_BITMAP_RENDER_H
