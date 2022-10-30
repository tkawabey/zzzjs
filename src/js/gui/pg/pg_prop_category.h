
#ifndef _WX_PC_PROPERTY_CATEGORY_H
#define _WX_PC_PROPERTY_CATEGORY_H

#include <wx/propgrid/property.h>
#include <wx/propgrid/props.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class PropertyCategory : public ApiWrapper<PropertyCategory, wxPropertyCategory>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxPropertyCategory)
				WXJS_DECLARE_DESTRUCTOR(wxPropertyCategory)
				WXJS_DECLARE_SET_STR_PROP(wxPropertyCategory)

				
				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(getTextExtent)
				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_CATEGORY_H
