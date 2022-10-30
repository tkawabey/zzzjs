/*
 * wxJavaScript - menuitem.cpp
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
 * $Id: menuitem.cpp 688 2007-04-27 20:45:09Z fbraem $
 */
// menuitem.cpp
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

#include "js/gui/misc/accentry.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/menuitem</file>
 * <module>gui</module>
 * <class name="wxMenuItem">
 *	A menu item represents an item in a popup menu. 
 *	Note that the majority of this class is only implemented under Windows so 
 *  far, but everything except fonts, colours and bitmaps can be achieved via 
 *  @wxMenu on all platforms.
 * </class>
 */
WXJS_INIT_CLASS(MenuItem, "MenuItem", 1)

/***
 * <properties>
 *	<property name="accel" type="@wxAcceleratorEntry">
 *	 Get/Set the accelerator.
 *  </property>
 *  <property name="backgroundColour" type="@wxColour">
 *  Get/Set the background colour of the item (Windows only)
 *  </property>
 *  <property name="bitmap" type="@wxBitmap">
 *	Get/Set the checked bitmap. (Windows only)
 *  </property>
 *  <property name="check" type="Boolean">
 *	 Check or uncheck the menu item.
 *  </property>
 *  <property name="checkable" type="Boolean">
 *	 Returns true if the item is checkable.
 *  </property>
 *  <property name="enable" type="Boolean">
 *	 Enables or disables the menu item.
 *  </property>
 *  <property name="font" type="@wxFont">
 *	 Get/Set the font. (Windows only)
 *  </property>
 *  <property name="help" type=WXJS_TYPE_STRING>
 *	 Get/Set the helpstring shown in the statusbar.
 *  </property>
 *  <property name="id" type=WXJS_TYPE_NUMBER>
 *	 Get/Set the id of the menu item
 *  </property>
 *  <property name="label" type=WXJS_TYPE_STRING readonly="Y">
 *	 Gets the text associated with the menu item without any accelerator
 *	 characters it might contain.
 *  </property>
 *  <property name="marginWidth" type=WXJS_TYPE_NUMBER>
 *	 Get/Set the width of the menu item checkmark bitmap (Windows only).
 *  </property>
 *  <property name="menu" type="@wxMenu" readonly="Y">
 *   Gets the menu that owns this item.
 *  </property>
 *  <property name="separator" type="Boolean">
 *	 Returns true if the item is a separator.
 *  </property>
 *  <property name="subMenu" type="@wxMenu" readonly="Y">
 *	 Gets the submenu associated with the menu item
 *  </property>
 *  <property name="text" type=WXJS_TYPE_STRING>
 *	 Get/Set the text associated with the menu item with any accelerator
 *   characters it may contain.
 *  </property>
 *  <property name="textColour"	type="@wxColour">
 *	 Get/Set the text colour. (Windows Only)
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(MenuItem)
  WXJS_READONLY_PROPERTY(P_LABEL, "label")
  WXJS_PROPERTY(P_ACCEL, "accel")
  WXJS_PROPERTY(P_TEXT, "text")
  WXJS_PROPERTY(P_CHECK, "check")
  WXJS_READONLY_PROPERTY(P_CHECKABLE, "checkable")
  WXJS_PROPERTY(P_ENABLE, "enable")
  WXJS_PROPERTY(P_HELP, "help")
  WXJS_PROPERTY(P_ID, "id")
  WXJS_PROPERTY(P_FONT, "font")
  WXJS_PROPERTY(P_TEXT_COLOUR, "textColour")
  WXJS_PROPERTY(P_BITMAP, "bitmap")
  WXJS_PROPERTY(P_MARGIN_WIDTH, "marginWidth")
  WXJS_READONLY_PROPERTY(P_SUB_MENU, "subMenu")
  WXJS_PROPERTY(P_BG_COLOUR, "backgroundColour")
  WXJS_READONLY_PROPERTY(P_MENU, "menu")
  WXJS_READONLY_PROPERTY(P_SEPARATOR, "separator")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxMenuItem, MenuItem)
	switch (id) 
	{
	case P_ACCEL:
      vp.set( AcceleratorEntry::CreateObject(cx, p->GetAccel()) 
		  );
      break;
	case P_BG_COLOUR:
	  #ifdef __WXMSW__
	    vp.set( Colour::CreateObject(cx, new wxColour(p->GetBackgroundColour())) 
			);
	  #endif
	  break;
	case P_LABEL:
      ToJSVal(cx, vp, p->GetItemLabel());
      break;
	case P_TEXT:
      ToJSVal(cx, vp, p->GetItemLabelText());
      break;
	case P_CHECK:
      ToJSVal(cx, vp, p->IsChecked());
      break;
	case P_CHECKABLE:
      ToJSVal(cx, vp, p->IsCheckable());
      break;
	case P_ENABLE:
      ToJSVal(cx, vp, p->IsEnabled());
      break;
	case P_HELP:
      ToJSVal(cx, vp, p->GetHelp());
      break;
	case P_ID:
      ToJSVal(cx, vp, p->GetId());
      break;
	case P_MARGIN_WIDTH:
      #ifdef __WXMSW__
        ToJSVal(cx, vp, p->GetMarginWidth());
      #endif
      break;
	case P_SUB_MENU:
        {
          wxMenu *subMenu = p->GetSubMenu();
          JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData*>(subMenu->GetClientObject());
          vp.set( (data->GetObject() == NULL) ? JSVAL_NULL 
                                            : OBJECT_TO_JSVAL(data->GetObject()) 
											);
          break;
	    }
	case P_MENU:
        {
          wxMenu *menu = p->GetMenu();
          JavaScriptClientData *data 
            = dynamic_cast<JavaScriptClientData*>(menu->GetClientObject());
          vp.set( (data->GetObject() == NULL) ? JSVAL_NULL 
                                            : OBJECT_TO_JSVAL(data->GetObject()) 
											);
          break;
        }
	case P_FONT:
		#ifdef __WXMSW__
	        vp.set( Font::CreateObject(cx, new wxFont(p->GetFont())) );
	    #endif
		break;
	case P_BITMAP:
		vp.set( Bitmap::CreateObject(cx, new wxBitmap(p->GetBitmap())) );
		break;
	case P_TEXT_COLOUR:
		#ifdef __WXMSW__
			vp.set( Colour::CreateObject(cx, new wxColour(p->GetTextColour())) );
		#endif
		break;
	case P_SEPARATOR:
		  ToJSVal(cx, vp, p->IsSeparator());
		  break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxMenuItem, MenuItem)
	switch(id) 
	{
	case P_ACCEL:
		{
			wxAcceleratorEntry *entry = AcceleratorEntry::GetPrivate(cx, vp);
            if ( entry != NULL )
                p->SetAccel(entry);
			break;
		}
	case P_BG_COLOUR:
		{
			#ifdef __WXMSW__
				wxColour *colour = Colour::GetPrivate(cx, vp);
				if ( colour != NULL )
					p->SetBackgroundColour(*colour);
			#endif
			break;
		}
	case P_TEXT:
		{
			wxString str;
			FromJS(cx, vp, str);
			//p->SetText(str);
			p->SetItemLabel(str);
			break;
		}
	case P_CHECK:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
			  p->Check(value);
			break;
		}
	case P_ENABLE:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
				p->Enable(value);
			break;
		}
	case P_HELP:
		{
			wxString str;
			FromJS(cx, vp, str);
			p->SetHelp(str);
			break;
		}
	case P_MARGIN_WIDTH:
		{
			#ifdef __WXMSW__
				int value;
				if ( FromJS(cx, vp, value) )
					p->SetMarginWidth(value);
			#endif
			break;
		}
	case P_FONT:
		{
			#ifdef __WXMSW__
				zzzJsPtr<wxFont> apFont;
				if ( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true )
					p->SetFont(*(apFont.get()));
			#endif
			break;
		}
	case P_BITMAP:
		{
			#ifdef __WXMSW__
				zzzJsPtr<wxBitmap> apBitmap;
				if ( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true )
					p->SetBitmaps(*(apBitmap.get()), wxNullBitmap);
			#endif
			break;
		}
	case P_TEXT_COLOUR:
		{
			#ifdef __WXMSW__
				wxColour *colour = Colour::GetPrivate(cx, vp);
				if ( colour != NULL )
					p->SetTextColour(*colour);
			#endif
			break;
		}
	}
	return true;
WXJS_END_SET_PROP

WXJS_BEGIN_METHOD_MAP(MenuItem)
  WXJS_METHOD("setBitmaps", setBitmaps, 2)
WXJS_END_METHOD_MAP()

/***
 * <ctor>
 *	<function>
 *	 <arg name="Menu" type="@wxMenu">Menu that owns the item</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER default="0">Identifier for this item</arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING default="">The text for the menu item</arg>
 *   <arg name="Help" type=WXJS_TYPE_STRING default="">The help message shown in
*     the statusbar</arg>
 *   <arg name="Checkable" type="Boolean" default="false">
 *    Indicates if the menu item can be checked or not.
 *   </arg>
 *   <arg name="SubMenu" type="@wxMenu" default="null">
 *    Indicates that the menu item is a submenu</arg>
 *  </function>
 *  <desc>
 *	 Constructs a new wxMenuItem object
 *  </desc>
 * </ctor>
 */
 
WXJS_BEGIN_CONSTRUCTOR(wxMenuItem, MenuItem)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc > 6 )
        argc = 6;

    int id = 0;
    wxString text = wxEmptyString;
    wxString help = wxEmptyString;
    bool checkable = false;
    wxMenu *subMenu = NULL;

    switch(argc)
    {
    case 6:
        if ( (subMenu = Menu::GetPrivate(cx, argv[5])) == NULL )
            break;
        // Fall through
    case 5:
        if ( ! FromJS(cx, argv[4], checkable) )
            break;
        // Fall through
    case 4:
        FromJS(cx, argv[3], help);
        // Fall through
    case 3:
        FromJS(cx, argv[2], text);
        // Fall through
    case 2:
        if ( ! FromJS(cx, argv[1], id) )
            break;
        // Fall through
    default:
        wxMenu *menu = Menu::GetPrivate(cx, argv[0]);
        if ( menu != NULL )
        {
            wxItemKind itemkind = wxITEM_NORMAL;
            if ( checkable )
                itemkind = wxITEM_CHECK; 
        #if wxCHECK_VERSION(2,7,0)
            return new wxMenuItem(menu, id, text, help, itemkind, subMenu);
		#else
            return new wxMenuItem(menu, id, text, help, checkable, subMenu);
		#endif
        }
    }

    return NULL;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxMenuItem, MenuItem)
WXJS_END_DESTRUCTOR
//void MenuItem::Destruct(JSContext* WXUNUSED(cx), wxMenuItem* WXUNUSED(p))



/***
 * <method name="setBitmaps">
 *	<function>
 *	 <arg name="BitmapChecked" type="@wxBitmap" />
 *   <arg name="BitmapUnchecked" type="@wxBitmap" default="null" />
 *  </function>
 *  <desc>
 *   Sets the checked/unchecked bitmaps for the menu item (Windows only).
 *   The first bitmap is also used as the single bitmap for uncheckable menu items.
 *  </desc>
 * </method>
 */
JSBool MenuItem::setBitmaps(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxMenuItem *p = MenuItem::GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	#ifdef __WXMSW__
	
		zzzJsPtr<wxBitmap> apBitmap;
		zzzJsPtr<wxBitmap> apBitmap2;

		if ( apBitmap.set(Bitmap::getObject2Instance(cx, argv[0], apBitmap.bAllocation)) == true  )
		{
			wxBitmap bmp2 = wxNullBitmap;
			if ( argc > 1 )
			{
				if ( apBitmap2.set(Bitmap::getObject2Instance(cx, argv[2], apBitmap2.bAllocation)) == true  )
				{
					return JS_FALSE;
				}
			}
	
			p->SetBitmaps(*(apBitmap.get()), apBitmap2.get() != NULL ? *(apBitmap2.get()) : wxNullBitmap );
			return JS_TRUE;
		}
	#else
		return JS_TRUE;
	#endif

	return JS_FALSE;
}
