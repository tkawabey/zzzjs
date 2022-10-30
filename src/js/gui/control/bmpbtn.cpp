/*
 * wxJavaScript - bmpbtn.cpp
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
 * $Id: bmpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/control/button.h"
#include "js/gui/control/control.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;

WXJS_INIT_CLASS(BitmapButton, "BitmapButton", 3)

/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(BitmapButton)
  WXJS_PROPERTY(P_BITMAP_DISABLED, "bitmapDisabled")
  WXJS_PROPERTY(P_BITMAP_FOCUS, "bitmapFocus")
  WXJS_PROPERTY(P_BITMAP_LABEL, "bitmapLabel")
  WXJS_PROPERTY(P_BITMAP_SELECTED, "bitmapSelected")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxBitmapButton, BitmapButton)
  switch (id) 
  {
  case P_BITMAP_DISABLED:
    vp.set( Bitmap::CreateObject(cx, new wxBitmap(p->GetBitmapDisabled())) );
    break;
  case P_BITMAP_FOCUS:
    vp.set( Bitmap::CreateObject(cx, new wxBitmap(p->GetBitmapFocus())) );
    break;
  case P_BITMAP_LABEL:
    vp.set( Bitmap::CreateObject(cx, new wxBitmap(p->GetBitmapLabel())) );
    break;
  case P_BITMAP_SELECTED:
    vp.set( Bitmap::CreateObject(cx, new wxBitmap(p->GetBitmapSelected())) );
    break;
  }
  return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxBitmapButton, BitmapButton)
  switch (id) 
  {
  case P_BITMAP_DISABLED:
    {
		zzzJsPtr<wxBitmap> apBitmap;
      if ( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true )
          p->SetBitmapDisabled(*(apBitmap.get()));
      break;
    }
  case P_BITMAP_FOCUS:
    {
		zzzJsPtr<wxBitmap> apBitmap;
      if ( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true )
          p->SetBitmapFocus(*(apBitmap.get()));
      break;
    }
  case P_BITMAP_LABEL:
    {
		zzzJsPtr<wxBitmap> apBitmap;
      if ( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true )
			p->SetBitmapLabel(*(apBitmap.get()));
		break;
    }
  case P_BITMAP_SELECTED:
    {
		zzzJsPtr<wxBitmap> apBitmap;
      if ( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true )
			p->SetBitmapSelected(*(apBitmap.get()));
		break;
    }
  }
  return true;
WXJS_END_SET_PROP

WXJS_BEGIN_ADD_PROP(wxBitmapButton, BitmapButton)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    ButtonEventHandler::ConnectEvent(p, prop, true);
    return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxBitmapButton, BitmapButton)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  ButtonEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxBitmapButton, BitmapButton)
	Button::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Bitmap" type="@wxBitmap">The bitmap to display</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTO_DRAW">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxBitmapButton object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxBitmapButton, BitmapButton)

	wxBitmapButton *p = new wxBitmapButton();



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


WXJS_BEGIN_DESTRUCTOR(wxBitmapButton, BitmapButton)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(BitmapButton)
    WXJS_METHOD("create", create, 3)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. 
 *    Use -1 when you don't need it.</arg>
 *   <arg name="Bitmap" type="@wxBitmap">The bitmap to display</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTO_DRAW">
 *    The style of the control</arg>
 *  </function>
 *  <desc>
 *   Creates a bitmap button.
 *  </desc>
 * </method>
 */
JSBool BitmapButton::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool BitmapButton::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxBitmapButton *p = GetPrivate(cx, obj);
    *rval = JSVAL_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = wxBU_AUTODRAW;
	
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
		zzzJsPtr<wxBitmap> apBitmap;
		wxWindow *parent = NULL;
        int id;
		
		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		if ( parent == NULL )
        {
            JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
            return JS_FALSE;
        }
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_AP_CHK_AND_ERROR(apBitmap, Bitmap);
		argIndex++;
		   
        

        JavaScriptClientData *clntParent =
               dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
        if ( clntParent == NULL )
        {
            JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
            return JS_FALSE;
        }
        JS_SetParent(cx, obj, clntParent->GetObject());

        if ( p->Create(parent, id, *(apBitmap.get()), *(apPoint.get()), *(apSize.get()), style) )
        {
            *rval = JSVAL_TRUE;
            p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
        }
    }
    return JS_TRUE;
}