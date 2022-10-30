/*
 * wxJavaScript - accentry.cpp
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
 * $Id: accentry.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// accentry.cpp

// http://docs.wxwidgets.org/3.0/classwx_accelerator_entry.html
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
#include "js/common/jsutil.h"
#include "js/gui/misc/accentry.h"
#include "js/gui/control/menuitem.h"



using namespace zzzJs;
using namespace zzzJs::gui;


#define PROP_FLAGS    "flags"
#define PROP_KEYCODE  "keyCode"
#define PROP_COMMAND  "command"
#define PROP_MENUITEM "menuItem"
#define PROP_IS_OK    "isOk"

/***
 * <file>misc/accentry</file>
 * <module>gui</module>
 * <class name="wxAcceleratorEntry">
 *  An object used by an application wishing to create an accelerator table.
 *  See @wxAcceleratorTable, wxMenuItem @wxMenuItem#accel property.
 * </class>
 */
ZZZJS_INIT_CLASS(AcceleratorEntry, "AcceleratorEntry", 0)

/***
 * <properties>
 *  <property name="flags" type=WXJS_TYPE_NUMBER>See @wxAcceleratorEntry#flag</property>
 *  <property name="keyCode" type=WXJS_TYPE_NUMBER>
 *   See @wxKeyCode
 *  </property>
 *  <property name="command" type=WXJS_TYPE_NUMBER>
 *   The menu or control command identifier.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(AcceleratorEntry)
	ZZZJS_PROPERTY(P_FLAG, PROP_FLAGS)
	ZZZJS_PROPERTY(P_KEYCODE, PROP_KEYCODE)
	ZZZJS_PROPERTY(P_COMMAND, PROP_COMMAND)
	ZZZJS_PROPERTY(P_MENUITEM, PROP_MENUITEM)
	ZZZJS_READONLY_PROPERTY(P_ISOK, PROP_IS_OK)
ZZZJS_END_PROPERTY_MAP()

/***
 * <constants>
 *  <type name="flag">
 *   <constant name="NORMAL" />
 *   <constant name="ALT" />
 *   <constant name="CTRL" />
 *   <constant name="SHIFT" />
 *  </type>
 * </constants>
 */
ZZZJS_BEGIN_CONSTANT_MAP(AcceleratorEntry)
	ZZZJS_CONSTANT(wxACCEL_, NORMAL)
	ZZZJS_CONSTANT(wxACCEL_, ALT)
	ZZZJS_CONSTANT(wxACCEL_, CTRL)  
	ZZZJS_CONSTANT(wxACCEL_, SHIFT) 
ZZZJS_END_CONSTANT_MAP()


ZZZJS_BEGIN_GET_PROP(wxAcceleratorEntry, AcceleratorEntry)
{
    switch (id) 
	{
	case P_FLAG:
		ToJSVal(cx, vp, p->GetFlags());
		break;
	case P_KEYCODE:
		ToJSVal(cx, vp, p->GetKeyCode());
		break;
	case P_COMMAND:
		ToJSVal(cx, vp, p->GetCommand());
		break;
	case P_MENUITEM:
		{
			wxMenuItem* pItem = p->GetMenuItem();
			vp.set( MenuItem::CreateObject( cx, pItem, NULL) );
		}
		break;
	case P_ISOK:
		ToJSVal(cx, vp, p->IsOk());
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxAcceleratorEntry, AcceleratorEntry)
{
    switch(id) 
	{
	case P_FLAG:
		{
			int flag;
			if ( FromJS(cx, vp, flag) )
				p->Set(flag, p->GetKeyCode(), p->GetCommand());
			break;
		}
	case P_KEYCODE:
		{
			int keycode;
			if ( FromJS(cx, vp, keycode) )
				p->Set(p->GetFlags(), keycode, p->GetCommand());
			break;
		}
	case P_COMMAND:
		{
			int command;
			if ( FromJS(cx, vp, command) )
				p->Set(p->GetFlags(), p->GetKeyCode(), command);
			break;
		}
	case P_MENUITEM:
		{
			wxMenuItem* pItem = MenuItem::GetPrivate(cx, vp);
			if( pItem != NULL ) {
				p->Set(p->GetFlags(), p->GetKeyCode(), p->GetCommand(), pItem );
			}
		}
		break;
	}
    return true;
}
ZZZJS_END_SET_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Flags" type=WXJS_TYPE_NUMBER default="0">
 *    Indicates which modifier key is pressed. See @wxAcceleratorEntry#constants
 *    for the possible values.
 *   </arg>
 *   <arg name="Keycode" type=WXJS_TYPE_NUMBER default="0">
 *    The keycode. See @wxKeyCode
 *   </arg>
 *   <arg name="Command" type=WXJS_TYPE_NUMBER default="0">
 *    The menu or command id.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxAcceleratorEntry object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxAcceleratorEntry, AcceleratorEntry)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	/*
 		wxAcceleratorEntry (int flags=0, int keyCode=0, int cmd=0, wxMenuItem *item=NULL)
 		Constructor. More...
 
 		wxAcceleratorEntry (const wxAcceleratorEntry &entry)
 		Copy ctor. More...
	*/
	int argIndex = 0;

	if( argc == 0 ) {
		return new wxAcceleratorEntry();
	}


	if( argv[argIndex].isNumber() == true ) 
	{
		// wxAcceleratorEntry (int flags=0, int keyCode=0, int cmd=0, wxMenuItem *item=NULL)


		int flags = 0;
		int keyCode = 0;
		int cmd = 0;
		wxMenuItem *item=NULL;
		
		ZZZJS_CHECK_ARG_COUNT(1, 4);
		
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flags, WXJS_TYPE_NUMBER);

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 4:
			// wxMenuItem *item=NULL
			item = MenuItem::GetPrivate(cx, argv[argIndex]);
			if( item == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "MenuItem");
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			// int cmd=0
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(cmd, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			// int keyCode=0,
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(keyCode, WXJS_TYPE_NUMBER);
			argIndex--;
		}		
		return new wxAcceleratorEntry(flags, keyCode, cmd);
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			zzzJsPtr<wxAcceleratorEntry> apRet;
			if( apRet.set( 
				AcceleratorEntry::getObject2Instance(cx, pObj, apRet.bAllocation) ) == true 
			) {
				if( apRet.bAllocation == true ) {
					return apRet.release();
				} else {
					return new wxAcceleratorEntry(*apRet.get());
				}
			}
		} while( 0 );
	}


	//int flag = 0;
	//int key = 0;
	//int id = 0;

	//JS::CallArgs argv = CallArgsFromVp(argc, vp);

	//if ( argc == 0 )
	//	return new wxAcceleratorEntry();

	//if ( argc > 3 )
 //       argc = 3;

	//switch(argc)
	//{
	//case 3:
	//	if ( ! FromJS(cx, argv[2], id) )
	//		break;
	//	// Walk through
	//case 2:
	//	if ( ! FromJS(cx, argv[1], key) )
	//		break;
	//	// Walk through
	//case 1:
	//	if ( ! FromJS(cx, argv[0], flag) )
	//		break;
	//	// Walk through
	//default:
	//	{
	//		return new wxAcceleratorEntry(flag, key, id);
	//	}
	//}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return NULL;
}
ZZZJS_END_CONSTRUCTOR

	
// Object 2 Instatance

ZZZJS_BEGIN_O2I(wxAcceleratorEntry, AcceleratorEntry)
{
	// wxAcceleratorEntry (int flags=0, int keyCode=0, int cmd=0, wxMenuItem *item=NULL)

	
	pRet = AcceleratorEntry::GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}


	if( GetPropertyWhenPresent( cx, obj, PROP_FLAGS, &v) == JS_TRUE )  
	{
		int flags = 0;
		int keyCode = 0;
		int cmd = 0;
		wxMenuItem *item=NULL;

		if( FromJS(cx, v, flags) == false ) {
			ReportError_PropTypeError(cx, PROP_FLAGS, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// depth
		ZZZJS_PROP_FROMJS_IF_EXIST(keyCode, obj, PROP_KEYCODE, WXJS_TYPE_NUMBER)	
		// cmd
		ZZZJS_PROP_FROMJS_IF_EXIST(cmd, obj, PROP_COMMAND, WXJS_TYPE_NUMBER)	

		if( GetPropertyWhenPresent( cx, obj, PROP_MENUITEM, &v) == JS_TRUE )  
		{
			item = MenuItem::GetPrivate(cx, v);
			if( item == NULL ) {
				ReportError_PropTypeError(cx, PROP_MENUITEM, "MenuItem");
				return JS_FALSE;
			}
		}

		bAllocation = true;
		return new wxAcceleratorEntry(flags, keyCode, cmd);
	}



	return NULL;
}
ZZZJS_END_O2I

ZZZJS_BEGIN_METHOD_MAP(AcceleratorEntry)
	ZZZJS_METHOD("set", set, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="set">
 *  <function>
 *   <arg name="Flags" type=WXJS_TYPE_NUMBER>
 *    Indicates which modifier key is pressed. See @wxAcceleratorEntry#constants
 *    for the possible values.
 *   </arg>
 *   <arg name="Keycode" type=WXJS_TYPE_NUMBER default="0">
 *    The keycode. See @wxKeyCode
 *   </arg>
 *   <arg name="Command" type=WXJS_TYPE_NUMBER default="0">
 *    The menu or command id.
 *   </arg>
 *  </function>
 *  <desc>
 *   See @wxAcceleratorEntry#ctor for the explanation of the arguments.
 *  </desc>
 * </method>
 */
ZZZJS_BEGIN_METHOD(AcceleratorEntry, set )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxAcceleratorEntry *p = GetPrivate(cx, obj);

	/*
	void 	Set (int flags, int keyCode, int cmd, wxMenuItem *item=NULL)
	*/
	if ( argc > 3 )
        argc = 3;
	
	int argIndex = 0;
	int flag = p->GetFlags();
	int keyCode = p->GetKeyCode();
	int cmd = p->GetCommand();
	wxMenuItem *item=p->GetMenuItem();


	if( argc == 0 ) {
		p->Set(flag, keyCode, cmd);
		return JS_TRUE;
	}


	if( argv[argIndex].isNumber() == true ) {
		ZZZJS_CHECK_ARG_COUNT(1, 4)

		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER)
		argIndex++;


		argIndex = argc - 1;
		switch( argc ) 
		{
		case 4:
			// wxMenuItem *item=NULL
			item = MenuItem::GetPrivate(cx, argv[argIndex]);
			if( item == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "MenuItem");
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			// int cmd=0
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(cmd, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			// int keyCode=0,
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(keyCode, WXJS_TYPE_NUMBER);
			argIndex--;
		}		
		p->Set(flag, keyCode, cmd, item);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Object�̏ꍇ
		
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(flag, pObj, PROP_FLAGS, WXJS_TYPE_NUMBER)
			ZZZJS_PROP_FROMJS_IF_EXIST(keyCode, pObj, PROP_KEYCODE, WXJS_TYPE_NUMBER)
			ZZZJS_PROP_FROMJS_IF_EXIST(cmd, pObj, PROP_COMMAND, WXJS_TYPE_NUMBER)
	
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_MENUITEM), &v) == JS_TRUE )  {
				item = MenuItem::GetPrivate(cx, v);
				if( item == NULL ) {
					ReportError_PropTypeError(cx, PROP_MENUITEM, "MenuItem");
					return JS_FALSE;
				}
			}

			p->Set(flag, keyCode, cmd, item);
			return JS_TRUE;		
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

	
ZZZJS_BEGIN_METHOD(AcceleratorEntry, toString )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxAcceleratorEntry *p = GetPrivate(cx, obj);

	/*
		wxString 	ToString () const
 			Returns a textual representation of this accelerator.
	*/

	*vp = ToJS(cx, p->ToString());

	return JS_TRUE;
}
ZZZJS_END_METHOD

	
ZZZJS_BEGIN_METHOD(AcceleratorEntry, toRawString )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxAcceleratorEntry *p = GetPrivate(cx, obj);

	/*
	wxString 	ToRawString () const
 		Returns a textual representation of this accelerator which is appropriate for saving in configuration files.
	*/

	*vp = ToJS(cx, p->ToRawString());

	return JS_TRUE;
}
ZZZJS_END_METHOD

	
ZZZJS_BEGIN_METHOD(AcceleratorEntry, fromString )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxAcceleratorEntry *p = GetPrivate(cx, obj);

	/*
	bool 	FromString (const wxString &str)
 		Parses the given string and sets the accelerator accordingly. 
	*/
	wxString str;
	if( p->FromString( str ) == false ) {
		vp->setNull();
	} else {
		*vp = ToJS(cx, str);
	}

	return JS_TRUE;
}
ZZZJS_END_METHOD