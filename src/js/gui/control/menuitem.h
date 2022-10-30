/*
 * wxJavaScript - menuitem.h
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
 * $Id: menuitem.h 688 2007-04-27 20:45:09Z fbraem $
 */
#ifndef _WXJSMENUITEM_H
#define _WXJSMENUITEM_H

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class MenuItem : public ApiWrapper<MenuItem, wxMenuItem>
        {
        public:
			WXJS_DECLARE_GET_PROP(wxMenuItem)
			WXJS_DECLARE_SET_PROP(wxMenuItem)
			WXJS_DECLARE_CONSTRUCTOR(wxMenuItem)
            WXJS_DECLARE_DESTRUCTOR(wxMenuItem)



	        WXJS_DECLARE_METHOD_MAP()
	        WXJS_DECLARE_METHOD(is_checkable)
	        WXJS_DECLARE_METHOD(is_separator)
	        WXJS_DECLARE_METHOD(setBitmaps)

            WXJS_DECLARE_PROPERTY_MAP()
	        enum
	        {
		        P_LABEL = WXJS_START_PROPERTY_ID
		        , P_TEXT
		        , P_CHECK
		        , P_CHECKABLE
		        , P_ENABLE
		        , P_HELP
		        , P_ID
		        , P_MARGIN_WIDTH
		        , P_SUB_MENU
		        , P_ACCEL
		        , P_BG_COLOUR
		        , P_MENU
		        , P_FONT
		        , P_BITMAP
		        , P_TEXT_COLOUR
		        , P_SEPARATOR
	        };
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSMENUITEM_H
