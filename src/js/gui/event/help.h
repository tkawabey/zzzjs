/*
 * wxJavaScript - help.h
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
 * $Id: help.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSHelpEvent_H
#define _WXJSHelpEvent_H

/////////////////////////////////////////////////////////////////////////////
// Name:        help.h
// Purpose:     HelpEvent ports wxHelpEvent to JavaScript.
// Author:      Franky Braem
// Modified by:
// Created:     28.09.2002
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        typedef JSEvent<wxHelpEvent> PrivHelpEvent;

        class HelpEvent : public ApiWrapper<HelpEvent, PrivHelpEvent>
        {
        public:
            virtual ~HelpEvent()
            {
            }
			
			WXJS_DECLARE_GET_PROP(PrivHelpEvent)
			WXJS_DECLARE_SET_PROP(PrivHelpEvent)
			WXJS_DECLARE_SET_STR_PROP(PrivHelpEvent)

            enum
            { 
              P_POSITION
            };

            WXJS_DECLARE_PROPERTY_MAP()
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSMoveEvent_H
