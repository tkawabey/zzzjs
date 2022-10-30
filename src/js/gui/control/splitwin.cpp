/*
 * wxJavaScript - splitwin.cpp
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
 * $Id: splitwin.cpp 810 2007-07-13 20:07:05Z fbraem $
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


#include "js/gui/misc/size.h"

#include "js/gui/event/jsevent.h"
#include "js/gui/event/split.h"

#include "js/gui/control/window.h"
#include "js/gui/control/splitwin.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/splitwin</file>
 * <module>gui</module>
 * <class name="wxSplitterWindow" prototype="@wxWindow">
 *  This class manages up to two subwindows. The current view can be split into two 
 *  programmatically, and unsplit either programmatically or via the wxSplitterWindow
 *  user interface.
 *  <br /><br />
 *  The following example shows a frame that contains a @wxTreeCtrl and a @wxListCtrl.
 *  The frame is splitted horizontally.
 *  <pre><code class="whjs">
 *   wxTheApp.onInit = function()
 *   {
 *     var frame = new wxFrame(null, -1, "wxSplitterWindow Example");
 *     var split = new wxSplitterWindow(frame, -1);
 *     var tree = new wxTreeCtrl(split, -1);
 *     var list = new wxListCtrl(split, -1);
 *   
 *     split.splitHorizontally(tree, list);
 *   
 *     topWindow = frame;
 *     frame.show();
 *   
 *     return true;
 *   };
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(SplitterWindow, "SplitterWindow", 2)

/***
 * <properties>
 *  <property name="minimumPaneSize" type=WXJS_TYPE_NUMBER>
 *   Get/Set the minimum pane size.
 *  </property>
 *  <property name="sashPosition" type=WXJS_TYPE_NUMBER>
 *   Get/Set the sash position in pixels. When set the panes, sash and border are redrawn.
 *   See @wxSplitterWindow#setSashPosition.
 *  </property>
 *  <property name="splitMode" type=WXJS_TYPE_NUMBER>
 *   Get/Set the split mode.
 *  </property>
 *  <property name="window1" type="@wxWindow" readonly="Y">
 *   Returns the left/top or only pane.
 *  </property>
 *  <property name="window2" type="@wxWindow" readonly="Y">
 *   Returns the right/bottom or only pane.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(SplitterWindow)
    WXJS_PROPERTY(P_MIN_PANE_SIZE, "minimumPaneSize")
    WXJS_PROPERTY(P_SASH_POS, "sashPosition")
    WXJS_PROPERTY(P_SPLIT_MODE, "splitMode")
    WXJS_READONLY_PROPERTY(P_WINDOW1, "window1")
    WXJS_READONLY_PROPERTY(P_WINDOW2, "window2")
    WXJS_READONLY_PROPERTY(P_IS_SPLIT, "isSplit")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxSplitterWindow, SplitterWindow)
    switch (id)
    {
    case P_MIN_PANE_SIZE:
        ToJSVal(cx, vp, p->GetMinimumPaneSize());
        break;
    case P_SASH_POS:
        ToJSVal(cx, vp, p->GetSashPosition());
        break;
    case P_WINDOW1:
        {
		  wxWindow *win = p->GetWindow1();
          if ( win == NULL )
          {
            vp.set( JSVAL_VOID );
          }
          else
          {
            JavaScriptClientData *data 
                = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
            vp.set( ( data == NULL ) ? JSVAL_VOID 
                                   : OBJECT_TO_JSVAL(data->GetObject()) 
								   );
          }
          break;
        }
    case P_WINDOW2:
        {
		  wxWindow *win = p->GetWindow2();
          if ( win == NULL )
          {
            vp.set( JSVAL_VOID );
          }
          else
          {
            JavaScriptClientData *data 
                = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
            vp.set(  ( data == NULL ) ? JSVAL_VOID 
                                   : OBJECT_TO_JSVAL(data->GetObject()) 
								   );
          }
          break;
        }
    case P_SPLIT_MODE:
        ToJSVal(cx, vp, (int) p->GetSplitMode());
        break;
    case P_IS_SPLIT:
        ToJSVal(cx, vp, p->IsSplit());
        break;
    }
    return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_SET_PROP(wxSplitterWindow, SplitterWindow)
    switch (id)
    {
    case P_MIN_PANE_SIZE:
        {
            int size;
            if ( FromJS(cx, vp, size) )
                p->SetMinimumPaneSize(size);
            break;
        }
    case P_SASH_POS:
        {
            int pos;
            if ( FromJS(cx, vp, pos) )
                p->SetSashPosition(pos);
            break;
        }
    }
    return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxSplitterWindow, SplitterWindow)
	Window::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


WXJS_BEGIN_ADD_PROP(wxSplitterWindow, SplitterWindow)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    SplitterEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxSplitterWindow, SplitterWindow)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  SplitterEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <constants>
 *  <type name="Styles">
 *   <constant name="3D">Draws a 3D effect border and sash.  </constant>
 *   <constant name="3DSASH">Draws a 3D effect sash.  </constant>
 *   <constant name="3DBORDER">Draws a 3D effect border.  </constant>
 *   <constant name="FULLSASH">Draws the ends of the sash (so the window can be used without a border).  </constant>
 *   <constant name="BORDER">Draws a thin black border around the window.  </constant>
 *   <constant name="NOBORDER">No border, and a black sash.  </constant>
 *   <constant name="PERMIT_UNSPLIT">Always allow to unsplit, even with the minimum pane size other than zero.  </constant>
 *   <constant name="LIVE_UPDATE">Don't draw XOR line but resize the child windows immediately.  </constant>
 *  </type>
 *  <type name="wxSplitMode">
 *   <constant name="VERTICAL" />
 *   <constant name="HORIZONTAL" />
 *  <desc>wxSplitMode is ported as a separate class</desc>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(SplitterWindow)
    WXJS_CONSTANT(wxSP_, 3D)
    WXJS_CONSTANT(wxSP_, 3DSASH)
    WXJS_CONSTANT(wxSP_, 3DBORDER)
//    WXJS_CONSTANT(wxSP_, FULLSASH)
    WXJS_CONSTANT(wxSP_, BORDER)
    WXJS_CONSTANT(wxSP_, NOBORDER)
    WXJS_CONSTANT(wxSP_, PERMIT_UNSPLIT)
    WXJS_CONSTANT(wxSP_, LIVE_UPDATE)
WXJS_END_CONSTANT_MAP()

void SplitterWindow::InitClass(JSContext *cx,
                               JSObject *obj,
                               JSObject* WXUNUSED(proto))
{
    JSConstDoubleSpec wxSplitModeMap[] = 
    {
        WXJS_CONSTANT(wxSPLIT_, VERTICAL)
        WXJS_CONSTANT(wxSPLIT_, HORIZONTAL)
	    { 0 }
    };
    JSObject *constObj = JS_DefineObject(cx, obj, "wxSplitMode", 
							             NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxSplitModeMap);

    SplitterEventHandler::InitConnectEventMap();
}

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxSplitterWindow.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the SplitterWindow control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the SplitterWindow control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxSplitterWindow.3D">
 *    The wxSplitterWindow style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxSplitterWindow object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxSplitterWindow, SplitterWindow)


	wxSplitterWindow *p = new wxSplitterWindow();



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
	
WXJS_BEGIN_DESTRUCTOR(wxSplitterWindow, SplitterWindow)
WXJS_END_DESTRUCTOR



WXJS_BEGIN_METHOD_MAP(SplitterWindow)
  WXJS_METHOD("create", create, 2)
  WXJS_METHOD("setSashPosition", setSashPosition, 1)
  WXJS_METHOD("initialize", initialize, 1)
  WXJS_METHOD("replaceWindow", replaceWindow, 2)
  WXJS_METHOD("splitHorizontally", splitHorizontally, 2)
  WXJS_METHOD("splitVertically", splitVertically, 2)
  WXJS_METHOD("unsplit", unsplit, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxSplitterWindow.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the SplitterWindow control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the SplitterWindow control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxSplitterWindow.3D">
 *    The wxSplitterWindow style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxSplitterWindow object.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool SplitterWindow::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSplitterWindow *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	int style = wxSP_3D;
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
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;
		
		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
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
 * <method name="setSashPosition">
 *  <function>
 *   <arg name="Pos" type=WXJS_TYPE_NUMBER>
 *    The sash position in pixels.
 *   </arg>
 *   <arg name="Redraw" type="Boolean" default="true">
 *    When true (the default) resizes the panes and redraws the sash and border.
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the sash position.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::setSashPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSplitterWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int pos;
    if ( ! FromJS(cx, argv[0], pos) )
        return JS_FALSE;

    bool redraw = true;
    if (    argc > 1
         && ! FromJS(cx, argv[1], redraw) )
         return JS_FALSE;

    p->SetSashPosition(pos, redraw);
    return JS_TRUE;
}

/***
 * <method name="initialize">
 *  <function>
 *   <arg name="Window" type="@wxWindow" />
 *  </function>
 *  <desc>
 *   Initializes the splitter window to have one pane.
 *   This should be called if you wish to initially view 
 *   only a single pane in the splitter window.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::initialize(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSplitterWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxWindow *win = Window::GetPrivate(cx, argv[0]);
    if ( win != NULL )
    {
        p->Initialize(win);
        return JS_TRUE;
    }
    return JS_FALSE;
}

/***
 * <method name="replaceWindow">
 *  <function returns="Boolean">
 *   <arg name="OldWindow" type="@wxWindow" />
 *   <arg name="NewWindow" type="@wxWindow" />
 *  </function>
 *  <desc>
 *   This function replaces one of the windows managed by the wxSplitterWindow 
 *   with another one. It is in general better to use it instead of calling 
 *   @wxSplitterWindow#unsplit and then resplitting the window back because
 *   it will provoke much less flicker (if any). It is valid to call this function 
 *   whether the splitter has two windows or only one.
 *   <br /><br />
 *   OldWindow must specify one of the windows managed by the splitter.
 *   If the parameters are incorrect or the window couldn't be replaced, false
 *   is returned. Otherwise the function will return true, but please notice that 
 *   it will not destroy the replaced window and you may wish to do it yourself.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::replaceWindow(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSplitterWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxWindow *oldWin = Window::GetPrivate(cx, argv[0]);
    if ( oldWin == NULL )
        return JS_FALSE;

    wxWindow *newWin = Window::GetPrivate(cx, argv[1]);
    if ( newWin == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->ReplaceWindow(oldWin, newWin));

    return JS_TRUE;
}

/***
 * <method name="splitHorizontally">
 *  <function>
 *   <arg name="Win1" type="@wxWindow">
 *    The top pane
 *   </arg>
 *   <arg name="Win2" type="@wxWindow">
 *    The bottom pane
 *   </arg>
 *   <arg name="SashPos" type=WXJS_TYPE_NUMBER default="0">
 *    The initial position of the sash. If this value is positive, it specifies
 *    the size of the upper pane. If it is negative, it is absolute value gives
 *    the size of the lower pane. Finally, specify 0 (default) to choose the 
 *    default position (half of the total window height).
 *   </arg>
 *  </function>
 *  <desc>
 *   Initializes the top and bottom panes of the splitter window.
 *   This should be called if you wish to initially view two panes. It can also
 *   be called at any subsequent time, but the application should check that the
 *   window is not currently split using @wxSplitterWindow#isSplit.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::splitHorizontally(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSplitterWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxWindow *win1 = Window::GetPrivate(cx, argv[0]);
    if ( win1 == NULL )
        return JS_FALSE;

    wxWindow *win2 = Window::GetPrivate(cx, argv[1]);
    if ( win2 == NULL )
        return JS_FALSE;

    int pos = 0;
    if (   argc > 2 
        && FromJS(cx, argv[2], pos) )
        return JS_FALSE;

    *vp = ToJS(cx, p->SplitHorizontally(win1, win2, pos));
    return JS_TRUE;
}

/***
 * <method name="splitVertically">
 *  <function>
 *   <arg name="Win1" type="@wxWindow">
 *    The top pane
 *   </arg>
 *   <arg name="Win2" type="@wxWindow">
 *    The bottom pane
 *   </arg>
 *   <arg name="SashPos" type=WXJS_TYPE_NUMBER default="0">
 *    The initial position of the sash. If this value is positive, it specifies
 *    the size of the left pane. If it is negative, it is absolute value gives 
 *    the size of the right pane. Finally, specify 0 (default) to choose the
 *    default position (half of the total window width).
 *   </arg>
 *  </function>
 *  <desc>
 *   Initializes the left and right panes of the splitter window.
 *   This should be called if you wish to initially view two panes. It can also
 *   be called at any subsequent time, but the application should check that the 
 *   window is not currently split using @wxSplitterWindow#isSplit.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::splitVertically(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSplitterWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxWindow *win1 = Window::GetPrivate(cx, argv[0]);
    if ( win1 == NULL )
        return JS_FALSE;

    wxWindow *win2 = Window::GetPrivate(cx, argv[1]);
    if ( win2 == NULL )
        return JS_FALSE;

    int pos = 0;
    if (   argc > 2 
        && FromJS(cx, argv[2], pos) )
        return JS_FALSE;

    *vp = ToJS(cx, p->SplitVertically(win1, win2, pos));
    return JS_TRUE;
}

/***
 * <method name="unsplit">
 *  <function>
 *   <arg name="Window" default="null">
 *    The pane to hide. When not specified, the right or bottom pane is hidden.
 *   </arg>
 *  </function>
 *  <desc>
 *   Unsplits the window.
 *  </desc>
 * </method>
 */
JSBool SplitterWindow::unsplit(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSplitterWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    if ( argc == 1 )
    {
        wxWindow *win = Window::GetPrivate(cx, argv[0]);
        if ( win != NULL )
        {
            *vp = ToJS(cx, p->Unsplit(win));
            return JS_TRUE;
        }
    }
    else
    {
        *vp = ToJS(cx, p->Unsplit());
        return JS_TRUE;
    }
    return JS_FALSE;
}

/***
 * <events>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxSplitterWindow)
const wxString WXJS_SASH_POS_CHANGING_EVENT = wxT("onSashPosChanging");
const wxString WXJS_SASH_POS_CHANGED_EVENT = wxT("onSashPosChanged");
const wxString WXJS_UNSPLIT_EVENT = wxT("onUnsplit");
const wxString WXJS_DCLICK_EVENT = wxT("onDClick");

void SplitterEventHandler::OnSashPosChanging(wxSplitterEvent &event)
{
  PrivSplitterEvent::Fire<SplitterEvent>(event, WXJS_SASH_POS_CHANGING_EVENT);
}

void SplitterEventHandler::OnSashPosChanged(wxSplitterEvent &event)
{
  PrivSplitterEvent::Fire<SplitterEvent>(event, WXJS_SASH_POS_CHANGED_EVENT);
}

void SplitterEventHandler::OnUnsplit(wxSplitterEvent &event)
{
  PrivSplitterEvent::Fire<SplitterEvent>(event, WXJS_UNSPLIT_EVENT);
}

void SplitterEventHandler::OnDClick(wxSplitterEvent &event)
{
  PrivSplitterEvent::Fire<SplitterEvent>(event, WXJS_DCLICK_EVENT);
}

void SplitterEventHandler::ConnectSashPosChanging(wxSplitterWindow *p,
                                                  bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, 
               wxSplitterEventHandler(SplitterEventHandler::OnSashPosChanging));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, 
                  wxSplitterEventHandler(SplitterEventHandler::OnSashPosChanging));
  }
}

void SplitterEventHandler::ConnectSashPosChanged(wxSplitterWindow *p,
                                                  bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, 
               wxSplitterEventHandler(SplitterEventHandler::OnSashPosChanged));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, 
                  wxSplitterEventHandler(SplitterEventHandler::OnSashPosChanged));
  }
}

void SplitterEventHandler::ConnectUnsplit(wxSplitterWindow *p,
                                          bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_SPLITTER_UNSPLIT, 
               wxSplitterEventHandler(SplitterEventHandler::OnUnsplit));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_SPLITTER_UNSPLIT, 
                  wxSplitterEventHandler(SplitterEventHandler::OnUnsplit));
  }
}

void SplitterEventHandler::ConnectDClick(wxSplitterWindow *p,
                                          bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_SPLITTER_DOUBLECLICKED, 
               wxSplitterEventHandler(SplitterEventHandler::OnDClick));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_SPLITTER_DOUBLECLICKED, 
                  wxSplitterEventHandler(SplitterEventHandler::OnDClick));
  }
}

void SplitterEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_SASH_POS_CHANGING_EVENT, ConnectSashPosChanging);
  AddConnector(WXJS_SASH_POS_CHANGED_EVENT, ConnectSashPosChanged);
  AddConnector(WXJS_UNSPLIT_EVENT, ConnectUnsplit);
  AddConnector(WXJS_DCLICK_EVENT, ConnectDClick);
}
