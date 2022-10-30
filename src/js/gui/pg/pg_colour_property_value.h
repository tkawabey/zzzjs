
#ifndef _WX_PC_CLOUR_PROPERTY_VALUE_H
#define _WX_PC_CLOUR_PROPERTY_VALUE_H

#include <wx/propgrid/property.h>
#include <wx/propgrid/props.h>
#include <wx/propgrid/advprops.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class ColourPropertyValue : public ApiWrapper<ColourPropertyValue, wxColourPropertyValue>
			{
			public:
				WXJS_DECLARE_CONSTRUCTOR(wxColourPropertyValue)
				WXJS_DECLARE_DESTRUCTOR(wxColourPropertyValue)
				
				
				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(init)
				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_CLOUR_PROPERTY_VALUE_H
