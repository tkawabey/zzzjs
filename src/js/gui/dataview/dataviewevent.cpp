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
#include "js/gui/event/event.h"
#include "js/gui/event/notify.h"
#include "js/ext/point.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewevent.h"
#include "js/gui/dataview/dataviewcolmn.h"
#include "js/gui/dataview/dataviewmodel.h"
#include "js/gui/dataview/dataviewitem.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;

/***
 * <file>event/command</file>
 * <module>gui</module>
 * <class name="wxCommandEvent" prototype="@wxEvent">
 *	This event class contains information about command events, 
 *	which originate from a variety of simple controls.
 * </class>
 */
WXJS_INIT_CLASS(DataViewEvent, "DataViewEvent", 0)

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
WXJS_BEGIN_PROPERTY_MAP(DataViewEvent)
	WXJS_PROPERTY(P_Column, "column")
	WXJS_PROPERTY(P_DataViewColumn, "dataViewColumn")
	WXJS_PROPERTY(P_Model, "model")
	WXJS_PROPERTY(p_Position, "position")
	WXJS_PROPERTY(p_Value, "value")
	WXJS_PROPERTY(P_DataFormat, "dataFormat")
	WXJS_READONLY_PROPERTY(P_DataSize, "dataSize")
	WXJS_READONLY_PROPERTY(P_DropEffect, "dropEffect")
	WXJS_READONLY_PROPERTY(P_CacheFrom, "cacheFrom")
	WXJS_READONLY_PROPERTY(P_CacheTo, "cacheTo")
	WXJS_PROPERTY(P_ITEM, "item")
	WXJS_PROPERTY(P_DragFlags, "dragFlags")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(PrivDataViewEvent, DataViewEvent)
    wxDataViewEvent *event = p->GetEvent();
	switch(id)
	{
	case P_Column:
		ToJSVal(cx, vp, event->GetColumn());
		break;
	case P_DataViewColumn:
		{
			wxDataViewColumn *pClmn = event->GetDataViewColumn();
			if( pClmn != NULL ) {
				vp.set(
					DataViewColumn::CreateObject(cx, pClmn)
				);
			}
		}
		break;
	case P_Model:
		{
			wxDataViewModel *pMdl = event->GetModel ();
			if( pMdl != NULL ) {
				vp.set(
					DataViewModel::CreateObject(cx, pMdl)
				);
			}
		}
		break;
	case p_Position:
		{
			wxPoint pt = event->GetPosition();
			vp.set(
				zzzJs::ext::Point::CreateObject(cx, new wxPoint(pt) )
			);
		}
		break;
	case p_Value:
		{
			ToJSVal(cx, vp, event->GetValue());
		}
		break;
	case P_DataFormat:
		{
			ToJSVal(cx, vp, (int)event->GetDataFormat());
		}
		break;
	case P_DataSize:
		{
			ToJSVal(cx, vp, (int)event->GetDataSize());
		}
		break;
	case P_DropEffect:
		{
			ToJSVal(cx, vp, (int)event->GetDropEffect());
		}
		break;
	case P_CacheFrom:
		{
			ToJSVal(cx, vp, (int)event->GetCacheFrom());
		}
		break;
	case P_CacheTo:
		{
			ToJSVal(cx, vp, (int)event->GetCacheTo());
		}
		break;
	case P_ITEM:
		{
			wxDataViewItem item = event->GetItem();
			vp.set(
				DataViewItem::CreateObject(cx, new wxDataViewItem(item))
			);
		}
		break;
	case P_DragFlags:
		ToJSVal(cx, vp, event->GetDragFlags());
		break;
	}
	return true;
WXJS_END_GET_PROP
	
	
WXJS_BEGIN_SET_PROP(PrivDataViewEvent, DataViewEvent)
    wxDataViewEvent *event = p->GetEvent();
	switch (id) 
	{
	case P_Column:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				event->SetColumn( val );
			}
		}
		break;
	case P_DataViewColumn:
		{
			wxDataViewColumn *pClmn = DataViewColumn::GetPrivate(cx, vp);
			if( pClmn != NULL ) {
				event->SetDataViewColumn(pClmn);
			}
		}
		break;
	case P_Model:
		{
			wxDataViewModel *pMdl = DataViewModel::GetPrivate(cx, vp);
			if( pMdl != NULL ) {
				event->SetModel(pMdl);
			}
		}
		break;
	case p_Position:
		{
			zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
			if( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, vp) == true ) {
				event->SetPosition(apPoint->x, apPoint->y);
			}
		}
		break;
	case p_Value:
		{
			wxVariant val;
			if( FromJS(cx, vp, val) == false ) {
				event->SetValue( val );
			}
		}
		break;
	case P_DataFormat:
		{
			int val;
			if( FromJS(cx, vp, val) == false ) {
				event->SetDataFormat( (wxDataFormat)val );
			}
		}
		break;
	case P_DropEffect:
		{
			int val;
			if( FromJS(cx, vp, val) == false ) {
				event->SetDropEffect( (wxDragResult)val );
			}
		}
		break;
	case P_DataSize:
		{
			int val;
			if( FromJS(cx, vp, val) == false ) {
				event->SetDataSize ( val );
			}
		}
		break;
	case P_ITEM:
		{
			wxDataViewItem *pItem = DataViewItem::GetPrivate(cx, vp);
			if( pItem != NULL ) {
				event->SetItem (*pItem);
			}
		}
		break;
	case P_DragFlags:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				event->SetDragFlags ( val );
			}
		}
		break;
	}
	return true;
WXJS_END_SET_PROP


WXJS_BEGIN_GET_SET_STR_PROP(PrivDataViewEvent, DataViewEvent)
	NotifyEvent::SetStringProperty((PrivNotifyEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

	

WXJS_BEGIN_METHOD_MAP(DataViewEvent)
  WXJS_METHOD("setEditCanceled", setEditCanceled, 1)
  WXJS_METHOD("setPosition", setPosition, 2)
  WXJS_METHOD("setCache", setCache, 2)
WXJS_END_METHOD_MAP()

JSBool DataViewEvent::setEditCanceled(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    PrivDataViewEvent *p = GetPrivate(cx, obj);
	
	if( p == NULL ) {
		return JS_FALSE;
	}
	bool editCancelled = false;


	if ( ! FromJS(cx, argv[0], editCancelled) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}
//	p->GetEvent()->SetEditCanceled( editCancelled );
	p->GetEvent()->SetEditCancelled( ); // From 3.1.1


	return JS_TRUE;
}

JSBool DataViewEvent::setPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    PrivDataViewEvent *p = GetPrivate(cx, obj);
	
	if( p == NULL ) {
		return JS_FALSE;
	}
	int  x = 0, y = 0;


	if ( ! FromJS(cx, argv[0], x) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	if ( ! FromJS(cx, argv[1], y) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	p->GetEvent()->SetPosition(x, y);


	return JS_TRUE;
}

JSBool DataViewEvent::setCache(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    PrivDataViewEvent *p = GetPrivate(cx, obj);
	
	if( p == NULL ) {
		return JS_FALSE;
	}
	int  from = 0, to = 0;


	if ( ! FromJS(cx, argv[0], from) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	if ( ! FromJS(cx, argv[1], to) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	p->GetEvent()->SetCache(from, to);


	return JS_TRUE;
}