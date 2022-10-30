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
#include "js/gui/misc/pen.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/bitmap.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_COLOUR			"colour"
#define PROP_NM_WIDTH			"width"
#define PROP_NM_STYLE			"style"
#define PROP_NM_STOPPLE			"stipple"
#define PROP_NM_PEN				"pen"
#define PROP_NM_RED					"red"
#define PROP_NM_GREEN				"green"
#define PROP_NM_BLUE				"blue"



/***
 * <file>misc/colour</file>
 * <module>gui</module>
 * <class name="wxPen">
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
ZZZJS_INIT_CLASS(Pen, "Pen", 0)

ZZZJS_BEGIN_PROPERTY_MAP(Pen)
	ZZZJS_PROPERTY(P_Cap, "cap")
	ZZZJS_PROPERTY(P_Colour, "colour")
	ZZZJS_PROPERTY(P_Dashes, "dashes")
	ZZZJS_PROPERTY(P_Join, "join")
	ZZZJS_PROPERTY(P_STIPPLE, "stipple")
	ZZZJS_PROPERTY(P_STYLE, "style")
	ZZZJS_PROPERTY(P_Width, "width")
	ZZZJS_READONLY_PROPERTY(P_IS_OK, "isOk ")
	ZZZJS_READONLY_PROPERTY(P_IS_NON_TRANSPARENT, "isNonTransparent ")
	ZZZJS_READONLY_PROPERTY(P_IS_TRANSPARENT, "isTransparent")
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Pen)
    ZZZJS_METHOD("setColour", setColour, 3)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxPen, Pen)
{
    switch(id) 
	{
	case P_Cap:
		vp.set( ToJS(cx, (int)p->GetCap()) );
		break;
	case P_Colour:
		{
			wxColour color = p->GetColour();
			vp.set( 
				Colour::CreateObject(cx, new wxColour(color), NULL)
			);
		}
		break;
	case P_Dashes:
		{

		}
		break;
	case P_Join:
		vp.set( ToJS(cx, (int)p->GetJoin()) );
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
	case P_Width:
		vp.set( ToJS(cx, (int)p->GetWidth()) );
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


ZZZJS_BEGIN_SET_PROP(wxPen, Pen)
{
    switch(id) 
	{
	case P_Cap:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetCap((wxPenCap)iVal);
			}
		}
		break;
	case P_Colour:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetColour( *(apColour.get()) );
			}
		}
		break;
	case P_Dashes:
		{
			wxString str;
			if( vp.isObjectOrNull() ) {
				if( JS_IsUint8ClampedArray(vp.toObjectOrNull()) == JS_FALSE ) {
					return JS_FALSE;
				}

				uint32_t i = 0, coutOfItems = 0;
				coutOfItems = JS_GetTypedArrayLength(vp.toObjectOrNull());
				if( coutOfItems == 0 ) {
					JS_ReportError(cx, "array size is 0.");
					return false;
				}
				wxDash* dash1 = new wxDash[coutOfItems];
				uint8_t *data = JS_GetUint8ArrayData(vp.toObjectOrNull());
				for(i = 0; i < coutOfItems; i++ ) {
					dash1[i] = (wxDash)data[i];
				}

				p->SetDashes(coutOfItems, dash1);
				delete []dash1;
			}
		}
		break;
	case P_Join:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetJoin((wxPenJoin)iVal);
			}
		}
		break;
	case P_STIPPLE:
		{
			zzzJsPtr<wxBitmap> apBitmap;
			if( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true ) {
				p->SetStipple( *(apBitmap.get()) );
			}
		}
		break;
	case P_STYLE:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetStyle((wxPenStyle )iVal);
			}
		}
		break;
	case P_Width:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetWidth(iVal);
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
 *   Constructs a new wxPen object.
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxPen, Pen)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	
	wxPenStyle style=wxPENSTYLE_SOLID;
	int width=1;
//	wxColour*	pColor = NULL;
	wxPen*	pPen = NULL;
//	wxColour color;
	zzzJsPtr<wxBitmap> apBitmap;
	zzzJsPtr<wxColour> apColour;
	/*
 	wxPen ()
 	Default constructor. More...
 
 	wxPen (const wxColour &colour, int width=1, wxPenStyle style=wxPENSTYLE_SOLID)
 	Constructs a pen from a colour object, pen width and style. More...
 
 	wxPen (const wxBitmap &stipple, int width)
 	Constructs a stippled pen from a stipple bitmap and a width. More...
 
 	wxPen (const wxPen &pen)
	*/
	// 引数の取得
	int argIndex = 0;
	
	if( argc == 0 ) {
		return new wxPen();
	}


	// 0 else
	if( ZZZJS_ARG_GET_AP(apColour, Colour) == true ) {
		int width = 1;
		int style = wxPENSTYLE_SOLID;

		ZZZJS_CHECK_ARG_COUNT(1, 3);


		argIndex = argc -1;
		switch( argc ) 
		{
		case 3:
			// 2
			if( FromJS(cx, argv[argIndex], style) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return NULL;
			}
			argIndex--;
		case 2:
			// 1
			if( FromJS(cx, argv[argIndex], width) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return NULL;
			}
			argIndex--;
		}

		return new wxPen( *(apColour.get()), width, style);
	} else
	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == true ) {
		ZZZJS_CHECK_ARG_COUNT(1, 2);

		argIndex = argc -1;
		switch( argc ) 
		{
		case 2:
			// 1
			if( FromJS(cx, argv[argIndex], width) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return NULL;
			}
			argIndex--;
		}
		return new wxPen(*(apBitmap.get()), width);
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
	
			zzzJsPtr<wxPen> apPen;

			if( apPen.set( 
				Pen::getObject2Instance(cx, pObj, apPen.bAllocation) ) == true 
			) {
				if( apPen.bAllocation == true ) {
					return apPen.release();
				} else {
					return new wxPen(*apPen.get());
				}
			}
	
		} while( 0 );
	}
	
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(wxPen, Pen)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	/*
	wxPen ()
		Default constructor. More...
 
	wxPen (const wxColour &colour, 
			int width=1, 
			wxPenStyle style=wxPENSTYLE_SOLID)
		Constructs a pen from a colour object, pen width and style. More...
 
	wxPen (const wxBitmap &stipple, int width)
		Constructs a stippled pen from a stipple bitmap and a width. More...
 
	wxPen (const wxPen &pen)
		Default constructor. More...
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
	{
		/*
		{
			colour : Colour
			width : Number[Option. Default=1]
			style : Number[Option. Default=wx.PENSTYLE.SOLID]
		}
		*/
		zzzJsPtr<wxColour> apColour;
		int width=1;
		int style=wxPENSTYLE_SOLID;
		
		ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, obj, Colour, PROP_NM_COLOUR);
		//width
		ZZZJS_PROP_FROMJS_IF_EXIST(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER)	
		// style
		ZZZJS_PROP_FROMJS_IF_EXIST(style, obj, PROP_NM_STYLE, WXJS_TYPE_NUMBER)	


		bAllocation = true;
		return new wxPen(*(apColour.get()), width, (wxPenStyle)style );
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_STOPPLE), &v) == JS_TRUE )  
	{
		/*
		{
			stipple : Bitmap
			width : Number[Option. Default=1]
		}
		*/
		zzzJsPtr<wxBitmap> apBitmap;
		int width=1;
		
		// stipple
		ZZZJS_PROP_AP_CHK_AND_ERROR(apBitmap, obj, Bitmap, PROP_NM_STOPPLE);
		// width
		ZZZJS_PROP_FROMJS_IF_EXIST(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER)	

		bAllocation = true;
		return new wxPen(*(apBitmap.get()), width );
	}

	return NULL;
}
ZZZJS_END_O2I



//wxPen* Pen::getConv(JSContext *cx, JS::Value v, wxPen& workData)
//{
//    if( v.isObjectOrNull() == false ) {
//		return NULL;
//	}
//	return Pen::getConv(cx, JSVAL_TO_OBJECT(v), workData);
//}
//wxPen* Pen::getConv(JSContext *cx, JSObject *obj, wxPen& workData)
//{
//	wxPen* pRet = NULL;
//
//	// objがPenオブジェクト
//	pRet = Pen::GetPrivate(cx, obj, false);
//	if( pRet != NULL ) {
//		return pRet;
//	}
//	/*
//		  colour or color : {r:*,g:*,b:*}
//		, width: ** <-- option
//		, style: ** <-- option
//
//		or
//		
//		  stipple : bitmap object
//		, width: **
//	*/
//	bool bFoundColour = false;
//	bool bFoundBmp = false;
//	JSBool bFound;
//	JS::Value v;
//
//	//  colour or color
//	do {
//		if( JS_HasUCProperty(cx, obj, L"colour", ::wcslen(L"colour"), &bFound) == JS_FALSE) {
//			return NULL;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"colour", ::wcslen(L"colour"), &v) == JS_FALSE) {
//				return NULL;
//			}
//			bFoundColour = true;
//			break;
//		}
//		if( JS_HasUCProperty(cx, obj, L"color", ::wcslen(L"color"), &bFound) == JS_FALSE) {
//			return NULL;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"color", ::wcslen(L"color"), &v) == JS_FALSE) {
//				return NULL;
//			}
//			bFoundColour = true;
//			break;
//		}
//	} while( 0 );
//
//	if( bFoundColour == false ) {
//		// stipple
//		do {
//			if( JS_HasUCProperty(cx, obj, L"stipple", ::wcslen(L"stipple"), &bFound) == JS_FALSE) {
//				return NULL;
//			}
//			if( bFound == JS_TRUE ) {
//				if( JS_GetUCProperty(cx, obj, L"stipple", ::wcslen(L"stipple"), &v) == JS_FALSE) {
//					return NULL;
//				}
//				bFoundBmp = true;
//				break;
//			}
//		} while( 0 );
//
//
//		// 対象となるプロパティーが何もセットされていなかった
//		return NULL;
//	}
//
//
//
//	if( bFoundColour == true ) {
//		zzzJsPtr<wxColour> apColour;
////		wxColour color;
//		int width=1;
//		int style=(int)wxPENSTYLE_SOLID; // wxPenStyle
//
//		// colour or color
//		if( apColour.set(Colour::getObject2Instance(cx, v, apColour.bAllocation)) == false ) 
//		{
//			return false;
//		}
//
//		// 	width
//		if( JS_HasUCProperty(cx, obj, L"width", ::wcslen(L"width"), &bFound) == JS_FALSE) {
//			return NULL;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"width", ::wcslen(L"width"), &v) == JS_FALSE) {
//				return NULL;
//			}
//			if( FromJS(cx, v, width ) == false ) {
//				return false;
//			}
//		}
//		// 	style
//		if( JS_HasUCProperty(cx, obj, L"style", ::wcslen(L"style"), &bFound) == JS_FALSE) {
//			return NULL;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"style", ::wcslen(L"style"), &v) == JS_FALSE) {
//				return NULL;
//			}
//			if( FromJS(cx, v, style ) == false ) {
//				return false;
//			}
//		}
//		workData = wxPen(*(apColour.get()), width, (wxPenStyle)style);
//		return &workData;
//	} else {
//		int width=1;
//		zzzJsPtr<wxBitmap> apBitmap;
//
//		if( apBitmap.set(Bitmap::getObject2Instance(cx, v, apBitmap.bAllocation)) == false ) {
//			return NULL;
//		}
//		// 	width
//		if( JS_HasUCProperty(cx, obj, L"width", ::wcslen(L"width"), &bFound) == JS_FALSE) {
//			return NULL;
//		}
//		if( bFound == JS_FALSE ) {
//			// widthは必須
//			return NULL;
//		}
//		if( JS_GetUCProperty(cx, obj, L"width", ::wcslen(L"width"), &v) == JS_FALSE) {
//			return NULL;
//		}
//		if( FromJS(cx, v, width ) == false ) {
//			return false;
//		}
//
//		workData = wxPen(*(apBitmap.get()), width);
//		return &workData;
//	}
//
//	return NULL;
//}
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
JSBool Pen::setColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxPen *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxPen"));
	
	int argIndex = 0;
	int R = 0;
	int G = 0;
	int B = 0;
	zzzJsPtr<wxColour> apColour;


	if( argv[argIndex].isNumber() == true )
	{
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(R, WXJS_TYPE_NUMBER);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(G, WXJS_TYPE_NUMBER);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(B, WXJS_TYPE_NUMBER);
	}
	else
	if( ZZZJS_ARG_GET_AP(apColour, Colour) == true ) {
		R = apColour->Red();
		G = apColour->Green();
		B = apColour->Blue();
	} 
	else
	{
		/*
		{ red, green, blue }のオブジェクトを受け入れるが、↑のColourに一致する
		ので、　ここを通過した場合は、該当するパラメータがないエラーになる
		*/

	
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}


	p->SetColour((unsigned char) R,
			(unsigned char) G,
			(unsigned char) B);
	return JS_TRUE;
}

void zzzJs::gui::DefineGlobalPens(JSContext *cx, JSObject *obj)
{
    DefineGlobalPen(cx, obj, "BLACK_DASHED_PEN", wxBLACK_DASHED_PEN);
    DefineGlobalPen(cx, obj, "BLACK_PEN", wxBLACK_PEN);
    DefineGlobalPen(cx, obj, "BLUE_PEN", wxBLUE_PEN);
    DefineGlobalPen(cx, obj, "CYAN_PEN", wxCYAN_PEN);
    DefineGlobalPen(cx, obj, "GREEN_PEN", wxGREEN_PEN);
    DefineGlobalPen(cx, obj, "YELLOW_PEN", wxYELLOW_PEN);
    DefineGlobalPen(cx, obj, "GREY_PEN", wxGREY_PEN);
    DefineGlobalPen(cx, obj, "LIGHT_GREY_PEN", wxLIGHT_GREY_PEN);
    DefineGlobalPen(cx, obj, "MEDIUM_GREY_PEN", wxMEDIUM_GREY_PEN);
    DefineGlobalPen(cx, obj, "RED_PEN", wxRED_PEN);
    DefineGlobalPen(cx, obj, "TRANSPARENT_PEN", wxTRANSPARENT_PEN);
    DefineGlobalPen(cx, obj, "WHITE_PEN", wxWHITE_PEN);
}

void zzzJs::gui::DefineGlobalPen(JSContext *cx, JSObject *obj,
						const char*name, const wxPen *pPen)
{
    wxASSERT_MSG(pPen != NULL, wxT("wxPen can't be NULL"));
    // Create a new colour object, because wxWindows destroys the global
    // colour objects and wxJSColour does the same. 
	Pen::DefineObject(cx, obj, name, new wxPen(*pPen)); 
}
