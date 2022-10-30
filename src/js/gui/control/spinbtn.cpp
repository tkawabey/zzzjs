/*
 * wxJavaScript - spinbtn.cpp
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

#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"
#include "js/gui/event/spinevt.h"

#include "js/gui/control/spinbtn.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <module>gui</module>
 * <file>control/spinbtn</file>
 * <class name="wxSpinButton" prototype="@wxControl">
 *  A wxSpinButton has two small up and down (or left and right) arrow buttons. 
 *  It is often used next to a text control for increment and decrementing a 
 *  value. Portable programs should try to use @wxSpinButton instead as 
 *  wxSpinButton is not implemented for all platforms but @wxSpinButton is as it 
 *  degenerates to a simple @wxTextCtrl on such platforms.
 * </class>
 */
WXJS_INIT_CLASS(SpinButton, "SpinButton", 2)
void SpinButton::InitClass(JSContext* WXUNUSED(cx),
                         JSObject* WXUNUSED(obj), 
                         JSObject* WXUNUSED(proto))
{
	SpinButtonEventHandler::InitConnectEventMap();
}

/***
 * <constants>
 *	<type name="styles">
 *   <constant name="ARROW_KEYS" />
 *   <constant name="WRAP" />
 *   <constant name="HORIZONTAL" />
 *   <constant name="VERTICAL" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(SpinButton)
	WXJS_CONSTANT(wxSP_, ARROW_KEYS)
	WXJS_CONSTANT(wxSP_, WRAP)
    WXJS_CONSTANT(wxSP_, HORIZONTAL)
    WXJS_CONSTANT(wxSP_, VERTICAL)
WXJS_END_CONSTANT_MAP()

/***
 * <properties>
 *  <property name="value" type=WXJS_TYPE_STRING>
 *   The value of the spin control.
 *  </property>
 *  <property name="min" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Gets minimal allowable value.
 *  </property>
 *  <property name="max" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Gets maximal allowable value.
 *  </property>
 * </properties>
 */   
WXJS_BEGIN_PROPERTY_MAP(SpinButton)
	WXJS_PROPERTY(P_VALUE, "value")
	WXJS_READONLY_PROPERTY(P_MIN, "min")
	WXJS_READONLY_PROPERTY(P_MAX, "max")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxSpinButton, SpinButton)
	switch (id) 
	{
	case P_VALUE:
		ToJSVal(cx, vp, p->GetValue());
		break;
	case P_MIN:
		ToJSVal(cx, vp, p->GetMin());
		break;
	case P_MAX:
		ToJSVal(cx, vp, p->GetMax());
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxSpinButton, SpinButton)
	switch (id) 
	{
	case P_VALUE:
		{
			int value;
			FromJS(cx, vp, value);
			p->SetValue(value);
			break;
		}
	}
	return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxSpinButton, SpinButton)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxSpinButton, SpinButton)
	if ( WindowEventHandler::ConnectEvent(p, prop, true) )
		return true;

	SpinButtonEventHandler::ConnectEvent(p, prop, true);

	return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxSpinButton, SpinButton)
	if ( WindowEventHandler::ConnectEvent(p, prop, false) )
		return true;
	
	SpinButtonEventHandler::ConnectEvent(p, prop, false);
	return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="parent" type="@wxWindow">
 *    Parent window. Must not be NULL.
 *   </arg>
 *   <arg name="id" type=WXJS_TYPE_NUMBER>
 *    Window identifier. A value of -1 indicates a default value.
 *   </arg>
 *   <arg name="pos" type="@wxPoint" default="wxDefaultPosition">
 *    Window position.
 *   </arg>
 *   <arg name="size" type="@wxSize" default="wxDefaultSize">
 *    Window size.
 *   </arg>
 *   <arg name="style" type=WXJS_TYPE_NUMBER default="wxSpinButton.ARROW_KEYS">
 *    Window style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Create a wxSpinButton
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxSpinButton, SpinButton)

	wxSpinButton *p = new wxSpinButton();



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
	
WXJS_BEGIN_DESTRUCTOR(wxSpinButton, SpinButton)
WXJS_END_DESTRUCTOR



WXJS_BEGIN_METHOD_MAP(SpinButton)
  WXJS_METHOD("create", create, 2)
  WXJS_METHOD("setRange", setRange, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="parent" type="@wxWindow">
 *    Parent window. Must not be NULL.
 *   </arg>
 *   <arg name="id" type=WXJS_TYPE_NUMBER>
 *    Window identifier. A value of -1 indicates a default value.
 *   </arg>
 *   <arg name="pos" type="@wxPoint" default="wxDefaultPosition">
 *    Window position.
 *   </arg>
 *   <arg name="size" type="@wxSize" default="wxDefaultSize">
 *    Window size.
 *   </arg>
 *   <arg name="style" type=WXJS_TYPE_NUMBER default="wxSpinButton.HORIZONTAL">
 *    Window style.
 *   </arg>
 *  </function>
 *  <desc>
 *   Create a wxSpinButton
 *  </desc>
 * </method>
 */
JSBool SpinButton::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool SpinButton::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSpinButton *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	if ( argc > 5 )
		argc = 5;
	
	int argIndex = 0;
	wxWindowID id = -1;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = wxSP_ARROW_KEYS;
	
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
 * <method name="setRange">
 *  <function>
 *   <arg name="Min" type=WXJS_TYPE_NUMBER />
 *   <arg name="Max" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Sets range of allowable values.
 *  </desc>
 * </method>
 */
JSBool SpinButton::setRange(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSpinButton *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int minVal, maxVal;

	if (! FromJS(cx, argv[0], minVal))
		return JS_FALSE;
		
	if (! FromJS(cx, argv[1], maxVal))
		return JS_FALSE;
	
	p->SetRange(minVal, maxVal);

	return JS_TRUE;
}

/***
 * <events>
 *  <event name="onSpin">
 *   Generated whenever an arrow is pressed. A @wxSpinEvent is passed
 *   as argument.
 *  </event>
 *  <event name="onSpinUp">
 *   Generated when left/up arrow is pressed. A @wxSpinEvent is passed
 *   as argument.
 *  </event>
 *  <event name="onSpinDown">
 *   Generated when right/down arrow is pressed. A @wxSpinEvent is passed
 *   as argument.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxSpinButton)
const wxString WXJS_SPIN_EVENT = wxT("onSpin");
const wxString WXJS_SPIN_UP_EVENT = wxT("onSpinUp");
const wxString WXJS_SPIN_DOWN_EVENT = wxT("onSpinDown");

void SpinButtonEventHandler::OnSpin(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_EVENT);
}

void SpinButtonEventHandler::OnSpinUp(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_UP_EVENT);
}

void SpinButtonEventHandler::OnSpinDown(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_DOWN_EVENT);
}

void SpinButtonEventHandler::ConnectSpin(wxSpinButton *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_SCROLL_THUMBTRACK,
				wxSpinEventHandler(SpinButtonEventHandler::OnSpin));
	}
	else
	{
		p->Disconnect(wxEVT_SCROLL_THUMBTRACK,
				wxSpinEventHandler(SpinButtonEventHandler::OnSpin));
	}
}

void SpinButtonEventHandler::ConnectSpinUp(wxSpinButton *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_SCROLL_LINEUP,
				wxSpinEventHandler(SpinButtonEventHandler::OnSpinUp));
	}
	else
	{
		p->Disconnect(wxEVT_SCROLL_LINEUP,
				wxSpinEventHandler(SpinButtonEventHandler::OnSpinUp));
	}
}

void SpinButtonEventHandler::ConnectSpinDown(wxSpinButton *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_SCROLL_LINEDOWN,
				wxSpinEventHandler(SpinButtonEventHandler::OnSpinDown));
	}
	else
	{
		p->Disconnect(wxEVT_SCROLL_LINEDOWN,
				wxSpinEventHandler(SpinButtonEventHandler::OnSpinDown));
	}
}

void SpinButtonEventHandler::InitConnectEventMap()
{
	AddConnector(WXJS_SPIN_EVENT, ConnectSpin);
	AddConnector(WXJS_SPIN_UP_EVENT, ConnectSpinUp);
	AddConnector(WXJS_SPIN_DOWN_EVENT, ConnectSpinDown);
}
