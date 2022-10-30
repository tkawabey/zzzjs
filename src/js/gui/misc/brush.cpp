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
#include "js/gui/errors.h"
#include "js/gui/misc/brush.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/bitmap.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>misc/colour</file>
 * <module>gui</module>
 * <class name="wxBrush">
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
ZZZJS_INIT_CLASS(Brush, "Brush", 0)


#define PROP_NM_COLOUR				"colour"
#define PROP_NM_COLOR				"colour"
#define PROP_NM_STIPPLE				"stipple"
#define PROP_NM_STYLE				"style"
#define PROP_NM_IS_HATCH			"isHatch"
#define PROP_NM_IS_OK				"isOk"
#define PROP_NM_IS_NON_TRANSPARENT	"isNonTransparent"
#define PROP_NM_IS_TRANSPARENT		"isTransparent"
#define PROP_NM_STIPPLE_BITMAP		"stippleBitmap"

ZZZJS_BEGIN_PROPERTY_MAP(Brush)
	ZZZJS_PROPERTY(P_Colour, PROP_NM_COLOUR)
	ZZZJS_PROPERTY(P_Colour, PROP_NM_COLOR)
	ZZZJS_PROPERTY(P_STIPPLE, PROP_NM_STIPPLE)
	ZZZJS_PROPERTY(P_STYLE, PROP_NM_STYLE)
	ZZZJS_READONLY_PROPERTY(P_IS_HATCH, PROP_NM_IS_HATCH)
	ZZZJS_READONLY_PROPERTY(P_IS_OK, PROP_NM_IS_OK)
	ZZZJS_READONLY_PROPERTY(P_IS_NON_TRANSPARENT, PROP_NM_IS_NON_TRANSPARENT)
	ZZZJS_READONLY_PROPERTY(P_IS_TRANSPARENT, PROP_NM_IS_TRANSPARENT)
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Brush)
    ZZZJS_METHOD("setColour", setColour, 3)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxBrush, Brush)
{
    switch(id) 
	{
	case P_Colour:
		{
			wxColour color = p->GetColour();
			vp.set( 
				Colour::CreateObject(cx, new wxColour(color), NULL)
			);
		}
		break;
	case P_STIPPLE:
		{
			wxBitmap* pBmp = p->GetStipple();
			if( pBmp == NULL ) {
				vp.setNull();
			} else {
				vp.set( 
					Bitmap::CreateObject(cx, new wxBitmap(*pBmp), NULL)
				);
			}
		}
		break;
	case P_STYLE:
		vp.set( ToJS(cx, (int)p->GetStyle()) );
		break;
	case P_IS_HATCH:
		vp.set( ToJS(cx, p->IsHatch()) );
		break;
	case P_IS_OK:
		vp.set( ToJS(cx, p->IsOk()) );
		break;
	case P_IS_NON_TRANSPARENT:
		vp.set( ToJS(cx, p->IsNonTransparent()) );
		break;
	case P_IS_TRANSPARENT:
		vp.set( ToJS(cx, p->IsTransparent()) );
		break;
    }
	return true;
}
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxBrush, Brush)
{
    switch(id) 
	{
	case P_Colour:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, obj, apColour.bAllocation) ) == true ) {
				p->SetColour( *(apColour.get()) );
			}
		}
		break;
	case P_STIPPLE:
		{
			zzzJsPtr<wxBitmap> apBitmap;
			if( apBitmap.set(Bitmap::getObject2Instance(cx, obj, apBitmap.bAllocation)) == true ) {
				p->SetStipple( *(apBitmap.get()) );
			}
		}
		break;
	case P_STYLE:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetStyle((wxBrushStyle)iVal);
			}
		}
		break;
    }
	return true;
}
ZZZJS_END_SET_PROP

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
 *   Constructs a new wxBrush object.
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxBrush, Brush)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	
	wxBrushStyle style=wxBRUSHSTYLE_SOLID;
	
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;
	zzzJsPtr<wxBrush>  apBrush;
	zzzJsPtr<wxColour>  apColour;


	if( argc > 2 ) {
		argc = 2;
	}
	/*
	wxBrush ()
		Default constructor. More...
	 
	wxBrush (const wxColour &colour, wxBrushStyle style=wxBRUSHSTYLE_SOLID)
		Constructs a brush from a colour object and style. More...
 
	wxBrush (const wxBitmap &stippleBitmap)
		Constructs a stippled brush using a bitmap. More...
 
	wxBrush (const wxBrush &brush)
		Copy constructor, uses reference counting. More...
	*/
	if( argc == 0 ) {
		return new wxBrush();
	}
	if( argc == 2 ) {
		int iStyle = 0;
		if( FromJS<int>(cx, argv[1], iStyle) ) {
			style = (wxBrushStyle)iStyle;
		}
	}

	if( ZZZJS_ARG_GET_AP(apColour, Colour) == true) {
		return new wxBrush(*(apColour.get()));
	} else
	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == true) {
		return new wxBrush(*(apBitmap.get()));
	} else
	if( ZZZJS_ARG_GET_AP(apBrush, Brush) == true) {
		if( apBrush.bAllocation == true ) {
			return apBrush.release();
		}
		return new wxBrush(*(apBrush.get()));
	}  else {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
	}

	return NULL;
}
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_O2I(wxBrush, Brush)
{
	// objがPenオブジェクト
	pRet = Brush::GetPrivate(cx, obj, false);
	if( pRet != NULL ) {
		return pRet;
	}





	// wxBrush (const wxColour &colour, wxBrushStyle style=wxBRUSHSTYLE_SOLID)
	/*
	{
		colour:Colour,
		style:Number( option. default is wx.BRUSHSTYLE_SOLID)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLOR), &v) == JS_TRUE ||
		GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLOUR), &v) == JS_TRUE  )  
	{
		zzzJsPtr<wxColour>  apColour;
		int style=wxBRUSHSTYLE_SOLID;

		if( apColour.set(Colour::getObject2Instance(cx, v, apColour.bAllocation)) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_COLOR, Colour::getClassName());
			return JS_FALSE;
		}

		// depth		
		ZZZJS_PROP_FROMJS_IF_EXIST(style, obj, PROP_NM_STYLE, WXJS_TYPE_NUMBER)	


		bAllocation = true;
		return new wxBrush(*(apColour.get()), style);
	}

	// wxBrush (const wxBitmap &stippleBitmap)
	/*
	{
		stippleBitmap:Bitmap
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_STIPPLE_BITMAP), &v) == JS_TRUE )  
	{		
		zzzJsPtr<wxBitmap>  apBitmap;

		if( apBitmap.set(Bitmap::getObject2Instance(cx, v, apBitmap.bAllocation)) == false) 
		{
			ReportError_PropTypeError(cx, PROP_NM_COLOR, "Bitmap");
			return JS_FALSE;
		}
		bAllocation = true;
		return new wxBrush(*(apBitmap.get()));
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
ZZZJS_BEGIN_METHOD(Brush, setColour )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxBrush *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxBrush"));

	
	unsigned argIndex = 0;
	zzzJsPtr<wxColour>  apColour;
	

	if( argv[argIndex].isNumber() == true ) {

		int r = 0;
		int g = 0;
		int b = 0;

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b, WXJS_TYPE_NUMBER);
		argIndex++;

		p->SetColour((unsigned char) r,
				(unsigned char) g,
				(unsigned char) b);
		return JS_TRUE;
	} 
	else
	if( ZZZJS_ARG_GET_AP(apColour, Colour) == true) {
		p->SetColour( *(apColour.get()) );
		return JS_TRUE;
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}
ZZZJS_END_METHOD


void zzzJs::gui::DefineGlobalBrushs(JSContext *cx, JSObject *obj)
{
    DefineGlobalBrush(cx, obj, "BLACK_BRUSH", wxBLACK_BRUSH);
    DefineGlobalBrush(cx, obj, "BLUE_BRUSH", wxBLUE_BRUSH);
    DefineGlobalBrush(cx, obj, "CYAN_BRUSH", wxCYAN_BRUSH);
    DefineGlobalBrush(cx, obj, "GREEN_BRUSH", wxGREEN_BRUSH);
    DefineGlobalBrush(cx, obj, "YELLOW_BRUSH", wxYELLOW_BRUSH);
    DefineGlobalBrush(cx, obj, "GREY_BRUSH", wxGREY_BRUSH);
    DefineGlobalBrush(cx, obj, "LIGHT_GREY_BRUSH", wxLIGHT_GREY_BRUSH);
    DefineGlobalBrush(cx, obj, "MEDIUM_GREY_BRUSH", wxMEDIUM_GREY_BRUSH);
    DefineGlobalBrush(cx, obj, "RED_BRUSH", wxRED_BRUSH);
    DefineGlobalBrush(cx, obj, "TRANSPARENT_BRUSH", wxTRANSPARENT_BRUSH);
    DefineGlobalBrush(cx, obj, "WHITE_BRUSH", wxWHITE_BRUSH);
}

void zzzJs::gui::DefineGlobalBrush(JSContext *cx, JSObject *obj,
						const char*name, const wxBrush *colour)
{
    wxASSERT_MSG(colour != NULL, wxT("wxBrush can't be NULL"));
    // Create a new colour object, because wxWindows destroys the global
    // colour objects and wxJSColour does the same. 
	Brush::DefineObject(cx, obj, name, new wxBrush(*colour)); 
}
