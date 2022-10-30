/*
 * wxJavaScript - frame.cpp
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
 * $Id: frame.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"


#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"
#include "js/gui/event/close.h"
#include "js/gui/event/iconize.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/constant.h"
#include "js/gui/errors.h"

#include "js/gui/control/menubar.h"
#include "js/gui/control/menu.h"
#include "js/gui/control/frame.h"
#include "js/gui/control/window.h"
#include "js/gui/control/toplevel.h"
#include "js/gui/control/statbar.h"
#include "js/gui/control/toolbar.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/*
MyFrame::~MyFrame()
{


}
*/


wxToolBar* Frame::OnCreateToolBar(long style, 
                                  wxWindowID id,
                                  const wxString& name)
{
	ToolBar *tbar = new ToolBar();
	tbar->Create(this, id, wxDefaultPosition, wxDefaultSize, style, name);
	return tbar;
}

/***
 * <file>control/frame</file>
 * <module>gui</module>
 * <class name="wxFrame" prototype="@wxTopLevelWindow">
 *	A frame is a window whose size and position can (usually) be changed by 
 *  the user. It usually has thick borders and a title bar, and can optionally 
 *  contain a menu bar, toolbar and status bar. A frame can contain any window 
 *  that is not a frame or dialog.
 * </class>
 */
WXJS_INIT_CLASS(Frame, "Frame", 3)
void Frame::InitClass(JSContext* WXUNUSED(cx),
                      JSObject* WXUNUSED(obj), 
                      JSObject* WXUNUSED(proto))
{
	FrameEventHandler::InitConnectEventMap();
}

bool Frame::Resolve(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id)
{

	jsval idVal;
	if( JS_IdToValue(cx, id, &idVal) == JS_FALSE ) {
		return JS_FALSE;
	}
	if( idVal.isInt32() == true ) 
	{
		return true;
	}
	else
	{

	}
	return true;
}
/***
 * <properties>
 *  <property name="menuBar" type="@wxMenuBar">
 *	 Set/Get the menubar
 *  </property>
 *	<property name="statusBar" type="@wxStatusBar">
 *	 Set/Get the statusbar
 *  </property>
 *	<property name="statusBarFields" type=WXJS_TYPE_NUMBER>
 *	 Set/Get the number of statusbar fields. A statusbar 
 *   is created when there isn't a statusbar created yet.
 *  </property>
 *	<property name="statusBarPane" type=WXJS_TYPE_NUMBER>
 *	 Set/Get the pane used to display menu and toolbar help. -1 
 *   disables help display.
 *  </property>
 *	<property name="toolBar" type="@wxToolBar">
 *	 Set/Get the toolbar
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Frame)
  WXJS_PROPERTY(P_STATUSBAR, "statusBar")
  WXJS_PROPERTY(P_TOOLBAR, "toolBar")
  WXJS_PROPERTY(P_MENUBAR, "menuBar")
  WXJS_PROPERTY(P_STATUSBAR_FIELDS, "statusBarFields")
  WXJS_PROPERTY(P_STATUSBAR_PANE, "statusBarPane")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxFrame, Frame)
{
  switch(id)  
  {
  case P_MENUBAR:
    {
      wxMenuBar *bar = p->GetMenuBar();
      if ( bar != NULL )
      {
        JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData *>(bar->GetClientObject());
        vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
      }
      else
      {
        vp.set( JSVAL_VOID );
      }
      break;
    }
  case P_STATUSBAR:
    {
      wxStatusBar *bar = p->GetStatusBar();
      if ( bar != NULL )
      {
        JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData *>(bar->GetClientObject());
        vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
      }
      else
      {
        vp.set( JSVAL_VOID );
      }
      break;
    }
  case P_TOOLBAR:
    {
      wxToolBar *bar = p->GetToolBar();
      if ( bar != NULL )
      {
        JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData *>(bar->GetClientObject());
        vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
      }
      else
      {
        vp.set( JSVAL_VOID );
      }
      break;
    }
  case P_STATUSBAR_FIELDS:
    {
      wxStatusBar *statusBar = p->GetStatusBar();
      if ( statusBar == NULL )
      {
        ToJSVal(cx, vp, 0);
      }
      else
      {
        ToJSVal(cx, vp, statusBar->GetFieldsCount());
      }
      break;
    }
  case P_STATUSBAR_PANE:
	ToJSVal(cx, vp, p->GetStatusBarPane());
	break;
  }
  return true;
}
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxFrame, Frame)
{
  switch(id) 
  {
  case P_MENUBAR:
    {
	if ( vp.isObject() )
      {
        JSObject *jsMenuBar = JSVAL_TO_OBJECT(vp);
        wxMenuBar *menuBar = MenuBar::GetPrivate(cx, jsMenuBar);
        if ( menuBar != NULL )
        {
          p->SetMenuBar(menuBar);
          menuBar->SetClientObject(new JavaScriptClientData(cx, jsMenuBar, true, false));
          break;
        }
      }
    }
	case P_STATUSBAR:
    {
      wxStatusBar *bar = StatusBar::GetPrivate(cx, vp);
      if ( bar != NULL )
        p->SetStatusBar(bar);
      break;
    }
	case P_TOOLBAR:
    {
      wxToolBar *bar = ToolBar::GetPrivate(cx, vp);
      if ( bar != NULL )
        p->SetToolBar(bar);
      break;
    }
	case P_STATUSBAR_FIELDS:
	{
	  wxStatusBar *statusBar = p->GetStatusBar();
	  int fields;
	  if (    FromJS(cx, vp, fields)
		   && fields > 0 )
	  {
	    if ( statusBar == (wxStatusBar*) NULL )
	    {
          p->CreateStatusBar(fields);
	    }
	    else
	    {
          statusBar->SetFieldsCount(fields);
	    }
	  }
	  break;
	}
	case P_STATUSBAR_PANE:
	{
      int pane;
      if ( FromJS(cx, vp, pane) )
          p->SetStatusBarPane(pane);
      break;
	}
  }
  return true;
}
WXJS_END_SET_PROP
	
WXJS_BEGIN_ADD_PROP(wxFrame, Frame)
{
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    FrameEventHandler::ConnectEvent(p, prop, true);

    return true;
}
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxFrame, Frame)
{
    if ( WindowEventHandler::ConnectEvent(p, prop, false) )
        return true;
    
    FrameEventHandler::ConnectEvent(p, prop, false);

    return true;
}
WXJS_END_DEL_PROP

//bool Frame::SetStringProperty(wxFrame* p,
//                                    JSContext* cx, 
//                                    JSObject* obj,
//                                    const wxString& propertyName,
//                                    JS::MutableHandle<JS::Value>& vp)
//{

WXJS_BEGIN_GET_SET_STR_PROP(wxFrame, Frame)
{
	TopLevelWindow::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
}
ZZZJS_END_GET_SET_STR_PROP


/***
 * <constants>
 *  <type name="Style">
 *   <constant name="DEFAULT_FRAME_STYLE" />
 *   <constant name="ICONIZE" />
 *   <constant name="CAPTION" />
 *   <constant name="MINIMIZE" />
 *   <constant name="MINIMIZE_BOX" />
 *   <constant name="MAXIMIZE" />
 *   <constant name="MAXIMIZE_BOX" />
 *   <constant name="STAY_ON_TOP" />
 *   <constant name="SYSTEM_MENU" />
 *   <constant name="SIMPLE_BORDER" />
 *   <constant name="RESIZE_BORDER" />
 *   <constant name="FRAME_FLOAT_ON_PARENT" />
 *   <constant name="FRAME_TOOL_WINDOW" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Frame)
  // Style constants
  WXJS_CONSTANT(wx, DEFAULT_FRAME_STYLE)
  WXJS_CONSTANT(wx, ICONIZE)
  WXJS_CONSTANT(wx, CAPTION)
  WXJS_CONSTANT(wx, MINIMIZE)
  WXJS_CONSTANT(wx, MINIMIZE_BOX)
  WXJS_CONSTANT(wx, MAXIMIZE)
  WXJS_CONSTANT(wx, MAXIMIZE_BOX)
  WXJS_CONSTANT(wx, STAY_ON_TOP)
  WXJS_CONSTANT(wx, SYSTEM_MENU)
  WXJS_CONSTANT(wx, SIMPLE_BORDER)
  WXJS_CONSTANT(wx, RESIZE_BORDER)
  WXJS_CONSTANT(wx, FRAME_FLOAT_ON_PARENT)
  WXJS_CONSTANT(wx, FRAME_TOOL_WINDOW)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of the wxFrame. Pass null, when you don't have a parent.
 *   </arg>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The windows identifier. -1 can be used when you don't need a unique id.
 *   </arg>
 *	 <arg name="Title" type=WXJS_TYPE_STRING>
 *	  The caption of the frame.
 *   </arg>
 *	 <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *	  The position of the frame.
 *   </arg>
 *	 <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *	  The size of the frame.
 *   </arg>
 *	 <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  The style of the frame.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Creates a new wxFrame object
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxFrame, Frame)
{
	Frame *p = new Frame();


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
}
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxFrame, Frame)
{
	if( p != NULL ) {
		p = NULL;
	}
}
WXJS_END_DESTRUCTOR

WXJS_BEGIN_METHOD_MAP(Frame)
  WXJS_METHOD("create", create, 3)
  WXJS_METHOD("processCommand", processCommand, 1)
  WXJS_METHOD("createStatusBar", createStatusBar, 0)
  WXJS_METHOD("setStatusText", setStatusText, 1)
  WXJS_METHOD("setStatusWidths", setStatusWidths, 1)
  WXJS_METHOD("createToolBar", createToolBar, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *	<function returns="Boolean">
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of the wxFrame. Pass null, when you don't have a parent.
 *   </arg>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The windows identifier. -1 can be used when you don't need a unique id.
 *   </arg>
 *	 <arg name="Title" type=WXJS_TYPE_STRING>
 *	  The caption of the frame.
 *   </arg>
 *	 <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *	  The position of the frame.
 *   </arg>
 *	 <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *	  The size of the frame.
 *   </arg>
 *	 <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  The style of the frame.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Creates a new wxFrame object
 *  </desc>
 * </method>
 */
JSBool Frame::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}

JSBool Frame::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	

	wxFrame *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	int style = wxDEFAULT_FRAME_STYLE;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);



	ZZZJS_CHECK_ARG_COUNT(3, 6);
	
	argIndex = argc -1;
	switch(argc)
	{
	case 6:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 5:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	default:
		wxString title;
		wxWindow *parent = NULL;
		int id;

		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(title, WXJS_TYPE_STRING);
		argIndex++;
		if ( parent != NULL )
		{
			JavaScriptClientData *clntParent =
				dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
			if ( clntParent == NULL )
			{
				JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
				return JS_FALSE;
			}
			JS_SetParent(cx, obj, clntParent->GetObject());
		}
	  
		if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), style) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
			p->Connect(wxID_ANY, wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, 
				wxCommandEventHandler(FrameEventHandler::OnMenu));
		}
	}

	return JS_TRUE;
}

/***
 * <method name="processCommand">
 *  <function>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    Identifier of a menu.
 *   </arg>
 *  </function>
 *  <desc>
 *   Simulates a menu command.
 *  </desc>
 * </method>
 */
JSBool Frame::processCommand(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFrame *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	if ( p->GetHandle() == NULL )
	{
		JS_ReportError(cx, "%s is not yet created", GetClass()->name);
		return JS_FALSE;
	}

	int id;
	if ( ! FromJS(cx, argv[0], id) )
		return JS_FALSE;

	p->ProcessCommand(id);

	return JS_TRUE;
}

/***
 * <method name="createStatusBar">
 *	<function returns="@wxStatusBar">
 *   <arg name="Field" type=WXJS_TYPE_NUMBER default="1">
 *	  The number of fields. Default is 1.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The style of the statusbar.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER default="-1">
 *    A unique id for the statusbar.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a status bar at the bottom of the frame.
 *   <br /><b>Remark:</b>
 *   The width of the status bar is the whole width of the frame 
 *   (adjusted automatically when resizing), and the height and text size 
 *   are chosen by the host windowing system
 *  </desc>
 * </method>
 */
#include "js/common/jsutil.h"
JSBool Frame::createStatusBar(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


//
//
//{
//	JSBool foundp = JS_FALSE;
//	JSBool b =  JS_HasProperty(cx, obj, "visible", &foundp);
//	jsval v = JSVAL_TRUE;
//	b = JS_GetProperty(cx, obj, "visible", &v);
//	JSBool foundp2 = foundp;
//	JS_SetPropertyById(cx, obj, 97, &v);
//
//	zzzJs::HasPrototype(cx,obj, "wxWindow");
//	
//}


    wxFrame *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
    if ( p->GetHandle() == NULL )
    {
      JS_ReportError(cx, "%s is not yet created", GetClass()->name);
      return JS_FALSE;
    }

    int fields = 1;
    long style = 0;
    int id = -1;
    
    switch(argc)
    {
    case 3:
        if ( ! FromJS(cx, argv[2], id) )
            return JS_FALSE;
        // Fall through
    case 2:
        if ( ! FromJS(cx, argv[1], style) )
            return JS_FALSE;
        // Fall through
    case 1:
        if ( ! FromJS(cx, argv[0], fields) )
            return JS_FALSE;
        // Fall through
    }
    
    wxStatusBar *bar = p->CreateStatusBar(fields, style, id);
    if ( bar )
    {
      *vp = StatusBar::CreateObject(cx, bar, obj);
      JSObject *obj = JSVAL_TO_OBJECT(*vp);
      bar->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
    }
    else
    {
      *vp = JSVAL_VOID;
    }

	return JS_TRUE;
}

/***
 * <method name="createToolBar">
 *  <function returns="@wxToolBar">
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxBorder.NONE | wxToolBar.HORIZONTAL">
 *    The toolbar style
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER default="-1">
 *    A unique id for the toolbar
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a toolbar at the top or left of the frame.
 *  </desc>
 * </method>
 */
JSBool Frame::createToolBar(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFrame *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    if ( p->GetHandle() == NULL )
    {
      JS_ReportError(cx, "%s is not yet created", GetClass()->name);
      return JS_FALSE;
    }

    long style = wxNO_BORDER | wxTB_HORIZONTAL;
    int id = -1;
    
    switch(argc)
    {
    case 2:
        if ( ! FromJS(cx, argv[1], id) )
            return JS_FALSE;
        // Fall through
    case 1:
        if ( ! FromJS(cx, argv[0], style) )
            return JS_FALSE;
        // Fall through
    }
    
    wxToolBar *bar = p->CreateToolBar(style, id);
    if ( bar == NULL )
    {
      *vp = JSVAL_VOID;
    }
    else
    {
      *vp = ToolBar::CreateObject(cx, bar, obj);
      JSObject *obj = JSVAL_TO_OBJECT(*vp);
      bar->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
      bar->Connect(wxID_ANY, wxID_ANY, wxEVT_COMMAND_TOOL_CLICKED, 
                   wxCommandEventHandler(ToolEventHandler::OnTool));
    }
	return JS_TRUE;
}

/***
 * <method name="setStatusText">
 *  <function>
 *   <arg name="Text" type=WXJS_TYPE_STRING>
 *    The text to set in the status field
 *   </arg>
 *   <arg name="Field" type=WXJS_TYPE_NUMBER default="0">
 *	  The number of the field (zero indexed)
 *   </arg>
 *  </function>
 *  <desc>
 *	 Sets the text of the given status field. When no field is specified, 
 *   the first one is used.
 *  </desc>
 * </method>
 */
JSBool Frame::setStatusText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFrame *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    if ( p->GetHandle() == NULL )
    {
      JS_ReportError(cx, "%s is not yet created", GetClass()->name);
      return JS_FALSE;
    }

	wxStatusBar *statusBar = p->GetStatusBar();
	if ( statusBar != (wxStatusBar*) NULL )
	{
        wxString text;
        FromJS(cx, argv[0], text);

        int field = 0;
        if (      argc == 2
             && ! FromJS(cx, argv[1], field) )
             return JS_FALSE;

		if (	field >= 0
			 && field  < statusBar->GetFieldsCount() )
		{
			p->SetStatusText(text, field);
		}
	}

	return JS_TRUE;
}

/***
 * <method name="setStatusWidths">
 *  <function>
 *   <arg name="Widths" type="Array">
 *    Contains an array of status field width in pixels. 
 *    A value of -1 indicates that the field is variable width.
 *    At least one field must be -1.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Sets the widths of the fields in the status bar.
 *   When the array contains more elements then fields, 
 *   those elements are discarded. See also @wxStatusBar#statusWidths.
 *  </desc>
 * </method>
 */
JSBool Frame::setStatusWidths(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFrame *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    if ( p->GetHandle() == NULL )
    {
      JS_ReportError(cx, "%s is not yet created", GetClass()->name);
      return JS_FALSE;
    }

	wxStatusBar *statusBar = p->GetStatusBar();
	if ( statusBar == (wxStatusBar*) NULL )
        return JS_TRUE;

	if ( argv[0].isObject() )
    {
        JSObject *obj = JSVAL_TO_OBJECT(argv[0]);
        if ( JS_IsArrayObject(cx, obj) == JS_TRUE )
        {
			uint32_t length = 0;
			JS_GetArrayLength(cx, obj, &length);
            uint32_t fields = statusBar->GetFieldsCount();
            if ( length > fields )
                length = fields;
			int *widths = new int[length];
			for(uint32_t i =0; i < length; i++)
			{
				jsval element;
				JS_GetElement(cx, obj, i, &element);
				if ( ! FromJS(cx, element, widths[i]) )
                {
                    delete[] widths;
                    return JS_FALSE;
                }
			}
            p->SetStatusWidths(length, widths);
            delete[] widths;
        }
	}
	return JS_TRUE;
}

/***
 * <events>
 *	<event name="onClose">
 *	 Called when the frame is closed. The type of the argument that your
 *   handler receives is @wxCloseEvent.
 *  </event>
 *  <event name="onIconize">
 *	 An event being sent when the frame is iconized (minimized).
 *   Currently only wxMSW and wxGTK generate such events.
 *   The type of the argument that your handler receives 
 *	 is @wxIconizeEvent. When you handle this event, 
 *   don't forget to set @wxEvent#skip to true. 
 *   Otherwise the frame will not be iconized.
 *  </event>
 *  <event name="onMaximize">
 *	 An event being sent when the frame is maximized.
 *   The type of the argument that your handler receives 
 *	 is @wxMaximizeEvent. When you handle this event, 
 *   don't forget to set @wxEvent#skip to true. 
 *   Otherwise the frame will not be maximized.
 *  </event>
 * </events>
 */

WXJS_INIT_EVENT_MAP(wxFrame)
const wxString WXJS_CLOSE_EVENT = wxT("onClose");
const wxString WXJS_ICONIZE_EVENT = wxT("onIconize");
const wxString WXJS_MAXIMIZE_EVENT = wxT("onMaximize");

void FrameEventHandler::OnMenu(wxCommandEvent &event)
{
	JavaScriptClientData *menuData = NULL;
	wxObject* pEvtObj = event.GetEventObject();
	if( pEvtObj == NULL ) {
		wxLogError(_T("ERR. FrameEventHandler::OnMenu. line:%d"), __LINE__);
			return;
	}
	if( pEvtObj->IsKindOf(CLASSINFO(wxMenu))  ) {
		wxMenu* pMenu = (wxMenu*)pEvtObj;
		
		menuData = dynamic_cast<JavaScriptClientData*>(pMenu->GetClientObject());

		wxWindow* pWindow = pMenu->GetWindow();
	}
	// if( ! pFram->IsKindOf(CLASSINFO(FrameMain))  ) {
	JavaScriptClientData *clientData 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
/*
  wxWindow *eventObject = dynamic_cast<wxWindow *>(event.GetEventObject());
  wxFrame *frame = dynamic_cast<wxFrame*>(eventObject);
  if ( frame == NULL )
  {
    // It can be a toolbar
    frame = dynamic_cast<wxFrame*>(eventObject->GetParent());
    if ( frame == NULL )
      return;
  }



  wxMenuBar *menuBar = frame->GetMenuBar();
  if ( menuBar == NULL )
    return;

  wxMenuItem *item = menuBar->FindItem(event.GetId());
  if ( item == NULL )
        return;

  wxMenu *menu = item->GetMenu();
  if ( menu == NULL )
    return;

  JavaScriptClientData *menuData 
      = dynamic_cast<JavaScriptClientData*>(menu->GetClientObject());
*/
	if( menuData == NULL ) {
		wxLogError(_T("ERR. FrameEventHandler::OnMenu. line:%d"), __LINE__);
		return ;
	}
//  JSContext *cx = clientData->GetContext();
	JSContext *cx = menuData->GetContext();
	JSAutoCompartment transaction(cx, menuData->GetObject() );
	jsval actions;
	if (    JS_GetProperty(cx, menuData->GetObject(), "actions", &actions) == JS_TRUE 
			&& actions.isObject()
			&& JS_IsArrayObject(cx, JSVAL_TO_OBJECT(actions)) == JS_TRUE )
	{
		jsval element;
		if ( JS_GetElement(cx, JSVAL_TO_OBJECT(actions), event.GetId(), &element) == JS_TRUE )
		{
			JSFunction *action = JS_ValueToFunction(cx, element);
			if ( action != NULL )
			{
				PrivCommandEvent *wxjsEvent = new PrivCommandEvent(event);
				jsval argv[] = { CommandEvent::CreateObject(cx, wxjsEvent) };

				jsval rval;
				JSBool result = JS_CallFunction(cx, clientData->GetObject(), action, 1,	argv, &rval);
				if ( result == JS_FALSE )
				{
					JS_ReportPendingException(cx); 
				}                
			}
		}
		else
		{
			event.Skip();
		}
	}
}

void FrameEventHandler::OnClose(wxCloseEvent &event)
{
	JavaScriptClientData *menuData = NULL;
	wxObject* pEvtObj = event.GetEventObject();
	if( pEvtObj == NULL ) {
		wxLogError(_T("ERR. FrameEventHandler::OnMenu. line:%d"), __LINE__);
		return;
	}
	if( pEvtObj->IsKindOf(CLASSINFO(wxFrame))  ) {
		wxFrame* pMenu = (wxFrame*)pEvtObj;
		
		menuData = dynamic_cast<JavaScriptClientData*>(pMenu->GetClientObject());



	}
  PrivCloseEvent::Fire<CloseEvent>(event, WXJS_CLOSE_EVENT);
}

void FrameEventHandler::OnIconize(wxIconizeEvent &event)
{
	PrivIconizeEvent::Fire<IconizeEvent>(event, WXJS_ICONIZE_EVENT);
}

void FrameEventHandler::OnMaximize(wxMaximizeEvent &event)
{
	PrivMaximizeEvent::Fire<MaximizeEvent>(event, WXJS_MAXIMIZE_EVENT);
}

void FrameEventHandler::ConnectClose(wxFrame *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(FrameEventHandler::OnClose));
  }
  else
  {
    p->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(FrameEventHandler::OnClose));
  }
}

void FrameEventHandler::ConnectIconize(wxFrame *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_ICONIZE, wxIconizeEventHandler(FrameEventHandler::OnIconize));
  }
  else
  {
    p->Disconnect(wxEVT_ICONIZE, wxIconizeEventHandler(FrameEventHandler::OnIconize));
  }
}

void FrameEventHandler::ConnectMaximize(wxFrame *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MAXIMIZE, wxMaximizeEventHandler(FrameEventHandler::OnMaximize));
  }
  else
  {
    p->Disconnect(wxEVT_MAXIMIZE, wxMaximizeEventHandler(FrameEventHandler::OnMaximize));
  }
}

void FrameEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_CLOSE_EVENT, ConnectClose);
  AddConnector(WXJS_ICONIZE_EVENT, ConnectIconize);
  AddConnector(WXJS_MAXIMIZE_EVENT, ConnectMaximize);
}
