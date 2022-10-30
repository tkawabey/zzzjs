/*
 * wxJavaScript - scrollwin.cpp
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
 * $Id: scrollwin.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
/**
 * @if JS
 *	@page wxScrollWinEvent wxScrollWinEvent
 *	@since version 0.4
 * @endif
 */
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
#include "js/gui/event/scrollwin.h"
#include "js/gui/event/event.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/scrollwin</file>
 * <module>gui</module>
 * <class name="wxScrollWinEvent" prototype="@wxEvent">
 *  A scroll event holds information about events sent from scrolling windows.
 * </class>
 */
WXJS_INIT_CLASS(ScrollWinEvent, "ScrollWinEvent", 0)

/***
 * <properties>
 *  <property name="orientation" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns wxDirection.HORIZONTAL or wxDirection.VERTICAL
 *  </property>
 *	<property name="position" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns the position of the ScrollWinbar
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ScrollWinEvent)
	WXJS_READONLY_PROPERTY(P_ORIENTATION, "orientation")
	WXJS_READONLY_PROPERTY(P_POSITION, "position")
WXJS_END_PROPERTY_MAP()

bool ScrollWinEvent::GetProperty(PrivScrollWinEvent *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxScrollWinEvent *event = p->GetEvent();
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

	
WXJS_BEGIN_GET_SET_STR_PROP(PrivScrollWinEvent, ScrollWinEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP