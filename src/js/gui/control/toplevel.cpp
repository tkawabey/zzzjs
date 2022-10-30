/*
 * wxJavaScript - toplevel.cpp
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
 * $Id: toplevel.cpp 714 2007-05-16 20:24:49Z fbraem $
 */
// toplevel.cpp
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



#include "js/gui/misc/icon.h"
#include "js/gui/control/toplevel.h"
#include "js/gui/control/window.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/toplevel</file>
 * <module>gui</module>
 * <class name="wxTopLevelWindow" prototype="wxWindow">
 *  wxTopLevelWindow is the prototype class for @wxDialog and @wxFrame. 
 * </class>
 */
WXJS_INIT_CLASS(TopLevelWindow, "TopLevelWindow", 0)

/***
 * <constants>
 *  <type name="wxFullScreen">
 *   <constant name="NOMENUBAR" /> 
 *   <constant name="NOTOOLBAR" /> 
 *   <constant name="NOSTATUSBAR" />  
 *   <constant name="NOBORDER" /> 
 *   <constant name="NOCAPTION" /> 
 *   <constant name="ALL" /> 
 *   <desc>
 *    wxFullScreen is ported to wxJS as a separate class
 *   </desc>
 *  </type>
 * </constants>
 */
void TopLevelWindow::InitClass(JSContext *cx, JSObject *obj, JSObject *proto)
{
    JSConstDoubleSpec wxFullScreenMap[] = 
    {
       WXJS_CONSTANT(wxFULLSCREEN_, NOMENUBAR)
       WXJS_CONSTANT(wxFULLSCREEN_, NOTOOLBAR)
       WXJS_CONSTANT(wxFULLSCREEN_, NOSTATUSBAR) 
       WXJS_CONSTANT(wxFULLSCREEN_, NOBORDER) 
       WXJS_CONSTANT(wxFULLSCREEN_, NOCAPTION) 
       WXJS_CONSTANT(wxFULLSCREEN_, ALL)
       { 0 }
    };
    JSObject *constObj = JS_DefineObject(cx, obj, "wxFullScreen", 
							             NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxFullScreenMap);
}

/***
 * <properties>
 *  <property name="fullScreen" type="Boolean">
 *   Get/Set fullscreen mode
 *  </property>
 *  <property name="icon" type="@wxIcon">
 *   Get/Set icon
 *  </property>
 *  <property name="icons" type="wxIconBundle">
 *   Not yet implemented
 *  </property>
 *  <property name="active" type="Boolean" readonly="Y">
 *   Is the window active?
 *  </property>
 *  <property name="defaultItem" type="@wxWindow" />
 *  <property name="iconized" type="Boolean">
 *   Get/Set iconized mode
 *  </property>
 *  <property name="maximized" type="Boolean">
 *   Get/Set maximized mode
 *  </property>
 *  <property name="title" type=WXJS_TYPE_STRING>
 *   Get/Set the title
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(TopLevelWindow)
    WXJS_PROPERTY(P_DEFAULT_ITEM, "defaultItem")
	WXJS_PROPERTY(P_FULL_SCREEN, "fullScreen")
	WXJS_PROPERTY(P_ICON, "icon")
	WXJS_PROPERTY(P_ICONS, "icons")
	WXJS_READONLY_PROPERTY(P_ACTIVE, "active")
	WXJS_PROPERTY(P_ICONIZED, "iconized")
	WXJS_PROPERTY(P_MAXIMIZED, "maximized")
	WXJS_PROPERTY(P_TITLE, "title")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxTopLevelWindow, TopLevelWindow)
	switch(id)  
	{
	case P_ICON:
        vp.set( Icon::CreateObject(cx, new wxIcon(p->GetIcon())) );
		break;
	case P_FULL_SCREEN:
		ToJSVal(cx, vp, p->IsFullScreen());
		break;
	case P_ICONS:
		//TODO
		break;
	case P_ICONIZED:
		ToJSVal(cx, vp, p->IsIconized());
		break;
	case P_MAXIMIZED:
		ToJSVal(cx, vp, p->IsMaximized());
		break;
	case P_TITLE:
		ToJSVal(cx, vp, p->GetTitle());
		break;
    case P_DEFAULT_ITEM:
      {
        wxWindow *win = p->GetDefaultItem();
        if ( win != NULL )
        {
          JavaScriptClientData *data
            = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
          if ( data != NULL )
          {
			  vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
          }
        }
        break;
      }
	}

	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxTopLevelWindow, TopLevelWindow)
	switch(id) 
	{
	case P_ICONS:
		//TODO
		break;
	case P_ICON:
		{
            wxIcon *ico = Icon::GetPrivate(cx, vp);
			if ( ico )
				p->SetIcon(*ico);
			break;
		}
	case P_ICONIZED:
		{
			bool iconize;
			if ( FromJS(cx, vp, iconize) )
				p->Iconize(iconize);
			break;
		}
	case P_FULL_SCREEN:
		{
			bool full;
			if ( FromJS(cx, vp, full) )
				p->ShowFullScreen(full, wxFULLSCREEN_ALL);
			break;
		}
	case P_MAXIMIZED:
		{
			bool maximize;
			if ( FromJS(cx, vp, maximize) )
				p->Maximize(maximize);
			break;
		}
	case P_TITLE:
		{
			wxString title;
			FromJS(cx, vp, title);
			p->SetTitle(title);
			break;
		}
    case P_DEFAULT_ITEM:
        wxWindow *win = Window::GetPrivate(cx, vp);
        if ( win != NULL )
        {
            p->SetDefaultItem(win);
        }
        break;
	}
    return true;
WXJS_END_SET_PROP
	

WXJS_BEGIN_GET_SET_STR_PROP(wxTopLevelWindow, TopLevelWindow)
	Window::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP



WXJS_BEGIN_METHOD_MAP(TopLevelWindow)
	WXJS_METHOD("requestUserAttention", requestUserAttention, 0)
	WXJS_METHOD("setLeftMenu", setLeftMenu, 0)
	WXJS_METHOD("setRightMenu", setRightMenu, 0)
	// setter
	WXJS_METHOD("setDefaultItem", setDefaultItem, 1)
	WXJS_METHOD("setFullScreen", setFullScreen, 1)
	WXJS_METHOD("setIcon", setIcon, 1)
	WXJS_METHOD("setIcons", setIcons, 1)
	WXJS_METHOD("setIconized", setIconized, 1)
	WXJS_METHOD("setMaximized", setMaximized, 1)
	WXJS_METHOD("setTitle", setTitle, 1)
WXJS_END_METHOD_MAP()

JSBool TopLevelWindow::requestUserAttention(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	//TODO
	return JS_TRUE;
}

JSBool TopLevelWindow::setLeftMenu(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	//TODO
	return JS_TRUE;
}

JSBool TopLevelWindow::setRightMenu(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	//TODO
	return JS_TRUE;
}

JSBool TopLevelWindow::setDefaultItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	

    wxWindow *win = Window::GetPrivate(cx, argv[0]);
    if ( win != NULL )
    {
        p->SetDefaultItem(win);
    }
	return JS_TRUE;
}

JSBool TopLevelWindow::setFullScreen(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	

	bool full;
	if ( FromJS(cx, argv[0], full) )
		p->ShowFullScreen(full, wxFULLSCREEN_ALL);


	return JS_TRUE;
}

JSBool TopLevelWindow::setIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	
    wxIcon *ico = Icon::GetPrivate(cx, argv[0]);
	if ( ico )
		p->SetIcon(*ico);

	return JS_TRUE;
}

JSBool TopLevelWindow::setIcons(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	
    //TODO

	return JS_TRUE;
}

JSBool TopLevelWindow::setIconized(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	
	bool iconize;
	if ( FromJS(cx, argv[0], iconize) )
		p->Iconize(iconize);

	return JS_TRUE;
}

JSBool TopLevelWindow::setMaximized(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	
	bool maximize;
	if ( FromJS(cx, argv[0], maximize) )
		p->Maximize(maximize);

	return JS_TRUE;
}

JSBool TopLevelWindow::setTitle(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxTopLevelWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	
	wxString title;
	FromJS(cx, argv[0], title);

	return JS_TRUE;
}











/***
 * <method name="showFullScreen">
 *  <function returns="Boolean">
 *   <arg name="Show" type="Boolean">
 *    Show the frame in full screen when true, restore when false.
 *   </arg>
 *   <arg name="Style=" type=WXJS_TYPE_NUMBER default="wxFullScreen.ALL">
 *    Use one of @wxTopLevelWindow#wxFullScreen.
 *   </arg>
 *  </function>
 *  <desc>
 *   Shows the frame in full screen or restores the frame.
 *  </desc>
 * </method>
 */
JSBool TopLevelWindow::showFullScreen(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxTopLevelWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    bool show;
    if ( ! FromJS(cx, argv[0], show) )
        return JS_FALSE;

    int style = wxFULLSCREEN_ALL;
    if (    argc > 1 
         && ! FromJS(cx, argv[1], style) )
         return JS_FALSE;

    *vp = ToJS(cx, p->ShowFullScreen(show, style));

	return JS_TRUE;
}
