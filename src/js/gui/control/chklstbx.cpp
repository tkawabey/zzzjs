/*
 * wxJavaScript - chklstbx.cpp
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
 * $Id: chklstbx.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/common/strsptr.h"
#include "js/common/index.h"
#include "js/ext/zzzjs_ext_init.h"


#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"

#include "js/gui/control/chklstbx.h"
#include "js/gui/control/chklstbxchk.h"
#include "js/gui/control/window.h"
#include "js/gui/control/listbox.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/chklstbx</file>
 * <module>gui</module>
 * <class name="wxCheckListBox" prototype="@wxListBox">
 *  A checklistbox is like a listbox, but allows items to be checked
 *  or unchecked.
 * </class>
 */
WXJS_INIT_CLASS(CheckListBox, "CheckListBox", 2)

void CheckListBox::InitClass(JSContext* WXUNUSED(cx),
                             JSObject* WXUNUSED(obj), 
                             JSObject* WXUNUSED(proto))
{
    CheckListBoxEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="checked" type="Array" readonly="Y">
 *   Array with @wxCheckListBoxItem elements. 
 *   Use it to check/uncheck a specific item.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CheckListBox)
  WXJS_PROPERTY(P_CHECKED, "checked")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxCheckListBox, CheckListBox)

    if ( id == P_CHECKED )
	{
        vp.set( CheckListBoxItem::CreateObject(cx, new Index(0), obj) );
	}
    return true;
WXJS_END_GET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxCheckListBox, CheckListBox)
	ListBox::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxCheckListBox, CheckListBox)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    if ( ListBoxEventHandler::ConnectEvent(p, prop, true) )
        return true;

    CheckListBoxEventHandler::ConnectEvent(p, prop, true);
    return true;
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxCheckListBox, CheckListBox)
    if ( WindowEventHandler::ConnectEvent(p, prop, false) )
        return true;
    
    if ( ListBoxEventHandler::ConnectEvent(p, prop, false) )
        return true;

    CheckListBoxEventHandler::ConnectEvent(p, prop, false);
    return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent of this control</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the CheckListBox control on the given parent.
 *   </arg>
 *   <arg name="Size" type="wxSize" default="wxDefaultSize">
 *    The size of the CheckListBox control.
 *   </arg>
 *   <arg name="Items" type="Array" default="null">
 *    An array of Strings to initialize the control
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The wxCheckListBox style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null">A validator</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxCheckListBox object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxCheckListBox, CheckListBox)

	wxCheckListBox *p = new wxCheckListBox();


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
	
WXJS_BEGIN_DESTRUCTOR(wxCheckListBox, CheckListBox)
WXJS_END_DESTRUCTOR

WXJS_BEGIN_METHOD_MAP(CheckListBox)
  WXJS_METHOD("create", create, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent of this control</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the CheckListBox control on the given parent.
 *   </arg>
 *   <arg name="Size" type="wxSize" default="wxDefaultSize">
 *    The size of the CheckListBox control.
 *   </arg>
 *   <arg name="Items" type="Array" default="null">
 *    An array of Strings to initialize the control
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    The wxCheckListBox style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null">A validator</arg>
 *  </function>
 *  <desc>
 *   Creates wxCheckListBox.
 *  </desc>
 * </method>
 */
JSBool CheckListBox::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}

JSBool CheckListBox::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxCheckListBox *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	StringsPtr items;
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
		argIndex--;
	case 6:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 5:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(items, WXJS_TYPE_ARRAY);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 3:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
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

		// Don't forget the wxLB_OWNERDRAW, 
		// because Create is called on wxListBox
		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), 
						items.GetCount(), items.GetStrings(), 
						style | wxLB_OWNERDRAW, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	
	return JS_TRUE;
}
/***
 * <events>
 *  <event name="onCheckListBox">
 *   Called when an item is checked or unchecked. 
 *   The function that is called gets a @wxCommandEvent
 *   object.</event>
 * </events>
 */

WXJS_INIT_EVENT_MAP(wxCheckListBox)
const wxString WXJS_CHECKLISTBOX_EVENT = wxT("onCheckListBox");

void CheckListBoxEventHandler::OnCheckListBox(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_CHECKLISTBOX_EVENT);
}

void CheckListBoxEventHandler::ConnectCheckListBox(wxCheckListBox *p,
                                                   bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, 
               wxCommandEventHandler(CheckListBoxEventHandler::OnCheckListBox));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, 
                  wxCommandEventHandler(CheckListBoxEventHandler::OnCheckListBox));
  }
}

void CheckListBoxEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_CHECKLISTBOX_EVENT, ConnectCheckListBox);
}
