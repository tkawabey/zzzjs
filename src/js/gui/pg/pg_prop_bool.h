
#ifndef _WX_PC_PROPERTY_BOOLEAN_H
#define _WX_PC_PROPERTY_BOOLEAN_H

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
			class BoolProperty : public ApiWrapper<BoolProperty, wxBoolProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxBoolProperty)
				WXJS_DECLARE_DESTRUCTOR(wxBoolProperty)
				WXJS_DECLARE_SET_STR_PROP(wxBoolProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_BOOLEAN_H
