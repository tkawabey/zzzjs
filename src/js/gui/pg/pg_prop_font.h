
#ifndef _WX_PC_PROPERTY_FONT_H
#define _WX_PC_PROPERTY_FONT_H

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
			class FontProperty : public ApiWrapper<FontProperty, wxFontProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxFontProperty)
				WXJS_DECLARE_DESTRUCTOR(wxFontProperty)
				WXJS_DECLARE_SET_STR_PROP(wxFontProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_FONT_H
