
#ifndef _WX_PC_PROPERTY_ARRAY_STRING_H
#define _WX_PC_PROPERTY_ARRAY_STRING_H

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
			class ArrayStringProperty : public ApiWrapper<ArrayStringProperty, wxArrayStringProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxArrayStringProperty)
				WXJS_DECLARE_DESTRUCTOR(wxArrayStringProperty)
				WXJS_DECLARE_SET_STR_PROP(wxArrayStringProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_H
