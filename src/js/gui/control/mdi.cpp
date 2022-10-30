/*
 * wxJavaScript - mdi.cpp
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




#include "js/gui/errors.h"
#include "js/gui/misc/size.h"
#include "js/gui/control/window.h"
#include "js/gui/control/mdi.h"
#include "js/gui/control/frame.h"
#include "js/gui/control/toolbar.h"

using namespace zzzJs::gui;

wxToolBar* MDIParentFrame::OnCreateToolBar(long style, 
                                           wxWindowID id,
                                           const wxString& name)
{
  ToolBar *tbar = new ToolBar();
  tbar->Create(this, id, wxDefaultPosition, wxDefaultSize, style, name);
  return tbar;
}

/***
 * <module>gui</module>
 * <file>control/mdiparent</file>
 * <class name="wxMDIParentFrame" prototype="@wxFrame">
 *  An MDI (Multiple Document Interface) parent frame is a window which can 
 *  contain MDI child frames in its own 'desktop'. It is a convenient way to 
 *  avoid window clutter, and is used in many popular Windows applications, 
 *  such as Microsoft Word(TM).
 * </class>
 */
WXJS_INIT_CLASS(MDIParentFrame, "MDIParentFrame", 3)


WXJS_BEGIN_ADD_PROP(wxMDIParentFrame, MDIParentFrame)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    FrameEventHandler::ConnectEvent((wxFrame*)p, prop, true);

    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxMDIParentFrame, MDIParentFrame)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  FrameEventHandler::ConnectEvent((wxFrame*)p, prop, false);
  return true;
WXJS_END_DEL_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxMDIParentFrame, MDIParentFrame)
	Frame::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>The window ID</arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>The title of the window</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition" />
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize" />
 *   <arg name="Style" type=WXJS_TYPE_NUMBER 
 *        default="wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL" />
 *  </function>
 *  <desc>
 *   Creates a new MDI parent frame.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxMDIParentFrame, MDIParentFrame)

	MDIParentFrame *p = new MDIParentFrame();

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
	
WXJS_BEGIN_DESTRUCTOR(wxMDIParentFrame, MDIParentFrame)
WXJS_END_DESTRUCTOR

/***
 * <properties>
 *  <property name="activeChild" type="@wxMDIChildFrame" readonly="Y">
 *   The active MDI child, if there is one.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(MDIParentFrame)
  WXJS_READONLY_PROPERTY(P_ACTIVE_CHILD, "activeChild")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxMDIParentFrame, MDIParentFrame)
  switch(id)
  {
  case P_ACTIVE_CHILD:
    {
      wxMDIChildFrame *child = p->GetActiveChild();
      if ( child != NULL )
      {
        JavaScriptClientData *data 
             = dynamic_cast<JavaScriptClientData*>(child->GetClientObject());
        if ( data )
        {
          vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
        }
      }
    }
  }
  return true;
WXJS_END_GET_PROP

WXJS_BEGIN_METHOD_MAP(MDIParentFrame)
  WXJS_METHOD("create", create, 3)
  WXJS_METHOD("activateNext", activateNext, 0)
  WXJS_METHOD("activatePrevious", activatePrevious, 0)
  WXJS_METHOD("arrangeIcons", arrangeIcons, 0)
  WXJS_METHOD("cascade", cascade, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
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
JSBool MDIParentFrame::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool MDIParentFrame::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxMDIParentFrame *p = GetPrivate(cx, obj);
	*vp = JSVAL_FALSE;
  
	int argIndex = 0;
	int style = wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL;
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
		{
			wxString title;
			wxWindow *parent = NULL;
			int id = -1;
        

			argIndex = 0;
			if ( ! JSVAL_IS_NULL(argv[0]) ) {
				ZZZJS_ARG_GET_PRIVATE(parent, Window);
				if ( parent == NULL )
				{
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Window");
					return JS_FALSE;
				}
			}
			
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(title, WXJS_TYPE_STRING);
			argIndex++;

			 

        
			if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), style) )
			{
				*vp = JSVAL_TRUE;
				p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
				p->Connect(wxID_ANY, wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, 
						wxCommandEventHandler(FrameEventHandler::OnMenu));
			}
		}
	}
	return JS_TRUE;
}    

/***
 * <method name="activeNext">
 *  <function />
 *  <desc>
 *   Activates the MDI child following the currently active one.
 *  </desc>
 * </method>
 */
JSBool MDIParentFrame::activateNext(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIParentFrame *p = GetPrivate(cx, obj);
  
  p->ActivateNext();
  return JS_TRUE;
}    

/***
 * <method name="activePrevious">
 *  <function />
 *  <desc>
 *   Activates the MDI child preceding the currently active one.
 *  </desc>
 * </method>
 */
JSBool MDIParentFrame::activatePrevious(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIParentFrame *p = GetPrivate(cx, obj);
  
  p->ActivatePrevious();
  return JS_TRUE;
}    

/***
 * <method name="arrangeIcons">
 *  <function />
 *  <desc>
 *   Arranges any iconized (minimized) MDI child windows.
 *  </desc>
 * </method>
 */
JSBool MDIParentFrame::arrangeIcons(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIParentFrame *p = GetPrivate(cx, obj);
  
  p->ArrangeIcons();
  return JS_TRUE;
}    

/***
 * <method name="cascade">
 *  <function />
 *  <desc>
 *   Arranges the MDI child windows in a cascade.
 *  </desc>
 * </method>
 */
JSBool MDIParentFrame::cascade(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIParentFrame *p = GetPrivate(cx, obj);
  
  p->Cascade();
  return JS_TRUE;
}    

/***
 * <method name="cascade">
 *  <function>
 *   <arg name="Orientation" type="@wxOrientation" 
 *    default="wxOrientation.HORIZONTAL" />
 *  </function>
 *  <desc>
 *   Tiles the MDI child windows either horizontally or vertically.
 *   Currently only implemented for MSW, does nothing under the other platforms.
 *  </desc>
 * </method>
 */
JSBool MDIParentFrame::tile(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxMDIParentFrame *p = GetPrivate(cx, obj);
  
  int orient = wxHORIZONTAL;
  if ( argc > 0 )
  {
    if ( ! FromJS(cx, argv[0], orient) )
    {
      return JS_TRUE;
    }
  }
  
  p->Tile((wxOrientation) orient);
  return JS_TRUE;
}    
