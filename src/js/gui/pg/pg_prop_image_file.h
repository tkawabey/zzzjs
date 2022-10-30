
#ifndef _WX_PC_PROPERTY_IMAGE_FILE_H
#define _WX_PC_PROPERTY_IMAGE_FILE_H

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
			class ImageFileProperty : public ApiWrapper<ImageFileProperty, wxImageFileProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxImageFileProperty)
				WXJS_DECLARE_DESTRUCTOR(wxImageFileProperty)
				WXJS_DECLARE_SET_STR_PROP(wxImageFileProperty)

				

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_IMAGE_FILE_H
