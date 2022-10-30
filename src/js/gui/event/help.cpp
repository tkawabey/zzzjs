/*
 * wxJavaScript - help.cpp
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
 * $Id: help.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"
#include "js/gui/event/jsevent.h"
#include "js/gui/event/help.h"
#include "js/gui/event/event.h"



using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/help</file>
 * <module>gui</module>
 * <class name="wxHelpEvent" prototype="@wxEvent">
 *  A help event is sent when the user has requested context-sensitive help.
 *  This can either be caused by the application requesting context-sensitive
 *  help mode via @wxContextHelp, or (on MS Windows) by the system generating
 *  a WM_HELP message when the user pressed F1 or clicked on the query button in 
 *  a dialog caption.
 *  <br /><br />
 *  A help event is sent to the window that the user clicked on, and is propagated up 
 *  the window hierarchy until the event is processed or there are no more event handlers.
 *  The application should use @wxEvent#id to check the identity of the clicked-on window,
 *  and then either show some suitable help or set @wxEvent#skip to true if the identifier is
 *  unrecognised. Setting @wxEvent#skip to true is important because it allows wxWindows to 
 *  generate further events for ancestors of the clicked-on window. Otherwise it would be 
 *  impossible to show help for container windows, since processing would stop after the 
 *  first window found.
 *  <br /><br />
 *  See @wxWindow#onHelp, @wxContextHelp and @wxContextHelpButton
 * </class>
 */
WXJS_INIT_CLASS(HelpEvent, "HelpEvent", 0)

/***
 * <properties>
 *	<property name="position" type="@wxPoint">
 *	 Get/Set the left-click position of the mouse in screen-coordinates.
 *   This helps the application to position the help appropriately.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(HelpEvent)
	WXJS_PROPERTY(P_POSITION, "position")
WXJS_END_PROPERTY_MAP()

bool HelpEvent::GetProperty(PrivHelpEvent *p,  
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
    wxHelpEvent *event = p->GetEvent();

	if ( id == P_POSITION )
	{
      vp.set( zzzJs::ext::CreatePoint(cx, event->GetPosition()) );
	}
	return true;
}

bool HelpEvent::SetProperty(PrivHelpEvent *p, 
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
    wxHelpEvent *event = p->GetEvent();

	if ( id == P_POSITION )
	{
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, vp) == true )
			event->SetPosition(*(apPoint.get()));
	}
	return true;
}
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivHelpEvent, HelpEvent)
{
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
}
ZZZJS_END_GET_SET_STR_PROP
