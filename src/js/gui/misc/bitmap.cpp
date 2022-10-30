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

// http://docs.wxwidgets.org/3.0/classwx_bitmap.html


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
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/image.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/mask.h"
#include "js/gui/misc/pallet.h"
#include "js/gui/misc/mask.h"
#include "js/gui/misc/size.h"
#include "js/gui/errors.h"
#include "js/gui/gdi/dc.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_DEPTH			"depth"
#define PROP_NM_HEIGHT			"height"
#define PROP_NM_OK				"isOk"
#define PROP_NM_WIDTH			"width"
// for object
#define PROP_NM_IMAGE			"img"
#define PROP_NM_SIZE			"size"
#define PROP_NM_NAME			"name"
#define PROP_NM_TYPE			"type"
#define PROP_NM_BITS			"bits"
#define PROP_NM_FILEPATH		"filepath"
// for arguments
#define PROP_NM_DC				"dc"
#define PROP_NM_ICON			"icon"
#define PROP_NM_logwidth		"logwidth"
#define PROP_NM_logheight		"logheight"
#define PROP_NM_logicalScale	"logicalScale"
#define PROP_NM_logicalScale	"logicalScale"

/***
 * <file>misc/bitmap</file>
 * <module>gui</module>
 * <class name="wxBitmap">
 *  This class encapsulates the concept of a platform-dependent bitmap, either monochrome or colour.
 *  See @wxIcon and @wxBitmapType
 * </class>
 */
ZZZJS_INIT_CLASS(Bitmap, "Bitmap", 0)
	
ZZZJS_BEGIN_CONSTANT_MAP(Bitmap)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, INVALID	)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, BMP	)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, BMP_RESOURCE	)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, ICO)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, ICO_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, CUR)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, CUR_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, XBM)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, XBM_DATA)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, XPM)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, XPM_DATA)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, TIFF)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, TIF)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, TIFF_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, TIF_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, GIF)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, GIF_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PNG)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PNG_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, JPEG)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, JPEG_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PNM)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PNM_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PCX)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PCX_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PICT)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, PICT_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, ICON)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, ICON_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, ANI)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, IFF)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, TGA)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, MACCURSOR)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, MACCURSOR_RESOURCE)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, MAX)
	ZZZJS_CONSTANT(wxBITMAP_TYPE_, ANY)

ZZZJS_END_CONSTANT_MAP()
/***
 * <properties>
 *  <property name="depth" type=WXJS_TYPE_NUMBER>
 *   Get/Set the colour depth of the bitmap. A value of 1 indicates a monochrome bitmap.
 *  </property>
 *  <property name="height" type=WXJS_TYPE_NUMBER>
 *   Get/Set the height of the bitmap in pixels.
 *  </property>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true when the bitmap data is available.
 *  </property>
 *  <property name="width" type=WXJS_TYPE_NUMBER>
 *   Get/Set the width of the bitmap in pixels.
 *  </property>
 * </properties>
 */


ZZZJS_BEGIN_PROPERTY_MAP(Bitmap)
  ZZZJS_PROPERTY(P_DEPTH, PROP_NM_DEPTH)
  ZZZJS_PROPERTY(P_HEIGHT, PROP_NM_HEIGHT)
  ZZZJS_READONLY_PROPERTY(P_OK, PROP_NM_OK)
  ZZZJS_PROPERTY(P_WIDTH, PROP_NM_WIDTH)
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Bitmap)
  ZZZJS_METHOD("create", create, 2)
  ZZZJS_METHOD("convertToImage", convertToImage, 0)
  ZZZJS_METHOD("copyFromIcon", copyFromIcon, 1)
  ZZZJS_METHOD("createScaled", createScaled, 4)
  ZZZJS_METHOD("loadFile", loadFile, 1)
  ZZZJS_METHOD("saveFile", saveFile, 2)
  ZZZJS_METHOD("setMask", setMask, 1)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxBitmap, Bitmap)
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
	case P_MASK:
		{
			wxMask *pMask = p->GetMask();
			vp.set( Mask::CreateObject(cx, new wxMask(*pMask)));
		}
		break;
	case P_PALETTE:
		{
			wxPalette *pPalette = p->GetPalette();
			vp.set( Palette::CreateObject(cx, new wxPalette(*pPalette)));
		}
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxBitmap, Bitmap)
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
	case P_MASK:
		{
			wxMask *pMask = Mask::GetPrivate(cx, vp);
			if ( pMask != NULL )
				p->SetMask(pMask);
			break;
		}
	case P_PALETTE:
		{
			wxPalette *pPalette = Palette::GetPrivate(cx, vp);
			if ( pPalette != NULL )
				p->SetPalette(*pPalette);
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
 *   <arg name="Name" type=WXJS_TYPE_STRING>Filename</arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER>The type of the bitmap.</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxBitmap object.
 *   See @wxBitmapType
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxBitmap, Bitmap)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	/*
 	wxBitmap ()
 		Default constructor. More...
 
 	wxBitmap (const wxBitmap &bitmap)
 		Copy constructor, uses reference counting. More...
 	wxBitmap (const wxImage &img, int depth=wxBITMAP_SCREEN_DEPTH)
 		Creates this bitmap object from the given image.	
 	wxBitmap (const wxSize &sz, int depth=wxBITMAP_SCREEN_DEPTH)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
 	wxBitmap (int width, int height, int depth=wxBITMAP_SCREEN_DEPTH)
 		Creates a new bitmap. More...
 	wxBitmap (const wxString &name, wxBitmapType type=wxBITMAP_DEFAULT_TYPE)
 		Loads a bitmap from a file or resource. More... 
 	wxBitmap (const char bits[], int width, int height, int depth=1)
 		Creates a bitmap from the given array bits. More...


 	wxBitmap (const char *const *bits)
 		Creates a bitmap from XPM data. More... 
	*/
	int argIndex = 0;

	wxImage* pImage = NULL;
	wxBitmap* pBitmap = NULL;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);


	if( argc == 0 ) {
		return new wxBitmap();
	}


	if( (ZZZJS_ARG_GET_PRIVATE(pBitmap, Bitmap)) != NULL ) {
		// wxBitmap (const wxBitmap &bitmap)
		return new wxBitmap(*pBitmap);
	}
	else
	if( (ZZZJS_ARG_GET_PRIVATE(pImage, Image)) != NULL ) {
		// wxBitmap (const wxImage &img, int depth=wxBITMAP_SCREEN_DEPTH)
		int depth=wxBITMAP_SCREEN_DEPTH;
		
		ZZZJS_CHECK_ARG_COUNT(1, 2);
		argIndex++;

		
		argIndex = argc -1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		}

		return new wxBitmap(*pImage, depth);
	}
	else 
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true)
	{
		// wxBitmap (const wxSize &sz, int depth=wxBITMAP_SCREEN_DEPTH)
		int depth=wxBITMAP_SCREEN_DEPTH;

		ZZZJS_CHECK_ARG_COUNT(1, 2);
		argIndex++;


		argIndex = argc -1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		}

		return new wxBitmap(*(apSize.get()), depth);
	}
	else
	if( argv[argIndex].isNumber() == true ) {
		// wxBitmap (int width, int height, int depth=wxBITMAP_SCREEN_DEPTH)
		int width = 0;
		int height = 0;
		int depth=wxBITMAP_SCREEN_DEPTH;

		ZZZJS_CHECK_ARG_COUNT(2, 3)
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;


		argIndex = argc -1;
		switch( argc ) 
		{
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		}
			
		return new wxBitmap(width, height, depth);
	}
	else
	if( argv[argIndex].isString() == true ) {
		// wxBitmap (const wxString &name, wxBitmapType type=wxBITMAP_DEFAULT_TYPE)
		wxString name;
		int type=wxBITMAP_DEFAULT_TYPE;

		
		ZZZJS_CHECK_ARG_COUNT(1, 2)

		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex++;

		// 1
		argIndex = argc -1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		}
		return new wxBitmap(name, (wxBitmapType) type);
	} 
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			if( JS_IsUint8ClampedArray(pObj) == JS_TRUE ) {
				int width,  height,  depth=1;
					
				ZZZJS_CHECK_ARG_COUNT(3, 4);
				argIndex++;


				//wxBitmap (const char bits[], int width, int height, int depth=1)
				uint32_t length = JS_GetTypedArrayLength(pObj);
				int8_t *data = JS_GetInt8ArrayData(pObj);
		
				argIndex++;

				// 1
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
				argIndex++;
				// 2
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
				argIndex++;

				argIndex = argc -1;
				switch( argc ) 
				{
				case 3:
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, WXJS_TYPE_NUMBER);
					argIndex--;
					break;
				}

				return new wxBitmap((const char*)data, width, height, depth);
			} else {
				zzzJsPtr<wxBitmap> apBitmap;

				if( apBitmap.set( 
					Bitmap::getObject2Instance(cx, pObj, apBitmap.bAllocation) ) == true 
				) {
					if( apBitmap.bAllocation == true ) {
						return apBitmap.release();
					} else {
						return new wxBitmap(*apBitmap.get());
					}
				}
			}
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
// Object 2 Instatance
//wxBitmap* Bitmap::getObject2Instance(JSContext *cx, JS::Value v, bool& bAllocation)
//{
//	bAllocation = false;
//	if( v.isObjectOrNull() == false ) {
//		return NULL;
//	}
//	return Bitmap::getObject2Instance(cx, v.toObjectOrNull(), bAllocation);
//}
//wxBitmap* Bitmap::getObject2Instance(JSContext *cx, JSObject *obj, bool& bAllocation)
//{
//	jsval v;
//	wxBitmap* pRet = NULL;
//
//	bAllocation = false;
ZZZJS_BEGIN_O2I(wxBitmap, Bitmap)
{

	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	// wxBitmap (const wxImage &img, int depth=wxBITMAP_SCREEN_DEPTH)
	/*
	{
		img: wxImage,
		depth: Number( option. default is wx.BITMAP_SCREEN_DEPTH)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_IMAGE), &v) == JS_TRUE )  
	{
		wxImage* pImg = Image::GetPrivate(cx, v);
		int depth=wxBITMAP_SCREEN_DEPTH;


		if( pImg == NULL ) {
			ReportError_PropTypeError(cx, PROP_NM_IMAGE, "Iamge");
			return NULL;
		}
		// depth		
		ZZZJS_PROP_FROMJS_IF_EXIST(depth, obj, PROP_NM_DEPTH, WXJS_TYPE_NUMBER)	


		bAllocation = true;
		return new wxBitmap(*pImg, depth);
	}


	// wxBitmap (const wxSize &sz, int depth=wxBITMAP_SCREEN_DEPTH)
	/*
	{
		size: wx.Size,
		depth: Number( option. default is wx.BITMAP_SCREEN_DEPTH)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
	{
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		int depth=wxBITMAP_SCREEN_DEPTH;

		ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_SIZE);

		// depth


		bAllocation = true;
		return new wxBitmap(*(apSize.get()), depth);
	}

	// wxBitmap (int width, int height, int depth=wxBITMAP_SCREEN_DEPTH)
	/*
	{
		width: Number,
		height: Number,
		depth: Number( option. default is wx.BITMAP_SCREEN_DEPTH)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_WIDTH), &v) == JS_TRUE )  
	{
		int width, height;
		int depth=wxBITMAP_SCREEN_DEPTH;

		// width
		if( FromJS(cx, v, width) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
			return NULL;
		}

		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)	
		// depth
		ZZZJS_PROP_FROMJS_IF_EXIST(depth, obj, PROP_NM_DEPTH, WXJS_TYPE_NUMBER)
		

		bAllocation = true;
		return new wxBitmap(width, height, depth);
	}
	// wxBitmap (const wxString &name, wxBitmapType type=wxBITMAP_DEFAULT_TYPE)
	/*
	{
		name: String,
		type: Number( option. default is wx.BITMAP_DEFAULT_TYPE)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
	{
		wxString name;
		int type=wxBITMAP_DEFAULT_TYPE;

		// name
		if( FromJS(cx, v, name) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_NAME, WXJS_TYPE_STRING);
			return NULL;
		}


		// type
		ZZZJS_PROP_FROMJS_IF_EXIST(type, obj, PROP_NM_TYPE, WXJS_TYPE_NUMBER)
			

		bAllocation = true;
		return new wxBitmap(name, (wxBitmapType)type);
	}
	//wxBitmap (const char bits[], int width, int height, int depth=1)
	/*
	{
		bits: Uint8ClampedArray,
		width: Number,
		height: Number,
		depth: Number( option. default is wx.BITMAP_SCREEN_DEPTH)
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
		uint8_t *data = JS_GetUint8ArrayData(pObj);


		// width
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER)		
		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
		// type
		ZZZJS_PROP_FROMJS_IF_EXIST(depth, obj, PROP_NM_DEPTH, WXJS_TYPE_NUMBER)
		

		bAllocation = true;
		return new wxBitmap((const char*)data, width, height, depth);
	}
	//bool 	LoadFile (const wxString &filepath, wxBitmapType type=wxBITMAP_DEFAULT_TYPE)
	/*
	{
		filepath: String,
		type: Number( option. default is wx.BITMAP_DEFAULT_TYPE)
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_FILEPATH), &v) == JS_TRUE )  
	{
		wxString filepath;
		int type=wxBITMAP_DEFAULT_TYPE;

		// filepath
		if( FromJS(cx, v, filepath) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_FILEPATH, WXJS_TYPE_STRING);
			return NULL;
		}


		// type
		ZZZJS_PROP_FROMJS_IF_EXIST(type, obj, PROP_NM_TYPE, WXJS_TYPE_NUMBER)


		wxBitmap* pRet =  new wxBitmap();

		if( pRet->LoadFile(filepath, (wxBitmapType)type) == false ) 
		{
			JS_ReportError(cx, "fai to load file:[%s].", (const char*)filepath.c_str());
			delete pRet;
			return NULL;
		}
		
		bAllocation = true;
		return pRet;
	}
	return NULL;
}
ZZZJS_END_O2I


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
//JSBool Bitmap::create(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, create )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);

	/*
		virtual bool 	Create (
				int width, 
				int height, 
				int depth=wxBITMAP_SCREEN_DEPTH
		)
 			Creates a fresh bitmap. More...
 
		virtual bool 	Create (
				const wxSize &sz, 
				int depth=wxBITMAP_SCREEN_DEPTH
		)
 			This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
 
		bool 	Create (
				int width, 
				int height, 
				const wxDC &dc
		)
 			Create a bitmap compatible with the given DC, inheriting its magnification factor.
	*/
	
	int argIndex = 0;
	int width = 0;
	int height = 0;
	int depth = wxBITMAP_SCREEN_DEPTH;
	wxDC* pDC = NULL;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);



	if( argv[argIndex].isNumber() == true ) {
		ZZZJS_CHECK_ARG_COUNT(2, 3)

		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER)
		argIndex++;

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 3:
			// wxDC or int depth=wxBITMAP_SCREEN_DEPTH
			pDC = zzzJs::gui::gdi::DC::GetPrivate(cx, argv[argIndex]);
			if( pDC == NULL ) {
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, "DC or Number")
			}
			argIndex--;
			break;
		}
		if( pDC != NULL ) {
			vp->setBoolean( p->Create( width, height, *pDC) );
		} else {
			vp->setBoolean( p->Create( width, height, depth) );
		}
		return JS_TRUE;
	}
	else
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true )
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2)
		
		switch( argc ) 
		{
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, WXJS_TYPE_NUMBER)
			argIndex++;
			break;
		}

		*vp = ToJS(cx, p->Create(*(apSize.get()), depth));
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();

		if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_WIDTH), &v) == JS_TRUE )  
		{
			// { width:***, height:***, [depth:***]}
			//    or
			// { width:***, height:***, dc:***}
			if( FromJS(cx, v, width) == false ) {
				ReportError_PropTypeError(cx, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			// height
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)

			// depth
			ZZZJS_PROP_FROMJS_IF_EXIST(depth, pObj, PROP_NM_DEPTH, WXJS_TYPE_NUMBER)
			if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_DC), &v) == JS_TRUE )
			{
				pDC = zzzJs::gui::gdi::DC::GetPrivate(cx, v);
				if( pDC == NULL ) {
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, "DC or Number")
					return JS_FALSE;
				}
			}


			if( pDC != NULL ) {
				*vp = ToJS(cx, p->Create(width, height, *pDC));
			} else {
				*vp = ToJS(cx, p->Create(width, height, depth));
			}
			return JS_TRUE;
		}
		else		
		if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
		{
			
			if( ZZZJS_PROP_GET_AP(apSize, Size, v) == false )
			{
				ReportError_PropTypeError(cx, PROP_NM_SIZE, Size::getClassName());
				return JS_FALSE;
			}
			ZZZJS_PROP_FROMJS_IF_EXIST(depth, pObj, PROP_NM_DEPTH, WXJS_TYPE_NUMBER)
				
			*vp = ToJS(cx, p->Create(*(apSize.get()), depth));

			return JS_TRUE;
		} 
	}
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}
ZZZJS_END_METHOD
	
/***
 * <method name="convertToImage">
 *  <function returns="Image">
 *  </function>
 *  <desc>
 *   Creates an image from a platform-dependent bitmap. 
 *  </desc>
 * </method>
 */
//JSBool Bitmap::convertToImage(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, convertToImage )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);
	
	/*
		virtual wxImage 	ConvertToImage () const
	*/
	wxImage img = p->ConvertToImage();
	*vp = Image::CreateObject(cx, new wxImage(img), NULL);
	
	return JS_FALSE;
}
ZZZJS_END_METHOD


/***
 * <method name="copyFromIcon">
 *  <function returns="Image">
 *  </function>
 *  <desc>
 *   Creates the bitmap from an icon.
 *  </desc>
 * </method>
 */
//JSBool Bitmap::copyFromIcon(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, copyFromIcon )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);
	
	/*
		virtual wxImage 	ConvertToImage () const
	*/
	int argIndex = 0;
	wxIcon* pIcon = NULL;

	// 0
	pIcon = Icon::GetPrivate(cx, argv[argIndex]);
	if( pIcon != NULL ) {
		vp->setBoolean( p->CopyFromIcon(*pIcon) );
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
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_ICON), &v) == JS_TRUE )  
			{
				// { icon:***}
				pIcon = Icon::GetPrivate(cx, argv[argIndex]);
				if( pIcon == NULL ) {
					ReportError_PropTypeError(cx, PROP_NM_ICON, Icon::getClassName());
					return JS_FALSE;
				}
				vp->setBoolean( p->CopyFromIcon(*pIcon) );
				return JS_TRUE;
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD	
/***
 * <method name="createScaled">
 *  <function returns="Image">
 *  </function>
 *  <desc>
 *   Creates the bitmap from an icon.
 *  </desc>
 * </method>
 */
//JSBool Bitmap::createScaled(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, createScaled )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);
	
	/*
		bool 	CreateScaled (
				int logwidth, 
				int logheight, 
				int depth, 
				double logicalScale)
 			Create a bitmap with a scale factor, width and height are multiplied with that factor. 
	*/
	int argIndex = 0;
	int logwidth;
	int logheight;
	int depth;
	double logicalScale;



	// 0
	if( argv[argIndex].isNumber() == true ) {
		ZZZJS_CHECK_ARG_COUNT(4, 4)
		// logwidth
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(logwidth, WXJS_TYPE_NUMBER)
		argIndex++;
		// logwidth
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(logheight, WXJS_TYPE_NUMBER)
		argIndex++;
		// logwidth
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(depth, WXJS_TYPE_NUMBER)
		argIndex++;
		// logwidth
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(logicalScale, WXJS_TYPE_DOUBLE)
		argIndex++;


		vp->setBoolean( p->CreateScaled(logwidth, 
					logheight, 
					depth, 
					logicalScale) );
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  logwidth:***
			, logheight:***
			, depth:***
			, logicalScale:***
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}

			// logwidth
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(logwidth, pObj, PROP_NM_logwidth, WXJS_TYPE_NUMBER)
			// logwidth
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(logheight, pObj, PROP_NM_logheight, WXJS_TYPE_NUMBER)
			// logwidth
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(depth, pObj, PROP_NM_DEPTH, WXJS_TYPE_NUMBER)
			// logwidth
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(logicalScale, pObj, PROP_NM_logicalScale, WXJS_TYPE_DOUBLE)


			vp->setBoolean( p->CreateScaled(logwidth, 
						logheight, 
						depth, 
						logicalScale) );
			return JS_TRUE;
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD	
	
/***
 * <method name="loadFile">
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the file.
 *   </arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER>
 *    The type of the bitmap.
 *   </arg>
 *  </function>
 *  <desc>
 *   Loads a bitmap from a file.
 *  </desc>
 * </method>
 */
//JSBool Bitmap::loadFile(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, loadFile )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);
	
	/*
		virtual bool 	LoadFile (
				const wxString &name, 
				wxBitmapType type=wxBITMAP_DEFAULT_TYPE
		)
 		Loads a bitmap from a file or resource.
	*/
	int argIndex = 0;
	wxString name;
	int type = wxBITMAP_DEFAULT_TYPE;

	// 0
	if( argv[argIndex].isString() == true ) {
		ZZZJS_CHECK_ARG_COUNT(1, 2)

		// name
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING)
		argIndex++;

		argIndex = argc - 1;
		switch( argIndex ) 
		{
		case 1:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER)
			argIndex--;
			break;
		}
		vp->setBoolean( p->LoadFile( name, (wxBitmapType)type) );
		return JS_TRUE;
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

			// name
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_NAME, WXJS_TYPE_STRING)
			argIndex++;
			// type
			ZZZJS_PROP_FROMJS_IF_EXIST(type, pObj, PROP_NM_TYPE, WXJS_TYPE_NUMBER)
			argIndex++;

		
			vp->setBoolean( p->LoadFile( name, (wxBitmapType)type) );
			return JS_TRUE;
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

	
/***
 * <method name="saveFile">
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the file.
 *   </arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER>
 *    The type of the bitmap.
 *   </arg>
 *   <arg name="Type" type="Palette">
 *    An optional palette used for saving the bitmap.
 *   </arg>
 *  </function>
 *  <desc>
 *   Saves a bitmap in the named file. 
 *  </desc>
 * </method>
 */
//JSBool Bitmap::saveFile(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, saveFile )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);
	
	/*
		virtual bool 	SaveFile (
				const wxString &name, 
				wxBitmapType type, 
				const wxPalette *palette=NULL) const
 			Saves a bitmap in the named file.
	*/
	int argIndex = 0;
	wxString name;
	int type = wxBITMAP_DEFAULT_TYPE;
	wxPalette *palette=NULL;



	// 0
	if( argv[argIndex].isString() == true ) {
		ZZZJS_CHECK_ARG_COUNT(2, 3)

			
		// name
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING)
		argIndex++;
		// type
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER)
		argIndex++;
		
		// 1
		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			if ( (ZZZJS_ARG_GET_PRIVATE(palette, Palette)) == NULL )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Palette");
				return JS_FALSE;
			}
			argIndex--;
			break;
		}

		vp->setBoolean( p->SaveFile( name, (wxBitmapType)type, palette) );

		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  name:***
			, type:***
			, palette:Palette[option. default=null]
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}

			// name
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_NAME, WXJS_TYPE_STRING)
			argIndex++;
			// type
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, pObj, PROP_NM_TYPE, WXJS_TYPE_NUMBER)
			argIndex++;



			// palette
			ZZZJS_PROP_PRIVATE_IF_EXIST(palette, pObj, Palette, "palette", "Palette")

			vp->setBoolean( p->LoadFile( name, (wxBitmapType)type) );
			return JS_TRUE;
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

 

	
/***
 * <method name="setMask">
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the file.
 *   </arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER>
 *    The type of the bitmap.
 *   </arg>
 *   <arg name="Type" type="Palette">
 *    An optional palette used for saving the bitmap.
 *   </arg>
 *  </function>
 *  <desc>
 *   Saves a bitmap in the named file. 
 *  </desc>
 * </method>
 */
//JSBool Bitmap::setMask(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Bitmap, setMask )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBitmap *p = GetPrivate(cx, obj);
	
	/*
		void wxBitmap::SetMask	(	wxMask * 	mask	)	

		The bitmap object owns the mask once this has been called.
	*/
	int argIndex = 0;
	wxMask *pMask=NULL;


	if ( (ZZZJS_ARG_GET_PRIVATE(pMask, Mask)) == NULL )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Mask");
		return JS_FALSE;
	}
	
	wxMask *pMaskSet =new wxMask( *pMask );
	p->SetMask( pMaskSet );
	
	return JS_TRUE;
}
ZZZJS_END_METHOD