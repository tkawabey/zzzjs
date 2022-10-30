
#ifndef _WX_PC_PROPERTY_LONG_STRING_H
#define _WX_PC_PROPERTY_LONG_STRING_H

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
			class LongStringProperty : public ApiWrapper<LongStringProperty, wxLongStringProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxLongStringProperty)
				WXJS_DECLARE_DESTRUCTOR(wxLongStringProperty)
				WXJS_DECLARE_SET_STR_PROP(wxLongStringProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_LONG_STRING_H
