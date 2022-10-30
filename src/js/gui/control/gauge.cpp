/*
 * wxJavaScript - gauge.cpp
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
 * $Id: gauge.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// gauge.cpp
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
#include "js/gui/misc/validate.h"

#include "js/gui/control/gauge.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/gauge</file>
 * <module>gui</module>
 * <class name="wxGauge" prototype="@wxControl">
 *  A gauge is a horizontal or vertical bar which shows a quantity (often time).
 * </class>
 */
WXJS_INIT_CLASS(Gauge, "Gauge", 3)

/***
 * <properties>
 *  <property name="bezelFace" type=WXJS_TYPE_NUMBER>
 *   Get/Set the width of the 3D bezel face. <I>Windows only</I>
 *  </property>
 *  <property name="range" type=WXJS_TYPE_NUMBER>
 *   Get/Set the maximum position of the gauge.
 *  </property>
 *  <property name="shadowWidth" type=WXJS_TYPE_NUMBER>
 *   Get/Set the 3D shadow margin width. <I>Windows only</I>
 *  </property>
 *  <property name="value" type=WXJS_TYPE_NUMBER>
 *   Get/Set the current value of the gauge.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Gauge)
  WXJS_PROPERTY(P_BEZEL_FACE, "bezelFace")
  WXJS_PROPERTY(P_RANGE, "range")
  WXJS_PROPERTY(P_SHADOW_WIDTH, "shadowWidth")
  WXJS_PROPERTY(P_VALUE, "value")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxGauge, Gauge)
    switch (id) 
	{
	case P_BEZEL_FACE:
		ToJSVal(cx, vp,p->GetBezelFace());
		break;
	case P_RANGE:
		ToJSVal(cx, vp,p->GetRange());
		break;
	case P_SHADOW_WIDTH:
		ToJSVal(cx, vp,p->GetShadowWidth());
		break;
	case P_VALUE:
		ToJSVal(cx, vp,p->GetValue());
		break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxGauge, Gauge)
    switch (id) 
	{
	case P_BEZEL_FACE:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetBezelFace(value);
			break;
		}
	case P_RANGE:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetRange(value);
			break;
		}
	case P_SHADOW_WIDTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetShadowWidth(value);
			break;
		}
	case P_VALUE:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetValue(value);
			break;
		}
	}
    return true;
WXJS_END_SET_PROP


WXJS_BEGIN_ADD_PROP(wxGauge, Gauge)
  return WindowEventHandler::ConnectEvent(p, prop, true);
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxGauge, Gauge)
	int a = wxGA_HORIZONTAL;
  return WindowEventHandler::ConnectEvent(p, prop, false);
WXJS_END_DEL_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxGauge, Gauge)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

/***
 * <constants>
 *  <type name="Style">
 *   <constant name="HORIZONTAL" />
 *   <constant name="VERTICAL" />
 *   <constant name="PROGRESSBAR" />
 *   <constant name="SMOOTH" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Gauge)
  WXJS_CONSTANT(wxGA_, HORIZONTAL)
  WXJS_CONSTANT(wxGA_, VERTICAL)
  WXJS_CONSTANT(wxGA_, PROGRESS)
  WXJS_CONSTANT(wxGA_, SMOOTH)
  WXJS_CONSTANT(wxGA_, TEXT)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxGauge.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Range" type=WXJS_TYPE_NUMBER>
 *    The maximum value of the gauge
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the Gauge control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the Gauge control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxGauge.HORIZONTAL">
 *    The wxGauge style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *   Constructs a new wxGauge object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxGauge, Gauge)

	wxGauge *p = new wxGauge();



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
	
WXJS_BEGIN_DESTRUCTOR(wxGauge, Gauge)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Gauge)
  WXJS_METHOD("create", create, 3)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *	<function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxGauge.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Range" type=WXJS_TYPE_NUMBER>
 *    The maximum value of the gauge
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the Gauge control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the Gauge control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxGauge.HORIZONTAL">
 *    The wxGauge style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *	 Creates a wxGauge
 *  </desc>
 * </method>
 */
JSBool Gauge::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool Gauge::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxGauge *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
	
	
	int argIndex = 0;
	int style = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(3, 7);

	argIndex = argc -1;
	switch(argc)
	{
	case 7:
		val = Validator::GetPrivate(cx, argv[6]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 7, "wxValidator");
			return JS_FALSE;
		}
		argIndex--;
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
		wxWindow *parent = NULL;
		int id;
		int range;


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
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(range, WXJS_TYPE_NUMBER);
		argIndex++;



		JavaScriptClientData *clntParent =
			dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, range, *(apPoint.get()), 
					*(apSize.get()), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	
	return JS_TRUE;
}

