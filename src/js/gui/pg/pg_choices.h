
#ifndef _WX_PC_CHOICES_H
#define _WX_PC_CHOICES_H

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
			class Choices : public ApiWrapper<Choices, wxPGChoices>
			{
			public:
				WXJS_DECLARE_CONSTRUCTOR(wxPGChoices)
				WXJS_DECLARE_DESTRUCTOR(wxPGChoices)
				WXJS_DECLARE_GET_PROP(wxPGChoices)
				
				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_COUNT
					,	P_IS_OK
					,	P_LABELS
				};
				
				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(add)
				WXJS_DECLARE_METHOD(addAsSorted)
				WXJS_DECLARE_METHOD(clear)
				WXJS_DECLARE_METHOD(ensureData)
				WXJS_DECLARE_METHOD(getLabel)
				WXJS_DECLARE_METHOD(getValue)
				WXJS_DECLARE_METHOD(getValuesFromStrings)
				WXJS_DECLARE_METHOD(getIndicesForStrings)
				WXJS_DECLARE_METHOD(index)
				WXJS_DECLARE_METHOD(insert)
				WXJS_DECLARE_METHOD(item)
				WXJS_DECLARE_METHOD(removeAt)
				WXJS_DECLARE_METHOD(set)
				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_CHOICES_H
