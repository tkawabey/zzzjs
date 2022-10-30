/*
 * wxJavaScript - treeevt.cpp
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
 * $Id: treeevt.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// treeevt.cpp

/**
 * @if JS
 *	@page wxTreeEvent wxTreeEvent
 *	@since version 0.6
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
#include "js/gui/event/treeevt.h"
#include "js/gui/event/key.h"
#include "js/gui/event/notify.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/control/treeid.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/treeevt</file>
 * <module>gui</module>
 * <class name="wxTreeEvent" prototype="@wxNotifyEvent">
 *  This object is passed to a function that is set to a @wxTreeCtrl event property.
 * </class>
 */
WXJS_INIT_CLASS(TreeEvent, "TreeEvent", 0)

/***
 * <properties>
 *  <property name="isEditCancelled" type="Boolean" readonly="Y">
 *   Returns true when the edit is cancelled.
 *  </property>
 *  <property name="item" type="@wxTreeItemId" readonly="Y">
 *   The item.
 *  </property>
 *  <property name="keyCode" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Keycode when the event is a keypress event. See @wxKeyCode.
 *  </property>
 *  <property name="keyEvent" type="@wxKeyEvent" readonly="Y">
 *   A key event. 
 *  </property>
 *  <property name="label" type=WXJS_TYPE_STRING readonly="Y">
 *   The label.
 *  </property>
 *  <property name="oldItem" type="@wxTreeItemId" readonly="Y">
 *   Get the previously selected item.
 *  </property>
 *  <property name="point" type="@wxPoint" readonly="Y">
 *   The position of the mouse pointer when the event is a drag event.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(TreeEvent)
    WXJS_READONLY_PROPERTY(P_ITEM, "item")
    WXJS_READONLY_PROPERTY(P_OLD_ITEM, "oldItem")
    WXJS_READONLY_PROPERTY(P_POINT, "point")
    WXJS_READONLY_PROPERTY(P_KEY_CODE, "keyCode")
    WXJS_READONLY_PROPERTY(P_KEY_EVENT, "keyEvent")
    WXJS_READONLY_PROPERTY(P_LABEL, "label")
    WXJS_READONLY_PROPERTY(P_IS_CANCELLED, "isEditCancelled")
WXJS_END_PROPERTY_MAP()

bool TreeEvent::GetProperty(PrivTreeEvent *p, 
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
    wxTreeEvent *event = p->GetEvent();
	switch (id) 
	{
    case P_KEY_CODE:
        ToJSVal(cx, vp, event->GetKeyCode());
        break;
    case P_KEY_EVENT:
        {
            wxKeyEvent evt(event->GetKeyEvent());
            PrivKeyEvent *jsEvent = new PrivKeyEvent(evt);
            jsEvent->SetScoop(false);
            vp.set( KeyEvent::CreateObject(cx, jsEvent) );
            break;
        }
    case P_POINT:
        vp.set( zzzJs::ext::CreatePoint(cx, event->GetPoint()) );
        break;
    case P_LABEL:
        ToJSVal(cx, vp, event->GetLabel());
        break;
    case P_IS_CANCELLED:
        ToJSVal(cx, vp, event->IsEditCancelled());
        break;
    case P_ITEM:
        vp.set( TreeItemId::CreateObject(cx, new wxTreeItemId(event->GetItem())) );
        break;
    case P_OLD_ITEM:
        vp.set( TreeItemId::CreateObject(cx, new wxTreeItemId(event->GetOldItem())) );
        break;
	}
	return true;
}

	
WXJS_BEGIN_GET_SET_STR_PROP(PrivTreeEvent, TreeEvent)
	NotifyEvent::SetStringProperty((PrivNotifyEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP