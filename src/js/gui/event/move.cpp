/*
 * wxJavaScript - move.cpp
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
 * $Id: move.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// move.cpp
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
#include "js/gui/event/move.h"
#include "js/gui/event/event.h"


#include "js/ext/zzzjs_ext_init.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/move</file>
 * <module>gui</module>
 * <class name="wxMoveEvent" prototype="@wxEvent">
 *	 A move event holds information about move change events.
 *   Handle this event by setting a function to the @wxWindow#onMove 
 *   property on a @wxWindow object. 
 * </class>
 */
WXJS_INIT_CLASS(MoveEvent, "MoveEvent", 0)

/***
 * <properties>
 *	<property name="position" type="@wxPoint" readonly="Y">
 *	 Returns the position of the window generating this event.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(MoveEvent)
	WXJS_READONLY_PROPERTY(P_POSITION, "position")
WXJS_END_PROPERTY_MAP()

bool MoveEvent::GetProperty(PrivMoveEvent *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxMoveEvent *event = p->GetEvent();

	if ( id == P_POSITION )
	{
      vp.set( zzzJs::ext::CreatePoint(cx, event->GetPosition()) );
	}
	return true;
}

	
WXJS_BEGIN_GET_SET_STR_PROP(PrivMoveEvent, MoveEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP