/*
 * wxJavaScript - close.cpp
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
 * $Id: close.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// close.cpp
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
#include "js/gui/event/close.h"
#include "js/gui/event/event.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/close</file>
 * <module>gui</module>
 * <class name="wxCloseEvent" prototype="@wxEvent">
 *	This object is passed to a function that is set to an onClose property of a
 *	@wxFrame or @wxDialog. The following example vetoes the close event
 *  because the text control was changed.
 *  <pre><code class="whjs">
 *	frame.onclose = close;
 *
 *	function close(closeEvent)
 *	{
 *	  if ( closeEvent.canVeto )
 *	  {
 *		if ( textCtrl.modified )
 *		{
 *		  wxMessageBox("Can't close because you didn't save the contents");
 *		  closeEvent.veto = true;
 *		}
 *	  }
 *	}
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(CloseEvent, "CloseEvent", 0)

/***
 * <properties>
 *	<property name="canVeto" type="Boolean" readonly="Y">
 *	 Returns true when the close event can be vetoed.
 *  </property>
 *	<property name="loggingOff" type="Boolean" readonly="Y">
 *	 Returns true when the user is logging off.
 *  </property>
 *	<property name="veto" type="Boolean"> 
 *	 Set this to true when you don't want to close the window.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CloseEvent)
  WXJS_READONLY_PROPERTY(P_CAN_VETO, "canVeto")
  WXJS_READONLY_PROPERTY(P_LOGGING_OFF, "loggingOff")
  WXJS_PROPERTY(P_VETO, "veto")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(PrivCloseEvent, CloseEvent)
    wxCloseEvent *event = p->GetEvent();
	switch (id) 
	{
	case P_CAN_VETO:
		ToJSVal(cx, vp, event->CanVeto());
		break;
	case P_LOGGING_OFF:
		ToJSVal(cx, vp, event->GetLoggingOff());
		break;
	case P_VETO:
		ToJSVal(cx, vp, event->GetVeto());
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(PrivCloseEvent, CloseEvent)
    wxCloseEvent *event = p->GetEvent();
	if (    id == P_VETO 
		 && event->CanVeto() )
	{
		bool veto;
		if ( FromJS(cx, vp, veto) )
		{
			event->Veto(veto);
		}
	}
	return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivCloseEvent, CloseEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);	
	return true;
ZZZJS_END_GET_SET_STR_PROP