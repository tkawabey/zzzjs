/*
 * wxJavaScript - combobox.cpp
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
 * $Id: combobox.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/common/index.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"

#include "js/gui/control/combobox.h"
#include "js/gui/control/window.h"
#include "js/gui/control/ctrlitem.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/combobox</file>
 * <module>gui</module>
 * <class name="wxComboBox" prototype="@wxControlWithItems">
 *	A combobox is like a combination of an edit control and a listbox.
 *	It can be displayed as static list with editable or read-only text field; 
 *	or a drop-down list with text field; or a drop-down list without a text 
 *  field.
 * </class>
 */
WXJS_INIT_CLASS(ComboBox, "ComboBox", 2)

void ComboBox::InitClass(JSContext* WXUNUSED(cx),
                         JSObject* WXUNUSED(obj), 
                         JSObject* WXUNUSED(proto))
{
  ComboBoxEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="canCopy" type="Boolean" readonly="Y">
 *   Returns true if the combobox is editable and there is a text 
 *   selection to copy to the clipboard. Only available on Windows.
 *  </property>
 *  <property name="canCut" type="Boolean" readonly="Y">
 *   Returns true if the combobox is editable and there is a text selection 
 *   to cut to the clipboard. Only available on Windows.
 *  </property>
 *  <property name="canPaste" type="Boolean" readonly="Y">
 *   Returns true if the combobox is editable and there is text to paste 
 *   from the clipboard. Only available on Windows.
 *  </property>
 *  <property name="canRedo" type="Boolean" readonly="Y">
 *   Returns true if the combobox is editable and the last undo can be redone. 
 *   Only available on Windows.
 *  </property>
 *  <property name="canUndo" type="Boolean" readonly="Y">
 *   Returns true if the combobox is editable and the last edit can be undone. 
 *   Only available on Windows.
 *  </property>
 *	<property name="value" type=WXJS_TYPE_STRING>
 *	 Gets/Sets the text field
 *  </property>
 *  <property name="insertionPoint" type=WXJS_TYPE_NUMBER>
 *	 Gets/Sets the insertion point of the text field
 *  </property>
 *	<property name="lastPosition" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Gets the last position of the text field
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ComboBox)
  WXJS_PROPERTY(P_VALUE, "value")
  WXJS_PROPERTY(P_INSERTION_POINT, "insertionPoint")
  WXJS_READONLY_PROPERTY(P_LAST_POSITION, "lastPosition")
  WXJS_READONLY_PROPERTY(P_CAN_COPY, "canCopy")
  WXJS_READONLY_PROPERTY(P_CAN_CUT, "canCut")
  WXJS_READONLY_PROPERTY(P_CAN_PASTE, "canPaste")
  WXJS_READONLY_PROPERTY(P_CAN_REDO, "canRedo")
  WXJS_READONLY_PROPERTY(P_CAN_UNDO, "canUndo")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxComboBox, ComboBox)
	switch (id) 
	{
	case P_CAN_COPY:
		ToJSVal(cx, vp,p->CanCopy());
		break;
	case P_CAN_CUT:
		ToJSVal(cx, vp,p->CanCut());
		break;
	case P_CAN_PASTE:
		ToJSVal(cx, vp,p->CanPaste());
		break;
	case P_CAN_REDO:
		ToJSVal(cx, vp,p->CanRedo());
		break;
	case P_CAN_UNDO:
		ToJSVal(cx, vp,p->CanUndo());
		break;
	case P_VALUE:
		ToJSVal(cx, vp,p->GetValue());
		break;
	case P_INSERTION_POINT:
		ToJSVal(cx, vp,p->GetInsertionPoint());
		break;
	case P_LAST_POSITION:
		ToJSVal(cx, vp,p->GetLastPosition());
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxComboBox, ComboBox)
	switch (id) 
	{
	case P_VALUE:
		{
			wxString value;
			FromJS(cx, vp, value);
			p->SetValue(value);
			break;
		}
	case P_INSERTION_POINT:
		{
			int point;
			if ( FromJS(cx, vp, point) )
				p->SetInsertionPoint(point);
			break;
		}
	}
	return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxComboBox, ComboBox)
	ControlWithItems::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxComboBox, ComboBox)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    ComboBoxEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxComboBox, ComboBox)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  ComboBoxEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <constants>
 *	<type name="Style">
 *	 <constant>SIMPLE</constant>
 *	 <constant>DROPDOWN</constant>
 *	 <constant>READONLY</constant>
 *	 <constant>SORT</constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(ComboBox)
  WXJS_CONSTANT(wxCB_, SIMPLE)
  WXJS_CONSTANT(wxCB_, DROPDOWN)
  WXJS_CONSTANT(wxCB_, READONLY)
  WXJS_CONSTANT(wxCB_, SORT)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *    The parent of the wxComboBox
 *   </arg>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  A window identifier. Use -1 when you don't need it
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING default="">
 *	  The default text of the text field
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *	  The position of the control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *	  The size of the control.
 *   </arg>
 *   <arg name="Items" type="Array" default="null">
 *	  An array of Strings to initialize the control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  The window style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null">
 *    A validator
 *   </arg>
 *  </function>
 *  <desc>
 *	 Constructs a new wxComboBox object
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxComboBox, ComboBox)

  wxComboBox *p = new wxComboBox();
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
	
WXJS_BEGIN_DESTRUCTOR(wxComboBox, ComboBox)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(ComboBox)
  WXJS_METHOD("create", create, 2)
  WXJS_METHOD("copy", copy, 0)
  WXJS_METHOD("cut", cut, 0)
  WXJS_METHOD("paste", paste, 0)
  WXJS_METHOD("replace", replace, 3)
  WXJS_METHOD("remove", remove, 2)
  WXJS_METHOD("redo", redo, 0)
  WXJS_METHOD("undo", undo, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *    The parent of the wxComboBox
 *   </arg>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  A window identifier. Use -1 when you don't need it
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING default="">
 *	  The default text of the text field
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *	  The position of the control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *	  The size of the control.
 *   </arg>
 *   <arg name="Items" type="Array" default="null">
 *	  An array of Strings to initialize the control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  The window style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null">
 *    A validator
 *   </arg>
 *  </function>
 *  <desc>
 *	 Creates a wxComboBox
 *  </desc>
 * </method>
 */
JSBool ComboBox::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
 
JSBool ComboBox::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxComboBox *p = GetPrivate(cx, obj);
	*vp = JSVAL_FALSE;

	
	int argIndex = 0;
	int style = 0;
	StringsPtr items;
	wxString text;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(3, 8);

	*rval = JSVAL_TRUE;

	switch(argc)
	{
	case 8:
		val = Validator::GetPrivate(cx, argv[7]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 8, "Validator");
			return JS_FALSE;
		}
	case 7:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
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
		wxWindow *parent = NULL;
		int id;
		wxString text;


		
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

		if ( p->Create(parent, id, text, *(apPoint.get()), *(apSize.get()), 
						items.GetCount(), items.GetStrings(), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

  return JS_TRUE;
}
/***
 * <method name="copy">
 *	<function />
 *  <desc>
 *	 Copies the selected text to the clipboard
 *  </desc>
 * </method>
 */
JSBool ComboBox::copy(JSContext *cx, unsigned argc, JS::Value *vp)
{
 
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
   wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->Copy();

	return JS_TRUE;
}

/***
 * <method name="cut">
 *	<function />
 *  <desc>
 *	 Copies the selected text to the clipboard and removes the selected text
 *  </desc>
 * </method>
 */
JSBool ComboBox::cut(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->Cut();

	return JS_TRUE;
}

/***
 * <method name="paste">
 *	<function />
 *  <desc>
 *	 Pastes the content of the clipboard in the text field.
 *  </desc>
 * </method>
 */
JSBool ComboBox::paste(JSContext *cx, unsigned argc, JS::Value *vp)
{
 
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
   wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->Paste();

	return JS_TRUE;
}

/***
 * <method name="redo">
 *	<function />
 *  <desc>
 *   Redoes the last undo in the text field. Windows only.
 *  </desc>
 * </method>
 */
JSBool ComboBox::redo(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->Redo();

	return JS_TRUE;
}

/***
 * <method name="remove">
 *	<function>
 *	 <arg name="From" type=WXJS_TYPE_NUMBER />
 *	 <arg name="To" type=WXJS_TYPE_NUMBER />
 *  </function>
 *	<desc>
 *   Removes the text between From and To
 *  </desc>
 * </method>
 */
JSBool ComboBox::remove(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
    long from = 0L;
	long to = 0L;
    if (    FromJS(cx, argv[0], from) 
         && FromJS(cx, argv[1], to) )
	{
		p->Remove(from, to);
		return JS_TRUE;
	}

    return JS_FALSE;
}

/***
 * <method name="replace">
 *	<function>
 *   <arg name="From" type=WXJS_TYPE_NUMBER />
 *	 <arg name="To" type=WXJS_TYPE_NUMBER />
 *	 <arg name="Text" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *	 Replaces the text between From and To with the given text
 *  </desc>
 * </method>
 */
JSBool ComboBox::replace(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int from;
	int to;
	wxString text;

    if (    FromJS(cx, argv[0], from)
         && FromJS(cx, argv[1], to)
         && FromJS(cx, argv[2], text) )
    {
    	p->Replace(from, to, text);
        return JS_TRUE;
    }
	return JS_FALSE;
}

/***
 * <method name="undo">
 *	<function />
 *  <desc>
 *	 Undoes the last edit in the text field. Windows only.
 *  </desc>
 * </method>
 */
JSBool ComboBox::undo(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxComboBox *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->Undo();

	return JS_TRUE;
}

/***
 * <events>
 *  <event name="onText">
 *	 Called when the text of the textfield is changed. 
 *	 The type of the argument that your handler receives is @wxCommandEvent.
 *  </event>
 *	<event name="onComboBox">
 *	 Called when an item is selected. The type of the argument 
 *	 that your handler receives is @wxCommandEvent.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxComboBox)
const wxString WXJS_COMBOBOX_EVENT = wxT("onComboBox");
const wxString WXJS_TEXT_EVENT = wxT("onText");
const wxString WXJS_TEXT_ENTER_EVENT = wxT("onTextEnter");

void ComboBoxEventHandler::OnText(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_TEXT_EVENT);
}

void ComboBoxEventHandler::OnTextEnter(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_TEXT_ENTER_EVENT);
}

void ComboBoxEventHandler::OnComboBox(wxCommandEvent &event)
{
	PrivCommandEvent::Fire<CommandEvent>(event, WXJS_COMBOBOX_EVENT);
}

void ComboBoxEventHandler::ConnectText(wxComboBox *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_TEXT_UPDATED, 
               wxCommandEventHandler(ComboBoxEventHandler::OnText));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, 
                  wxCommandEventHandler(ComboBoxEventHandler::OnText));
  }
}

void ComboBoxEventHandler::ConnectTextEnter(wxComboBox *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_TEXT_ENTER, 
               wxCommandEventHandler(ComboBoxEventHandler::OnTextEnter));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_TEXT_ENTER, 
                  wxCommandEventHandler(ComboBoxEventHandler::OnTextEnter));
  }
}

void ComboBoxEventHandler::ConnectComboBox(wxComboBox *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, 
               wxCommandEventHandler(ComboBoxEventHandler::OnComboBox));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, 
                  wxCommandEventHandler(ComboBoxEventHandler::OnComboBox));
  }
}

void ComboBoxEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_COMBOBOX_EVENT, ConnectComboBox);
  AddConnector(WXJS_TEXT_EVENT, ConnectText);
  AddConnector(WXJS_TEXT_ENTER_EVENT, ConnectTextEnter);
}
