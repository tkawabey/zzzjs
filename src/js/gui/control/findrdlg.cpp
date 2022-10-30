/*
 * wxJavaScript - findrdlg.cpp
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
 * $Id: findrdlg.cpp 762 2007-06-16 13:33:43Z fbraem $
 */
// findrdlg.cpp
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

#include "js/gui/event/jsevent.h"
#include "js/gui/event/findr.h"

#include "js/gui/control/findrdlg.h"
#include "js/gui/control/finddata.h"
#include "js/gui/control/window.h"
#include "js/gui/control/dialog.h"

#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/findrdlg</file>
 * <module>gui</module>
 * <class name="wxFindReplaceDialog" prototype="@wxDialog">
 *  wxFindReplaceDialog is a standard modeless dialog which is used to allow 
 *  the user to search for some text (and possible replace it with something 
 *  else). The actual searching is supposed to be done in the owner window 
 *  which is the parent of this dialog. Note that it means that 
 *  unlike for the other standard dialogs this one must have a parent window. 
 *  Also note that there is no way to use this dialog in a modal way, it is 
 *  always, by design and implementation, modeless.
 * </class>
 */
//TODO: add a sample!
WXJS_INIT_CLASS(FindReplaceDialog, "FindReplaceDialog", 0)
void FindReplaceDialog::InitClass(JSContext* WXUNUSED(cx),
                                  JSObject* WXUNUSED(obj), 
                                  JSObject* WXUNUSED(proto))
{
  FindReplaceEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *	<property name="data" type="@wxFindReplaceData">
 *	 Get/Set the data
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(FindReplaceDialog)
  WXJS_PROPERTY(P_DATA, "data")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxFindReplaceDialog, FindReplaceDialog)
	if (id == P_DATA )
    {
      FindReplaceClientData *data 
            = dynamic_cast<FindReplaceClientData *>(p->GetClientObject());
      vp.set( FindReplaceData::CreateObject(cx, 
                                          new wxFindReplaceData(data->m_data)) 
			);
    }
    return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxFindReplaceDialog, FindReplaceDialog)
	Dialog::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


WXJS_BEGIN_ADD_PROP(wxFindReplaceDialog, FindReplaceDialog)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    FindReplaceEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxFindReplaceDialog, FindReplaceDialog)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  FindReplaceEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <constants>
 *  <type name="Styles">
 *   <constant name="REPLACEDIALOG" />
 *   <constant name="NOUPDOWN" />
 *   <constant name="NOMACTHCASE" />
 *   <constant name="NOWHOLEWORD" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(FindReplaceDialog)
  WXJS_CONSTANT(wxFR_, REPLACEDIALOG)
  WXJS_CONSTANT(wxFR_, NOUPDOWN)
  WXJS_CONSTANT(wxFR_, NOMATCHCASE)
  WXJS_CONSTANT(wxFR_, NOWHOLEWORD)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of wxFindReplaceDialog. Can't be null.
 *   </arg>
 *   <arg name="Data" type="@wxFindReplaceData" />
 *   <arg name="Title" type=WXJS_TYPE_STRING>
 *	  The title of the dialog
 *   </arg>
 *	 <arg name="Style" type=WXJS_TYPE_NUMBER default="0" />
 *  </function>
 *  <function />
 *  <desc>
 *	 Constructs a new wxFindReplaceDialog object
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxFindReplaceDialog, FindReplaceDialog)

	wxFindReplaceDialog *p = new wxFindReplaceDialog();

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

WXJS_BEGIN_DESTRUCTOR(wxFindReplaceDialog, FindReplaceDialog)
WXJS_END_DESTRUCTOR

WXJS_BEGIN_METHOD_MAP(FindReplaceDialog)
  WXJS_METHOD("create", create, 4)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function>
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of wxFindReplaceDialog. Can't be null.
 *   </arg>
 *   <arg name="Data" type="@wxFindReplaceData" />
 *   <arg name="Title" type=WXJS_TYPE_STRING>
 *	  The title of the dialog
 *   </arg>
 *	 <arg name="Style" type=WXJS_TYPE_NUMBER default="0" />
 *  </function>
 *  <desc>
 *   Creates a wxFindReplaceDialog.
 *  </desc>
 * </method>
 */
JSBool FindReplaceDialog::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool FindReplaceDialog::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxFindReplaceDialog *p = FindReplaceDialog::GetPrivate(cx, obj);
    *rval = JSVAL_FALSE;

    if ( argc > 4 )
      argc = 4;

	int style = 0;
    if ( argc == 4 )
    {
      if ( ! FromJS(cx, argv[3], style) )
      {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
        return JS_FALSE;
      }
    }

	wxString title;
    FromJS(cx, argv[2], title);

    wxFindReplaceData *data = FindReplaceData::GetPrivate(cx, argv[1]);
    if ( data == NULL )
    {
      JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "wxFindReplaceData");
      return JS_FALSE;
    }

    wxWindow *parent = Window::GetPrivate(cx, argv[0]);
    if ( parent == NULL )
    {
        JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
        return JS_FALSE;
    }

    if ( p->Create(parent, data, title, style) )
    {
      FindReplaceClientData *clntData = new FindReplaceClientData(cx, obj,
                                                                  true, false);
      p->SetClientObject(clntData);
      // Copy the data
      clntData->m_data.SetFlags(data->GetFlags());
      clntData->m_data.SetFindString(data->GetFindString());
      clntData->m_data.SetReplaceString(data->GetReplaceString());
      *rval = JSVAL_TRUE;
      p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
    }

    return JS_TRUE;
}
/***
 * <events>
 *  <event name="onFind">
 *   The find button was pressed. 
 *   The argument passed to the function is a @wxFindDialogEvent
 *  </event>
 *  <event name="onFindNext">
 *   The find next button was pressed. 
 *   The argument passed to the function is a @wxFindDialogEvent
 *  </event>
 *  <event name="onFindReplace">
 *   The replace button was pressed. 
 *   The argument passed to the function is a @wxFindDialogEvent
 *  </event>
 *  <event name="onFindReplaceAll">
 *   The replace all button was pressed. 
 *   The argument passed to the function is a @wxFindDialogEvent
 *  </event>
 *  <event name="onFindClose">
 *   The dialog is being destroyed. 
 *   The argument passed to the function is a @wxFindDialogEvent
 * </event>
 * </events>
 */

WXJS_INIT_EVENT_MAP(wxFindReplaceDialog)
const wxString WXJS_FIND_EVENT = wxT("onFind");
const wxString WXJS_FIND_NEXT_EVENT = wxT("onFindNext");
const wxString WXJS_FIND_REPLACE_EVENT = wxT("onFindReplace");
const wxString WXJS_FIND_REPLACE_ALL_EVENT = wxT("onFindReplaceAll");
const wxString WXJS_FIND_CLOSE_EVENT = wxT("onFindClose");

void FindReplaceEventHandler::OnFind(wxFindDialogEvent& event)
{
  PrivFindDialogEvent::Fire<FindDialogEvent>(event, WXJS_FIND_EVENT);
}

void FindReplaceEventHandler::OnFindNext(wxFindDialogEvent& event)
{
  PrivFindDialogEvent::Fire<FindDialogEvent>(event, WXJS_FIND_NEXT_EVENT);
}

void FindReplaceEventHandler::OnReplace(wxFindDialogEvent& event)
{
  PrivFindDialogEvent::Fire<FindDialogEvent>(event, WXJS_FIND_REPLACE_EVENT);
}

void FindReplaceEventHandler::OnReplaceAll(wxFindDialogEvent& event)
{
  PrivFindDialogEvent::Fire<FindDialogEvent>(event, 
                                             WXJS_FIND_REPLACE_ALL_EVENT);
}

void FindReplaceEventHandler::OnFindClose(wxFindDialogEvent& event)
{
  PrivFindDialogEvent::Fire<FindDialogEvent>(event, WXJS_FIND_CLOSE_EVENT);
  //Destroy();
}

void FindReplaceEventHandler::ConnectFind(wxFindReplaceDialog *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_FIND, wxFindDialogEventHandler(FindReplaceEventHandler::OnFind));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_FIND, wxFindDialogEventHandler(FindReplaceEventHandler::OnFind));
  }
}

void FindReplaceEventHandler::ConnectFindNext(wxFindReplaceDialog *p,
                                              bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_FIND_NEXT, wxFindDialogEventHandler(FindReplaceEventHandler::OnFindNext));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_FIND_NEXT,
                  wxFindDialogEventHandler(FindReplaceEventHandler::OnFindNext));
  }
}

void FindReplaceEventHandler::ConnectReplace(wxFindReplaceDialog *p,
                                             bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_FIND_REPLACE, wxFindDialogEventHandler(FindReplaceEventHandler::OnReplace));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_FIND_REPLACE, 
                  wxFindDialogEventHandler(FindReplaceEventHandler::OnReplace));
  }
}

void FindReplaceEventHandler::ConnectReplaceAll(wxFindReplaceDialog *p,
                                                bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_FIND_REPLACE_ALL, 
               wxFindDialogEventHandler(FindReplaceEventHandler::OnReplaceAll));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_FIND_REPLACE_ALL, 
                  wxFindDialogEventHandler(FindReplaceEventHandler::OnReplaceAll));
  }
}

void FindReplaceEventHandler::ConnectFindClose(wxFindReplaceDialog *p,
                                               bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_FIND_CLOSE, wxFindDialogEventHandler(FindReplaceEventHandler::OnFindClose));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_FIND_CLOSE,
                  wxFindDialogEventHandler(FindReplaceEventHandler::OnFindClose));
  }
}

void FindReplaceEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_FIND_EVENT, ConnectFind);
  AddConnector(WXJS_FIND_NEXT_EVENT, ConnectFindNext);
  AddConnector(WXJS_FIND_REPLACE_EVENT, ConnectReplace);
  AddConnector(WXJS_FIND_REPLACE_ALL_EVENT, ConnectReplaceAll);
  AddConnector(WXJS_FIND_CLOSE_EVENT, ConnectFindClose);
}
