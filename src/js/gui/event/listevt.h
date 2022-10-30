/*
 * wxJavaScript - listevt.h
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
 * $Id: listevt.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSListEvent_H
#define _WXJSListEvent_H

/////////////////////////////////////////////////////////////////////////////
// Name:        listevt.h
// Purpose:		Ports wxListEvent to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     04.10.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/listctrl.h>

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        typedef JSEvent<wxListEvent> PrivListEvent;
        class ListEvent : public ApiWrapper<ListEvent, PrivListEvent>
        {
        public:
			WXJS_DECLARE_GET_PROP(PrivListEvent)
			WXJS_DECLARE_SET_STR_PROP(PrivListEvent)

            virtual ~ListEvent()
            {
            }
                
            enum
            {
	            P_CODE
	            , P_INDEX
                , P_COLUMN
                , P_POINT
                , P_LABEL
                , P_TEXT
                , P_IMAGE
                , P_DATA
                , P_MASK
                , P_ITEM
                , P_CACHE_FROM
                , P_CACHE_TO
            };

            WXJS_DECLARE_PROPERTY_MAP()
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSCalendarEvent_H
