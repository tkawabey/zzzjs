/*
 * wxJavaScript - font.cpp
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
 * $Id: font.cpp 689 2007-04-27 20:45:43Z fbraem $
 */
// font.cpp
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
#include "js/gui/misc/font.h"
#include "js/gui/misc/size.h"

using namespace zzzJs;
using namespace zzzJs::gui;



// プロパティー名
#define PROP_NM_faceName					"faceName"
#define PROP_NM_family						"family"
#define PROP_NM_pointSize					"pointSize"
#define PROP_NM_style						"style"
#define PROP_NM_underlined					"underlined"
#define PROP_NM_weight						"weight"
#define PROP_NM_ok							"ok"
// スタティックプロパティー名
#define PROP_NM_defaultEncoding				"defaultEncoding"
// プロパティー名
#define PROP_NM_encoding					"encoding"
#define PROP_NM_pixelSize					"pixelSize"
#define PROP_NM_nativeInfoString			"nativeInfoString"

/***
 * <file>misc/font</file>
 * <module>gui</module>
 * <class name="wxFont">
 *  A font is an object which determines the appearance of text. 
 *  Fonts are used for drawing text to a device context, and setting the 
 *  appearance of a window's text.
 * </class>
 */
ZZZJS_INIT_CLASS(Font, "Font", 0)

/***
 * <properties>
 *  <property name="encoding" type=WXJS_TYPE_NUMBER />
 *  <property name="faceName" type=WXJS_TYPE_STRING>
 *   Get/Set the actual typeface to be used.
 *  </property>
 *  <property name="family" type=WXJS_TYPE_NUMBER>
 *   Font family, a generic way of referring to fonts without specifying an actual facename.
 *  </property>
 *  <property name="ok" type="Boolean">
 *   Returns true when the font is ok.
 *  </property>
 *  <property name="pointSize" type=WXJS_TYPE_NUMBER>
 *   Get/Set size in points
 *  </property>
 *  <property name="style" type=WXJS_TYPE_NUMBER>
 *   Get/Set the font style
 *  </property>
 *  <property name="underlined" type="Boolean">
 *   Get/Set underline.
 *  </property>
 *  <property name="weight" type=WXJS_TYPE_NUMBER>
 *   Get/Set the weight of the font
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Font)
	ZZZJS_PROPERTY(P_FACE_NAME, PROP_NM_faceName)
	ZZZJS_PROPERTY(P_FAMILY, PROP_NM_family)
	ZZZJS_PROPERTY(P_POINT_SIZE, PROP_NM_pointSize)
	ZZZJS_PROPERTY(P_STYLE, PROP_NM_style)
	ZZZJS_PROPERTY(P_UNDERLINED, PROP_NM_underlined)
	ZZZJS_PROPERTY(P_WEIGHT, PROP_NM_weight)
	ZZZJS_PROPERTY(P_OK, PROP_NM_ok)
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_GET_PROP(wxFont, Font)
    switch (id) 
	{
	case P_FACE_NAME:
        if ( p->Ok() )
		   ToJSVal(cx, vp, p->GetFaceName());
		break;
	case P_FAMILY:
        if ( p->Ok() )
    		ToJSVal<int>(cx, vp, p->GetFamily());
		break;
	case P_POINT_SIZE:
        if ( p->Ok() )
    		ToJSVal(cx, vp,  p->GetPointSize());
		break;
	case P_STYLE:
        if ( p->Ok() )
    		ToJSVal<int>(cx, vp,  p->GetStyle());
		break;
	case P_UNDERLINED:
        if ( p->Ok() )
    		ToJSVal(cx, vp,  p->GetUnderlined());
		break;
	case P_WEIGHT:
        if ( p->Ok() )
    		ToJSVal<int>(cx, vp,  p->GetWeight());
		break;
    case P_OK:
        ToJSVal(cx, vp,  p->Ok());
        break;
    }
    return true;
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxFont, Font)
    switch (id) 
	{
	case P_FACE_NAME:
		{
			wxString name;
			FromJS(cx, vp, name);
			p->SetFaceName(name);
			break;
		}
	case P_FAMILY:
		{
			int family;
			if ( FromJS(cx, vp, family) )
				p->SetFamily(family);
			break;
		}
	case P_POINT_SIZE:
		{
			int size;
			if ( FromJS(cx, vp, size) )
				p->SetPointSize(size);
			break;
		}
	case P_STYLE:
		{
			int style;
			if ( FromJS(cx, vp, style) )
				p->SetStyle(style);
			break;
		}
	case P_UNDERLINED:
		{
			bool underlined;
			if ( FromJS(cx, vp, underlined) )
				p->SetUnderlined(underlined);
			break;
		}
	case P_WEIGHT:
		{
			int weight;
			if ( FromJS(cx, vp, weight) )
				p->SetWeight(weight);
			break;
		}
	}

    return true;
ZZZJS_END_SET_PROP

/***
 * <class_properties>
 *  <property name="defaultEncoding" type=WXJS_TYPE_NUMBER>
 *	 Get/Set the default encoding
 *  </property>
 * </class_properties>
 */
ZZZJS_BEGIN_STATIC_PROPERTY_MAP(Font)
	ZZZJS_STATIC_PROPERTY(P_DEFAULT_ENCODING, PROP_NM_defaultEncoding)
ZZZJS_END_PROPERTY_MAP()

bool Font::GetStaticProperty(JSContext* cx,
                                    int id,
                                    JS::MutableHandle<JS::Value>& vp)
{
    if ( id == P_DEFAULT_ENCODING )
    {
        ToJSVal(cx, vp, (int)wxFont::GetDefaultEncoding());
    }
    return true;
}

bool Font::SetStaticProperty(JSContext* cx, 
                                    int id,
                                    JS::MutableHandle<JS::Value> &vp)
{
    if ( id == P_DEFAULT_ENCODING )
    {
        int encoding;
        FromJS(cx, vp, encoding);
        wxFont::SetDefaultEncoding((wxFontEncoding) encoding);
    }
    return true;
}

/***
 * <constants>
 *  <type name="Family">
 *   <constant name="DEFAULT" />
 *   <constant name="DECORATIVE" />
 *   <constant name="ROMAN" />
 *   <constant name="SCRIPT" />
 *   <constant name="SWISS" />
 *   <constant name="MODERN" />
 *  </type>
 *  <type name="Style">
 *   <constant name="NORMAL" />
 *   <constant name="SLANT" />
 *   <constant name="ITALIC" />
 *  </type>
 *  <type name="Weight">
 *   <constant name="NORMAL" />
 *   <constant name="LIGHT" />
 *   <constant name="BOLD" />
 *  </type>
 * </constants>
 */
ZZZJS_BEGIN_CONSTANT_MAP(Font)
	// Family constants 
	ZZZJS_CONSTANT(wx, DEFAULT)
	ZZZJS_CONSTANT(wx, DECORATIVE)
	ZZZJS_CONSTANT(wx, ROMAN)
	ZZZJS_CONSTANT(wx, SCRIPT)
	ZZZJS_CONSTANT(wx, SWISS)
	ZZZJS_CONSTANT(wx, MODERN)  
	// Style constants
	ZZZJS_CONSTANT(wx, NORMAL)
	ZZZJS_CONSTANT(wx, SLANT)
	ZZZJS_CONSTANT(wx, ITALIC)
	// Weight constants
	ZZZJS_CONSTANT(wx, LIGHT)
	ZZZJS_CONSTANT(wx, BOLD)
ZZZJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="PointSize" type=WXJS_TYPE_NUMBER>
 *    Size in points
 *   </arg>
 *   <arg name="Family" type=WXJS_TYPE_NUMBER>
 *    Font family, a generic way of referring to fonts without specifying actual facename.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER>
 *    Font style
 *   </arg>
 *   <arg name="Weight" type=WXJS_TYPE_NUMBER>
 *    Font weight
 *   </arg>
 *   <arg name="Underline" type="Boolean" />
 *   <arg name="FaceName" type=WXJS_TYPE_STRING default="">
 *    An optional string specifying the actual typeface to be used.
 *    When not specified, a default typeface will chosen based on the family.
 *   </arg>
 *   <arg name="Encoding" type="@wxFontEncoding" default="wxFontEncoding.DEFAULT" />
 *  </function>
 *  <desc>
 *   Constructs a new wxFont object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxFont, Font)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	/*
	wxFont ()
	Default ctor. More...
 
	wxFont (const wxFont &font)
		Copy constructor, uses reference counting. More...
 
 
	wxFont (
			int pointSize, 
			wxFontFamily family, 
			wxFontStyle style, 
			wxFontWeight weight, 
			bool underline=false, 
			const wxString &faceName=wxEmptyString, 
			wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
		Creates a font object with the specified attributes and size in points. More...
 
	wxFont (
			const wxSize &pixelSize, 
			wxFontFamily family, 
			wxFontStyle style, 
			wxFontWeight weight, 
			bool underline=false, 
			const wxString &faceName=wxEmptyString, 
			wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
		Creates a font object with the specified attributes and size in pixels. More...
 
	wxFont (const wxString &nativeInfoString)
		Constructor from font description string. More...
 
	wxFont (const wxFontInfo &fontInfo)
		Creates a font object using the specified font description. More...
	wxFont (const wxNativeFontInfo &nativeInfo)
		Construct font from a native font info structure. More...
	*/
	int argIndex = 0;
	

	if ( argc == 0 )
	{
		return new wxFont();
	}
	
	wxFont* pFont = NULL;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	if( (ZZZJS_ARG_GET_PRIVATE(pFont, Font)) != NULL ) {
		// wxFont (const wxFont &font)
		return new wxFont(*pFont);
	}
	else
	if( argv[argIndex].isNumber() == true ) {
		/*
		wxFont (
				int pointSize, 
				wxFontFamily family, 
				wxFontStyle style, 
				wxFontWeight weight, 
				bool underline=false, 
				const wxString &faceName=wxEmptyString, 
				wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
			Creates a font object with the specified attributes and size in points. More...
		*/
		int pointSize;
		int family; // wxFontFamily
		int style; // wxFontStyle
		int weight; // wxFontWeight

		bool underline=false;
		wxString faceName=wxEmptyString;
		int encoding=wxFONTENCODING_DEFAULT; // wxFontEncoding
		

		ZZZJS_CHECK_ARG_COUNT(4, 7);

		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(pointSize, WXJS_TYPE_NUMBER);
		argIndex++;
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(family, WXJS_TYPE_NUMBER);
		argIndex++;
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex++;
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(weight, WXJS_TYPE_NUMBER);
		argIndex++;

		argIndex = argc -1;
		switch( argc ) 
		{
		case 7:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(encoding, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		case 6:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(faceName, WXJS_TYPE_STRING);
			argIndex--;
			break;
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(underline, "Boolean");
			argIndex--;
			break;
		}

        return new wxFont(pointSize, (wxFontFamily)family, (wxFontStyle)style, 
						  (wxFontWeight)weight, underline, 
						  faceName, (wxFontEncoding) encoding);
	}
	else
	if( argv[argIndex].isString() == true ) {
		/*
			wxFont (const wxString &nativeInfoString)
				Constructor from font description string. More...
		*/
		wxString nativeInfoString;

		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(nativeInfoString, WXJS_TYPE_STRING);
		argIndex++;

        return new wxFont(nativeInfoString);
	}
	else
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true )
	{
		/*
		wxFont (
				const wxSize &pixelSize, 
				wxFontFamily family, 
				wxFontStyle style, 
				wxFontWeight weight, 
				bool underline=false, 
				const wxString &faceName=wxEmptyString, 
				wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
			Creates a font object with the specified attributes and size in pixels. More...
		*/

		int family; // wxFontFamily
		int style; // wxFontStyle
		int weight; // wxFontWeight

		bool underline=false;
		wxString faceName=wxEmptyString;
		int encoding=wxFONTENCODING_DEFAULT; // wxFontEncoding
		

		ZZZJS_CHECK_ARG_COUNT(4, 7);
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(family, WXJS_TYPE_NUMBER);
		argIndex++;
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex++;
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(weight, WXJS_TYPE_NUMBER);
		argIndex++;

		argIndex = argc -1;
		switch( argc ) 
		{
		case 7:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(encoding, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		case 6:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(faceName, WXJS_TYPE_STRING);
			argIndex--;
			break;
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(underline, "Boolean");
			argIndex--;
			break;
		}

        return new wxFont(*(apSize.get()), (wxFontFamily)family, (wxFontStyle)style, 
						  (wxFontWeight)weight, underline, 
						  faceName, (wxFontEncoding) encoding);

	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {

		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			zzzJsPtr<wxFont> apFont;

			if( apFont.set( 
				Font::getObject2Instance(cx, pObj, apFont.bAllocation) ) == true 
			) {
				if( apFont.bAllocation == true ) {
					return apFont.release();
				} else {
					return new wxFont(*apFont.get());
				}
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return NULL;
 }
ZZZJS_END_CONSTRUCTOR

	
ZZZJS_BEGIN_O2I(wxFont, Font)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	/*
	wxFont (
			int pointSize, 
			wxFontFamily family, 
			wxFontStyle style, 
			wxFontWeight weight, 
			bool underline=false, 
			const wxString &faceName=wxEmptyString, 
			wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
		Creates a font object with the specified attributes and size in points. More...
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_pointSize), &v) == JS_TRUE )  
	{
		int pointSize;
		int family = wxFONTFAMILY_DEFAULT; // wxFontFamily
		int style = wxFONTSTYLE_NORMAL; // wxFontStyle
		int weight = wxFONTWEIGHT_NORMAL; // wxFontWeight

		bool underline=false;
		wxString faceName=wxEmptyString;
		int encoding=wxFONTENCODING_DEFAULT; // wxFontEncoding
		

		// pointSize
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pointSize, obj, PROP_NM_pointSize, WXJS_TYPE_NUMBER);
		// family
		ZZZJS_PROP_FROMJS_IF_EXIST(family, obj, PROP_NM_family, WXJS_TYPE_NUMBER)	
		// style
		ZZZJS_PROP_FROMJS_IF_EXIST(style, obj, PROP_NM_style, WXJS_TYPE_NUMBER)	
		// weight
		ZZZJS_PROP_FROMJS_IF_EXIST(weight, obj, PROP_NM_weight, WXJS_TYPE_NUMBER)	
		// depth
		ZZZJS_PROP_FROMJS_IF_EXIST(underline, obj, PROP_NM_underlined, WXJS_TYPE_BOOLEAN)
		// depth
		ZZZJS_PROP_FROMJS_IF_EXIST(faceName, obj, PROP_NM_faceName, WXJS_TYPE_STRING)
		// encoding
		ZZZJS_PROP_FROMJS_IF_EXIST(encoding, obj, PROP_NM_encoding, WXJS_TYPE_NUMBER)
		
		bAllocation = true;
		return new wxFont(pointSize, (wxFontFamily)family, (wxFontStyle)style, 
						  (wxFontWeight)weight, underline, 
						  faceName, (wxFontEncoding) encoding);		
	}
	/*
	wxFont (
			const wxSize &pixelSize, 
			wxFontFamily family, 
			wxFontStyle style, 
			wxFontWeight weight, 
			bool underline=false, 
			const wxString &faceName=wxEmptyString, 
			wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
		Creates a font object with the specified attributes and size in pixels. More...
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_pixelSize), &v) == JS_TRUE )  
	{
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		int family; // wxFontFamily
		int style; // wxFontStyle
		int weight; // wxFontWeight

		bool underline=false;
		wxString faceName=wxEmptyString;
		int encoding=wxFONTENCODING_DEFAULT; // wxFontEncoding
		

		// pointSize
		if( ZZZJS_PROP_GET_AP(apSize, Size, v) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_pixelSize, Size::getClassName());
			return JS_FALSE;
		}

		// family
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(family, obj, PROP_NM_family, WXJS_TYPE_NUMBER)	
		// style
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(style, obj, PROP_NM_style, WXJS_TYPE_NUMBER)	
		// weight
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(weight, obj, PROP_NM_weight, WXJS_TYPE_NUMBER)	
		// depth
		ZZZJS_PROP_FROMJS_IF_EXIST(underline, obj, PROP_NM_underlined, WXJS_TYPE_BOOLEAN)
		// depth
		ZZZJS_PROP_FROMJS_IF_EXIST(faceName, obj, PROP_NM_faceName, WXJS_TYPE_STRING)
		// encoding
		ZZZJS_PROP_FROMJS_IF_EXIST(faceName, obj, PROP_NM_encoding, WXJS_TYPE_NUMBER)

		bAllocation = true;
		return new wxFont(*(apSize.get()), (wxFontFamily)family, (wxFontStyle)style, 
						  (wxFontWeight)weight, underline, 
						  faceName, (wxFontEncoding) encoding);		
	}
	/*
		wxFont (const wxString &nativeInfoString)
			Constructor from font description string. More...
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_nativeInfoString), &v) == JS_TRUE )  
	{
		
		wxString nativeInfoString;
		// nativeInfoString
		if( FromJS(cx, v, nativeInfoString) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_nativeInfoString, WXJS_TYPE_STRING);
			return JS_FALSE;
		}

		bAllocation = true;
		return new wxFont(nativeInfoString);		
	}	
	return NULL;
}
ZZZJS_END_O2I


//
//// Object 2 Instatance
//wxFont* Font::getObject2Instance(JSContext *cx, JS::Value v, wxFont& workData)
//{
//	if( v.isObjectOrNull() == false ) {
//		return NULL;
//	}
//	return Font::getObject2Instance(cx, v.toObjectOrNull(), workData);
//}
//wxFont* Font::getObject2Instance(JSContext *cx, JSObject *obj, wxFont& workData)
//{
//	jsval v;
//	wxFont* pRet = NULL;
//
//	pRet = Font::GetPrivate(cx, obj);
//	if( pRet != NULL ) {
//		return pRet;
//	}
//
//	/*
//	wxFont (
//			int pointSize, 
//			wxFontFamily family, 
//			wxFontStyle style, 
//			wxFontWeight weight, 
//			bool underline=false, 
//			const wxString &faceName=wxEmptyString, 
//			wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
//		Creates a font object with the specified attributes and size in points. More...
//	*/
//	if( GetPropertyWhenPresent( cx, obj, _T("pointSize"), &v) == JS_TRUE )  
//	{
//		int pointSize;
//		int family = wxFONTFAMILY_DEFAULT; // wxFontFamily
//		int style = wxFONTSTYLE_NORMAL; // wxFontStyle
//		int weight = wxFONTWEIGHT_NORMAL; // wxFontWeight
//
//		bool underline=false;
//		wxString faceName=wxEmptyString;
//		int encoding=wxFONTENCODING_DEFAULT; // wxFontEncoding
//		
//
//		// pointSize
//		if( FromJS(cx, v, pointSize) == false ) {
//			ReportError_PropTypeError(cx, "pointSize", WXJS_TYPE_NUMBER);
//			return JS_FALSE;
//		}
//
//		// family
//		ZZZJS_PROP_FROMJS_IF_EXIST(family, obj, "family", WXJS_TYPE_NUMBER)	
//		// style
//		ZZZJS_PROP_FROMJS_IF_EXIST(style, obj, "style", WXJS_TYPE_NUMBER)	
//		// weight
//		ZZZJS_PROP_FROMJS_IF_EXIST(weight, obj, "weight", WXJS_TYPE_NUMBER)	
//		// depth
//		ZZZJS_PROP_FROMJS_IF_EXIST(underline, obj, "underline", WXJS_TYPE_BOOLEAN)
//		// depth
//		ZZZJS_PROP_FROMJS_IF_EXIST(faceName, obj, "faceName", WXJS_TYPE_STRING)
//		// encoding
//		ZZZJS_PROP_FROMJS_IF_EXIST(encoding, obj, "encoding", WXJS_TYPE_NUMBER)
//
//		workData = wxFont(pointSize, (wxFontFamily)family, (wxFontStyle)style, 
//						  (wxFontWeight)weight, underline, 
//						  faceName, (wxFontEncoding) encoding);		
//		pRet = &workData;
//		return pRet;
//	}
//	/*
//	wxFont (
//			const wxSize &pixelSize, 
//			wxFontFamily family, 
//			wxFontStyle style, 
//			wxFontWeight weight, 
//			bool underline=false, 
//			const wxString &faceName=wxEmptyString, 
//			wxFontEncoding encoding=wxFONTENCODING_DEFAULT)
//		Creates a font object with the specified attributes and size in pixels. More...
//	*/
//	if( GetPropertyWhenPresent( cx, obj, _T("pixelSize"), &v) == JS_TRUE )  
//	{
//		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
//		int family; // wxFontFamily
//		int style; // wxFontStyle
//		int weight; // wxFontWeight
//
//		bool underline=false;
//		wxString faceName=wxEmptyString;
//		int encoding=wxFONTENCODING_DEFAULT; // wxFontEncoding
//		
//
//		// pointSize
//		if( ZZZJS_PROP_GET_AP(apSize, Size, v) == false ) {
//			ReportError_PropTypeError(cx, "pointSize", Size::getClassName());
//			return JS_FALSE;
//		}
//
//		// family
//		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(family, obj, "family", WXJS_TYPE_NUMBER)	
//		// style
//		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(style, obj, "style", WXJS_TYPE_NUMBER)	
//		// weight
//		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(weight, obj, "weight", WXJS_TYPE_NUMBER)	
//		// depth
//		ZZZJS_PROP_FROMJS_IF_EXIST(underline, obj, "underline", WXJS_TYPE_BOOLEAN)
//		// depth
//		ZZZJS_PROP_FROMJS_IF_EXIST(faceName, obj, "faceName", WXJS_TYPE_STRING)
//		// encoding
//		ZZZJS_PROP_FROMJS_IF_EXIST(faceName, obj, "encoding", WXJS_TYPE_NUMBER)
//
//		workData = wxFont(*(apSize.get()), (wxFontFamily)family, (wxFontStyle)style, 
//						  (wxFontWeight)weight, underline, 
//						  faceName, (wxFontEncoding) encoding);		
//		pRet = &workData;
//		return pRet;
//	}
//	/*
//		wxFont (const wxString &nativeInfoString)
//			Constructor from font description string. More...
//	*/
//	if( GetPropertyWhenPresent( cx, obj, _T("nativeInfoString"), &v) == JS_TRUE )  
//	{
//		
//		wxString nativeInfoString;
//		// nativeInfoString
//		if( FromJS(cx, v, nativeInfoString) == false ) {
//			ReportError_PropTypeError(cx, "nativeInfoString", WXJS_TYPE_STRING);
//			return JS_FALSE;
//		}
//
//		workData = wxFont(nativeInfoString);		
//		pRet = &workData;
//		return pRet;
//	}
//	return NULL;
//}




void zzzJs::gui::DefineGlobalFonts(JSContext *cx, JSObject *obj)
{
    DefineGlobalFont(cx, obj, "ITALIC_FONT", wxITALIC_FONT);
    DefineGlobalFont(cx, obj, "SWISS_FONT", wxSWISS_FONT);
    DefineGlobalFont(cx, obj, "NORMAL_FON", wxNORMAL_FONT);
    DefineGlobalFont(cx, obj, "SMALL_FONT", wxSMALL_FONT);
}
void zzzJs::gui::DefineGlobalFont(JSContext *cx, JSObject *obj,
						const char *name, const wxFont*pFont)
{	
	Font::DefineObject(cx, obj, name, new wxFont(*pFont)); 
}