/*
 * wxJavaScript - button.cpp
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
 * $Id: button.cpp 810 2007-07-13 20:07:05Z fbraem $
 */

/***
 * <file>control/button</file>
 * <module>gui</module>
 * <class name="wxButton" prototype="@wxControl">
 *	A button is a control that contains a text string,
 *	and is one of the commonest elements of a GUI. It may 
 *	be placed on a dialog box or panel, or indeed almost any other window.
 *  An example:
 *  <pre><code class="whjs">// dlg is a wxDialog
 *  var button = new wxButton(dlg, -1, "Click me");
 *  button.onClicked = function(event)
 *  {
 *    wxMessageBox("You've clicked me");
 *  }</code></pre><br />
 * </class>
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
#include "js/ext/point.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"

#include "js/gui/control/button.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"
#include "js/gui/errors.h"


using namespace zzzJs;
using namespace zzzJs::gui;

WXJS_INIT_CLASS(Button, "Button", 3)

void Button::InitClass(JSContext* WXUNUSED(cx), 
                       JSObject* WXUNUSED(obj), 
                       JSObject* WXUNUSED(proto))
{
    ButtonEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="label" type=WXJS_TYPE_STRING>
 *   Get/Set the label of the button.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Button)
  WXJS_PROPERTY(P_LABEL, "label")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxButton, Button)
  if ( id == P_LABEL )
    ToJSVal(cx, vp, p->GetLabel());

  return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxButton, Button)
  if ( id == P_LABEL )
  {
    wxString label;
    FromJS(cx, vp, label);
    p->SetLabel(label);
  }
  return true;
WXJS_END_SET_PROP


WXJS_BEGIN_ADD_PROP(wxButton, Button)
  if ( WindowEventHandler::ConnectEvent(p, prop, true) )
    return true;
  
  ButtonEventHandler::ConnectEvent(p, prop, true);
  return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxButton, Button)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  ButtonEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <class_properties>
 *  <property name="defaultSize" type=WXJS_TYPE_NUMBER readonly="Y">
 *    Gets the default size of a button.
 *  </property>
 * </class_properties>
 */
WXJS_BEGIN_STATIC_PROPERTY_MAP(Button)
  WXJS_READONLY_STATIC_PROPERTY(P_DEFAULT_SIZE, "defaultSize")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_STATIC_PROP(Button)
{
  if ( id == P_DEFAULT_SIZE )
  {
    vp.set( Size::CreateObject(cx, new wxSize(wxButton::GetDefaultSize())) );
  }
  return true;
}
WXJS_END_GET_STATIC_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxButton, Button)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <constants>
 *  <type name="Style">
 *   <constant name="LEFT">
 *    Left-justifies the label. Windows and GTK+ only.
 *   </constant>
 *   <constant name="RIGHT">
 *    Right-justifies the bitmap label. Windows and GTK+ only.
 *   </constant>
 *   <constant name="TOP">
 *    Aligns the label to the top of the button. Windows and GTK+ only.
 *   </constant>
 *   <constant name="BOTTOM">
 *    Aligns the label to the bottom of the button. Windows and GTK+ only.
 *   </constant>
 *   <constant name="EXACTFIT">
 *    Creates the button as small as possible instead of making it of the 
 *    standard size (which is the default behaviour ).
 *   </constant>
 *   <constant name="NO_BORDER">
 *    Creates a flat button. Windows and GTK+ only.
 *   </constant>
 *   <constant name="AUTODRAW">
 *    If this is specified, the button will be drawn automatically using 
 *    the label bitmap only, providing a 3D-look border. If this style is not 
 *    specified, 
 *    the button will be drawn without borders and using all provided bitmaps. 
 *    WIN32 only.
 *   </constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Button)
  WXJS_CONSTANT(wxBU_, LEFT)
  WXJS_CONSTANT(wxBU_, RIGHT)
  WXJS_CONSTANT(wxBU_, TOP)
  WXJS_CONSTANT(wxBU_, BOTTOM)
  WXJS_CONSTANT(wxBU_, EXACTFIT)
  WXJS_CONSTANT(wxBU_, AUTODRAW)
  WXJS_CONSTANT(wx, NO_BORDER)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent of the button.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>The label of the button</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the button on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the button.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTODRAW">
 *    The button style
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="wxDefaultValidator" />
 *  </function>
 *  <desc>
 *   Constructs a new wxButton object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxButton, Button)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxButton *p = new wxButton();
	
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

	
WXJS_BEGIN_DESTRUCTOR(wxButton, Button)
 //   JavaScriptClientData *pCln 
 //             = dynamic_cast<JavaScriptClientData *>(p->GetClientObject());
	//if( pCln != NULL ) {
	//	//delete	pCln;
	//}
	if( p != NULL ) {
		p = NULL;
	}
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Button)
  WXJS_METHOD("create", create, 3)
  WXJS_METHOD("setDefault", setDefault, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent of the button.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>The label of the button</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the button on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the button.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTODRAW">
 *    The button style
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="wxDefaultValidator" />
 *  </function>
 *  <desc>
 *   Creates a button.
 *  </desc>
 * </method>
 */
JSBool Button::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}

JSBool Button::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxButton *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
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
		int id;
		wxString text;
		wxWindow *parent = NULL;

		
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


		JavaScriptClientData *clntParent 
				= dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, text, *(apPoint.get()), *(apSize.get()), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

	return JS_TRUE;
}
/***
 * <method name="setDefault">
 *  <function />
 *  <desc>
 *   This sets the button to be the default item for the panel or dialog box.
 *   see @wxPanel#defaultItem.
 *  </desc>
 * </method>
 */
JSBool Button::setDefault(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxButton *p = GetPrivate(cx, obj);
  if ( p == NULL )
    return JS_FALSE;

  p->SetDefault();

  return JS_TRUE;
}

/***
 * <events>
 *  <event name="onClicked">
 *   Called when the button is clicked. The type of the argument that your
*    handler receives is @wxCommandEvent.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxButton)
const wxString WXJS_BUTTON_CLICKED_EVENT = wxT("onClicked");

void ButtonEventHandler::OnClicked(wxCommandEvent &event)
{
  PrivCommandEvent::Fire<CommandEvent>(event, WXJS_BUTTON_CLICKED_EVENT);
}

void ButtonEventHandler::ConnectClicked(wxButton *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ButtonEventHandler::OnClicked));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, 
                  wxCommandEventHandler(ButtonEventHandler::OnClicked));
  }
}

void ButtonEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_BUTTON_CLICKED_EVENT, ConnectClicked);
}
