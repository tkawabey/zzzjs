/*
 * wxJavaScript - colour.h
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
 * $Id: colour.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _ZZZZJS_MISC_PEN_H
#define _ZZZZJS_MISC_PEN_H

#include "js/common/jswrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        colour.h
// Purpose:		Ports wxColour to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     04.07.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////


namespace zzzJs
{
    namespace gui
    {
        class Pen : public JsWrapper<Pen, wxPen>
        {
        public:
			
			ZZZJS_DECLARE_GET_PROP(wxPen)
			ZZZJS_DECLARE_SET_PROP(wxPen)
			ZZZJS_DECLARE_CONSTRUCTOR(wxPen)
			
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxPen)
			
			
			// Propeties
	        enum
	        {
					P_Cap
				,	P_Colour 
				,	P_Dashes
				,	P_Join
				,	P_STIPPLE 
				,	P_STYLE 
				,	P_Width
				,	P_IS_OK
				,	P_IS_NON_TRANSPARENT
				,	P_IS_TRANSPARENT
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()

				
			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(setColour);
        };

        void DefineGlobalPens(JSContext *cx, JSObject *obj);
        void DefineGlobalPen(JSContext *cx, JSObject *obj,
						        const char *name, const wxPen*colour);
    }; // namespace gui
}; // namespace zzzJs

#endif //_ZZZZJS_MISC_PEN_H
