/*
 * wxJavaScript - sttext.cpp
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
 * $Id: sttext.cpp 810 2007-07-13 20:07:05Z fbraem $
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

#include "js/gui/control/sttext.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"

#include "js/gui/misc/size.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/sttext</file>
 * <module>gui</module>
 * <class name="wxStaticText" prototype="@wxControl">
 *  A static text control displays one or more lines of read-only text.
 * </class>
 */
WXJS_INIT_CLASS(StaticText, "StaticText", 3)

/***
 * <properties>
 *  <property name="label" type=WXJS_TYPE_STRING>
 *   Get/Sets the text.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(StaticText)
  WXJS_PROPERTY(P_LABEL, "label")
WXJS_END_PROPERTY_MAP()

/***
 * <constants>
 *  <type name="Style">
 *   <constant name="ALIGN_LEFT" />
 *   <constant name="ALIGN_RIGHT" />
 *   <constant name="ALIGN_CENTER" />
 *   <constant name="NO_AUTORESIZE" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(StaticText)
  WXJS_CONSTANT(wx, ALIGN_LEFT)
  WXJS_CONSTANT(wx, ALIGN_RIGHT)
  WXJS_CONSTANT(wx, ALIGN_CENTER)
  WXJS_CONSTANT(wxST_, NO_AUTORESIZE)
WXJS_END_CONSTANT_MAP()


WXJS_BEGIN_GET_PROP(wxStaticText, StaticText)
    if (id == P_LABEL )
    {
		ToJSVal(cx, vp, p->GetLabel());
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxStaticText, StaticText)
    if ( id == P_LABEL )
	{
		wxString label;
		FromJS(cx, vp, label);
		p->SetLabel(label);
	}
    return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxStaticText, StaticText)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


WXJS_BEGIN_ADD_PROP(wxStaticText, StaticText)
  WindowEventHandler::ConnectEvent(p, prop, true);
  return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxStaticText, StaticText)
  WindowEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of the static text. This can't be <I>null</I>.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    The unique identifier.
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>
 *    The text of the static text
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the static text.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the static text.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The style of the static text. See @wxStaticText#styles
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxStaticText object
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxStaticText, StaticText)

	wxStaticText *p = new wxStaticText();



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
	
WXJS_BEGIN_DESTRUCTOR(wxStaticText, StaticText)
WXJS_END_DESTRUCTOR



WXJS_BEGIN_METHOD_MAP(StaticText)
  WXJS_METHOD("create", create, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of the static text. This can't be <I>null</I>.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    The unique identifier.
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>
 *    The text of the static text
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the static text.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the static text.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The style of the static text. See @wxStaticText#styles
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxStaticText object
 *  </desc>
 * </method>
 */
JSBool StaticText::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool StaticText::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxStaticText *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	

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

		if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), style) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

	return JS_TRUE;
}
