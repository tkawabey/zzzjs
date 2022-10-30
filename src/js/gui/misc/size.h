/*
 * wxJavaScript - size.h
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
 * $Id: size.h 598 2007-03-07 20:13:28Z fbraem $
 */
/////////////////////////////////////////////////////////////////////////////
// Name:        size.h
// Purpose:		Ports wxSize to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     30.12.01
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#ifndef _WXJSSize_H
#define _WXJSSize_H
#include "js/common/jswrap.h"


namespace zzzJs
{
	namespace gui
	{
		class Size : public JsWrapper<Size, wxSize>
		{
		public:
			
			ZZZJS_DECLARE_GET_PROP(wxSize)
			ZZZJS_DECLARE_SET_PROP(wxSize)
			ZZZJS_DECLARE_CONSTRUCTOR(wxSize)

			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxSize)

			
			// Propeties
			enum
			{
				  P_WIDTH
				, P_HEIGHT
			};
			ZZZJS_DECLARE_PROPERTY_MAP()
        };
		

		void DefineSizeConst(JSContext *cx, JSObject *obj);
	}; // namespace gui
}; // namespace wxjs

#endif //_WXJSSize_H
