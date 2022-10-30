/*
 * wxJavaScript - radiobtn.cpp
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
 * $Id: radiobtn.cpp 810 2007-07-13 20:07:05Z fbraem $
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

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"

#include "js/gui/control/radiobtn.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/radiobtn</file>
 * <module>gui</module>
 * <class name="wxRadioButton" prototype="@wxControl">
 *  A radio button item is a button which usually denotes one of several mutually exclusive 
 *  options. It has a text label next to a (usually) round button.
 *  <br /><br />You can create a group of mutually-exclusive radio buttons by specifying 
 *  wxRadioButton.GROUP for the first in the group. The group ends when another radio button
 *  group is created, or there are no more radio buttons. 
 *  See also @wxRadioBox.
 * </class>
 */
WXJS_INIT_CLASS(RadioButton, "RadioButton", 3)
void RadioButton::InitClass(JSContext* WXUNUSED(cx),
                            JSObject* WXUNUSED(obj), 
                            JSObject* WXUNUSED(proto))
{
  RadioButtonEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="value" type="Boolean">
 *   Select/Deselect the button
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(RadioButton)
	WXJS_PROPERTY(P_VALUE, "value")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxRadioButton, RadioButton)
	if (id == P_VALUE )
	{
		ToJSVal(cx, vp, p->GetValue());
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxRadioButton, RadioButton)
	if ( id == P_VALUE )
	{
		bool value; 
		if ( FromJS(cx, vp, value) )
			p->SetValue(value);
	}
    return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxRadioButton, RadioButton)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxRadioButton, RadioButton)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    RadioButtonEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxRadioButton, RadioButton)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  RadioButtonEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <constants>
 *  <type name="Styles">
 *   <constant name="GROUP">Marks the beginning of a new group of radio buttons.</constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(RadioButton)
    WXJS_CONSTANT(wxRB_, GROUP)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function returns="Boolean" />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxRadioButton.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Label" type=WXJS_TYPE_STRING>
 *    The title of the RadioButton.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the RadioButton control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the RadioButton control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The wxRadioButton style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *   Constructs a new wxRadioButton object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxRadioButton, RadioButton)

	wxRadioButton *p = new wxRadioButton();



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
	
WXJS_BEGIN_DESTRUCTOR(wxRadioButton, RadioButton)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(RadioButton)
  WXJS_METHOD("create", create, 3)
WXJS_END_METHOD_MAP()

JSBool RadioButton::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool RadioButton::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxRadioButton *p = GetPrivate(cx, obj);
	*vp = JSVAL_FALSE;

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(3, 7);
	argIndex = argc -1;
	switch(argc)
	{
	case 7:
		val = Validator::GetPrivate(cx, argv[6]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 7, "Validator");
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
		wxString text;
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
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(text, WXJS_TYPE_STRING);
		argIndex++;

		JavaScriptClientData *clntParent =
				dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, text, *(apPoint.get()), *(apSize.get()), style, *val) )
		{
			*vp = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

	return JS_TRUE;
}

/***
 * <events>
 *  <event name="onRadioButton">
 *	 Called when a radio button is clicked. The type of the argument that
 *   your handler receives is @wxCommandEvent.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxRadioButton)
const wxString WXJS_RADIOBUTTON_EVENT = wxT("onRadioButton");

void RadioButtonEventHandler::OnRadioButton(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_RADIOBUTTON_EVENT);
}

void RadioButtonEventHandler::ConnectRadioButton(wxRadioButton *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED,
               wxCommandEventHandler(RadioButtonEventHandler::OnRadioButton));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, 
                  wxCommandEventHandler(RadioButtonEventHandler::OnRadioButton));
  }
}

void RadioButtonEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_RADIOBUTTON_EVENT, ConnectRadioButton);
}
