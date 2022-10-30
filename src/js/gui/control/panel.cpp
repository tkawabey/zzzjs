/*
 * wxJavaScript - panel.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
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
 * $Id: panel.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// panel.cpp
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
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"


#include "js/gui/event/jsevent.h"

#include "js/gui/misc/size.h"

#include "js/gui/control/button.h"
#include "js/gui/control/panel.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/panel</file>
 * <module>gui</module>
 * <class name="wxPanel" prototype="@wxWindow">
 *  A panel is a window on which controls are placed. It is usually placed within a frame. 
 *  Its main purpose is to be similar in appearance and functionality to a dialog,
 *  but with the flexibility of having any window as a parent.
 *  See @wxDialog and @wxFrame
 * </class>
 */
WXJS_INIT_CLASS(Panel, "Panel", 2)

void Panel::InitClass(JSContext* WXUNUSED(cx),
                      JSObject* WXUNUSED(obj), 
                      JSObject* WXUNUSED(proto))
{
  PanelEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="defaultItem" type="@wxButton">
 *   Get/Set the default button.
 *  </property>
 * </properties> 
 */
WXJS_BEGIN_PROPERTY_MAP(Panel)
	WXJS_PROPERTY(P_DEFAULT_ITEM, "defaultItem")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxPanel, Panel)
  if ( id == P_DEFAULT_ITEM )
  {
    wxWindow *win = NULL;
   
    #if wxCHECK_VERSION(2,7,0)
      wxTopLevelWindow *tlw = wxDynamicCast(wxGetTopLevelParent(p), 
                                            wxTopLevelWindow);
      if ( tlw )
          win = tlw->GetDefaultItem();
    #else       
      win = p->GetDefaultItem();
    #endif

    if ( win )
    {
      JavaScriptClientData *data 
        = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
      vp.set( data->GetObject() == NULL ? JSVAL_VOID 
                                      : OBJECT_TO_JSVAL(data->GetObject())
									  ); 
    }
  }
  return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxPanel, Panel)
  if ( id == P_DEFAULT_ITEM )
  {
    wxWindow *win = Window::GetPrivate(cx, vp);
    if ( win != NULL )
    {
      #if wxCHECK_VERSION(2,7,0)
        wxTopLevelWindow *tlw = wxDynamicCast(wxGetTopLevelParent(p), 
                                              wxTopLevelWindow);
        if ( tlw )
          tlw->SetDefaultItem(win);
      #else
        p->SetDefaultItem(win);
      #endif
    } 
  }
  return true;
WXJS_END_SET_PROP


WXJS_BEGIN_ADD_PROP(wxPanel, Panel)
  if ( WindowEventHandler::ConnectEvent(p, prop, true) )
      return true;
    
  PanelEventHandler::ConnectEvent(p, prop, true);

  return true;
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxPanel, Panel)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  PanelEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP
	

WXJS_BEGIN_GET_SET_STR_PROP(wxPanel, Panel)
	Window::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxPanel.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the Panel control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the Panel control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The wxPanel style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxPanel object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxPanel, Panel)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxPanel *p = new wxPanel();



    SetPrivate(cx, obj, p);

    if ( argc > 0 )
    {
        jsval rval;
        if ( ! _innerCreate(cx, obj, argc, vp, &rval) )
        {
          return NULL;
        }
    }

	return p;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxPanel, Panel)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Panel)
  WXJS_METHOD("create", create, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxPanel.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the Panel control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the Panel control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The wxPanel style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxPanel object.
 *  </desc>
 * </method>
 */
JSBool Panel::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool Panel::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxPanel *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	if ( argc > 5 )
	argc = 5;
	
	int argIndex = 0;
	int style = wxTAB_TRAVERSAL;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	

	ZZZJS_CHECK_ARG_COUNT(2, 5);
	
	argIndex = argc -1;
	switch(argc)
	{
	case 5:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 3:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	default:
		wxWindow *parent = NULL;
		int id;


		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		argIndex++;
		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;


		JavaScriptClientData *clntParent =
		dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), style) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

    return JS_TRUE;
}

/***
 * <events>
 *  <event name="onSysColourChanged">
 *   To process a system colour changed event, use this property to set
 *   an event handler function. The function takes a @wxSysColourChangedEvent argument.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxPanel)
const wxString WXJS_SYS_COLOUR_CHANGED_EVENT = wxT("onSysColourChanged");

void PanelEventHandler::OnSysColourChanged(wxSysColourChangedEvent &event)
{
  PrivSysColourChangedEvent::Fire<SysColourChangedEvent>(event, WXJS_SYS_COLOUR_CHANGED_EVENT);
}

void PanelEventHandler::ConnectSysColourChanged(wxPanel *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SYS_COLOUR_CHANGED,
               wxSysColourChangedEventHandler(PanelEventHandler::OnSysColourChanged));
  }
  else
  {
    p->Disconnect(wxEVT_SYS_COLOUR_CHANGED, 
                  wxSysColourChangedEventHandler(PanelEventHandler::OnSysColourChanged));
  }
}

void PanelEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_SYS_COLOUR_CHANGED_EVENT, PanelEventHandler::ConnectSysColourChanged);
}
