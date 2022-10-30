/*
 * wxJavaScript - rect.h
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
 * $Id: rect.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _ZZZJSRect_H
#define _ZZZJSRect_H

#include "js/common/jswrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        rect.h
// Purpose:		Ports wxRect to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     25.05.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class Rect : public JsWrapper<Rect, wxRect>
        {
        public:
			
			
			ZZZJS_DECLARE_GET_PROP(wxRect)
			ZZZJS_DECLARE_SET_PROP(wxRect)
			ZZZJS_DECLARE_CONSTRUCTOR(wxRect)
        	

			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxRect)



	        static JSBool inflate(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool deflate(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool offset(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool intersect(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool inside(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool intersects(JSContext *cx, unsigned argc, JS::Value *vp);

	        ZZZJS_DECLARE_PROPERTY_MAP()
	        ZZZJS_DECLARE_METHOD_MAP()

	        /**
	         * Property Ids.
	         */
	        enum
	        {
		        P_WIDTH
		        , P_HEIGHT
		        , P_BOTTOM
		        , P_LEFT
		        , P_POSITION
		        , P_RIGHT
		        , P_SIZE
		        , P_TOP
		        , P_X
		        , P_Y
	        };
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZJSRect_H

