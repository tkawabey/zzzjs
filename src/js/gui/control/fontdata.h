/*
 * wxJavaScript - fontdata.h
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
 * $Id: fontdata.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSFontData_H
#define _WXJSFontData_H

/////////////////////////////////////////////////////////////////////////////
// Name:        fontdata.h
// Purpose:		FontData ports wxFontData to JavaScript.
// Author:      Franky Braem
// Modified by:
// Created:     05.08.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////
#include <wx/fontdata.h>
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class FontData : public ApiWrapper<FontData, wxFontData>
        {
        public:
			WXJS_DECLARE_GET_PROP(wxFontData)
			WXJS_DECLARE_SET_PROP(wxFontData)
			WXJS_DECLARE_CONSTRUCTOR(wxFontData)

	        WXJS_DECLARE_PROPERTY_MAP()

	        /**
	         * Property Ids.
	         */
	        enum
	        {
	          P_ALLOW_SYMBOLS
	          , P_ENABLE_EFFECTS
	          , P_CHOSEN_FONT
              , P_COLOUR
              , P_INITIAL_FONT
              , P_SHOW_HELP
	        };
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSFontData_H
