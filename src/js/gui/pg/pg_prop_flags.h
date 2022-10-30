
#ifndef _WX_PC_PROPERTY_FLAGS_H
#define _WX_PC_PROPERTY_FLAGS_H

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
			class FlagsProperty : public ApiWrapper<FlagsProperty, wxFlagsProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxFlagsProperty)
				WXJS_DECLARE_DESTRUCTOR(wxFlagsProperty)
				WXJS_DECLARE_GET_PROP(wxFlagsProperty)
				WXJS_DECLARE_SET_STR_PROP(wxFlagsProperty)

				


				/**
				* Property Ids.
				*/
				WXJS_DECLARE_PROPERTY_MAP()
				enum
				{
						P_ITEM_COUNT
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(getLabel)
				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_FLAGS_H
