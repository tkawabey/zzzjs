/*
 * wxJavaScript - accentry.h
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
 * $Id: accentry.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSAcceleratorEntry_H
#define _WXJSAcceleratorEntry_H


#include "js/common/jswrap.h"

/////////////////////////////////////////////////////////////////////////////
// Name:        accentry.h
// Purpose:		AcceleratorEntry ports wxAcceleratorEntry to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     06.06.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class AcceleratorEntry : public JsWrapper<AcceleratorEntry, wxAcceleratorEntry>
        {
        public:
			
			ZZZJS_DECLARE_GET_PROP(wxAcceleratorEntry)
			ZZZJS_DECLARE_SET_PROP(wxAcceleratorEntry)
			ZZZJS_DECLARE_CONSTRUCTOR(wxAcceleratorEntry)
        	
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxAcceleratorEntry)


	        ZZZJS_DECLARE_CONSTANT_MAP()

	        /**
	         * Property Ids.
	         */
	        enum
	        {
		          P_FLAG
		        , P_KEYCODE
		        , P_COMMAND
		        , P_MENUITEM
		        , P_ISOK
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()
			
			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(set);
			ZZZJS_DECLARE_METHOD(toString);
			ZZZJS_DECLARE_METHOD(toRawString);
			ZZZJS_DECLARE_METHOD(fromString);
        };
    }; // namespace gui
}; // namespace zzzJs

#endif //_WXJSAcceleratorEntry_H
