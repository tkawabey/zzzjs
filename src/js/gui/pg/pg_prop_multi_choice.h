
#ifndef _WX_PC_PROPERTY_MULTI_CHOICE_H
#define _WX_PC_PROPERTY_MULTI_CHOICE_H

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
			class MultiChoiceProperty : public ApiWrapper<MultiChoiceProperty, wxMultiChoiceProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxMultiChoiceProperty)
				WXJS_DECLARE_DESTRUCTOR(wxMultiChoiceProperty)
				WXJS_DECLARE_GET_PROP(wxMultiChoiceProperty)
				WXJS_DECLARE_SET_STR_PROP(wxMultiChoiceProperty)
				
				
				/**
				* Property Ids.
				*/
				WXJS_DECLARE_PROPERTY_MAP()
				enum
				{
						P_VALUE_ARRAY_INT
				};
				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_MULTI_CHOICE_H
