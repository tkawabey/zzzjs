/*
 * wxJavaScript - mask.h
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
 * $Id: mask.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _ZZZJS_GUI_MISC_MASK_H
#define _ZZZJS_GUI_MISC_MASK_H

#include "js/common/jswrap.h"
#include <wx/bitmap.h>
/////////////////////////////////////////////////////////////////////////////
// Name:        mask.h
// Purpose:		Ports wxMask to JavaScript
// Author:      Kawabuchi
// Modified by:
// Created:     2017.09.11
// Copyright:   (c) 2017-2017 Kawabuchi
// Licence:     LGPL
// Since:       version 0.1
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class Mask : public JsWrapper<Mask, wxMask>
        {
        public:
			
			ZZZJS_DECLARE_GET_PROP(wxMask)
			ZZZJS_DECLARE_CONSTRUCTOR(wxMask)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxMask)

			
			// Propeties
	        enum
	        {
					P_BITMAP
	        };

	        ZZZJS_DECLARE_PROPERTY_MAP()

			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
	        static JSBool create(JSContext *cx, unsigned argc, JS::Value *vp);
			
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZJS_GUI_MISC_MASK_H
