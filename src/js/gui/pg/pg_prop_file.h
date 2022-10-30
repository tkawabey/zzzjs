
#ifndef _WX_PC_PROPERTY_FILE_H
#define _WX_PC_PROPERTY_FILE_H

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
			class FileProperty : public ApiWrapper<FileProperty, wxFileProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxFileProperty)
				WXJS_DECLARE_DESTRUCTOR(wxFileProperty)
				WXJS_DECLARE_GET_PROP(wxFileProperty)
				WXJS_DECLARE_SET_STR_PROP(wxFileProperty)

				
				/**
				* Property Ids.
				*/
				WXJS_DECLARE_PROPERTY_MAP()
				enum
				{
						P_FILE_NAME
				};

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_FILE_H
