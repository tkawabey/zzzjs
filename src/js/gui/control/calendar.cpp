/*
 * wxJavaScript - calendar.cpp
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
 * $Id: calendar.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// calendar.cpp
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/ext/point.h"
#include "js/common/conf.h"
#include "js/common/index.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"


#include "js/gui/event/jsevent.h"
#include "js/gui/event/cal.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/colour.h"

#include "js/gui/control/calendar.h"
#include "js/gui/control/caldate.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"
#include "js/gui/errors.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/calendar</file>
 * <module>gui</module>
 * <class name="wxCalendarCtrl" prototype="@wxControl">
 *  The calendar control allows the user to pick a date. For this, 
 *  it displays a window containing several parts: a control at the top to pick 
 *  the month and the year (either or both of them may be disabled),
 *  and a month area below them which shows all the days in the month. 
 *  The user can move the current selection using the keyboard and select the
*   date (generating @wxCalendarCtrl#onCalendar event) 
 *  by pressing return or double clicking it.
 *  <br /><br />
 *  It has advanced possibilities for the customization of its display. 
 *  All global settings (such as colours and fonts used) can, of course, be 
 *  changed. But also, the display style for each day in the month can be set 
 *  independently using @wxCalendarDateAttr.
 * </class>
 */
WXJS_INIT_CLASS(CalendarCtrl, "CalendarCtrl", 2)

void CalendarCtrl::InitClass(JSContext* WXUNUSED(cx),
                             JSObject* WXUNUSED(obj), 
                             JSObject* WXUNUSED(proto))
{
    CalendarEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="attr" type="@wxCalendarDateAttr array" readonly="Y">
 *   Get the attributes of a day. The array index must be between 1 and 31.
 *  </property>
 *  <property name="date" type="Date">Get/Set the current date</property>
 *  <property name="enableHolidayDisplay" type="Boolean">
 *   Show/hide holidays (write only)
 *  </property>
 *  <property name="enableMonthChange" type="Boolean">
 *   Enable/Disable month changing (write only)
 *  </property>
 *  <property name="enableYearChange" type="Boolean">
 *   Enable/Disable year changing (write only)
 *  </property>
 *  <property name="headerColourBg" type="@wxColour">
 *   Get/Set the background colour of the header. 
 *   See @wxCalendarCtrl#setHeaderColours and @wxCalendarCtrl#headerColourFg
 *  </property>
 *  <property name="headerColourFg" type="@wxColour">
 *   Get/Set the foreground colour of the header.
 *   See @wxCalendarCtrl#setHeaderColours and @wxCalendarCtrl#headerColourBg
 *  </property>
 *  <property name="highlightColourBg" type="@wxColour">
 *   Get/Set the background colour of the selected date.
 *   See @wxCalendarCtrl#setHighlightColours 
 *   and @wxCalendarCtrl#highlightColourFg
 *  </property>
 *  <property name="highlightColourFg" type="@wxColour">
 *   Get/Set the foreground colour of the selected date.
 *   See @wxCalendarCtrl#setHighlightColours and
 *   @wxCalendarCtrl#highlightColourBg
 *  </property>
 *  <property name="holidayColourBg" type="@wxColour">
 *   Get/Set the background colour of a holiday.
 *   See @wxCalendarCtrl#setHolidayColours and @wxCalendarCtrl#holidayColourFg
 *  </property>
 *  <property name="holidayColourFg" type="@wxColour">
 *   Get/Set the foreground colour of a holiday.
 *   See @wxCalendarCtrl#setHolidayColours and @wxCalendarCtrl#holidayColourBg
 *  </property>
 *  <property name="lowerDateLimit" type="Date">
 *   Get/Set the lower date limit in which selection might occur.
 *   Set to null to remove the lower limit. See @wxCalendarCtrl#upperDateLimit
 *   and @wxCalendarCtrl#setDateRange
 *  </property>
 *  <property name="upperDateLimit" type="Date">
 *   Get/Set the upper date limit in which selection might occur.
 *   Set to null to remove the upper limit. See @wxCalendarCtrl#lowerDateLimit
 *   and @wxCalendarCtrl#setDateRange
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CalendarCtrl)
  WXJS_PROPERTY(P_DATE, "date")
  //WXJS_PROPERTY(P_LOWER_DATE_LIMIT, "lowerDateLimit")
  //WXJS_PROPERTY(P_UPPER_DATE_LIMIT, "upperDateLimit")
  WXJS_PROPERTY(P_ENABLE_HOLIDAY_DISPLAY, "enableHolidayDisplay")
  WXJS_PROPERTY(P_ENABLE_MONTH_CHANGE, "enableMonthChange")
  //WXJS_PROPERTY(P_ENABLE_YEAR_CHANGE, "enableYearChange")
  WXJS_PROPERTY(P_HEADER_COLOUR_FG, "headerColourFg")
  WXJS_PROPERTY(P_HEADER_COLOUR_BG, "headerColourBg")
  WXJS_PROPERTY(P_HIGHLIGHT_COLOUR_FG, "highlightColourFg")
  WXJS_PROPERTY(P_HIGHLIGHT_COLOUR_BG, "highlightColourBg")
  WXJS_PROPERTY(P_HOLIDAY_COLOUR_FG, "holidayColourFg")
  WXJS_PROPERTY(P_HOLIDAY_COLOUR_BG, "holidayColourBg")
  WXJS_READONLY_PROPERTY(P_ATTR, "attr")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxCalendarCtrl, CalendarCtrl)
    switch (id) 
    {
    case P_ATTR:
        vp.set( CalendarDateAttr::CreateObject(cx, NULL, obj) );
        break;
    case P_DATE:
        ToJSVal(cx, vp, p->GetDate());
        break;
    //case P_LOWER_DATE_LIMIT:
    //    ToJSVal(cx, vp, p->GetLowerDateLimit());
    //    break;
    //case P_UPPER_DATE_LIMIT:
    //    ToJSVal(cx, vp, p->GetUpperDateLimit());
    //    break;
    case P_HEADER_COLOUR_FG:
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetHeaderColourFg())) );
        break;
    case P_HEADER_COLOUR_BG:
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetHeaderColourBg())) );
        break;
    case P_HIGHLIGHT_COLOUR_FG:
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetHighlightColourFg())) );
        break;
    case P_HIGHLIGHT_COLOUR_BG:
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetHighlightColourBg())) );
        break;
    case P_HOLIDAY_COLOUR_FG:
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetHolidayColourFg())) );
        break;
    case P_HOLIDAY_COLOUR_BG:
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetHolidayColourBg())) );
        break;
    }
    return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxCalendarCtrl, CalendarCtrl)
    switch (id) 
    {
    case P_DATE:
        {
            wxDateTime date;
            if ( FromJS(cx, vp, date) )
                p->SetDate(date);
            break;
        }
    //case P_LOWER_DATE_LIMIT:
    //    {
    //        if ( JSVAL_IS_NULL(*vp) )
    //            p->SetLowerDateLimit();
    //        else if ( JSVAL_IS_OBJECT(*vp) )
    //        {
    //            wxDateTime date;
    //            if ( FromJS(cx, *vp, date) )
    //                p->SetLowerDateLimit(date);
    //        }
    //        break;
    //    }
    //case P_UPPER_DATE_LIMIT:
    //    {
    //        if ( JSVAL_IS_NULL(*vp) )
    //            p->SetLowerDateLimit();
    //        else if ( JSVAL_IS_OBJECT(*vp) )
    //        {
    //            wxDateTime date;
    //            if ( FromJS(cx, *vp, date) )
    //                p->SetUpperDateLimit(date);
    //        }
    //        break;
    //    }
    case P_ENABLE_HOLIDAY_DISPLAY:
        {
            bool enable;
            if ( FromJS(cx, vp, enable) )
                p->EnableHolidayDisplay(enable);
            break;
        }
    //case P_ENABLE_YEAR_CHANGE:
    //    {
    //        bool enable;
    //        if ( FromJS(cx, vp, enable) )
    //            p->EnableYearChange(enable);
    //        break;
    //    }
    case P_ENABLE_MONTH_CHANGE:
        {
            bool enable;
            if ( FromJS(cx, vp, enable) )
                p->EnableMonthChange(enable);
            break;	
        }
    case P_HEADER_COLOUR_FG:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
            {
                wxColour bg = p->GetHeaderColourBg();
                p->SetHeaderColours(*colour, bg);
            }
            break;
        }
    case P_HEADER_COLOUR_BG:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
            {
                wxColour fg = p->GetHeaderColourFg();
                p->SetHeaderColours(fg, *colour);
            }
            break;
        }
    case P_HIGHLIGHT_COLOUR_FG:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
            {
                wxColour bg = p->GetHighlightColourBg();
                p->SetHighlightColours(*colour, bg);
            }
            break;
        }
    case P_HIGHLIGHT_COLOUR_BG:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
            {
                wxColour fg = p->GetHighlightColourBg();
                p->SetHighlightColours(fg, *colour);
            }
            break;
        }
    case P_HOLIDAY_COLOUR_FG:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
            {
                wxColour bg = p->GetHolidayColourBg();
                p->SetHolidayColours(*colour, bg);
            }
            break;
        }
    case P_HOLIDAY_COLOUR_BG:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
            {
                wxColour fg = p->GetHolidayColourBg();
                p->SetHolidayColours(fg, *colour);
            }
            break;
        }
    }
    return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxCalendarCtrl, CalendarCtrl)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


WXJS_BEGIN_ADD_PROP(wxCalendarCtrl, CalendarCtrl)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    CalendarEventHandler::ConnectEvent(p, prop, true);
    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxCalendarCtrl, CalendarCtrl)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  CalendarEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <constants>
 *  <type name="Styles">
 *   <constant name="SUNDAY_FIRST">
 *    Show Sunday as the first day in the week
 *   </constant>
 *   <constant name="MONDAY_FIRST">
 *    Show Monday as the first day in the week
 *   </constant>
 *   <constant name="SHOW_HOLIDAYS">
 *    Highlight holidays in the calendar
 *   </constant>
 *   <constant name="NO_YEAR_CHANGE">
 *    Disable the year changing
 *   </constant>
 *   <constant name="NO_MONTH_CHANGE">
 *    Disable the month (and, implicitly, the year) changing
 *   </constant>
 *   <constant name="SHOW_SURROUNDING_WEEKS">
 *    Show the neighbouring weeks in the previous and next months
 *   </constant>
 *   <constant name="SEQUENTIAL_MONTH_SELECTION">
 *    Use alternative, more compact, style for the month 
 *    and year selection controls.
 *   </constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(CalendarCtrl)
  WXJS_CONSTANT(wxCAL_, SUNDAY_FIRST)
  WXJS_CONSTANT(wxCAL_, MONDAY_FIRST)
  WXJS_CONSTANT(wxCAL_, SHOW_HOLIDAYS)
  WXJS_CONSTANT(wxCAL_, NO_YEAR_CHANGE)
  WXJS_CONSTANT(wxCAL_, NO_MONTH_CHANGE)
  WXJS_CONSTANT(wxCAL_, SHOW_SURROUNDING_WEEKS)
  WXJS_CONSTANT(wxCAL_, SEQUENTIAL_MONTH_SELECTION)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent of wxCalendarCtrl.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="DefaultDate" type="Date">
 *    The date to select when the control is shown. Use null to use
 *    the default.
 *   </arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the CalendarCtrl control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the CalendarCtrl control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxCalendarCtrl.SHOW_HOLIDAYS">
 *    The wxCalendarCtrl style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxCalendarCtrl object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxCalendarCtrl, CalendarCtrl)

	 wxCalendarCtrl *p = new wxCalendarCtrl();

    SetPrivate(cx, obj, p);

    if ( argc > 0 )
    {
        jsval rval;
        if ( ! _innerCreate(cx, obj, argc, vp, &rval) )
        {
          return NULL;
        }
    }

	return p;
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxCalendarCtrl, CalendarCtrl)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(CalendarCtrl)
  WXJS_METHOD("create", create, 2)
  WXJS_METHOD("setDateRange", setDateRange, 2)
  WXJS_METHOD("setHeaderColours", setHeaderColours, 2)
  WXJS_METHOD("setHighlightColours", setHighlightColours, 2)
  WXJS_METHOD("setHolidayColours", setHolidayColours, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent of wxCalendarCtrl.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="DefaultDate" type="Date">
 *    The date to select when the control is shown. Use null to use
 *    the default.
 *   </arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the CalendarCtrl control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the CalendarCtrl control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxCalendarCtrl.SHOW_HOLIDAYS">
 *    The wxCalendarCtrl style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a calendar control.
 *  </desc>
 * </method>
 */
JSBool CalendarCtrl::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
 
JSBool CalendarCtrl::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{	
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxCalendarCtrl *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
    
	if ( argc > 6 )
	argc = 6;
	
	int argIndex = 0;
	int style = 0;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	wxDateTime date;
	
	ZZZJS_CHECK_ARG_COUNT(3, 6);

	
	argIndex = argc -1;
	switch(argc)
	{
	case 6: // style
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 5:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	case 3:
		if ( ! FromJS(cx, argv[argIndex], date) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Date");
			return JS_FALSE;
		}
		argIndex--;
	default:
		int id;
		wxWindow *parent =NULL;

		
		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;



		JavaScriptClientData *clntParent =
			dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, date, *(apPoint.get()), *(apSize.get()), style) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	return JS_TRUE;
}
/***
 * <method name="setDateRange">
 *  <function>
 *   <arg name="LowerLimit" type="Date" default="null">
 *    The lower limit of the selection. Use null to reset this.
 *   </arg>
 *   <arg name="UpperLimit" type="Date" default="null">
 *    The upper limit of the selection. Use null to reset this.
 *   </arg>
 *  </function>
 *  <desc>
 *   Set the range in which selection can occur. 
 *   See @wxCalendarCtrl#lowerDateLimit and
 *   @wxCalendarCtrl#upperDateLimit
 *  </desc>
 * </method>
 */
JSBool CalendarCtrl::setDateRange(JSContext *cx, unsigned argc, JS::Value *vp)
{
 	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxCalendarCtrl *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxDateTime minDate;
    wxDateTime maxDate;
    if (    FromJS(cx, argv[0], minDate)
         && FromJS(cx, argv[1], maxDate) )
    	p->SetDateRange(minDate, maxDate);

	return JS_TRUE;
}

/***
 * <method name="setHeaderColours">
 *  <function>
 *   <arg name="ForegroundColour" type="@wxColour">
 *    The foreground colour of the header</arg>
 *   <arg name="BackgroundColour" type="@wxColour">
 *    The background colour of the header</arg>
 *  </function>
 *  <desc>
 *   Sets the colours of the header. 
 *   See @wxCalendarCtrl#headerColourFg and @wxCalendarCtrl#headerColourBg
 *  </desc>
 * </method>
 */
JSBool CalendarCtrl::setHeaderColours(JSContext *cx, unsigned argc, JS::Value *vp)
{
 	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxCalendarCtrl *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxColour *fg = Colour::GetPrivate(cx, argv[0]);
	wxColour *bg = Colour::GetPrivate(cx, argv[1]);

	if (    fg != NULL
		 && bg != NULL )
	{
		p->SetHeaderColours(*fg, *bg);
		return JS_TRUE;
	}

    return JS_FALSE;
}

/***
 * <method name="setHighlightColours">
 *  <function>
 *   <arg name="ForegroundColour" type="@wxColour">
 *    The foreground colour of the highlighted date
 *   </arg>
 *   <arg name="BackgroundColour" type="@wxColour">
 *    The background colour of the highlighted date
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the colours of the highlighted date. 
 *   See @wxCalendarCtrl#highlightColourFg
 *   and @wxCalendarCtrl#highlightColourBg
 *  </desc>
 * </method>
 */
JSBool CalendarCtrl::setHighlightColours(JSContext *cx, unsigned argc, JS::Value *vp)
{
 	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxCalendarCtrl *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxColour *fg = Colour::GetPrivate(cx, argv[0]);
	wxColour *bg = Colour::GetPrivate(cx, argv[1]);

	if (    fg != NULL
		 && bg != NULL )
	{
		p->SetHighlightColours(*fg, *bg);
		return JS_TRUE;
	}

    return JS_FALSE;
}

/***
 * <method name="setHolidayColours">
 *  <function>
 *   <arg name="ForegroundColour" type="@wxColour">
 *    The foreground colour of a holiday
 *   </arg>
 *   <arg name="BackgroundColour" type="@wxColour">
 *    The background colour of a holiday
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the colours of a holiday. 
 *   See @wxCalendarCtrl#holidayColourFg and @wxCalendarCtrl#holidayColourBg
 *  </desc>
 * </method>
 */
JSBool CalendarCtrl::setHolidayColours(JSContext *cx, unsigned argc, JS::Value *vp)
{
 	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

   wxCalendarCtrl *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxColour *fg = Colour::GetPrivate(cx, argv[0]);
	wxColour *bg = Colour::GetPrivate(cx, argv[1]);

	if (    fg != NULL
		 && bg != NULL )
	{
		p->SetHolidayColours(*fg, *bg);
		return JS_TRUE;
	}

    return JS_FALSE;
}

WXJS_INIT_EVENT_MAP(wxCalendarCtrl)
const wxString WXJS_CAL_EVENT = wxT("onCalendar");
const wxString WXJS_CAL_SELCHANGED_EVENT = wxT("onCalendarSelChanged");
const wxString WXJS_CAL_DAY_EVENT = wxT("onCalendarDay");
const wxString WXJS_CAL_MONTH_EVENT = wxT("onCalendarMonth");
const wxString WXJS_CAL_YEAR_EVENT = wxT("onCalendarYear");
const wxString WXJS_CAL_WEEKDAY_CLICKED_EVENT = wxT("onCalendarWeekDayClicked");

/***
 * <events>
 *  <event name="onCalendar">
 *   A day is double clicked. The function gets a @wxCalendarEvent as argument.
 *  </event>
 *  <event name="onCalendarSelChanged">
 *   The selected date is changed. 
 *   The function gets a @wxCalendarEvent as argument.
 *  </event>
 *  <event name="onCalendarDay">
 *   The selected day is changed. 
 *   The function gets a @wxCalendarEvent as argument.
 *  </event>
 *  <event name="onCalendarMonth">
 *   The selected month is changed. 
 *   The function gets a @wxCalendarEvent as argument.
 *  </event>
 *  <event name="onCalendarYear">
 *   The selected year is changed. 
 *   The function gets a @wxCalendarEvent as argument.
 *  </event>
 *  <event name="onCalendarWeekDayClicked">
 *   The user clicked on the week day header.
 *   The function gets a @wxCalendarEvent as argument.
 *  </event>
 * </events>
 */

void CalendarEventHandler::OnCalendar(wxCalendarEvent &event)
{
  PrivCalendarEvent::Fire<CalendarEvent>(event, WXJS_CAL_EVENT);
}

void CalendarEventHandler::OnCalendarSelChanged(wxCalendarEvent &event)
{
  PrivCalendarEvent::Fire<CalendarEvent>(event, WXJS_CAL_SELCHANGED_EVENT);
}

void CalendarEventHandler::OnCalendarDay(wxCalendarEvent &event)
{
  PrivCalendarEvent::Fire<CalendarEvent>(event, WXJS_CAL_DAY_EVENT);
}

void CalendarEventHandler::OnCalendarMonth(wxCalendarEvent &event)
{
  PrivCalendarEvent::Fire<CalendarEvent>(event, WXJS_CAL_MONTH_EVENT);
}

void CalendarEventHandler::OnCalendarYear(wxCalendarEvent &event)
{
  PrivCalendarEvent::Fire<CalendarEvent>(event, WXJS_CAL_YEAR_EVENT);
}

void CalendarEventHandler::OnCalendarWeekDayClicked(wxCalendarEvent &event)
{
  PrivCalendarEvent::Fire<CalendarEvent>(event, WXJS_CAL_WEEKDAY_CLICKED_EVENT);
}

void CalendarEventHandler::ConnectCalendar(wxCalendarCtrl *p,
                                           bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CALENDAR_DOUBLECLICKED,
               wxCalendarEventHandler(CalendarEventHandler::OnCalendar));
  }
  else
  {
    p->Disconnect(wxEVT_CALENDAR_DOUBLECLICKED,
                  wxCalendarEventHandler(CalendarEventHandler::OnCalendar));
  }
}

void CalendarEventHandler::ConnectCalendarDay(wxCalendarCtrl *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CALENDAR_DAY_CHANGED, 
               wxCalendarEventHandler(CalendarEventHandler::OnCalendarDay));
  }
  else
  {
    p->Disconnect(wxEVT_CALENDAR_DAY_CHANGED, 
                  wxCalendarEventHandler(CalendarEventHandler::OnCalendarDay));
  }
}

void CalendarEventHandler::ConnectCalendarSelChanged(wxCalendarCtrl *p,
                                                     bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CALENDAR_SEL_CHANGED,
               wxCalendarEventHandler(CalendarEventHandler::OnCalendarSelChanged));
  }
  else
  {
    p->Disconnect(wxEVT_CALENDAR_SEL_CHANGED,
                  wxCalendarEventHandler(CalendarEventHandler::OnCalendarSelChanged));
  }
}

void CalendarEventHandler::ConnectCalendarMonth(wxCalendarCtrl *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CALENDAR_MONTH_CHANGED,
               wxCalendarEventHandler(CalendarEventHandler::OnCalendarMonth));
  }
  else
  {
    p->Disconnect(wxEVT_CALENDAR_MONTH_CHANGED,
                  wxCalendarEventHandler(CalendarEventHandler::OnCalendarMonth));
  }
}

void CalendarEventHandler::ConnectCalendarYear(wxCalendarCtrl *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CALENDAR_YEAR_CHANGED,
               wxCalendarEventHandler(CalendarEventHandler::OnCalendarYear));
  }
  else
  {
    p->Disconnect(wxEVT_CALENDAR_YEAR_CHANGED,
                  wxCalendarEventHandler(CalendarEventHandler::OnCalendarYear));
  }
}

void CalendarEventHandler::ConnectCalendarWeekDayClicked(wxCalendarCtrl *p,
                                                         bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CALENDAR_WEEKDAY_CLICKED,
               wxCalendarEventHandler(CalendarEventHandler::OnCalendarWeekDayClicked));
  }
  else
  {
    p->Disconnect(wxEVT_CALENDAR_WEEKDAY_CLICKED,
                  wxCalendarEventHandler(CalendarEventHandler::OnCalendarWeekDayClicked));
  }
}

void CalendarEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_CAL_EVENT, ConnectCalendar);
  AddConnector(WXJS_CAL_DAY_EVENT, ConnectCalendarDay);
  AddConnector(WXJS_CAL_MONTH_EVENT, ConnectCalendarMonth);
  AddConnector(WXJS_CAL_YEAR_EVENT, ConnectCalendarYear);
  AddConnector(WXJS_CAL_SELCHANGED_EVENT, ConnectCalendarSelChanged);
  AddConnector(WXJS_CAL_WEEKDAY_CLICKED_EVENT, ConnectCalendarWeekDayClicked);
}
