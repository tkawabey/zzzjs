/*
 * wxJavaScript - mdichild.cpp
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
 * $Id$
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




// wxJS_gui includes
#include "js/gui/errors.h"
#include "js/gui/misc/size.h"
#include "js/gui/control/mdi.h"
#include "js/gui/control/mdichild.h"
#include "js/gui/control/frame.h"
#include "js/gui/control/window.h"
#include "js/gui/control/toolbar.h"

using namespace zzzJs::gui;

wxToolBar* MDIChildFrame::OnCreateToolBar(long style, 
                                          wxWindowID id,
                                          const wxString& name)
{
  ToolBar *tbar = new ToolBar();
  tbar->Create(this, id, wxDefaultPosition, wxDefaultSize, style, name);
  return tbar;
}

/***
 * <module>gui</module>
 * <file>control/mdichild</file>
 * <class name="wxMDIChildFrame" prototype="@wxFrame">
 *  An MDI child frame is a frame that can only exist in a @wxMDIParentFrame 
 * </class>
 */
WXJS_INIT_CLASS(MDIChildFrame, "MDIChildFrame", 3)


WXJS_BEGIN_ADD_PROP(wxMDIChildFrame, MDIChildFrame)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    FrameEventHandler::ConnectEvent((wxFrame*)p, prop, true);

    return true;
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxMDIChildFrame, MDIChildFrame)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  FrameEventHandler::ConnectEvent((wxFrame*)p, prop, false);
  return true;
WXJS_END_DEL_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxMDIChildFrame, MDIChildFrame)
	Frame::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxMDIParentFrame">
 *    The parent frame. This can't be null.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>The window ID</arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>The title of the window</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition" />
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize" />
 *   <arg name="Style" type=WXJS_TYPE_NUMBER 
 *        default="wxDEFAULT_FRAME_STYLE" />
 *  </function>
 *  <desc>
 *   Creates a new MDI child frame.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxMDIChildFrame, MDIChildFrame)

  MDIChildFrame *p = new MDIChildFrame();



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
	
WXJS_BEGIN_DESTRUCTOR(wxMDIChildFrame, MDIChildFrame)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(MDIChildFrame)
  WXJS_METHOD("create", create, 3)
  WXJS_METHOD("activate", activate, 0)
  WXJS_METHOD("maximize", maximize, 1)
  WXJS_METHOD("restore", restore, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxMDIParentFrame">
 *    The parent frame. This can't be null.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>The window ID</arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>The title of the window</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition" />
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize" />
 *   <arg name="Style" type=WXJS_TYPE_NUMBER 
 *        default="wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL" />
 *  </function>
 *  <desc>
 *   Sets a pixel to a particular color.
 *  </desc>
 * </method>
 */
JSBool MDIChildFrame::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool MDIChildFrame::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxMDIChildFrame *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
  
	int argIndex = 0;
	int style = wxDEFAULT_FRAME_STYLE;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
  
	ZZZJS_CHECK_ARG_COUNT(3, 6);
  
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
		{
			wxString title;
			wxMDIParentFrame *parent = NULL;
			int id = -1;
        

			argIndex = 0;
			ZZZJS_ARG_GET_PRIVATE(parent, MDIParentFrame);
			if (    parent == NULL 
				|| parent->GetHandle() == NULL )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "MDIParentFrame");
				return JS_FALSE;
			}
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(title, WXJS_TYPE_STRING);
			argIndex++;

        
			parent = MDIParentFrame::GetPrivate(cx, argv[0]);

        
			if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), style) )
			{
				*rval = JSVAL_TRUE;
				p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
				p->Connect(wxID_ANY, wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, 
					wxCommandEventHandler(FrameEventHandler::OnMenu));
			}
		}
	}
	return JS_TRUE;
}    

/***
 * <method name="activate">
 *  <function />
 *  <desc>
 *   Activates this MDI child frame
 *  </desc>
 * </method>
 */
JSBool MDIChildFrame::activate(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIChildFrame *p = GetPrivate(cx, obj);
  
  p->Activate();
  return JS_TRUE;
}    

/***
 * <method name="maximize">
 *  <function>
 *   <arg name="Maximize" type="Boolean" />
 *  </function>
 *  <desc>
 *   Maximizes this MDI child frame
 *  </desc>
 * </method>
 */
JSBool MDIChildFrame::maximize(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIChildFrame *p = GetPrivate(cx, obj);
  
  bool sw = true;
  FromJS(cx, argv[0], sw);
  p->Maximize(sw);
  
  return JS_TRUE;
}    

/***
 * <method name="restore">
 *  <function />
 *  <desc>
 *   Restores this MDI child frame
 *  </desc>
 * </method>
 */
JSBool MDIChildFrame::restore(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIChildFrame *p = GetPrivate(cx, obj);
  
  p->Restore();
  return JS_TRUE;
}    
