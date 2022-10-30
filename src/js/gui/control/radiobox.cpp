/*
 * wxJavaScript - radiobox.cpp
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
 * $Id: radiobox.cpp 810 2007-07-13 20:07:05Z fbraem $
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

#include "js/gui/control/radiobox.h"
#include "js/gui/control/radioboxit.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/radiobox</file>
 * <module>gui</module>
 * <class name="wxRadioBox" prototype="@wxControl">
 *  A radio box item is used to select one of number of mutually exclusive choices. 
 *  It is displayed as a vertical column or horizontal row of labelled buttons.
 * </class>
 */
WXJS_INIT_CLASS(RadioBox, "RadioBox", 3)

void RadioBox::InitClass(JSContext* WXUNUSED(cx),
                         JSObject* WXUNUSED(obj), 
                         JSObject* WXUNUSED(proto))
{
  RadioBoxEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="count" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Get the number of items
 *  </property>
 *  <property name="item" type="Array" readonly="Y">
 *   Get an array of with @wxRadioBoxItem items.
 *  </property>
 *  <property name="selection" type=WXJS_TYPE_NUMBER>
 *   Get/Set the selected button. (zero-indexed)
 *  </property>
 *  <property name="stringSelection" type=WXJS_TYPE_STRING>
 *   Get/Set the selected string.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(RadioBox)
	WXJS_PROPERTY(P_SELECTION, "selection")
	WXJS_PROPERTY(P_STRING_SELECTION, "stringSelection")
	WXJS_READONLY_PROPERTY(P_COUNT, "count")
	WXJS_READONLY_PROPERTY(P_ITEM, "item")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxRadioBox, RadioBox)
    switch (id) 
	{
	case P_COUNT:
		ToJSVal(cx, vp, p->GetCount());
		break;
	case P_SELECTION:
		ToJSVal(cx, vp, p->GetSelection());
		break;
	case P_STRING_SELECTION:
		ToJSVal(cx, vp, p->GetStringSelection());
		break;
	case P_ITEM:
        vp.set( RadioBoxItem::CreateObject(cx, new Index(0)) );
		break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxRadioBox, RadioBox)
    switch (id) 
	{
	case P_SELECTION:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetSelection(value);
			break;
		}
	case P_STRING_SELECTION:
		{
			wxString value;
			FromJS(cx, vp, value);
			p->SetStringSelection(value);
			break;
		}
	}
    return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxRadioBox, RadioBox)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


WXJS_BEGIN_ADD_PROP(wxRadioBox, RadioBox)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    RadioBoxEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxRadioBox, RadioBox)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  RadioBoxEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <constants>
 *  <type name="Styles">
 *   <constant name="SPECIFY_ROWS">The major dimension parameter refers to the maximum number of rows.</constant>
 *   <constant name="SPECIFY_COLS">The major dimension parameter refers to the maximum number of columns.</constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(RadioBox)
    WXJS_CONSTANT(wxRA_, SPECIFY_ROWS)
	WXJS_CONSTANT(wxRA_, SPECIFY_COLS)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent of wxRadioBox.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A window identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>The title of the radiobox.</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the RadioBox control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the RadioBox control.
 *   </arg>
 *   <arg name="Items" type="Array" default="null">
 *    An array of Strings to initialize the control.
 *   </arg>
 *   <arg name="MaximumDimension" type=WXJS_TYPE_NUMBER default="0">
 *    Specifies the maximum number of rows (if style contains SPECIFY_ROWS) or columns
 *    (if style contains SPECIFY_COLS) for a two-dimensional radiobox.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="SPECIFY_COLS">
 *    The wxRadioBox style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *   Constructs a new wxRadioBox object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxRadioBox, RadioBox)

	wxRadioBox *p = new wxRadioBox();



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
	
WXJS_BEGIN_DESTRUCTOR(wxRadioBox, RadioBox)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(RadioBox)
	WXJS_METHOD("create", create, 3)
	WXJS_METHOD("setString", setString, 2)
	WXJS_METHOD("findString", setString, 2)
	WXJS_METHOD("enable", enable, 2)
	WXJS_METHOD("show", show, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent of wxRadioBox.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A window identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>The title of the radiobox.</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the RadioBox control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the RadioBox control.
 *   </arg>
 *   <arg name="Items" type="Array" default="null">
 *    An array of Strings to initialize the control.
 *   </arg>
 *   <arg name="MaximumDimension" type=WXJS_TYPE_NUMBER default="0">
 *    Specifies the maximum number of rows (if style contains SPECIFY_ROWS) or columns
 *    (if style contains SPECIFY_COLS) for a two-dimensional radiobox.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="SPECIFY_COLS">
 *    The wxRadioBox style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *   Constructs a new wxRadioBox object.
 *  </desc>
 * </method>
 */
JSBool RadioBox::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool RadioBox::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxRadioBox *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;


	
	int argIndex = 0;
	int style = 0;
	int max = 0;
	StringsPtr items;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(3, 9);

	
	argIndex = argc -1;
	switch(argc)
	{
	case 9:
		val = Validator::GetPrivate(cx, argv[8]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 9, "Validator");
			return JS_FALSE;
		}
		argIndex--;
	case 8:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 7:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(max, WXJS_TYPE_NUMBER);
		argIndex--;
	case 6:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(items, WXJS_TYPE_ARRAY);
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
		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(title, WXJS_TYPE_STRING);
		argIndex++;


		JavaScriptClientData *clntParent =
				dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());
		if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), 
				items.GetCount(), items.GetStrings(), max, style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

  return JS_TRUE;
}

/***
 * <method name="setString">
 *  <function>
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    The zero-based index of a button
 *   </arg> 
 *   <arg name="Label" type=WXJS_TYPE_STRING>
 *    Sets the label of the button.
 *   </arg>
 *  </function>
 *  <desc />
 * </method>
 */
JSBool RadioBox::setString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxRadioBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int idx;
	wxString label;

	if ( FromJS(cx, argv[0], idx) )
	{
		FromJS(cx, argv[1], label);
		p->SetString(idx, label);
	}
	else
	{
		return JS_FALSE;
	}
	return JS_TRUE;
}

/***
 * <method name="findString">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Str" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Finds a button matching the given string, returning the position if found, 
 *   or -1 if not found.
 *  </desc>
 * </method>
 */
JSBool RadioBox::findString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxRadioBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxString label;
	FromJS(cx, argv[0], label);
	*vp = ToJS(cx, p->FindString(label));

	return JS_TRUE;
}

/***
 * <method name="enable">
 *  <function>
 *   <arg name="Switch" type="Boolean" />
 *  </function>
 *  <function>
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    The zero-based index of a button
 *   </arg> 
 *   <arg name="Switch" type="Boolean" />
 *  </function>
 *  <desc>
 *   Enables/Disables the button at the given index.
 *   See @wxRadioBoxItem @wxRadioBoxItem#enable.
 *  </desc>
 * </method>
 */
JSBool RadioBox::enable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxRadioBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	if ( argc == 1 ) // The prototype method enable
	{
		bool sw;
		if ( FromJS(cx, argv[0], sw) )
		{
			p->Enable(sw);
			return JS_TRUE;
		}
	}
	else if ( argc == 2 )
	{
		int idx;
		bool sw;
		if (    FromJS(cx, argv[0], idx) 
			 && FromJS(cx, argv[1], sw) )
		{
			p->Enable(idx, sw);
			return JS_TRUE;
		}
	}

	return JS_FALSE;
}

/***
 * <method name="show">
 *  <function>
 *   <arg name="Switch" type="Boolean" />
 *  </function>
 *  <function>
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    The zero-based index of a button
 *   </arg> 
 *   <arg name="Switch" type="Boolean" />
 *  </function>
 *  <desc>
 *   Shows/Hides the button at the given index.
 *   See @wxRadioBoxItem @wxRadioBoxItem#enable.
 *  </desc>
 * </method>
 */
JSBool RadioBox::show(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxRadioBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	if ( argc == 1 ) // The prototype method enable
	{
		bool sw;
		if ( FromJS(cx, argv[0], sw) )
		{
			p->Show(sw);
			return JS_TRUE;
		}
	}
	else if ( argc == 2 )
	{
		int idx;
		bool sw;
		if (    FromJS(cx, argv[0], idx) 
			 && FromJS(cx, argv[1], sw) )
		{
			p->Show(idx, sw);
			return JS_TRUE;
		}
	}
	
	return JS_FALSE;
}

/***
 * <events>
 *  <event name="onRadioBox">
 *	 Called when a radio button is clicked. The type of the argument that your
 *   handler receives is @wxCommandEvent.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxRadioBox)
const wxString WXJS_RADIOBOX_EVENT = wxT("onRadioBox");

void RadioBoxEventHandler::OnRadioBox(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_RADIOBOX_EVENT);
}

void RadioBoxEventHandler::ConnectRadioBox(wxRadioBox *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, 
               wxCommandEventHandler(RadioBoxEventHandler::OnRadioBox));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_RADIOBOX_SELECTED, 
                  wxCommandEventHandler(RadioBoxEventHandler::OnRadioBox));
  }
}

void RadioBoxEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_RADIOBOX_EVENT, ConnectRadioBox);
}
#include "precompile.h"
