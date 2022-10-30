#ifndef _WXJSPoint_H
#define _WXJSPoint_H

#include <wx/buffer.h>
#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/jswrap.h"
#include "js/common/conf.h"


namespace zzzJs
{
	namespace ext
	{
		class Point : public JsWrapper<Point, wxPoint>
		{
		public:
			ZZZJS_DECLARE_GET_PROP(wxPoint)
			ZZZJS_DECLARE_SET_PROP(wxPoint)
			ZZZJS_DECLARE_CONSTRUCTOR(wxPoint)
			
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxPoint)

			// Propeties
			enum
			{
			  P_X
			, P_Y
			};
			ZZZJS_DECLARE_PROPERTY_MAP()
		};
	}; // namespace gui
}; // namespace wxjs

#endif //_WXJSPoint_H
