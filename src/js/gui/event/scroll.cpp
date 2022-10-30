/*
 * wxJavaScript - scroll.cpp
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
 * $Id: scroll.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// scroll.cpp
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
#include "js/gui/event/scroll.h"
#include "js/gui/event/command.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/scroll</file>
 * <module>gui</module>
 * <class name="wxScrollEvent" prototype="@wxCommandEvent">
 *  A scroll event holds information about events sent from stand-alone scrollbars, 
 *  spin-buttons and sliders. Note that scrolled windows send the @wxScrollWinEvent 
 *  don't confuse these two kinds of events, and use this event only for the scrollbar-like controls.
 * </class>
 */
WXJS_INIT_CLASS(ScrollEvent, "ScrollEvent", 0)

/***
 * <properties>
 *	<property name="orientation" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns wxDirection.HORIZONTAL or wxDirection.VERTICAL
 *  </property>
 *  <property name="position" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns the position of the scrollbar
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ScrollEvent)
	WXJS_READONLY_PROPERTY(P_ORIENTATION, "orientation")
	WXJS_READONLY_PROPERTY(P_POSITION, "position")
WXJS_END_PROPERTY_MAP()

bool ScrollEvent::GetProperty(PrivScrollEvent *p,  
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxScrollEvent *event = p->GetEvent();
	switch(id)
	{
	case P_ORIENTATION:
		ToJSVal(cx, vp, event->GetOrientation());
		break;
	case P_POSITION:
		ToJSVal(cx, vp, event->GetPosition());
		break;
	}
	return true;
}

	
WXJS_BEGIN_GET_SET_STR_PROP(PrivScrollEvent, ScrollEvent)
	CommandEvent::SetStringProperty((PrivCommandEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP