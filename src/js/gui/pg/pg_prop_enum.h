
#ifndef _WX_PC_PROPERTY_ENUM_H
#define _WX_PC_PROPERTY_ENUM_H

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
			class EnumProperty : public ApiWrapper<EnumProperty, wxEnumProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxEnumProperty)
				WXJS_DECLARE_DESTRUCTOR(wxEnumProperty)
				WXJS_DECLARE_GET_PROP(wxEnumProperty)
				WXJS_DECLARE_SET_STR_PROP(wxEnumProperty)

				
				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_ITEM_COUNT
				};
				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_ENUM_H
