/*
 * wxJavaScript - sizeevt.cpp
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
 * $Id: sizeevt.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// sizeevt.cpp
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
#include "js/gui/event/sizeevt.h"
#include "js/gui/event/event.h"
#include "js/gui/misc/size.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/sizeevt</file>
 * <module>gui</module>
 * <class name="wxSizeEvent" prototype="@wxEvent">
 *	 A size event holds information about size change events.
 *   Handle this event by setting a function to the @wxWindow#onSize 
 *   property on a @wxWindow object. 
 *   <br /><br />
 *   The size retrieved with size property is the size of the whole window.
 *   Use @wxWindow#clientSize for the area which may be used by the application.
 * </class>
 */
WXJS_INIT_CLASS(SizeEvent, "SizeEvent", 0)

/***
 * <properties>
 *	<property name="size" type="@wxSize" readonly="Y">
 * 	 Returns the size of the window generating this event.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(SizeEvent)
	WXJS_READONLY_PROPERTY(P_SIZE, "size")
WXJS_END_PROPERTY_MAP()

bool SizeEvent::GetProperty(PrivSizeEvent *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxSizeEvent *event = (wxSizeEvent*) p->GetEvent();

	if ( id == P_SIZE )
	{
		vp.set( Size::CreateObject(cx, new wxSize(event->GetSize())) );
	}
	return true;
}

	
WXJS_BEGIN_GET_SET_STR_PROP(PrivSizeEvent, SizeEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
