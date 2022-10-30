/*
 * wxJavaScript - scrollwnd.h
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://wxjs.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id: scrollwnd.h 692 2007-05-02 21:30:16Z fbraem $
 */
#ifndef _WXJSScrolledWindow_H
#define _WXJSScrolledWindow_H

#include <wx/scrolwin.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
      class ScrolledWindow : public ApiWrapper<ScrolledWindow, wxScrolledWindow>
      {
      public:


			WXJS_DECLARE_ADD_PROP(wxScrolledWindow)
			WXJS_DECLARE_DEL_PROP(wxScrolledWindow)
			WXJS_DECLARE_GET_PROP(wxScrolledWindow)
			WXJS_DECLARE_SET_STR_PROP(wxScrolledWindow)
			WXJS_DECLARE_CONSTRUCTOR(wxScrolledWindow)
			WXJS_DECLARE_DESTRUCTOR(wxScrolledWindow)
			WXJS_DECLARE_PROPERTY_MAP()
			enum
			{
				P_SCROLL_PIXELS_PER_UNIT = WXJS_START_PROPERTY_ID
				, P_VIEW_START
				, P_VIRTUAL_SIZE
				, P_RETAINED
			};

			WXJS_DECLARE_METHOD_MAP()
			WXJS_DECLARE_METHOD(create)
			WXJS_DECLARE_METHOD(calcScrolledPosition)
			WXJS_DECLARE_METHOD(calcUnscrolledPosition)
			WXJS_DECLARE_METHOD(enableScrolling)
			WXJS_DECLARE_METHOD(getScrollPixelsPerUnit)
			WXJS_DECLARE_METHOD(scroll)
			WXJS_DECLARE_METHOD(setScrollbars)
			WXJS_DECLARE_METHOD(setScrollRate)
			WXJS_DECLARE_METHOD(setTargetWindow)
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);

      };
    }; // namespace gui
}; //namespace wxjs
#endif //_WXJSScrolledWindow_H
