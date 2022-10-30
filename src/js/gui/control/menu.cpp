/*
 * wxJavaScript - menu.cpp
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
 * $Id: menu.cpp 783 2007-06-24 20:36:30Z fbraem $
 */
// menu.cpp
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




#include "js/gui/control/menu.h"
#include "js/gui/control/menuitem.h"

#include "js/gui/event/jsevent.h"

#include "js/gui/event/command.h"

using namespace zzzJs;
using namespace zzzJs::gui;
/*
Menu::~Menu()
{
	// When the menu is attached, it's destroyed by wxWindows
	// Setting the private data to NULL, will prevent an access-violation.
	if ( IsAttached() )
	{
		JS_SetPrivate(GetContext(), GetObject(), NULL);
	}
}
*/
/***
 * <file>control/menu</file>
 * <module>gui</module>
 * <class name="wxMenu">
 *	A menu is a popup (or pull down) list of items, 
 *	one of which may be selected before the menu goes away 
 *	(clicking elsewhere dismisses the menu). Menus may 
 *	be used to construct either menu bars or popup menus.
 *	See @wxMenuBar and @wxFrame#menuBar property.
 * </class>
 */
WXJS_INIT_CLASS(Menu, "Menu", 0)

/***
 * <properties>
 *	<property name="actions" type="Array">
 *   An array containing the function callbacks. A function will be called when a menu item is selected.
 *   Use @wxMenuItem#id id as index of the array. It is possible to change the function
 *   after the menu item is appended to the menu.
 *  </property>
 *	<property name="menuItemCount" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the number of menu items.
 *  </property>
 *	<property name="menuItems" type="Array" readonly="Y">
 *   Returns all the menu items.
 *  </property>
 *	<property name="title" type=WXJS_TYPE_STRING>
 *   Get/Set the title of the menu
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Menu)
  WXJS_READONLY_PROPERTY(P_MENU_ITEM_COUNT, "menuItemCount")
  WXJS_READONLY_PROPERTY(P_MENU_ITEMS, "menuItems")
  WXJS_PROPERTY(P_TITLE, "title")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxMenu, Menu)
{
	switch (id) 
	{
	case P_MENU_ITEM_COUNT:
	  {
		  ToJSVal(cx, vp, p->GetMenuItemCount());
		  break;
	  }
	case P_MENU_ITEMS:
		{
			wxMenuItemList &list = p->GetMenuItems();
			uint32_t count = list.GetCount();

			JSObject *objItems = JS_NewArrayObject(cx, count, NULL);
			vp.set( OBJECT_TO_JSVAL(objItems) );
			
			uint32_t i = 0;
			for (wxMenuItemList::Node *node = list.GetFirst(); 
                 node; 
                 node = node->GetNext() )
			{
                jsval element = MenuItem::CreateObject(cx, node->GetData());
				JS_SetElement(cx, objItems, i++, &element);
			}

			break;
		}
	case P_TITLE:
		ToJSVal(cx, vp, p->GetTitle());
		break;
	}
	return true;
}
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxMenu, Menu)
{
	if ( id == P_TITLE )
	{
		wxString title;
		FromJS(cx, vp, title);
		p->SetTitle(title);
	}

	return true;
}
WXJS_END_SET_PROP

/***
 * <constants>
 *	<type name="Styles">
 *	 <constant name="TEAROFF">(wxGTK only)</constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Menu)
  // Style constants
  WXJS_CONSTANT(wxMENU_, TEAROFF)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *	<function>
 *	 <arg name="Title" type=WXJS_TYPE_STRING default="">
 *	  A title for the popup menu
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  A menu style
 *   </arg>
 *  </function>
 *	<function>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  A menu style
 *   </arg>
 *  </function>
 *	<desc>
 *   Creates a new wxMenu object
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxMenu, Menu)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    if ( argc > 2 )
        argc = 2;

    wxMenu *p = NULL;

    switch(argc)
    {
    case 2:
        {
            wxString title;
            int style;

            FromJS(cx, argv[0], title);
            if ( FromJS(cx, argv[1], style) )
                p = new wxMenu(title, style);
            break;
        }
        break;
    case 1:
        if ( JSVAL_IS_INT(argv[0]) )
        {
            int style = 0;
            if ( FromJS(cx, argv[0], style) )
                p =  new wxMenu(style);
        }
        else
        {
            wxString title;
            FromJS(cx, argv[0], title);
            p = new wxMenu(title);
        }
        break;
    default:
        p =  new wxMenu();
    }

    if ( p != NULL )
    {
      p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
      JSObject *objActionArray = JS_NewArrayObject(cx, 0, NULL);
      JS_DefineProperty(cx, obj, "actions", OBJECT_TO_JSVAL(objActionArray), 
                        NULL, NULL, JSPROP_ENUMERATE |JSPROP_PERMANENT);
    }

    return p;
}
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxMenu, Menu)
{
}
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Menu)
  WXJS_METHOD("append", append, 3)
  WXJS_METHOD("appendCheckItem", append_checkItem, 3)
  WXJS_METHOD("appendRadioItem", append_radioItem, 3)
  WXJS_METHOD("appendSubMenu", append_subMenu, 3)
  WXJS_METHOD("appendSeparator", append_separator, 0)
  WXJS_METHOD("deleteItem", delete_item, 1)
  WXJS_METHOD("destroy", destroy, 0)
  WXJS_METHOD("findItem", find_item, 1)
  WXJS_METHOD("getHelpString", getHelpString, 1)
  WXJS_METHOD("getLabel", getLabel, 1)
  WXJS_METHOD("newColumn", new_column, 0)
  WXJS_METHOD("check", check, 2)
  WXJS_METHOD("enable", enable, 2)
  WXJS_METHOD("getItem", getItem, 1)
  WXJS_METHOD("insert", insert, 2)
  WXJS_METHOD("isChecked", isChecked, 1)
  WXJS_METHOD("isEnabled", isEnabled, 1)
  WXJS_METHOD("remove", remove, 1)
  WXJS_METHOD("setHelpString", setHelpString, 2)
  WXJS_METHOD("setLabel", setLabel, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="append">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item.
 *   </arg>
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *	  The name of the menu item.
 *   </arg>
 *   <arg name="Action" type="Function">
 *	  The function that is called when the menu item is selected. The argument to the
 *	  function will be @wxCommandEvent.
 *   </arg>
 *	 <arg name="HelpString" type=WXJS_TYPE_STRING default="">
 *	  Message which is shown in the statusbar.
 *   </arg>
 *	 <arg name="Checkable" type="Boolean" default="false">
 *	  Indicates if the menu item can be checked or not.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Appends a new menu item to the menu.
 *  </desc>
 * </method>
 */
JSBool Menu::append(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

    wxString help = wxEmptyString;
    bool checkable = false;

    switch(argc)
    {
    case 5:
        if ( ! FromJS(cx, argv[4], checkable) )
            break;
        // Fall through
    case 4:
        FromJS(cx, argv[3], help);
        // Fall through
    default:
        wxString name;
        FromJS(cx, argv[1], name);

        int id = 0;

        if ( ! FromJS(cx, argv[0], id) )
            break;

	    p->Append(id, name, help, checkable);
		
		if( argc >= 3 ) {
			jsval actions;
			if ( JS_GetProperty(cx, obj, "actions", &actions) == JS_TRUE )
			{
				JS_SetElement(cx, JSVAL_TO_OBJECT(actions), id, &argv[2]);
			}
		}
        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool Menu::append_checkItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

    wxString help = wxEmptyString;

    switch(argc)
    {
    case 4:
        FromJS(cx, argv[3], help);
        // Fall through
    default:
        wxString name;
        FromJS(cx, argv[1], name);

        int id = 0;

        if ( ! FromJS(cx, argv[0], id) )
            break;

	    p->AppendCheckItem(id, name, help);
		
		if( argc >= 3 ) {
			jsval actions;
			if ( JS_GetProperty(cx, obj, "actions", &actions) == JS_TRUE )
			{
				JS_SetElement(cx, JSVAL_TO_OBJECT(actions), id, &argv[2]);
			}
		}
        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool Menu::append_radioItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

    wxString help = wxEmptyString;

    switch(argc)
    {
    case 4:
        FromJS(cx, argv[3], help);
        // Fall through
    default:
        wxString name;
        FromJS(cx, argv[1], name);

        int id = 0;

        if ( ! FromJS(cx, argv[0], id) )
            break;

	    p->AppendRadioItem(id, name, help);

		if( argc >= 3 ) {
			jsval actions;
			if ( JS_GetProperty(cx, obj, "actions", &actions) == JS_TRUE )
			{
				JS_SetElement(cx, JSVAL_TO_OBJECT(actions), id, &argv[2]);
			}
		}
        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool Menu::append_subMenu(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxMenu* pMenu = NULL;

    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

    wxString help = wxEmptyString;

    switch(argc)
    {
    case 3:
        FromJS(cx, argv[2], help);
        // Fall through
    default:
        wxString name;
        FromJS(cx, argv[1], name);

        int id = 0;

		if( Menu::HasPrototype(cx, argv[0]) == false )
		{
			break;
		}
		pMenu = Menu::GetPrivate(cx, argv[0], false);
		if( pMenu == NULL ) 
		{
			break;
		}

	    p->AppendSubMenu(pMenu, name, help);

        return JS_TRUE;
    }

    return JS_FALSE;
}
/***
 * <method name="check">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item.
 *   </arg>
 *   <arg name="Check" type="Boolean">
 *	  Check (true) or uncheck (false) the item
 *   </arg>
 *  </function>
 *  <desc>
 *	 Checks or unchecks the menu item.
 *  </desc>
 * </method>
 */
JSBool Menu::check(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int id = 0;
	bool check = false;

	if (    FromJS(cx, argv[0], id)
		 && FromJS(cx, argv[1], check) )
	{
		p->Check(id, check);
        return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="enable">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item.
 *   </arg>
 *	 <arg name="Enable" type="Boolean">
 *	  Enables (true) or disables (false) the item
 *   </arg>
 *  </function>
 *  <desc>
 *	 Enables or disables the menu item.
 *  </desc>
 * </method>
 */
JSBool Menu::enable(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int id = 0;
	bool flag = false;

	if (    FromJS(cx, argv[0], id)
		 && FromJS(cx, argv[1], flag) )
	{
		p->Enable(id, flag);
    	return JS_TRUE;
	}

    return JS_FALSE;
}

/***
 * <method name="deleteItem">
 *	<function>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="MenuItem" type="@wxMenuItem">
 *    A menu item.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Deletes the menu item from the menu. If the item is a submenu, 
 *   it will not be deleted. Use @wxMenu#destroy if you want to delete a submenu.
 *  </desc>
 * </method>
 */
JSBool Menu::delete_item(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int id;
	if ( FromJS(cx, argv[0], id) )
	{
		p->Delete(id);
		return JS_TRUE;
	}
	else
	{
        wxMenuItem *item = MenuItem::GetPrivate(cx, argv[0]);
		if ( item != NULL )
		{
			p->Delete(item);
			return JS_TRUE;
		}
	}

	return JS_FALSE;
}

/***
 * <method name="findItem">
 *	<function returns=WXJS_TYPE_NUMBER>
 *	 <arg name="Search" type=WXJS_TYPE_STRING>
 *	  The search string
 *   </arg>
 *  </function>
 *  <desc>
 *	 Searches the menu item with the given search string and
 *   returns its identifier. -1 is returned when the item is not found.
 *   Any special menu codes are stripped out of source and target strings before matching.
 *  </desc>
 * </method>
 */
JSBool Menu::find_item(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	wxString search;
	FromJS(cx, argv[0], search);
	*vp = ToJS(cx, p->FindItem(search));

	return JS_TRUE;
}

/***
 * <method name="break">
 *	<function />
 *  <desc>
 *	 Adds a new column
 *  </desc>
 * </method>
 */
JSBool Menu::new_column(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	p->Break();
	
	return JS_TRUE;
}

/***
 * <method name="appendSeparator">
 *	<function />
 *  <desc>
 *	 Adds a separator
 *  </desc>
 * </method>
 */
JSBool Menu::append_separator(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = Menu::GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	p->AppendSeparator();
	
	return JS_TRUE;
}

/***
 * <method name="getHelpString">
 *	<function returns=WXJS_TYPE_STRING>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the helpstring of the menu item with the given id.
 *   See @wxMenu#setHelpString and @wxMenuItem#help property
 *  </desc>
 * </method>
 */
JSBool Menu::getHelpString(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
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
 *	  The id of the menu item
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the label of the menu item with the given id.
 *   See @wxMenu#setLabel and @wxMenuItem#label property.
 *  </desc>
 * </method>
 */
JSBool Menu::getLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
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
 * <method name="getItem">
 *	<function returns="@wxMenuItem">
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the @wxMenuItem object of the menu item with the given id.
 *  </desc>
 * </method>
 */
JSBool Menu::getItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;
	
	int id;
	if ( FromJS(cx, argv[0], id) )
	{
		wxMenuItem *item = p->FindItem(id);
        *vp = ( item == NULL ) ? JSVAL_NULL : MenuItem::CreateObject(cx, item);
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="destroy">
 *	<function>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *	  The id of the menu item
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="MenuItem" type="@wxMenuItem" />
 *  </function>
 *  <desc>
 *	 Deletes the menu item from the menu. If the item is a submenu, it will be deleted.
 *   Use @wxMenu#remove if you want to keep the submenu (for example, to reuse it later).
 *  </desc>
 * </method>
 */
JSBool Menu::destroy(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int id;
	if ( FromJS(cx, argv[0], id) )
	{
		p->Destroy(id);
		return JS_TRUE;
	}
	else if ( argv[0].isObject() )
	{
        wxMenuItem *item = MenuItem::GetPrivate(cx, argv[0]);
		if ( item != NULL )
		{
			p->Destroy(item);
			return JS_TRUE;
		}
	}

	return JS_FALSE;
}

/***
 * <method name="insert">
 *  <function>
 *   <arg name="Pos" type=WXJS_TYPE_NUMBER />
 *   <arg name="MenuItem" type="@wxMenuItem" />
 *  </function>
 *  <desc>
 *   Inserts the given item before the position pos.
 *   Inserting the item at the position @wxMenu#menuItemCount
 *   is the same as appending it.
 *  </desc>
 * </method>
 */
JSBool Menu::insert(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int pos;
	if ( FromJS(cx, argv[0], pos)
		  && argv[1].isObject() )
	{
        wxMenuItem *item = MenuItem::GetPrivate(cx, argv[1]);
		if ( item != NULL )
		{
			return JS_TRUE;
		}
	}

	return JS_FALSE;
}

/***
 * <method name="isChecked">
 *	<function returns="Boolean">
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns true when the menu item is checked.
 *  </desc>
 * </method>
 */
JSBool Menu::isChecked(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
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
 *  <function returns="Boolean">
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns true when the menu item is enabled.
 *  </desc>
 * </method>
 */
JSBool Menu::isEnabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
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
 * <method name="remove">
 *	<function returns="@wxMenuItem">
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An identifier of a menu item.
 *   </arg>
 *  </function>
 *  <function returns="@wxMenuItem">
 *   <arg name="MenuItem" type="@wxMenuItem" />
 *  </function>
 *  <desc>
 * 	 Removes the menu item from the menu but doesn't delete the object.
 *   This allows to reuse the same item later by adding it back to the menu 
 *   (especially useful with submenus).
 *  </desc>
 * </method>
 */
JSBool Menu::remove(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	wxMenuItem *item = NULL;
	int id;

	if ( FromJS(cx, argv[0], id) )
	{
		item = p->Remove(id);
	}
	else if ( argv[0].isObject() )
	{
        wxMenuItem *removeItem = MenuItem::GetPrivate(cx, argv[1]);
        if ( removeItem != NULL )
		    item = p->Remove(removeItem);
	}
	else
	{
		return JS_FALSE;
	}

    *vp = ( item == NULL ) ? JSVAL_VOID : MenuItem::CreateObject(cx, item);
	return JS_TRUE;

}

/***
 * <method name="setHelpString">
 *	<function>
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    A menu item identifier.
 *   </arg>
 *   <arg name="Help" type=WXJS_TYPE_STRING>
 *    The help text
 *   </arg>
 *  </function>
 *  <desc>
 *	 Sets the help associated with a menu item.
 *   See @wxMenuItem#help property and @wxMenuBar#setHelpString method.
 *  </desc>
 * </method>
 */
JSBool Menu::setHelpString(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int id;
	wxString help;
	
	if ( FromJS(cx, argv[0], id) )
	{
		FromJS(cx, argv[1], help);
		p->SetHelpString(id, help);
	}

	return JS_FALSE;
}

/***
 * <method name="setLabel">
 *	 <function>
 *    <arg name="Id" type=WXJS_TYPE_NUMBER>
 *     A menu item identifier.
 *    </arg>
 *    <arg name="Label" type=WXJS_TYPE_STRING>
 *     A new label
 *    </arg>
 *   </function>
 *	 <desc>
 *    Sets the label of a menu item.
 *    See @wxMenuItem#label property and @wxMenuBar#setLabel method
 *   </desc>
 * </method>
 */
JSBool Menu::setLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


    wxMenu *p = GetPrivate(cx, obj);	
	if ( p == NULL )
		return JS_FALSE;

	int id;
	wxString label;
	
	if ( FromJS(cx, argv[0], id) )
	{
		FromJS(cx, argv[1], label);
		p->SetLabel(id, label);
		return JS_TRUE;
	}

	return JS_FALSE;
}
