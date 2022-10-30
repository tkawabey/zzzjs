
#ifndef _WX_PC_PROPERTY_UINT_H
#define _WX_PC_PROPERTY_UINT_H

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
			class UIntProperty : public ApiWrapper<UIntProperty, wxUIntProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxUIntProperty)
				WXJS_DECLARE_DESTRUCTOR(wxUIntProperty)
				WXJS_DECLARE_SET_STR_PROP(wxUIntProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_UINT_H
