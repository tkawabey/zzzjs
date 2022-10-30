/*
 * wxJavaScript - menubar.cpp
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
 * $Id: menubar.cpp 784 2007-06-25 18:34:22Z fbraem $
 */
// menubar.cpp
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

#include "js/gui/control/menubar.h"
#include "js/gui/control/menu.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/menubar</file>
 * <module>gui</module>
 * <class name="wxMenuBar">
 *	A menu bar is a series of menus accessible from the top of a frame.
 *	See @wxFrame#menuBar property, @wxMenu and @wxMenuItem.
 * </class>
 */
WXJS_INIT_CLASS(MenuBar, "MenuBar", 0)

/***
 * <properties>
 *	<property name="menuCount" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 The number of menus
 *  </property>
 *	<property name="menus" type="Array" readonly="Y">
 *   Returns all the menus belonging to the menubar.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(MenuBar)
  WXJS_READONLY_PROPERTY(P_MENUCOUNT, "menuCount")
  WXJS_READONLY_PROPERTY(P_MENUS, "menus")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxMenuBar, MenuBar)
	switch(id) 
	{
	case P_MENUCOUNT:
		{
			ToJSVal(cx, vp, p->GetMenuCount());
			break;
		}
	case P_MENUS:
		{
			uint32_t count = p->GetMenuCount();

			JSObject *objMenus = JS_NewArrayObject(cx, count, NULL);
			vp.set( OBJECT_TO_JSVAL(objMenus) );
			
			for (uint32_t i = 0; i < count; i++ )
			{
                JavaScriptClientData *data
                  = dynamic_cast<JavaScriptClientData*>(p->GetMenu(i));
                if ( data != NULL )
                {
				    jsval element = OBJECT_TO_JSVAL(data->GetObject());
				    JS_SetElement(cx, objMenus, i++, &element);
                }
			}
			break;
		}
	}
	return true;
WXJS_END_GET_PROP

/***
 * <constants>
 *	<type name="Styles">
 *	 <constant name="DOCKABLE">(wxGTK only)</constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(MenuBar)
  // Style constants
  WXJS_CONSTANT(wxMB_, DOCKABLE)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *	<function>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0" />
 *  </function>
 *  <desc>
 *	 Constructs a new wxMenuBar object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxMenuBar, MenuBar)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int style = 0;
    if (      argc == 1
         && ! FromJS(cx, argv[0], style) )
         return NULL;

    wxMenuBar *p = new wxMenuBar(style);
    SetPrivate(cx, obj, p);
    return p;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxMenuBar, MenuBar)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(MenuBar)
  WXJS_METHOD("append", append, 2)
  WXJS_METHOD("check", check, 2)
  WXJS_METHOD("enable", enable, 2)
  WXJS_METHOD("enableTop", enableTop, 2)
  WXJS_METHOD("getMenu", get_menu, 1)
  WXJS_METHOD("insert", insert, 3)
  WXJS_METHOD("findMenu", findMenu, 1)
  WXJS_METHOD("findMenuItem", findMenuItem, 2)
  WXJS_METHOD("getHelpString", getHelpString, 1)
  WXJS_METHOD("getLabel", getLabel, 1)
  WXJS_METHOD("getLabelTop", getLabelTop, 1)
  WXJS_METHOD("refresh", refresh, 0)
  WXJS_METHOD("remove", remove, 1)
  WXJS_METHOD("replace", replace, 3)
  WXJS_METHOD("setHelpString", setHelpString, 2)
  WXJS_METHOD("setLabel", setLabel, 2)
  WXJS_METHOD("setLabelTop", setLabelTop, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="append">
 *	<function>
 *   <arg name="Menu" type="@wxMenu" />
 *	 <arg name="Name" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 * 	 Adds the menu to the menubar
 *  </desc>
 * </method>
 */
JSBool MenuBar::append(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxMenu *menu = Menu::GetPrivate(cx, argv[0]);
    if ( menu == NULL )
        return JS_FALSE;

    wxString name;
    FromJS(cx, argv[1], name);

	*vp = ToJS(cx, p->Append(menu, name));
	return JS_TRUE;
}

/***
 * <method name="check">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    The menu item identifier
 *   </arg>
 *   <arg name="Switch" type="Boolean">
 *    If true, checks the menu item, otherwise the item is unchecked
 *   </arg>
 *  </function>
 *  <desc>
 *	 Checks/Unchecks the menu with the given id. Only use this when the
 *   menu bar has been associated with a @wxFrame; otherwise, 
 *   use the @wxMenu equivalent call.
 *  </desc>
 * </method>
 */
JSBool MenuBar::check(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;
	bool checked;

	if (    FromJS(cx, argv[0], id)
		 && FromJS(cx, argv[1], checked) )
	{
		p->Check(id, checked);
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="enable">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    The menu item identifier
 *   </arg>
 *   <arg name="Switch" type="Boolean">
 *    If true, enables the menu item, otherwise the item is disabled
 *   </arg>
 *  </function>
 *  <desc>
 *	 Enables/Disables the menu with the given id.
 *   Only use this when the menu bar has been associated with a 
 *   @wxFrame; otherwise, use the @wxMenu equivalent call.
 *  </desc>
 * </method>
 */
JSBool MenuBar::enable(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;
	bool sw;

	if (    FromJS(cx, argv[0], id)
		 && FromJS(cx, argv[1], sw) )
	{
		p->Enable(id, sw);
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="enableTop">
 *  <function>
 *	 <arg name="Pos" type=WXJS_TYPE_NUMBER>
 *    The position of the menu, starting from zero
 *   </arg>
 *   <arg name="Switch" type="Boolean">
 *    If true, enables the menu, otherwise the menu is disabled
 *   </arg>
 *  </function>
 *  <desc>
 *	 Enables or disables a whole menu.
 *   Only use this when the menu bar has been associated with a @wxFrame.
 *  </desc>
 * </method>
 */
JSBool MenuBar::enableTop(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;
	bool sw;

	if (    FromJS(cx, argv[0], id)
		 && FromJS(cx, argv[1], sw) )
	{
		p->EnableTop(id, sw);
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="findMenu">
 *	<function returns=WXJS_TYPE_NUMBER>
 *	 <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the menu
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the index of the menu with the given name. -1
 *   is returned when the menu is not found.
 *  </desc>
 * </method>
 */
JSBool MenuBar::findMenu(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxString name;
	FromJS(cx, argv[0], name);
	*vp = ToJS(cx, p->FindMenu(name));
	return JS_TRUE;
}

/***
 * <method name="findMenuItem">
 *	<function returns=WXJS_TYPE_NUMBER>
 *   <arg name="MenuName" type=WXJS_TYPE_STRING>
 *    The name of the menu
 *   </arg>
 *   <arg name="ItemName" type=WXJS_TYPE_STRING>
 *    The name of the menuitem.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Finds the menu item id for a menu name/menu item string pair.
 *   -1 is returned when nothing is found.
 *  </desc>
 * </method>
 */
JSBool MenuBar::findMenuItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxString menuName;
	wxString itemName;

	FromJS(cx, argv[0], menuName);
	FromJS(cx, argv[1], itemName);
	*vp = ToJS(cx, p->FindMenuItem(menuName, itemName));
	return JS_TRUE;
}

/***
 * <method name="getHelpString">
 *	<function returns=WXJS_TYPE_STRING>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the helpstring associated with the menu item or an empty
 *   String when the menu item is not found. See @wxMenuItem#help property
 *   and @wxMenu#getHelpString method.
 *  </desc>
 * </method>
 */
JSBool MenuBar::getHelpString(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;
	if ( FromJS(cx, argv[0], id) )
	{
		*vp = ToJS(cx, p->GetHelpString(id));
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="getLabel">
 *	<function returns=WXJS_TYPE_STRING>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the label associated with the menu item or an empty
 *   String when the menu item is not found.
 *   Use only after the menubar has been associated with a @wxFrame.
 *  </desc>
 * </method>
 */
JSBool MenuBar::getLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;
	if ( FromJS(cx, argv[0], id) )
	{
		*vp = ToJS(cx, p->GetLabel(id));
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="getLabelTop">
 *	<function returns=WXJS_TYPE_STRING>
 *	 <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    Position of the menu on the menu bar, starting from zero.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the menu label, or the empty string if the menu was not found.
 *   Use only after the menubar has been associated with a @wxFrame.
 *   See also @wxMenu#title and @wxMenuBar#setLabelTop
 *  </desc>
 * </method>
 */
JSBool MenuBar::getLabelTop(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int idx;
	if ( FromJS(cx, argv[0], idx) )
	{
//		*vp = ToJS(cx, p->GetLabelTop(idx));
		*vp = ToJS(cx, p->GetMenuLabel(idx));
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="getMenu">
 *	<function returns="@wxMenu">
 *	 <arg name="Index" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Returns the @wxMenu at the given index (zero-indexed).
 *  </desc>
 * </method>
 */
JSBool MenuBar::get_menu(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int idx;
	if ( FromJS(cx, argv[0], idx) )
	{
		wxMenu *menu = (wxMenu*) p->GetMenu(idx);
        if ( menu != NULL )
        {
          JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData*>(menu->GetClientObject());
          if ( data != NULL )
          {
    		*vp = OBJECT_TO_JSVAL(data->GetObject());
          }
		  return JS_TRUE;
        }
	}

	return JS_FALSE;
}

/***
 * <method name="insert">
 *	<function returns="Boolean">
 *	 <arg name="Pos" type=WXJS_TYPE_NUMBER>
 *    The position of the new menu in the menu bar
 *   </arg>
 *   <arg name="Menu" type="@wxMenu">
 *    The menu to add.
 *   </arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>
 *    The title of the menu.
 *   </arg>
 *  </function>
 *  <desc>
 * 	 Inserts the menu at the given position into the menu bar.
 *   Inserting menu at position 0 will insert it in the very beginning of it, 
 *   inserting at position @wxMenuBar#menuCount is the same as calling 
 *   @wxMenuBar#append.
 *  </desc>
 * </method>
 */
JSBool MenuBar::insert(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int pos;

    if ( ! FromJS(cx, argv[0], pos) )
        return JS_FALSE;

	wxMenu *menu = Menu::GetPrivate(cx, argv[1]);
    if ( menu == NULL )
        return JS_FALSE;

	wxString title;
    FromJS(cx, argv[2], title);

	p->Insert(pos, menu, title);
	return JS_TRUE;
}

/***
 * <method name="isChecked">
 *	<function returns="Boolean">
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns true when the menu item is checked.
 *   See @wxMenu#check method, @wxMenu#isChecked and @wxMenuItem#check property.
 *  </desc>
 * </method>
 */
JSBool MenuBar::isChecked(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int idx;
	if ( FromJS(cx, argv[0], idx) )
	{
		*vp = ToJS(cx, p->IsChecked(idx));
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="isEnabled">
 *	<function returns="Boolean">
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns true when the menu item is enabled.
 *   @wxMenu#enable method, @wxMenuItem#enable property and @wxMenuBar#enable
 *  </desc>
 * </method>
 */
JSBool MenuBar::isEnabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int idx;
	if ( FromJS(cx, argv[0], idx) )
	{
		*vp = ToJS(cx, p->IsEnabled(idx));
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="refresh">
 *	<function />
 *  <desc>
 * 	 Redraw the menu bar.
 *  </desc>
 * </method>
 */
JSBool MenuBar::refresh(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->Refresh();

	return JS_TRUE;
}

/***
 * <method name="remove">
 *	<function returns="Boolean">
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    The index of the menu to remove (zero-indexed).
 *   </arg>
 *  </function>
 *  <desc>
 *	 Removes the menu from the menu bar and returns the @wxMenu object.
 *   This function may be used together with @wxMenuBar#insert to change
 *   the menubar dynamically.
 *  </desc>
 * </method>
 */
JSBool MenuBar::remove(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int idx;
	if ( FromJS(cx, argv[0], idx) )
	{
		wxMenu *menu = p->Remove(idx);
        if ( menu != NULL )
        {
          JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData*>(menu->GetClientObject());
          if ( data != NULL )
            *vp = OBJECT_TO_JSVAL(data->GetObject());
        }
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="replace">
 *	<function returns="@wxMenu">
 *	 <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    The index of the menu to replace (zero-indexed).
 *   </arg>
 *   <arg name="Menu" type="@wxMenu">
 *    The new menu
 *   </arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>
 *    The title of the menu
 *   </arg>
 *  </function>
 *  <desc>
 *	 Replaces the menu at the given position with the new one.
 *  </desc>
 * </method>
 */
JSBool MenuBar::replace(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int pos;
    if ( ! FromJS(cx, argv[0], pos) )
        return JS_FALSE;

	wxMenu *menu = Menu::GetPrivate(cx, argv[1]);
    if ( menu == NULL )
        return JS_FALSE;

	wxString title;
    FromJS(cx, argv[2], title);

	wxMenu *oldMenu = p->Replace(pos, menu, title);
    if ( oldMenu == NULL )
    {
        *vp = JSVAL_VOID;
    }
    else
    {
      JavaScriptClientData *data 
        = dynamic_cast<JavaScriptClientData*>(oldMenu->GetClientObject());
      *vp = ( data == NULL ) ? JSVAL_VOID 
                               : OBJECT_TO_JSVAL(data->GetObject());
	}
	return JS_TRUE;
}

/***
 * <method name="setHelpString">
 *  <function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *   <arg name="Help" type=WXJS_TYPE_STRING>
 *    The help text
 *   </arg>
 *  </function>
 *  <desc>
 *	 Sets the help associated with a menu item.
 *   See @wxMenuItem#help property, @wxMenu#setHelpString method
 *  </desc>
 * </method>
 */
JSBool MenuBar::setHelpString(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;

	if ( ! FromJS(cx, argv[0], id) )
        return JS_FALSE;

	wxString str;
	FromJS(cx, argv[1], str);
	p->SetHelpString(id, str);
	return JS_TRUE;
}

/***
 * <method name="setLabel">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *   <arg name="Label" type=WXJS_TYPE_STRING>
 *    A new label
 *   </arg>
 *	</function>
 *  <desc>
 *   Sets the label of a menu item.
 *   Only use this when the menubar is associated with a @wxFrame
 *   @wxMenuItem#label property, @wxMenu#setLabel method
 *  </desc>
 * </method>
 */
JSBool MenuBar::setLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int id;

	if ( ! FromJS(cx, argv[0], id) )
        return JS_FALSE;

	wxString str;
	FromJS(cx, argv[1], str);
	
    p->SetLabel(id, str);
	
    return JS_TRUE;
}

/***
 * <method name="setLabelTop">
 *	<function>
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    A menu index (zero-indexed)
 *   </arg>
 *   <arg name="Label" type=WXJS_TYPE_STRING>
 *    A label for a menu
 *   </arg>
 *  </function>
 *  <desc>
 *	 Sets the label of a menu.
 *   Only use this when the menubar is associated with a @wxFrame
 *   See @wxMenu#title property
 *  </desc>
 * </method>
 */
JSBool MenuBar::setLabelTop(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuBar *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int idx;
	wxString str;

	if ( FromJS(cx, argv[0], idx) )
	{
		FromJS(cx, argv[1], str);
		//p->SetLabelTop(idx, str);
		p->SetLabel(idx, str);
		return JS_TRUE;
	}

	return JS_FALSE;
}
