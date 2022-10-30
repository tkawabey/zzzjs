/*
 * wxJavaScript - checkbox.cpp
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
 * $Id: checkbox.cpp 810 2007-07-13 20:07:05Z fbraem $
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

#include "js/gui/control/checkbox.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/checkbox</file>
 * <module>gui</module>
 * <class name="wxCheckBox" prototype="@wxControl">
 *  A checkbox is a labeled box which is either on 
 *  (checkmark is visible) or off (no checkmark).
 *  <br />An example:
 *  <pre><code class="whjs">
 *   // dlg is a wxDialog
 *   var chkbox = new wxCheckBox(dlg, -1, "Check me");
 *   chkbox.onCheckBox = function(event)
 *   {
 *     if ( event.checked )
 *       wxMessageBox("Checked");
 *     else
 *       wxMessageBox("Unchecked");
 *   }
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(CheckBox, "CheckBox", 3)
void CheckBox::InitClass(JSContext* WXUNUSED(cx),
                         JSObject* WXUNUSED(obj), 
                         JSObject* WXUNUSED(proto))
{
    CheckBoxEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="value" type="Boolean">
 *   Checks/Unchecks the checkbox.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CheckBox)
  WXJS_PROPERTY(P_VALUE, "value")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxCheckBox, CheckBox)
    if ( id == P_VALUE )
	{
		ToJSVal(cx, vp, p->GetValue());
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxCheckBox, CheckBox)
    if (id == P_VALUE )
	{
		bool value;
		if ( FromJS(cx, vp, value) )
			p->SetValue(value);
    }
    return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxCheckBox, CheckBox)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxCheckBox, CheckBox)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    CheckBoxEventHandler::ConnectEvent(p, prop, true);
    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxCheckBox, CheckBox)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  CheckBoxEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent of the checkbox</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A window identifier. Use -1 when you don't need it</arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>The label of the checkbox</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">The position of the checkbox on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the checkbox</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">The style of the checkbox</arg>
 *   <arg name="Validator" type="@wxValidator" default="null">A validator</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxCheckBox object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxCheckBox, CheckBox)

	wxCheckBox *p = new wxCheckBox();

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
	
WXJS_BEGIN_DESTRUCTOR(wxCheckBox, CheckBox)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(CheckBox)
  WXJS_METHOD("create", create, 3)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of the checkbox</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>The label of the checkbox
 *   </arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the checkbox on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the checkbox
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The style of the checkbox
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null">A validator</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxCheckBox object.
 *  </desc>
 * </method>
 */
JSBool CheckBox::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool CheckBox::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxCheckBox *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(3, 7);

	switch(argc)
	{
	case 7:
		val = Validator::GetPrivate(cx, argv[6]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 7, "Validator");
			return JS_FALSE;
		}
	case 6:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 5:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	// Fall through
	default:
		wxString title;
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

		if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

    return JS_TRUE;
}


/***
 * <events>
 *  <event name="onCheckBox">
 *   Called when the checkbox is clicked. The type of the argument that your 
 *   handler receives is @wxCommandEvent.
 *  </event>
 * </events>
 */

WXJS_INIT_EVENT_MAP(wxCheckBox)
const wxString WXJS_CHECKBOX_EVENT = wxT("onCheckBox");

void CheckBoxEventHandler::OnCheckBox(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_CHECKBOX_EVENT);
}


void CheckBoxEventHandler::ConnectCheckBox(wxCheckBox *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, 
               wxCommandEventHandler(CheckBoxEventHandler::OnCheckBox));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, 
                  wxCommandEventHandler(CheckBoxEventHandler::OnCheckBox));
  }
}

void CheckBoxEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_CHECKBOX_EVENT, ConnectCheckBox);
}
