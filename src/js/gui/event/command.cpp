/*
 * wxJavaScript - command.cpp
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
 * $Id: command.cpp 744 2007-06-11 19:57:09Z fbraem $
 */
// command.cpp
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
#include "js/gui/event/command.h"
#include "js/gui/event/event.h"




using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/command</file>
 * <module>gui</module>
 * <class name="wxCommandEvent" prototype="@wxEvent">
 *	This event class contains information about command events, 
 *	which originate from a variety of simple controls.
 * </class>
 */
WXJS_INIT_CLASS(CommandEvent, "CommandEvent", 0)

/***
 * <properties>
 *  <property name="integer" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns the integer identifier corresponding to a listbox, choice or 
 *   radiobox selection (only if the event was a selection, not a deselection)
 *   , or a boolean value representing the value of a checkbox. 
 *  </property>
 *	<property name="checked" type="Boolean" readonly="Y">
 *	 This can be used for menus or checkboxes to check if they are checked or not
 *  </property>
 *	<property name="selection" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 This can be used to know which item is selected in a @wxListBox or @wxChoice control
 *  </property>
 *	<property name="string" type=WXJS_TYPE_STRING readonly="Y">
 *	 This can be used to know the string of the item selected in a 
 *	 @wxListBox or @wxChoice control.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CommandEvent)
	WXJS_READONLY_PROPERTY(P_CHECKED, "checked")
	WXJS_READONLY_PROPERTY(P_SELECTION, "selection")
	WXJS_READONLY_PROPERTY(P_STRING, "string")
	WXJS_READONLY_PROPERTY(P_INTEGER, "integer")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(PrivCommandEvent, CommandEvent)
    wxCommandEvent *event = p->GetEvent();
	switch(id)
	{
	case P_CHECKED:
		ToJSVal(cx, vp, event->IsChecked());
		break;
	case P_SELECTION:
		ToJSVal(cx, vp, event->GetSelection());
		break;
	case P_STRING:
		ToJSVal(cx, vp, event->GetString());
		break;
    case P_INTEGER:
      ToJSVal(cx, vp, event->GetInt());
      break;
	}
	return true;
WXJS_END_GET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivCommandEvent, CommandEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP