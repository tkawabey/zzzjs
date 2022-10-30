/*
 * wxJavaScript - spinctrl.cpp
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
 * Remark: This class was donated by Philip Taylor.
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

#include "js/gui/control/spinctrl.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <module>gui</module>
 * <file>control/spinctrl</file>
 * <class name="wxSplitCtrl" prototype="@wxControl">
 *  wxSpinCtrl combines @wxTextCtrl and @wxSpinButton in one control.
 * </class>
 */
WXJS_INIT_CLASS(SpinCtrl, "SpinCtrl", 1)
void SpinCtrl::InitClass(JSContext* WXUNUSED(cx),
                         JSObject* WXUNUSED(obj), 
                         JSObject* WXUNUSED(proto))
{
	SpinCtrlEventHandler::InitConnectEventMap();
}

/***
 * <constants>
 *	<type name="styles">
 *   <constant name="ARROW_KEYS" />
 *   <constant name="WRAP" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(SpinCtrl)
	WXJS_CONSTANT(wxSP_, ARROW_KEYS)
	WXJS_CONSTANT(wxSP_, WRAP)
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
WXJS_BEGIN_PROPERTY_MAP(SpinCtrl)
	WXJS_PROPERTY(P_VALUE, "value")
	WXJS_READONLY_PROPERTY(P_MIN, "min")
	WXJS_READONLY_PROPERTY(P_MAX, "max")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxSpinCtrl, SpinCtrl)
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


WXJS_BEGIN_SET_PROP(wxSpinCtrl, SpinCtrl)
	switch (id) 
	{
	case P_VALUE:
		{
			wxString value;
			FromJS(cx, vp, value);
			p->SetValue(value);
			break;
		}
	}
	return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxSpinCtrl, SpinCtrl)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxSpinCtrl, SpinCtrl)
	if ( WindowEventHandler::ConnectEvent(p, prop, true) )
		return true;

	SpinCtrlEventHandler::ConnectEvent(p, prop, true);

	return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxSpinCtrl, SpinCtrl)
	if ( WindowEventHandler::ConnectEvent(p, prop, false) )
		return true;
	
	SpinCtrlEventHandler::ConnectEvent(p, prop, false);
	return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="parent" type="@wxWindow">
 *    Parent window. Must not be NULL.
 *   </arg>
 *   <arg name="id" type=WXJS_TYPE_NUMBER default="-1">
 *    Window identifier. A value of -1 indicates a default value.
 *   </arg>
 *   <arg name="value" type=WXJS_TYPE_STRING default="">
 *    Default value.
 *   </arg>
 *   <arg name="pos" type="@wxPoint" default="wxDefaultPosition">
 *    Window position.
 *   </arg>
 *   <arg name="size" type="@wxSize" default="wxDefaultSize">
 *    Window size.
 *   </arg>
 *   <arg name="style" type=WXJS_TYPE_NUMBER default="wxSpinCtrl.ARROW_KEYS">
 *    Window style.
 *   </arg>
 *   <arg name="min" type=WXJS_TYPE_NUMBER default="0">
 *    Minimal value.
 *   </arg>
 *   <arg name="max" type=WXJS_TYPE_NUMBER default="100">
 *    Maximal value.
 *   </arg>
 *   <arg name="initial" type=WXJS_TYPE_NUMBER default="0">
 *    Initial value.
 *   </arg>
 *  </function>
 *  <desc>
 *   Create a wxSpinCtrl
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxSpinCtrl, SpinCtrl)


	wxSpinCtrl *p = new wxSpinCtrl();



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
	
WXJS_BEGIN_DESTRUCTOR(wxSpinCtrl, SpinCtrl)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(SpinCtrl)
  WXJS_METHOD("create", create, 1)
  WXJS_METHOD("setRange", setRange, 2)
  WXJS_METHOD("setSelection", setSelection, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="parent" type="@wxWindow">
 *    Parent window. Must not be NULL.
 *   </arg>
 *   <arg name="id" type=WXJS_TYPE_NUMBER default="-1">
 *    Window identifier. A value of -1 indicates a default value.
 *   </arg>
 *   <arg name="value" type=WXJS_TYPE_STRING default="">
 *    Default value.
 *   </arg>
 *   <arg name="pos" type="@wxPoint" default="wxDefaultPosition">
 *    Window position.
 *   </arg>
 *   <arg name="size" type="@wxSize" default="wxDefaultSize">
 *    Window size.
 *   </arg>
 *   <arg name="style" type=WXJS_TYPE_NUMBER default="wxSpinCtrl.ARROW_KEYS">
 *    Window style.
 *   </arg>
 *   <arg name="min" type=WXJS_TYPE_NUMBER default="0">
 *    Minimal value.
 *   </arg>
 *   <arg name="max" type=WXJS_TYPE_NUMBER default="100">
 *    Maximal value.
 *   </arg>
 *   <arg name="initial" type=WXJS_TYPE_NUMBER default="0">
 *    Initial value.
 *   </arg>
 *  </function>
 *  <desc>
 *   Create a wxSpinCtrl
 *  </desc>
 * </method>
 */
JSBool SpinCtrl::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool SpinCtrl::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSpinCtrl *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	if ( argc > 9 )
		argc = 9;
	
	int argIndex = 0;
	wxWindowID id = -1;
	wxString value = wxEmptyString;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = wxSP_ARROW_KEYS;
	int min = 0;
	int max = 100;
	int initial = 0;
	
	ZZZJS_CHECK_ARG_COUNT(3, 6);
	
	argIndex = argc -1;
	switch(argc)
	{
	case 9:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(initial, WXJS_TYPE_NUMBER);
		argIndex--;
	case 8:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(max, WXJS_TYPE_NUMBER);
		argIndex--;
	case 7:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(min, WXJS_TYPE_NUMBER);
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
	case 3:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex--;
	default:
		wxWindow *parent = NULL;

		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
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

		if ( p->Create(parent, id, value, *(apPoint.get()), *(apSize.get()), style, min, max, initial) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

	return JS_TRUE;
}

/***
 * <method name="setSelection">
 *  <function>
 *   <arg name="From" type=WXJS_TYPE_NUMBER />
 *   <arg name="To" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Select the text in the text part of the control between positions from 
 *   (inclusive) and to (exclusive). This is similar to @wxTextCtrl#setSelection.
 *  </desc>
 * </method>
 */
JSBool SpinCtrl::setSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSpinCtrl *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	long from, to;

	if (! FromJS(cx, argv[0], from))
		return JS_FALSE;
		
	if (! FromJS(cx, argv[1], to))
		return JS_FALSE;
	
	p->SetSelection(from, to);

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
JSBool SpinCtrl::setRange(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSpinCtrl *p = GetPrivate(cx, obj);
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
 *  <event name="onText">
 *   See @wxTextCtrl#onText
 *  </event>
 *  <event name="onSpinCtrl">
 *   Called whenever the numeric value of the spinctrl is updated.
 *   The method takes a @wxSpinEvent.
 *  </event>
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
WXJS_INIT_EVENT_MAP(wxSpinCtrl)
const wxString WXJS_TEXT_EVENT = wxT("onText");
const wxString WXJS_SPIN_CTRL_EVENT = wxT("onSpinCtrl");
const wxString WXJS_SPIN_EVENT = wxT("onSpin");
const wxString WXJS_SPIN_UP_EVENT = wxT("onSpinUp");
const wxString WXJS_SPIN_DOWN_EVENT = wxT("onSpinDown");

void SpinCtrlEventHandler::OnText(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_TEXT_EVENT);
}

void SpinCtrlEventHandler::OnSpinCtrl(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_CTRL_EVENT);
}

void SpinCtrlEventHandler::OnSpin(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_EVENT);
}

void SpinCtrlEventHandler::OnSpinUp(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_UP_EVENT);
}

void SpinCtrlEventHandler::OnSpinDown(wxSpinEvent &event)
{
	PrivSpinEvent::Fire<SpinEvent>(event, WXJS_SPIN_DOWN_EVENT);
}

void SpinCtrlEventHandler::ConnectText(wxSpinCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_COMMAND_TEXT_UPDATED,
				wxCommandEventHandler(SpinCtrlEventHandler::OnText));
	}
	else
	{
		p->Disconnect(wxEVT_COMMAND_TEXT_UPDATED,
				wxCommandEventHandler(SpinCtrlEventHandler::OnText));
	}
}

void SpinCtrlEventHandler::ConnectSpinCtrl(wxSpinCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpinCtrl));
	}
	else
	{
		p->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpinCtrl));
	}
}

void SpinCtrlEventHandler::ConnectSpin(wxSpinCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_SCROLL_THUMBTRACK,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpin));
	}
	else
	{
		p->Disconnect(wxEVT_SCROLL_THUMBTRACK,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpin));
	}
}

void SpinCtrlEventHandler::ConnectSpinUp(wxSpinCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_SCROLL_LINEUP,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpinUp));
	}
	else
	{
		p->Disconnect(wxEVT_SCROLL_LINEUP,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpinUp));
	}
}

void SpinCtrlEventHandler::ConnectSpinDown(wxSpinCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_SCROLL_LINEDOWN,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpinDown));
	}
	else
	{
		p->Disconnect(wxEVT_SCROLL_LINEDOWN,
				wxSpinEventHandler(SpinCtrlEventHandler::OnSpinDown));
	}
}

void SpinCtrlEventHandler::InitConnectEventMap()
{
	AddConnector(WXJS_TEXT_EVENT, ConnectText);
	AddConnector(WXJS_SPIN_CTRL_EVENT, ConnectSpinCtrl);
	AddConnector(WXJS_SPIN_EVENT, ConnectSpin);
	AddConnector(WXJS_SPIN_UP_EVENT, ConnectSpinUp);
	AddConnector(WXJS_SPIN_DOWN_EVENT, ConnectSpinDown);
}
