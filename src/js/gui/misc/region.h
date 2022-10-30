/*
 * wxJavaScript - region.h
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
 * $Id: bitmap.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _ZZZZJS_GUI_MISC_REGION_H
#define _ZZZZJS_GUI_MISC_REGION_H

#include "js/common/jswrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        bitmap.h
// Purpose:		Ports wxRegion to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     09.08.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
// Since:       version 0.4
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class Region : public JsWrapper<Region, wxRegion>
        {
        public:
			
			ZZZJS_DECLARE_GET_PROP(wxRegion)
			ZZZJS_DECLARE_SET_PROP(wxRegion)
			ZZZJS_DECLARE_CONSTRUCTOR(wxRegion)
			
			// Object 2 Instatance
			static wxRegion* getObject2Instance(JSContext *cx, JS::Value v, bool& bAllocation);
			static wxRegion* getObject2Instance(JSContext *cx, JSObject *obj, bool& bAllocation);


			// Propeties
	        enum
	        {
					P_IsEMPTY
				,	P_BOX
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()

			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
	        static JSBool contains(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool convertToBitmap(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool intersect(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool isEqual(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool subtract(JSContext *cx, unsigned argc, JS::Value *vp);
			static JSBool __union(JSContext *cx, unsigned argc, JS::Value *vp);	// unionÇÕó\ñÒåÍÇ»ÇÃÇ≈ÅA__unionÇ∆Ç¢Ç§ä÷êîñºÇ…ÇµÇƒÇ¢ÇÈÅB
			static JSBool xor(JSContext *cx, unsigned argc, JS::Value *vp);
			static JSBool offset(JSContext *cx, unsigned argc, JS::Value *vp);

        };
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZZJS_GUI_MISC_REGION_H
