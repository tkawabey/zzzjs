/*
 * wxJavaScript - colour.cpp
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
 * $Id: colour.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// colour.cpp
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
#include "js/gui/misc/colour.h"

using namespace zzzJs;
using namespace zzzJs::gui;

#define PROP_NM_RED			"red"
#define PROP_NM_R			"r"
#define PROP_NM_GREEN		"green"
#define PROP_NM_G			"g"
#define PROP_NM_BLUE		"blue"
#define PROP_NM_B			"b"
#define PROP_NM_ALHA		"alpha"
#define PROP_NM_A			"a"
#define PROP_NM_IS_OK		"isOk"


/***
 * <file>misc/colour</file>
 * <module>gui</module>
 * <class name="wxColour">
 *  A colour is an object representing a combination of Red, Green, and Blue (RGB) intensity values.
 *  This is a list of predefined colour objects:
 *  wxBLACK, wxWHITE, wxRED, wxBLUE, wxGREEN, wxCYAN and wxLIGHT_GREY
 * </class>
 * <properties>
 *  <property name="blue" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Gets the Blue value
 *  </property>
 *  <property name="green" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Gets the Green value
 *  </property>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true when the colour is valid
 *  </property>
 *  <property name="red" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Gets the Red value
 *  </property>
 * </properties>
 */
ZZZJS_INIT_CLASS(Colour, "Colour", 0)

ZZZJS_BEGIN_PROPERTY_MAP(Colour)
	ZZZJS_READONLY_PROPERTY(P_BLUE, PROP_NM_BLUE)
	ZZZJS_READONLY_PROPERTY(P_BLUE, PROP_NM_B)
	ZZZJS_READONLY_PROPERTY(P_GREEN, PROP_NM_GREEN)
	ZZZJS_READONLY_PROPERTY(P_GREEN, PROP_NM_G)
	ZZZJS_READONLY_PROPERTY(P_RED, PROP_NM_RED)
	ZZZJS_READONLY_PROPERTY(P_RED, PROP_NM_R)
	ZZZJS_READONLY_PROPERTY(P_OK, PROP_NM_IS_OK)
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Colour)
    ZZZJS_METHOD("set", set, 3)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxColour, Colour)
{
    switch(id) 
	{
	case P_BLUE:
		ToJSVal<int>(cx, vp, p->Blue());
		break;
	case P_GREEN:
		ToJSVal<int>(cx, vp, p->Green());
		break;
	case P_RED:
		ToJSVal<int>(cx, vp, p->Red());
		break;
	case P_OK:
		ToJSVal<bool>(cx, vp, p->Ok());
		break;
    }
	return true;
}
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Red" type=WXJS_TYPE_NUMBER>
 *    The red value
 *   </arg>
 *   <arg name="Green" type=WXJS_TYPE_NUMBER>
 *    The green value
 *   </arg>
 *   <arg name="Blue" type=WXJS_TYPE_NUMBER>
 *    The blue value
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="ColourName" type=WXJS_TYPE_STRING>
 *    The name used to retrieve the colour from wxTheColourDatabase
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxColour object.
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxColour, Colour)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if( argc == 0 ) {
		return new wxColour();
	}
    if ( argc == 3 ) // RGB
    {
		int R;
		int G;
		int B;
		if (    FromJS<int>(cx, argv[0], R)
			 && FromJS<int>(cx, argv[1], G)
			 && FromJS<int>(cx, argv[2], B) )
		{
			return new wxColour(R, G, B);
		}
    }
    else if ( argc == 1 )
    {
		wxString name;
		FromJS(cx, argv[0], name);
        return new wxColour(name);
    }
	return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(wxColour, Colour)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	/*
	{
		r:Number,
		g:Number,
		b:Number,
	}
	 or 
	{
		red:Number,
		green:Number,
		bulue:Number,
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_RED), &v) == JS_TRUE )  
	{
		int r = 0, g = 0, b = 0;
		int alpha = (int)wxALPHA_OPAQUE;


		// red
		if( FromJS(cx, v, r) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_RED, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// green
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g, obj, PROP_NM_GREEN, WXJS_TYPE_NUMBER)	;
		// green
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b, obj, PROP_NM_BLUE, WXJS_TYPE_NUMBER)	;
		// alpha
		ZZZJS_PROP_FROMJS_IF_EXIST(alpha, obj, PROP_NM_ALHA, WXJS_TYPE_NUMBER)	


		bAllocation = true;
		return new wxColour(r, g, b, alpha);
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_R), &v) == JS_TRUE )  
	{
		int r = 0, g = 0, b = 0;
		int alpha = (int)wxALPHA_OPAQUE;


		// red
		if( FromJS(cx, v, r) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_R, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// green
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g, obj, PROP_NM_G, WXJS_TYPE_NUMBER)	;
		// green
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b, obj, PROP_NM_B, WXJS_TYPE_NUMBER)	;
		// alpha
		ZZZJS_PROP_FROMJS_IF_EXIST(alpha, obj, PROP_NM_A, WXJS_TYPE_NUMBER)	


		bAllocation = true;
		return new wxColour(r, g, b, alpha);
	}


	return NULL;
}
ZZZJS_END_O2I
/***
 * <method name="set">
 *  <function>
 *   <arg name="Red" type=WXJS_TYPE_NUMBER>
 *    The red value
 *   </arg>
 *   <arg name="Green" type=WXJS_TYPE_NUMBER>
 *    The green value
 *   </arg>
 *   <arg name="Blue" type=WXJS_TYPE_NUMBER>
 *    The blue value
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the RGB values.
 *  </desc>
 * </method>
 */
JSBool Colour::set(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxColour *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxColour"));

	int R;
	int G;
	int B;
	if (    FromJS<int>(cx, argv[0], R)
		 && FromJS<int>(cx, argv[1], G)
		 && FromJS<int>(cx, argv[2], B) )
	{
		p->Set((unsigned char) R,
			   (unsigned char) G,
			   (unsigned char) B);
	}
	else
	{
		return JS_FALSE;
	}

	return JS_TRUE;
}

void zzzJs::gui::DefineGlobalColours(JSContext *cx, JSObject *obj)
{
    DefineGlobalColour(cx, obj, "RED", wxRED);
	DefineGlobalColour(cx, obj, "BLACK", wxBLACK);
	DefineGlobalColour(cx, obj, "WHITE", wxWHITE);
	DefineGlobalColour(cx, obj, "RED", wxRED);
	DefineGlobalColour(cx, obj, "BLUE", wxBLUE);
	DefineGlobalColour(cx, obj, "GREEN", wxGREEN);
	DefineGlobalColour(cx, obj, "CYAN", wxCYAN);
	DefineGlobalColour(cx, obj, "LIGHT_GREY", wxLIGHT_GREY);
}

void zzzJs::gui::DefineGlobalColour(JSContext *cx, JSObject *obj,
						const char*name, const wxColour *colour)
{
    wxASSERT_MSG(colour != NULL, wxT("wxColour can't be NULL"));
    // Create a new colour object, because wxWindows destroys the global
    // colour objects and wxJSColour does the same. 
	Colour::DefineObject(cx, obj, name, new wxColour(*colour)); 
}
