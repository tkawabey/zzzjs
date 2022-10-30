/*
 * wxJavaScript - iconize.cpp
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
 * $Id: iconize.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// iconize.cpp
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
#include "js/gui/event/iconize.h"
#include "js/gui/event/event.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/iconize</file>
 * <module>gui</module>
 * <class name="wxIconizeEvent" prototype="@wxEvent">
 *  An event being sent when the frame is iconized (minimized) or restored.
 *  Currently only Windows and GTK generate such events.
 *  See @wxFrame.
 * </class>
 */
WXJS_INIT_CLASS(IconizeEvent, "IconizeEvent", 0)

/***
 * <properties>
 *	<property name="iconized" type="Boolean" readonly="Y">
 *	 Returns true when the frame is iconized, false when it's not.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(IconizeEvent)
  WXJS_READONLY_PROPERTY(P_ICONIZED, "iconized")
WXJS_END_PROPERTY_MAP()

bool IconizeEvent::GetProperty(PrivIconizeEvent *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxIconizeEvent *event = p->GetEvent();
	if ( id == P_ICONIZED )
		ToJSVal(cx, vp, event->IsIconized());
	return true;
}
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivIconizeEvent, IconizeEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
