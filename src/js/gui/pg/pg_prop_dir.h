
#ifndef _WX_PC_PROPERTY_DIR_H
#define _WX_PC_PROPERTY_DIR_H

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
			class DirProperty : public ApiWrapper<DirProperty, wxDirProperty>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxDirProperty)
				WXJS_DECLARE_DESTRUCTOR(wxDirProperty)
				WXJS_DECLARE_SET_STR_PROP(wxDirProperty)


				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_DIR_H
