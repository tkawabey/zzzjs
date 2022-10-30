/*
 * wxJavaScript - bmpbtn.h
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
 * $Id: bmpbtn.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _WXJSBitmapButton_H
#define _WXJSBitmapButton_H

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class BitmapButton : public ApiWrapper<BitmapButton, wxBitmapButton>
        {
        public:

			WXJS_DECLARE_ADD_PROP(wxBitmapButton)
			WXJS_DECLARE_DEL_PROP(wxBitmapButton)
			WXJS_DECLARE_GET_PROP(wxBitmapButton)
			WXJS_DECLARE_SET_PROP(wxBitmapButton)
			WXJS_DECLARE_SET_STR_PROP(wxBitmapButton)
			WXJS_DECLARE_CONSTRUCTOR(wxBitmapButton)
            WXJS_DECLARE_DESTRUCTOR(wxBitmapButton)

	        WXJS_DECLARE_PROPERTY_MAP()

	        /**
	         * Property Ids.
	         */
	        enum
	        {
		        P_BITMAP_DISABLED
		        , P_BITMAP_FOCUS
		        , P_BITMAP_SELECTED
		        , P_BITMAP_LABEL
	        };

            WXJS_DECLARE_METHOD_MAP()
            WXJS_DECLARE_METHOD(create)

			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };
    }; // namespace gui
}; //namespace wxjs
#endif //_WXJSBitmapButton_H
