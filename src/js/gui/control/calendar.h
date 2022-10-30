/*
 * wxJavaScript - calendar.h
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
 * $Id: calendar.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _WXJSCalendarCtrl_H
#define _WXJSCalendarCtrl_H

#include <wx/calctrl.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class CalendarCtrl : public ApiWrapper<CalendarCtrl, wxCalendarCtrl>
        {
        public:

          static void InitClass(JSContext* cx, 
                                JSObject* obj, 
                                JSObject* proto);


			WXJS_DECLARE_ADD_PROP(wxCalendarCtrl)
			WXJS_DECLARE_DEL_PROP(wxCalendarCtrl)
			WXJS_DECLARE_GET_PROP(wxCalendarCtrl)
			WXJS_DECLARE_SET_PROP(wxCalendarCtrl)
			WXJS_DECLARE_SET_STR_PROP(wxCalendarCtrl)
			WXJS_DECLARE_CONSTRUCTOR(wxCalendarCtrl)
			WXJS_DECLARE_DESTRUCTOR(wxCalendarCtrl)

          WXJS_DECLARE_PROPERTY_MAP()
          enum
          {
             P_DATE = WXJS_START_PROPERTY_ID
           //, P_LOWER_DATE_LIMIT
           //, P_UPPER_DATE_LIMIT
           , P_ENABLE_HOLIDAY_DISPLAY
           //, P_ENABLE_YEAR_CHANGE
           , P_ENABLE_MONTH_CHANGE
           , P_HEADER_COLOUR_BG
           , P_HEADER_COLOUR_FG
           , P_HIGHLIGHT_COLOUR_BG
           , P_HIGHLIGHT_COLOUR_FG
           , P_HOLIDAY_COLOUR_BG
           , P_HOLIDAY_COLOUR_FG
           , P_ATTR
          };

          WXJS_DECLARE_CONSTANT_MAP()
          WXJS_DECLARE_METHOD_MAP()
          
          WXJS_DECLARE_METHOD(create)
          WXJS_DECLARE_METHOD(setDateRange)
          WXJS_DECLARE_METHOD(setHeaderColours)
          WXJS_DECLARE_METHOD(setHighlightColours)
          WXJS_DECLARE_METHOD(setHolidayColours)

			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };

        class CalendarEventHandler : public EventConnector<wxCalendarCtrl>
                                   , public wxEvtHandler
        {
        public:
          // Events
          void OnCalendar(wxCalendarEvent &event);
          void OnCalendarSelChanged(wxCalendarEvent &event);
          void OnCalendarDay(wxCalendarEvent &event);
          void OnCalendarMonth(wxCalendarEvent &event);
          void OnCalendarYear(wxCalendarEvent &event);
          void OnCalendarWeekDayClicked(wxCalendarEvent &event);
          static void InitConnectEventMap();
        private:
          static void ConnectCalendar(wxCalendarCtrl *p,
                                      bool connect);
          static void ConnectCalendarSelChanged(wxCalendarCtrl *p,
                                                bool connect);
          static void ConnectCalendarDay(wxCalendarCtrl *p,
                                         bool connect);
          static void ConnectCalendarMonth(wxCalendarCtrl *p, bool connect);
          static void ConnectCalendarYear(wxCalendarCtrl *p, bool connect);
          static void ConnectCalendarWeekDayClicked(wxCalendarCtrl *p,
                                                    bool connect);
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSCalendarCtrl_H
