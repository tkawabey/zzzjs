
#ifndef _WX_PC_PROPERTY_INT_H
#define _WX_PC_PROPERTY_INT_H

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
			class IntProperty : public ApiWrapper<IntProperty, wxIntProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxIntProperty)
				WXJS_DECLARE_DESTRUCTOR(wxIntProperty)
				WXJS_DECLARE_SET_STR_PROP(wxIntProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_INT_H
