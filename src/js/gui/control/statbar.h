/*
 * wxJavaScript - statbar.h
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
 * $Id: statbar.h 694 2007-05-03 21:14:13Z fbraem $
 */
#ifndef _WXJSStatusBar_H
#define _WXJSStatusBar_H

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class StatusBar : public ApiWrapper<StatusBar, wxStatusBar>
        {
        public:
			
			WXJS_DECLARE_GET_PROP(wxStatusBar)
			WXJS_DECLARE_SET_PROP(wxStatusBar)
			WXJS_DECLARE_SET_STR_PROP(wxStatusBar)
			WXJS_DECLARE_CONSTRUCTOR(wxStatusBar)
			WXJS_DECLARE_DESTRUCTOR(wxStatusBar)


            WXJS_DECLARE_CONSTANT_MAP()

            WXJS_DECLARE_METHOD_MAP()
            WXJS_DECLARE_METHOD(create)
            WXJS_DECLARE_METHOD(getFieldRect)
            WXJS_DECLARE_METHOD(setFieldsCount)
            WXJS_DECLARE_METHOD(setStatusText)
            WXJS_DECLARE_METHOD(getStatusText)
			
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
 
            WXJS_DECLARE_PROPERTY_MAP()
            enum
            {
                P_FIELDS_COUNT
                , P_STATUS_WIDTHS
            };
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSStatusBar_H
