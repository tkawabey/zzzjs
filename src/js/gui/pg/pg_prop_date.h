
#ifndef _WX_PC_PROPERTY_DATE_H
#define _WX_PC_PROPERTY_DATE_H

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
			class DateProperty : public ApiWrapper<DateProperty, wxDateProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxDateProperty)
				WXJS_DECLARE_DESTRUCTOR(wxDateProperty)
				WXJS_DECLARE_GET_PROP(wxDateProperty)
				WXJS_DECLARE_SET_PROP(wxDateProperty)
				WXJS_DECLARE_SET_STR_PROP(wxDateProperty)
				
				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_FORMAT
					,	P_DATE_VALUE
					,	P_DATE_PICKER_STYLE
				};

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_DATE_H
