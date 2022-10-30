/*
 * wxJavaScript - icon.cpp
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
 * $Id: icon.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// icon.cpp
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
#include "js/gui/misc/icon.h"
#include "js/gui/misc/bitmap.h"


using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_DEPTH			"depth"
#define PROP_NM_OK				"isOk"
#define PROP_NM_HEIGHT			"height"
#define PROP_NM_WIDTH			"width"
// for object
#define PROP_NM_NAME			"name"
#define PROP_NM_BITS			"bits"
#define PROP_NM_TYPE			"type"
#define PROP_NM_desiredWidth	"desiredWidth"
#define PROP_NM_desiredHeight	"desiredHeight"
#define PROP_NM_FILEPATH		"filepath"
#define PROP_NM_INDEX			"index"





/***
 * <file>misc/icon</file>
 * <module>gui</module>
 * <class name="wxIcon" prototype="@wxBitmap">
 *  An icon is a small rectangular bitmap usually used for denoting a minimized application. 
 *  It differs from a wxBitmap in always having a mask associated with it for transparent drawing. 
 *  On some platforms, icons and bitmaps are implemented identically,
 *  since there is no real distinction between a wxBitmap with a mask and an icon; 
 *  and there is no specific icon format on some platforms 
 *  (X-based applications usually standardize on XPMs for small bitmaps and icons). 
 *  However, some platforms (such as Windows) make the distinction, so a separate class is provided.
 *  See @wxBitmap, wxFrame @wxFrame#icon property and @wxBitmapType
 * </class>
 */
ZZZJS_INIT_CLASS(Icon, "Icon", 0)
	

ZZZJS_BEGIN_PROPERTY_MAP(Icon)
  ZZZJS_PROPERTY(P_DEPTH, PROP_NM_DEPTH)
  ZZZJS_PROPERTY(P_HEIGHT, PROP_NM_HEIGHT)
  ZZZJS_PROPERTY(P_WIDTH, PROP_NM_WIDTH)
  ZZZJS_READONLY_PROPERTY(P_OK, PROP_NM_OK)
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_METHOD_MAP(Icon)
  ZZZJS_METHOD("loadFile", loadFile, 1)
  ZZZJS_METHOD("copyFromBitmap", copyFromBitmap, 1)
ZZZJS_END_METHOD_MAP()



ZZZJS_BEGIN_GET_PROP(wxIcon, Icon)
{
    switch(id) 
	{
	case P_DEPTH:
		ToJSVal(cx, vp, p->GetDepth());
		break;
	case P_OK:
		ToJSVal(cx, vp, p->Ok());
		break;
	case P_WIDTH:
		ToJSVal(cx, vp, p->GetWidth());
		break;
	case P_HEIGHT:
		ToJSVal(cx, vp, p->GetHeight());
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxIcon, Icon)
{
    switch (id) 
	{
	case P_DEPTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetDepth(value);
			break;
		}
	case P_HEIGHT:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetHeight(value);
			break;
		}
	case P_WIDTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetWidth(value);
			break;
		}
	}
    return true;
}
ZZZJS_END_SET_PROP
/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>
 *    Filename
 *   </arg>
 *   <arg name="Type" type=ZZZJS_TYPE_NUMBER>
 *    The type of the Icon. Use the bitmap types.
 *   </arg>
 *   <arg name="DesiredWidth" type=ZZZJS_TYPE_NUMBER default="-1" />
 *   <arg name="DesiredHeight" type=ZZZJS_TYPE_NUMBER default="-1" />
 *  </function>
 *  <desc>
 *   Constructs a new wxIcon object. The first constructor creates
 *   an icon without data. Use @wxIcon#loadFile to load an icon.
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxIcon, Icon)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	/*
 	wxIcon ()
 		Default ctor. More...
 	wxIcon (const wxIcon &icon)
 		Copy ctor. More...
 	wxIcon (const char bits[], int width, int height)
 		Creates an icon from an array of bits. More...
 	wxIcon (const char *const *bits)
 		Creates a bitmap from XPM data. More...
 	wxIcon (const wxString &name, wxBitmapType type=wxICON_DEFAULT_TYPE, int desiredWidth=-1, int desiredHeight=-1)
 		Loads an icon from a file or resource. More...
 	wxIcon (const wxIconLocation &loc)
 		Loads an icon from the specified location.
	*/
	
	int argIndex = 0;

    if ( argc == 0 ) 
	{
        return new wxIcon();
	}

    if ( JSVAL_IS_STRING(argv[0]) )
    {
		// wxIcon (const wxString &name, wxBitmapType type=wxICON_DEFAULT_TYPE, int desiredWidth=-1, int desiredHeight=-1)

		ZZZJS_CHECK_ARG_COUNT(1, 4);

		int desiredWidth = -1;
		int desiredHeight = -1;
		int type=wxICON_DEFAULT_TYPE;
		wxString name;
		
		argIndex = argc -1;
		switch(argc)
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(desiredHeight, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(desiredWidth, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);
			argIndex--;
		default:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
			argIndex--;
			return new wxIcon(name, (wxBitmapType) type, desiredWidth, desiredHeight);
		}
    }
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}



			if( JS_IsUint8ClampedArray(pObj) == JS_TRUE ) {
				int width = -1,  height = -1;
					
				ZZZJS_CHECK_ARG_COUNT(3, 3);
				argIndex++;


				//wxIcon (const char bits[], int width, int height)
				uint32_t length = JS_GetTypedArrayLength(pObj);
				int8_t *data = JS_GetInt8ArrayData(pObj);
		
				argIndex++;

				// 1
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
				argIndex++;
				// 2
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
				argIndex++;


				return new wxIcon((const char*)data, width, height);
			} else {
				zzzJsPtr<wxIcon> apIcon;

				if( apIcon.set( 
					Icon::getObject2Instance(cx, pObj, apIcon.bAllocation) ) == true 
				) {
					if( apIcon.bAllocation == true ) {
						return apIcon.release();
					} else {
						return new wxIcon(*apIcon.get());
					}
				}
			}
		} while( 0 );
	}


    return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(wxIcon, Icon)
{

	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}
	
	// wxIcon (const wxString &name, wxBitmapType type=wxICON_DEFAULT_TYPE, int desiredWidth=-1, int desiredHeight=-1)
	/*
	{
			name:String
		,	type:Number(option. default=wx.ICON.DEFAULT_TYPE)
		,	desiredWidth:Number(option. default=-1)
		,	desiredHeight:Number(option. default=-1)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
	{
		int desiredWidth = -1;
		int desiredHeight = -1;
		int type=wxICON_DEFAULT_TYPE;
		wxString name;


		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, obj, PROP_NM_NAME, WXJS_TYPE_STRING);
		ZZZJS_PROP_FROMJS_IF_EXIST(type, obj, PROP_NM_NAME, WXJS_TYPE_NUMBER);
		ZZZJS_PROP_FROMJS_IF_EXIST(desiredWidth, obj, PROP_NM_desiredWidth, WXJS_TYPE_NUMBER);
		ZZZJS_PROP_FROMJS_IF_EXIST(desiredHeight, obj, PROP_NM_desiredHeight, WXJS_TYPE_NUMBER);

		
		return new wxIcon(name, (wxBitmapType) type, desiredWidth, desiredHeight);
	}

	// wxIcon (const char bits[], int width, int height)
	/*
	{
			bits: Uint8ClampedArray,
		,	width: Number
		,	height: Number
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_BITS), &v) == JS_TRUE )  
	{
		int width, height;
		int depth=wxBITMAP_SCREEN_DEPTH;

		// bits
		if( v.isObjectOrNull() == false ) {
			ReportError_PropTypeError(cx, PROP_NM_BITS, "Uint8ClampedArray");
			return NULL;
		}
		JSObject* pObj = v.toObjectOrNull();
		if( JS_IsUint8ClampedArray(pObj) == JS_FALSE ) {
			ReportError_PropTypeError(cx, PROP_NM_BITS, "Uint8ClampedArray");
			return NULL;
		}
		uint32_t length = JS_GetTypedArrayLength(pObj);
		int8_t *data = JS_GetInt8ArrayData(pObj);


		// width
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER)		
		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
		

		bAllocation = true;
		return new wxIcon((const char*)data, width, height);
	}

	//wxIcon (const wxIconLocation &loc)
	/*
	{
		filepath: String,
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_FILEPATH), &v) == JS_TRUE )  
	{
		wxString filepath;
		int			index = 0;
		// filepath
		if( FromJS(cx, v, filepath) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_FILEPATH, WXJS_TYPE_STRING);
			return NULL;
		}
		// index
		ZZZJS_PROP_FROMJS_IF_EXIST(index, obj, PROP_NM_INDEX, WXJS_TYPE_NUMBER);
		
		return new wxIcon( wxIconLocation(filepath, index) );
	}



	return NULL;
}
ZZZJS_END_O2I
/***
 * <method name="loadFile">
 *  <function returns="Boolean">
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>
 *    The name of the file.
 *   </arg>
 *   <arg name="Type" type=ZZZJS_TYPE_NUMBER>
 *    The type of the Icon.
 *   </arg>
 *  </function>
 *  <desc>
 *   Loads an icon from a file.
 *  </desc>
 * </method>
 */
//JSBool Icon::loadFile(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Icon, loadFile )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxIcon *p = GetPrivate(cx, obj);
	
	/*
		bool 	LoadFile (
				const wxString &name
				, wxBitmapType type=wxICON_DEFAULT_TYPE
				, int desiredWidth=-1
				, int desiredHeight=-1)
 			Loads an icon from a file or resource. More...
	*/
	int argIndex = 0;


    if ( JSVAL_IS_STRING(argv[argIndex]) )
    {
		// wxIcon (const wxString &name, wxBitmapType type=wxICON_DEFAULT_TYPE, int desiredWidth=-1, int desiredHeight=-1)

		ZZZJS_CHECK_ARG_COUNT(1, 4);

		int desiredWidth = -1;
		int desiredHeight = -1;
		int type=wxICON_DEFAULT_TYPE;
		wxString name;
		
		argIndex = argc -1;
		switch(argc)
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(desiredHeight, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(desiredWidth, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);
			argIndex--;
		default:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
			argIndex--;
			vp->setBoolean( p->LoadFile(name, (wxBitmapType) type, desiredWidth, desiredHeight) );
		}

		return JS_TRUE;
    }
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}


			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
			{
				int desiredWidth = -1;
				int desiredHeight = -1;
				int type=wxICON_DEFAULT_TYPE;
				wxString name;


				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_NAME, WXJS_TYPE_STRING);
				ZZZJS_PROP_FROMJS_IF_EXIST(type, pObj, PROP_NM_NAME, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(desiredWidth, pObj, PROP_NM_desiredWidth, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(desiredHeight, pObj, PROP_NM_desiredHeight, WXJS_TYPE_NUMBER);

		
				vp->setBoolean( p->LoadFile(name, (wxBitmapType) type, desiredWidth, desiredHeight) );
				return JS_TRUE;
			}
		} while( 0 );
	}	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD


	
ZZZJS_BEGIN_METHOD(Icon, copyFromBitmap )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxIcon *p = GetPrivate(cx, obj);

	
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;


	ZZZJS_ARG_AP_CHK_AND_ERROR(apBitmap, Bitmap);

	p->CopyFromBitmap( *(apBitmap.get()) );

	return JS_TRUE;
}
ZZZJS_END_METHOD