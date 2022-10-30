
#ifndef _WX_DATAVIEW_RENDER_H
#define _WX_DATAVIEW_RENDER_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewRenderer : public ApiWrapper<DataViewRenderer, wxDataViewRenderer>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxDataViewRenderer)
				WXJS_DECLARE_DEL_PROP(wxDataViewRenderer)
				WXJS_DECLARE_GET_PROP(wxDataViewRenderer)
				WXJS_DECLARE_SET_PROP(wxDataViewRenderer)

				WXJS_DECLARE_PROPERTY_MAP()

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

				WXJS_DECLARE_METHOD_MAP()
			    WXJS_DECLARE_METHOD(setValueAdjuster )
			    WXJS_DECLARE_METHOD(validate)
				WXJS_DECLARE_METHOD(createEditorCtrl)
				WXJS_DECLARE_METHOD(getValueFromEditorCtrl)
				WXJS_DECLARE_METHOD(startEditing)
				WXJS_DECLARE_METHOD(cancelEditing)
				WXJS_DECLARE_METHOD(finishEditing)
				WXJS_DECLARE_METHOD(getEditorCtrl)


				//WXJS_DECLARE_CONSTANT_MAP()
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_RENDER_H
