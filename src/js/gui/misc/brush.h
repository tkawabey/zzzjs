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
#ifndef _ZZZZJS_MISC_BRUSH_H
#define _ZZZZJS_MISC_BRUSH_H

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
        class Brush : public JsWrapper<Brush, wxBrush>
        {
        public:
			
			ZZZJS_DECLARE_GET_PROP(wxBrush)
			ZZZJS_DECLARE_SET_PROP(wxBrush)
			ZZZJS_DECLARE_CONSTRUCTOR(wxBrush)
			
			//static wxBrush* getConv(JSContext *cx, JS::Value v, wxBrush& workData);
			//static wxBrush* getConv(JSContext *cx, JSObject *obj, wxBrush& workData);
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxBrush)
			
			// Propeties
	        enum
	        {
					P_Colour 
				,	P_STIPPLE
				,	P_STYLE
				,	P_IS_HATCH
				,	P_IS_OK
				,	P_IS_NON_TRANSPARENT
				,	P_IS_TRANSPARENT
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()

				
			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(setColour);
        };

        void DefineGlobalBrushs(JSContext *cx, JSObject *obj);
        void DefineGlobalBrush(JSContext *cx, JSObject *obj,
						        const char *name, const wxBrush*colour);
    }; // namespace gui
}; // namespace zzzJs

#endif //_ZZZZJS_MISC_BRUSH_H
