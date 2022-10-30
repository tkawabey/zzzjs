/*
 * wxJavaScript - command.h
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
 * $Id: command.h 744 2007-06-11 19:57:09Z fbraem $
 */
#ifndef _WXJSCommandEvent_H
#define _WXJSCommandEvent_H

/////////////////////////////////////////////////////////////////////////////
// Name:        command.h
// Purpose:     CommandEvent ports wxCommandEvent to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     01.02.2002
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Name:        command.h
// Purpose:     CommandEvent ports wxCommandEvent to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     01.02.2002
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        typedef JSEvent<wxCommandEvent> PrivCommandEvent;
        class CommandEvent : public ApiWrapper<CommandEvent, PrivCommandEvent>
        {
        public:
			WXJS_DECLARE_GET_PROP(PrivCommandEvent)
			WXJS_DECLARE_SET_STR_PROP(PrivCommandEvent)

            virtual ~CommandEvent()
            {
            }

            enum
            { 
              P_CHECKED
              , P_SELECTION
              , P_STRING
              , P_INTEGER
            };

            WXJS_DECLARE_PROPERTY_MAP()
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSCommandEvent_H
