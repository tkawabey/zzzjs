
#ifndef _WX_PG_WNDLIST_H
#define _WX_PG_WNDLIST_H

#include <wx/propgrid/editors.h>
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
			class WindowList : public ApiWrapper<WindowList, wxPGWindowList>
			{
			public:



				WXJS_DECLARE_CONSTRUCTOR(wxPGWindowList)
				//WXJS_DECLARE_DESTRUCTOR(wxPGWindowList)
				//WXJS_DECLARE_SET_STR_PROP(wxPGWindowList)
				

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(setSecondary)

				//WXJS_DECLARE_CONSTANT_MAP()
			};

		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_WNDLIST_H
