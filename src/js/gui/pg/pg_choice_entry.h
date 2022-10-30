
#ifndef _WX_PC_CHOICE_ENTRY_H
#define _WX_PC_CHOICE_ENTRY_H

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
			class ChoiceEntry : public ApiWrapper<ChoiceEntry, wxPGChoiceEntry>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxPGChoiceEntry)
				WXJS_DECLARE_DESTRUCTOR(wxPGChoiceEntry)
				WXJS_DECLARE_GET_PROP(wxPGChoiceEntry)
				WXJS_DECLARE_SET_PROP(wxPGChoiceEntry)
				WXJS_DECLARE_SET_STR_PROP(wxPGChoiceEntry)
				
				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_VALUE
				};

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_DATE_H
