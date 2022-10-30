/*
 * wxJavaScript - bitmap.cpp
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
 * $Id: bitmap.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// bitmap.cpp
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
#include "js/gui/misc/pallet.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/image.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_RED				"red"
#define PROP_NM_GREEN			"green"
#define PROP_NM_BLUE			"blue"
#define PROP_NM_PIXEL			"pixel"
/***
 * <file>misc/bitmap</file>
 * <module>gui</module>
 * <class name="wxPalette">
 *  This class encapsulates the concept of a platform-dependent bitmap, either monochrome or colour.
 *  See @wxIcon and @wxBitmapType
 * </class>
 */
ZZZJS_INIT_CLASS(Palette, "Palette", 0)

/***
 * <properties>
 *  <property name="depth" type=ZZZJS_TYPE_NUMBER>
 *   Get/Set the colour depth of the bitmap. A value of 1 indicates a monochrome bitmap.
 *  </property>
 *  <property name="height" type=ZZZJS_TYPE_NUMBER>
 *   Get/Set the height of the bitmap in pixels.
 *  </property>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true when the bitmap data is available.
 *  </property>
 *  <property name="width" type=ZZZJS_TYPE_NUMBER>
 *   Get/Set the width of the bitmap in pixels.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Palette)
	ZZZJS_READONLY_PROPERTY(P_ColoursCount, "coloursCount")
	ZZZJS_READONLY_PROPERTY(P_IsOK, "isOk")
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Palette)
	ZZZJS_METHOD("create", create, 3)
	ZZZJS_METHOD("getPixel", getPixel, 3)
	ZZZJS_METHOD("getRGB", getRGB, 1)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxPalette, Palette)
{
    switch(id) 
	{
	case P_ColoursCount:
		ToJSVal(cx, vp, p->GetColoursCount());
		break;
	case P_IsOK:
		ToJSVal(cx, vp, p->IsOk());
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP


/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>Filename</arg>
 *   <arg name="Type" type=ZZZJS_TYPE_NUMBER>The type of the bitmap.</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxPalette object.
 *   See @wxBitmapType
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxPalette, Palette)
{
	wxPalette *p = new wxPalette();
	
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
}
ZZZJS_END_CONSTRUCTOR

JSBool Palette::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPalette *p = GetPrivate(cx, obj);
    *rval = JSVAL_FALSE;


	// 引数の取得
	int argIndex = 0;

	/*
	bool 	Create (
				int n, 
				const unsigned char *red, 
				const unsigned char *green, 
				const unsigned char *blue
	)
 		Creates a palette from arrays of size n, one for each red, blue or green component.
	*/
	JSObject* pObjR = NULL;
	JSObject* pObjG = NULL;
	JSObject* pObjB = NULL;
	bool	bOk = false;

	// red
	if( argv[argIndex].isObjectOrNull() == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Uint8ClampedArray");
		return JS_FALSE;
	}
	pObjR = argv[argIndex].toObjectOrNull();
	argIndex++;
	if( JS_IsUint8ClampedArray(pObjR) == JS_TRUE ) {
		// green
		if( argv[argIndex].isObjectOrNull() == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Uint8ClampedArray");
			return JS_FALSE;
		}
		pObjG = argv[argIndex].toObjectOrNull();
		if( JS_IsUint8ClampedArray(pObjG) == JS_FALSE ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Uint8ClampedArray");
			return JS_FALSE;
		}
		argIndex++;


		// blue
		if( argv[argIndex].isObjectOrNull() == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Uint8ClampedArray");
			return JS_FALSE;
		}
		pObjB = argv[argIndex].toObjectOrNull();
		if( JS_IsUint8ClampedArray(pObjB) == JS_FALSE ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Uint8ClampedArray");
			return JS_FALSE;
		}
		argIndex++;

		bOk = true;
	} 
	else
	{
		// Objectの場合
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			// red 
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_FALSE )
			{
				break;
			}
			if( v.isObjectOrNull() == false ) {
				ReportError_PropMustError(cx, PROP_NM_RED);
				return JS_FALSE;
			}
			pObjR = argv[argIndex].toObjectOrNull();
			if( JS_IsUint8ClampedArray(pObjR) == JS_FALSE ) {
				ReportError_PropTypeError(cx, PROP_NM_RED, "Uint8ClampedArray");
				return JS_FALSE;
			}



			// green
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_GREEN), &v) == JS_FALSE )
			{
				break;
			}
			if( v.isObjectOrNull() == false ) {
				ReportError_PropMustError(cx, PROP_NM_GREEN);
				return JS_FALSE;
			}
			pObjG = v.toObjectOrNull();
			if( JS_IsUint8ClampedArray(pObjG) == JS_FALSE ) {
				ReportError_PropTypeError(cx, PROP_NM_GREEN, "Uint8ClampedArray");
				return JS_FALSE;
			}


			// blue
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_BLUE), &v) == JS_FALSE )
			{
				break;
			}
			if( v.isObjectOrNull() == false ) {
				ReportError_PropMustError(cx, PROP_NM_BLUE);
				return JS_FALSE;
			}
			pObjB = v.toObjectOrNull();
			if( JS_IsUint8ClampedArray(pObjB) == JS_FALSE ) {
				ReportError_PropTypeError(cx, PROP_NM_BLUE, "Uint8ClampedArray");
				return JS_FALSE;
			}
			
			bOk = true;
		} while( 0 );
	}


	if( bOk == false ) 
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	uint32_t lengthR = JS_GetTypedArrayLength(pObjR);
	uint8_t *dataR   = JS_GetUint8ClampedArrayData(pObjR);
	uint32_t lengthG = JS_GetTypedArrayLength(pObjG);
	uint8_t *dataG   = JS_GetUint8ClampedArrayData(pObjG);
	uint32_t lengthB = JS_GetTypedArrayLength(pObjB);
	uint8_t *dataB   = JS_GetUint8ClampedArrayData(pObjB);

	if( !(lengthR == lengthG == lengthB )) {
		JS_ReportError(cx, "array size is incorrect.");
		return JS_FALSE;
	}

	if( p->Create((int)lengthR, dataR, dataG, dataB) == false ) {
		JS_ReportError(cx, "fail to create pallet.");
		return JS_FALSE;
	}		

    return JS_TRUE;
}
/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the bitmap in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the bitmap in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the bitmap in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh bitmap.
 *  </desc>
 * </method>
 */
JSBool Palette::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}


/***
 * <method name="getPixel">
 *	<function returns=WXJS_TYPE_NUMBER>
 *	 <arg name="red" type=WXJS_TYPE_NUMBER />
 *	 <arg name="green" type=WXJS_TYPE_NUMBER />
 *	 <arg name="blue" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Returns a pixel value (index into the palette) for the given RGB values.
 *   The nearest palette index or NOT_FOUND for unexpected errors.
 *  </desc>
 * </method>
 */
JSBool Palette::getPixel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPalette *p = GetPrivate(cx, obj);

	// 引数の取得
	int argIndex = 0;
	int r, g, b;
	bool	bOk = false;

	if( argv[argIndex].isNumber() == true ) 
	{
		// 0
		if ( FromJS(cx, argv[argIndex], r) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( FromJS(cx, argv[argIndex], g) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( FromJS(cx, argv[argIndex], b) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;

		bOk = true;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  name:***
			, [type:***]
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}

			// red
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(r, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER)
			// green
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER)
			// blue
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER)
			
			bOk = true;

		} while( 0 );
	}

	// APIの実行と、戻り値の設定
	if( bOk  == true )
	{
		vp->setInt32( p->GetPixel(r, g, b) );
	}
	else
	{
		vp->setNull();
	}
	
    return JS_FALSE;
}



/***
 * <method name="getPixel">
 *	<function returns=WXJS_TYPE_NUMBER>
 *	 <arg name="pixel" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Returns RGB values for a given palette index.
 *   object if the operation was successful.
 *   object is { red:R, green:G, blue:B  }
 *  </desc>
 * </method>
 */
JSBool Palette::getRGB(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPalette *p = GetPrivate(cx, obj);

	// 引数の取得
	int argIndex = 0;
	int pixel;
	unsigned char r, g, b;
	bool		bOk = false;


	// 0
	if( argv[argIndex].isNumber() == true ) 
	{
		if ( FromJS(cx, argv[argIndex], pixel) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  pixel:Number
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}

			// pixel
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pixel, pObj, PROP_NM_PIXEL, WXJS_TYPE_NUMBER)
			
			bOk = true;

		} while( 0 );
	}

	if( bOk  == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	// APIの実行と、戻り値の設定
	if( p->GetRGB(pixel, &r, &g, &b ) == false ) {
		vp->setNull();
		return JS_TRUE;
	}

	JSObject* pObj = JS_NewObject(cx, NULL, NULL, NULL);
	JS::RootedObject jsvaAttr(cx, pObj);
	{
		wxString strName(_T(PROP_NM_RED));
		jsval attrValue = ToJS(cx, (int)r );
		JS_SetUCProperty(cx, 
			pObj, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T(PROP_NM_GREEN));
		jsval attrValue = ToJS(cx, (int)g );
		JS_SetUCProperty(cx, 
			pObj, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T(PROP_NM_BLUE));
		jsval attrValue = ToJS(cx, (int)b );
		JS_SetUCProperty(cx, 
			pObj, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}

	vp->setObjectOrNull( pObj );
	
    return JS_TRUE;
}
