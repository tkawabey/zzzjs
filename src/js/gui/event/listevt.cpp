/*
 * wxJavaScript - listevt.cpp
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
 * $Id: listevt.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// listevt.cpp
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
#include "js/gui/event/listevt.h"
#include "js/gui/event/notify.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/control/listitem.h"



using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/listevt</file>
 * <module>gui</module>
 * <class name="wxListEvent" prototype="@wxNotifyEvent">
 *	This object is passed to a function that is set to a @wxListCtrl event property.
 * </class>
 */
WXJS_INIT_CLASS(ListEvent, "ListEvent", 0)

/***
 * <properties>
 *	<property name="cacheFrom" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The first item which the list control advises us to cache.
 *  </property>
 *	<property name="cacheTo" type=WXJS_TYPE_NUMBER readonly="Y">
 *  The lasst item which the list control advises us to cache.
 *  </property>
 *	<property name="column" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The column index. For the column dragging events, it is the column to the left of 
 *   the divider being dragged, for the column click events it may be -1 if the user 
 *   clicked in the list control header outside any column.
 *  </property>
 *	<property name="data" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The associated data of the item.
 *  </property>
 *	<property name="image" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The image index of the item.
 *  </property>
 *	<property name="index" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The item index.
 *  </property>
 *	<property name="item" type="@wxListItem" readonly="Y">
 *   The item.
 *  </property>
 *	<property name="keyCode" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Keycode when the event is a keypress event. 
 *   See @wxKeyCode
 *  </property>
 *	<property name="label" type=WXJS_TYPE_STRING readonly="Y">
 *   The label.
 *  </property>
 *	<property name="mask" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The mask.
 *  </property>
 *	<property name="point" type="@wxPoint" readonly="Y">
 *   The position of the mouse pointer when the event is a drag event.
 *  </property>
 *	<property name="text" type=WXJS_TYPE_STRING readonly="Y">
 *   The text.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ListEvent)
    WXJS_READONLY_PROPERTY(P_CODE, "keyCode")
    WXJS_READONLY_PROPERTY(P_INDEX, "index")
    WXJS_READONLY_PROPERTY(P_COLUMN, "column")
    WXJS_READONLY_PROPERTY(P_POINT, "point")
    WXJS_READONLY_PROPERTY(P_LABEL, "label")
    WXJS_READONLY_PROPERTY(P_TEXT, "text")
    WXJS_READONLY_PROPERTY(P_IMAGE, "image")
    WXJS_READONLY_PROPERTY(P_DATA, "data")
    WXJS_READONLY_PROPERTY(P_MASK, "mask")
    WXJS_READONLY_PROPERTY(P_ITEM, "item")
    WXJS_READONLY_PROPERTY(P_CACHE_FROM, "cacheFrom")
    WXJS_READONLY_PROPERTY(P_CACHE_TO, "cacheTo")
WXJS_END_PROPERTY_MAP()

bool ListEvent::GetProperty(PrivListEvent *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxListEvent *event = p->GetEvent();
	switch (id) 
	{
    case P_CODE:
        ToJSVal(cx, vp, event->GetKeyCode());
        break;
    case P_INDEX:
        ToJSVal(cx, vp, event->GetIndex());
        break;
    case P_COLUMN:
        ToJSVal(cx, vp, event->GetColumn());
        break;
    case P_POINT:
		vp.set( zzzJs::ext::CreatePoint(cx, event->GetPoint()) );
        break;
    case P_LABEL:
        ToJSVal(cx, vp, event->GetLabel());
        break;
    case P_TEXT:
        ToJSVal(cx, vp, event->GetText());
        break;
    case P_IMAGE:
        ToJSVal(cx, vp, event->GetImage());
        break;
    case P_DATA:
        ToJSVal(cx, vp, event->GetData());
        break;
    case P_MASK:
        ToJSVal(cx, vp, event->GetMask());
        break;
    case P_ITEM:
        vp.set( ListItem::CreateObject(cx, new wxListItem(event->GetItem())) );
        break;
    case P_CACHE_FROM:
        ToJSVal(cx, vp, event->GetCacheFrom());
        break;
    case P_CACHE_TO:
        ToJSVal(cx, vp, event->GetCacheTo());
        break;
	}
	return true;
}
 
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivListEvent, ListEvent)
	NotifyEvent::SetStringProperty((PrivNotifyEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

