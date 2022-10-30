
#ifndef _WX_PC_PROPERTY_FLOAT_H
#define _WX_PC_PROPERTY_FLOAT_H

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
			class FloatProperty : public ApiWrapper<FloatProperty, wxFloatProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxFloatProperty)
				WXJS_DECLARE_DESTRUCTOR(wxFloatProperty)
				WXJS_DECLARE_SET_STR_PROP(wxFloatProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_FLOAT_H
