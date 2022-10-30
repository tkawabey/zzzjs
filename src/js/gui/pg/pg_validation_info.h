
#ifndef _WX_PC_VALIDATION_INFO_H
#define _WX_PC_VALIDATION_INFO_H

#include <wx/propgrid/property.h>
#include <wx/propgrid/propgrid.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class ValidationInfo : public ApiWrapper<ValidationInfo, wxPGValidationInfo>
			{
			public:
				

				WXJS_DECLARE_GET_PROP(wxPGValidationInfo)
				WXJS_DECLARE_SET_PROP(wxPGValidationInfo)
				WXJS_DECLARE_CONSTRUCTOR(wxPGValidationInfo)
				//WXJS_DECLARE_DESTRUCTOR(wxPGValidationInfo) wxPGValidationInfoのアドレスは、deleteするので、WXJS_DECLARE_DESTRUCTOR　は定義しない。

				WXJS_DECLARE_PROPERTY_MAP()
				WXJS_DECLARE_CONSTANT_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_FailureBehavior 
					,	P_FailureMessage 
					,	P_Value
				};
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_VALIDATION_INFO_H
