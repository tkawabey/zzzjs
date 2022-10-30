/*
 * wxJavaScript - caldate.h
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
 * $Id: caldate.h 667 2007-04-06 20:34:24Z fbraem $
 */
#ifndef _WXJSCalendarDateAttr_H
#define _WXJSCalendarDateAttr_H
#include <wx/calctrl.h>
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
      class CalendarDateAttr : public ApiWrapper<CalendarDateAttr,
                                                 wxCalendarDateAttr>
      {
      public:
		  
			WXJS_DECLARE_GET_PROP(wxCalendarDateAttr)
			WXJS_DECLARE_SET_PROP(wxCalendarDateAttr)
			//WXJS_DECLARE_SET_STR_PROP(wxCalendarDateAttr)	e‚Í–³‚µ
			WXJS_DECLARE_CONSTRUCTOR(wxCalendarDateAttr)
            WXJS_DECLARE_DESTRUCTOR(wxCalendarDateAttr)

            static wxCalendarDateAttr *Clone(wxCalendarDateAttr *attr)
            {
              return new wxCalendarDateAttr(attr->GetTextColour()
                                            , attr->GetBackgroundColour()
                                            , attr->GetBorderColour()
                                            , attr->GetFont()
                                            , attr->GetBorder());
            }

            WXJS_DECLARE_PROPERTY_MAP()
            enum
            {
                P_TEXT_COLOUR = WXJS_START_PROPERTY_ID
                , P_BG_COLOUR
                , P_BORDER_COLOUR
                , P_FONT
                , P_BORDER
                , P_HOLIDAY
            };
        };
    }; // namespace gui
}; // namespace wxjs
#endif //_WXJSCalendarDateAttr_H
