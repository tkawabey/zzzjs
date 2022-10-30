/*
 * wxJavaScript - dialog.cpp
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
 * $Id: dialog.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/gui/event/jsevent.h"
#include "js/gui/event/close.h"

#include "js/gui/control/dialog.h"
#include "js/gui/control/window.h"
#include "js/gui/control/toplevel.h"

#include "js/gui/misc/size.h"

#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/dialog</file>
 * <module>gui</module>
 * <class name="wxDialog" prototype="@wxTopLevelWindow">
 *  A dialog box is a window with a title bar and sometimes a system menu, 
 *  which can be moved around the screen. It can contain controls and other windows.
 *  <br /><br />
 *  The following sample shows a simple dialog:
 *  <pre><code class="whjs">// Initialize the application
 *  wxTheApp.onInit = function()
 *  {
 *    dlg = new wxDialog(null, -1, "test");
 *  
 *    dlg.button = new wxButton(dlg, 1, "Ok");
 *  
 *    dlg.button.onClicked = function()
 *    {
 *       endModal(1);
 *    }
 *    
 *    dlg.showModal();
 *    
 *    // Return false, will end the main loop
 *    return false;
 *  }
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(Dialog, "Dialog", 3)

void Dialog::InitClass(JSContext* WXUNUSED(cx),
                       JSObject* WXUNUSED(obj),
                       JSObject* WXUNUSED(proto))
{
    DialogEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="returnCode" type=WXJS_TYPE_NUMBER readonly="Y">
 *   The returncode of the modal dialog
 *  </property>
 *  <property name="modal" type="Boolean" readonly="Y">
 *   Returns true when the dialog is a modal dialog
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Dialog)
  WXJS_READONLY_PROPERTY(P_RETURN_CODE, "returnCode")
  WXJS_READONLY_PROPERTY(P_MODAL, "modal")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxDialog, Dialog)
  switch (id)
  {
  case P_RETURN_CODE:
    ToJSVal(cx, vp,p->GetReturnCode());
    break;
  case P_MODAL:
    ToJSVal(cx, vp,p->IsModal());
    break;
  }
  return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_ADD_PROP(wxDialog, Dialog)
  if ( WindowEventHandler::ConnectEvent(p, prop, true) )
    return true;
  
  DialogEventHandler::ConnectEvent(p, prop, true);
  return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxDialog, Dialog)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  DialogEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP


WXJS_BEGIN_GET_SET_STR_PROP(wxDialog, Dialog)
	TopLevelWindow::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


/***
 * <constants>
 *  <type name="Style">
 *   <constant name="DIALOG_MODAL" />
 *   <constant name="CAPTION" />
 *   <constant name="DEFAULT_DIALOG_STYLE" />
 *   <constant name="RESIZE_BORDER" />
 *   <constant name="SYSTEM_MENU" />
 *   <constant name="THICK_FRAME" />
 *   <constant name="STAY_ON_TOP" />
 *   <constant name="NO_3D" />
 *   <constant name="DIALOG_EX_CONTEXTHELP" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Dialog)
  // Style constants
//  WXJS_CONSTANT(wx, DIALOG_MODAL)
  WXJS_CONSTANT(wx, CAPTION)
  WXJS_CONSTANT(wx, DEFAULT_DIALOG_STYLE)
  WXJS_CONSTANT(wx, RESIZE_BORDER)
  WXJS_CONSTANT(wx, SYSTEM_MENU)
//  WXJS_CONSTANT(wx, THICK_FRAME)
  WXJS_CONSTANT(wx, STAY_ON_TOP)
//  WXJS_CONSTANT(wx, NO_3D)
  WXJS_CONSTANT(wx, DIALOG_EX_CONTEXTHELP)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of the dialog. null is Allowed.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    The window identifier
 *   </arg>
 *   <arg name="title" type=WXJS_TYPE_STRING>
 *    The title of the dialog
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the dialog.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the dialog
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxDialog.DEFAULT_DIALOG_STYLE">
 *    The window style
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a dialog
 *  </desc>
 * </ctor>
 */
 
WXJS_BEGIN_CONSTRUCTOR(wxDialog, Dialog)

	wxDialog *p = new wxDialog();

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


WXJS_BEGIN_DESTRUCTOR(wxDialog, Dialog)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Dialog)
  WXJS_METHOD("create", create, 3)
  WXJS_METHOD("endModal", end_modal, 1)
  WXJS_METHOD("showModal", show_modal, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of the dialog. null is Allowed.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    The window identifier
 *   </arg>
 *   <arg name="title" type=WXJS_TYPE_STRING>
 *    The title of the dialog
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the dialog.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the dialog
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxDialog.DEFAULT_DIALOG_STYLE">
 *    The window style
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a dialog.
 *  </desc>
 * </method>
 */
JSBool Dialog::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
 JSBool Dialog::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
 {
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxDialog *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
	
	int argIndex = 0;
	int style = wxDEFAULT_DIALOG_STYLE;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	
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
			style |= wxDIALOG_NO_PARENT;
		}
		else
		{
			JavaScriptClientData *clntParent 
				= dynamic_cast<JavaScriptClientData*>(parent->GetClientObject());
			if ( clntParent == NULL )
			{
				JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
				return JS_FALSE;
			}
			JS_SetParent(cx, obj, clntParent->GetObject());
		}

		if ( p->Create(parent, id, title, *(apPoint.get()), *(apSize.get()), style) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	return JS_TRUE;
}
/***
 * <method name="endModal">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="ReturnCode" type=WXJS_TYPE_NUMBER>
 *    The value to be returned from @wxDialog#showModal
 *   </arg>
 *  </function>
 *  <desc>
 *   Ends a modal dialog.
 *  </desc>
 * </method>
 */
JSBool Dialog::end_modal(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxDialog *p = Dialog::GetPrivate(cx, obj);
  if ( p == NULL )
      return JS_FALSE;

  int code;
  if ( FromJS(cx, argv[0], code) )
  {
    p->EndModal(code);
    return JS_TRUE;
  }

  return JS_FALSE;
}

/***
 * <method name="showModal">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   Shows a modal dialog. 
 *   The value returned is the return code set by @wxDialog#endModal.
 *  </desc>
 * </method>
 */
JSBool Dialog::show_modal(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxDialog *p = Dialog::GetPrivate(cx, obj);
  if ( p == NULL )
    return JS_FALSE;

  *vp = ToJS(cx, p->ShowModal());

  return JS_TRUE;
}

/***
 * <events>
 *  <event name="onClose">
 *   Called when the dialog is closed. The type of the argument that your 
 *   handler receives is @wxCloseEvent.
 *  </event>
 *  <event name="onInitDialog">
 *   This event is sent as a dialog or panel is being initialised.
 *   Handlers for this event can transfer data to the window. 
 *   The function gets a @wxInitDialogEvent as argument
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxDialog)
const wxString WXJS_CLOSE_EVENT = wxT("onClose");
const wxString WXJS_INIT_DIALOG_EVENT = wxT("onInitDialog");

void DialogEventHandler::OnInitDialog(wxInitDialogEvent &event)
{
  PrivInitDialogEvent::Fire<InitDialogEvent>(event, WXJS_INIT_DIALOG_EVENT);
}

void DialogEventHandler::OnClose(wxCloseEvent &event)
{
  PrivCloseEvent::Fire<CloseEvent>(event, WXJS_CLOSE_EVENT);
/*
  bool destroy = true;

  wxDialog *p = dynamic_cast<wxDialog*>(event.GetEventObject());

  if ( PrivCloseEvent::Fire<CloseEvent>(this, event, "onClose") )
  {
    destroy = ! event.GetVeto();
  }

  // When the close event is not handled by JavaScript,
  // wxJS destroys the dialog.
  if ( destroy )
  {
    p->Destroy();
  }
*/
}

void DialogEventHandler::ConnectClose(wxDialog *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(DialogEventHandler::OnClose));
  }
  else
  {
    p->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(DialogEventHandler::OnClose));
  }
}

void DialogEventHandler::ConnectInitDialog(wxDialog *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(DialogEventHandler::OnInitDialog));
  }
  else
  {
    p->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(DialogEventHandler::OnInitDialog));
  }
}

void DialogEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_CLOSE_EVENT, ConnectClose);
  AddConnector(WXJS_INIT_DIALOG_EVENT, ConnectInitDialog);
}
