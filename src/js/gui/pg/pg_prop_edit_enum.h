
#ifndef _WX_PC_PROPERTY_EDIT_ENUM_H
#define _WX_PC_PROPERTY_EDIT_ENUM_H

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
			class EditEnumProperty : public ApiWrapper<EditEnumProperty, wxEditEnumProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxEditEnumProperty)
				WXJS_DECLARE_DESTRUCTOR(wxEditEnumProperty)
				WXJS_DECLARE_GET_PROP(wxEditEnumProperty)
				WXJS_DECLARE_SET_STR_PROP(wxEditEnumProperty)

				

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_EDIT_ENUM_H
