/*
 * wxJavaScript - cal.cpp
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
 * $Id: cal.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// cal.cpp
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/gui/event/jsevent.h"
#include "js/gui/event/cal.h"
#include "js/gui/event/event.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/cal</file>
 * <module>gui</module>
 * <class name="wxCalendarEvent" prototype="@wxEvent">
 *	This object is passed to a function that is set to a @wxCalendarCtrl event property.
 * </class>
 */
WXJS_INIT_CLASS(CalendarEvent, "CalendarEvent", 0)

/***
 * <properties>
 *	<property name="date" type="Date" readonly="Y">
 *	 Returns the date.
 *  </property>
 *	<property name="weekDay" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the weekday
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CalendarEvent)
	WXJS_READONLY_PROPERTY(P_DATE, "date")
	WXJS_READONLY_PROPERTY(P_WEEKDAY, "weekDay")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(PrivCalendarEvent, CalendarEvent)
	switch (id) 
	{
	case P_DATE:
		ToJSVal(cx, vp, p->GetEvent()->GetDate());
		break;
	case P_WEEKDAY:
		ToJSVal(cx, vp, (int) p->GetEvent()->GetWeekDay());
		break;
	}
	return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivCalendarEvent, CalendarEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
