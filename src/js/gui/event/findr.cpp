/*
 * wxJavaScript - findr.cpp
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
 * $Id: findr.cpp 714 2007-05-16 20:24:49Z fbraem $
 */
// findr.cpp
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
#include "js/common/clntdata.h"
#include "js/gui/event/jsevent.h"
#include "js/gui/event/findr.h"
#include "js/gui/event/event.h"


//#include "../../common/type.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/findr</file>
 * <module>gui</module>
 * <class name="wxFindDialogEvent" prototype="@wxEvent">
 *	This event class contains the information about 
 *  all @wxFindReplaceDialog events: @wxFindReplaceDialog#onFind
 *	@wxFindReplaceDialog#onFindNext, @wxFindReplaceDialog#onFindReplace,
 *	@wxFindReplaceDialog#onFindReplaceAll, @wxFindReplaceDialog#onFindClose.
 * </class>
 */
WXJS_INIT_CLASS(FindDialogEvent, "FindDialogEvent", 0)

/***
 * <properties>
 *	<property name="findString" type=WXJS_TYPE_STRING readonly="Y" />
 *  <property name="flags" type=WXJS_TYPE_NUMBER readonly="Y" />
 *  <property name="replaceString" type=WXJS_TYPE_STRING readonly="Y" />
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(FindDialogEvent)
	WXJS_READONLY_PROPERTY(P_FLAGS, "flags")
	WXJS_READONLY_PROPERTY(P_FINDSTRING, "findString")
	WXJS_READONLY_PROPERTY(P_REPLACESTRING, "replaceString")
	WXJS_READONLY_PROPERTY(P_DIALOG, "dialog")
WXJS_END_PROPERTY_MAP()

bool FindDialogEvent::GetProperty(PrivFindDialogEvent *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxFindDialogEvent *event = p->GetEvent();
	switch (id) 
	{
	case P_FLAGS:
		ToJSVal(cx, vp, event->GetFlags());
		break;
	case P_FINDSTRING:
		ToJSVal(cx, vp, event->GetFindString());
		break;
	case P_REPLACESTRING:
		ToJSVal(cx, vp, event->GetReplaceString());
		break;
	case P_DIALOG:
		{
		  wxWindow *win = event->GetDialog();
          if ( win != NULL )
          {
            JavaScriptClientData *data
              = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
            if ( data != NULL )
    	      vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
          }
		  break;
		}
	}
	return true;
}
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivFindDialogEvent, FindDialogEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
