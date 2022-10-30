
#ifndef _WX_DATAVIEW_ITEM_ATTR_H
#define _WX_DATAVIEW_ITEM_ATTR_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewItemAttr : public ApiWrapper<DataViewItemAttr, wxDataViewItemAttr>
			{
			public:
				WXJS_DECLARE_GET_PROP(wxDataViewItemAttr)
				WXJS_DECLARE_SET_PROP(wxDataViewItemAttr)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewItemAttr)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewItemAttr)

				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_BOLD
					,	P_BackgroundColour
					,	P_HasBackgroundColour
					,	P_Italic
					,	P_Colour 
					,	P_HasColour 
					,	P_HasFont
					,	P_HasEffectiveFont
				};
				
				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(getEffectiveFont)
				
//				WXJS_DECLARE_CONSTANT_MAP()
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_ITEM_ATTR_H
