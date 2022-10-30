
#ifndef _WX_PC_PROPERTY_COLOUR_H
#define _WX_PC_PROPERTY_COLOUR_H

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
			class ColourProperty : public ApiWrapper<ColourProperty, wxColourProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxColourProperty)
				WXJS_DECLARE_DESTRUCTOR(wxColourProperty)
//				WXJS_DECLARE_GET_PROP(wxSystemColourProperty)
				WXJS_DECLARE_SET_STR_PROP(wxColourProperty)

				

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_COLOUR_H
