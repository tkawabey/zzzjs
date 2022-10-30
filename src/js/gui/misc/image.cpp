/*
 * wxJavaScript - image.cpp
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
 * $Id: image.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
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
#include "js/gui/misc/image.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/imghand.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/common/jsutil.h"
#include "js/ext/point.h"
#include "js/io/stream.h"
#include "js/io/istream.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_SIZE				"size"
#define PROP_NM_CLEAR				"clear"
#define PROP_NM_DATA				"data"
#define PROP_NM_STATIC_DATA			"static_data"
#define PROP_NM_ALPHA				"alpha"
#define PROP_NM_HEIGHT				"height"
#define PROP_NM_WIDTH				"width"
#define PROP_NM_NAME				"name"
#define PROP_NM_VALUE				"value"
#define PROP_NM_FILEPATH			"filepath"
#define PROP_NM_TYPE				"type"
#define PROP_NM_MIMETYPE			"mimetype"
#define PROP_NM_INDEX				"index"
#define PROP_NM_STREAM				"stream"
// for object
#define PROP_NM_IMAGE				"image"
#define PROP_NM_X					"x"
#define PROP_NM_Y					"y"
#define PROP_NM_QUALITY				"quality"
#define PROP_NM_ANGLE				"angle"
#define PROP_NM_CENTER				"center"
#define PROP_NM_INTERPOLATING		"interpolating"
#define PROP_NM_OFFSET_AFTER_RORATION		"offsetAfterRotation"
#define PROP_NM_COLOUR				"colour"
#define PROP_NM_COLOUR1				"colour1"
#define PROP_NM_COLOUR2				"colour2"
#define PROP_NM_R1					"r1"
#define PROP_NM_G1					"g1"
#define PROP_NM_B1					"b1"
#define PROP_NM_R2					"r2"
#define PROP_NM_G2					"g2"
#define PROP_NM_B2					"b2"
#define PROP_NM_POS					"pos"
#define PROP_NM_RED					"red"
#define PROP_NM_GREEN				"green"
#define PROP_NM_BLUE				"blue"
#define PROP_NM_THRESHOLD			"threshold"
#define PROP_NM_WEIGHT_R			"weight_r"
#define PROP_NM_WEIGHT_G			"weight_g"
#define PROP_NM_WEIGHT_B			"weight_b"
#define PROP_NM_BRIGHTNESS			"brightness"
#define PROP_NM_RECT				"rect"
#define PROP_NM_POS					"pos"
#define PROP_NM_START				"start"
#define PROP_NM_START_R				"startR"
#define PROP_NM_START_G				"startG"
#define PROP_NM_START_B				"startB"
#define PROP_NM_MASK				"mask"




/***
 * <file>misc/image</file>
 * <module>gui</module>
 * <class name="wxImage">
 *  This class encapsulates a platform-independent image. An image can be loaded from a 
 *  file in a variety of formats.
 * </class>
 */
ZZZJS_INIT_CLASS(Image, "Image", 0)

/***
 * <properties>
 *  <property name="hasMask" type="Boolean" readonly="Y">
 *   Returns true when a mask is active.
 *  </property>
 *  <property name="hasPalette" type="Boolean" readonly="Y">
 *   Returns true when a palette is used.
 *  </property>
 *  <property name="height" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Gets the height of the image in pixels.
 *  </property>
 *  <property name="mask" type="Boolean">
 *   Specifies whether there is a mask or not. The area of the mask is determined 
 *   by the current mask colour.
 *  </property>
 *  <property name="maskBlue" type=ZZZJS_TYPE_NUMBER>
 *   Returns the blue value of the mask colour.
 *  </property>
 *  <property name="maskGreen" type=ZZZJS_TYPE_NUMBER>
 *   Returns the green value of the mask colour.
 *  </property>
 *  <property name="maskRed" type=ZZZJS_TYPE_NUMBER>
 *  Returns the red value of the mask colour.
 *  </property>
 *  <property name="ok" type="Boolean" readonly="Y">
 *  Returns true when the image data is available.
 *  </property>
 *  <property name="size" type="@wxSize" readonly="Y">
 *   Returns the size of the image in pixels.
 *  </property>
 *  <property name="width" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the width of the image in pixels.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Image)
    ZZZJS_READONLY_PROPERTY(P_OK, "ok")
    ZZZJS_PROPERTY(P_MASK_RED, "maskRed")
    ZZZJS_PROPERTY(P_MASK_GREEN, "maskGreen")
    ZZZJS_PROPERTY(P_MASK_BLUE, "maskBlue")
    ZZZJS_PROPERTY(P_WIDTH, "width")
    ZZZJS_PROPERTY(P_HEIGHT, "height")
    ZZZJS_PROPERTY(P_MASK, "mask")
    ZZZJS_READONLY_PROPERTY(P_HAS_MASK, "hasMask")
    ZZZJS_READONLY_PROPERTY(P_HAS_PALETTE, "hasPalette")
    ZZZJS_PROPERTY(P_PALETTE, "palette")
    ZZZJS_READONLY_PROPERTY(P_SIZE, "size")
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_GET_PROP(wxImage, Image)
{
    switch (id)
    {
    case P_OK:
        ToJSVal(cx, vp, p->Ok());
        break;
    case P_MASK_RED:
        ToJSVal(cx, vp, (int) p->GetMaskRed());
        break;
    case P_MASK_GREEN:
        ToJSVal(cx, vp, (int) p->GetMaskGreen());
        break;
    case P_MASK_BLUE:
        ToJSVal(cx, vp, (int) p->GetMaskBlue());
        break;
    case P_WIDTH:
        ToJSVal(cx, vp, p->GetWidth());
        break;
    case P_HEIGHT:
        ToJSVal(cx, vp, p->GetHeight());
        break;
    case P_MASK:
    case P_HAS_MASK:
        ToJSVal(cx, vp, p->HasMask());
        break;
    case P_HAS_PALETTE:
        ToJSVal(cx, vp, p->HasPalette());
        break;
    case P_PALETTE:
        vp.set( JSVAL_VOID );
        break;
    case P_SIZE:
        vp.set( Size::CreateObject(cx, new wxSize(p->GetWidth(), p->GetHeight())) );
        break;
    }
    return true;
}
ZZZJS_END_GET_PROP
	
ZZZJS_BEGIN_SET_PROP(wxImage, Image)
{
    switch (id)
    {
    case P_MASK_RED:
        {
            int maskRed;
            if ( FromJS(cx, vp, maskRed) )
            {
                unsigned char g = p->GetMaskGreen();
                unsigned char b = p->GetMaskBlue();
                p->SetMaskColour((unsigned char) maskRed, g, b);
            }
            break;
        }
    case P_MASK_GREEN:
        {
            int maskGreen;
            if ( FromJS(cx, vp, maskGreen) )
            {
                unsigned char r = p->GetMaskRed();
                unsigned char b = p->GetMaskBlue();
                p->SetMaskColour(r, (unsigned char) maskGreen, b);
            }
            break;
        }
    case P_MASK_BLUE:
        {
            int maskBlue;
            if ( FromJS(cx, vp, maskBlue) )
            {
                unsigned char r = p->GetMaskRed();
                unsigned char g = p->GetMaskGreen();
                p->SetMaskColour(r, g, (unsigned char) maskBlue);
            }
            break;
        }
    case P_MASK:
        {
            bool mask;
            if ( FromJS(cx, vp, mask) )
                p->SetMask(mask);
            break;
        }
    case P_PALETTE:
        break;
    }
    return true;
}
ZZZJS_END_SET_PROP

/***
 * <class_properties>
 *  <property name="handlers" type="Array" readonly="Y">
 *   Array of @wxImageHandler elements. Get the available list of image handlers.
 *  </property>
 * </class_properties>
 */
ZZZJS_BEGIN_STATIC_PROPERTY_MAP(Image)
    ZZZJS_READONLY_PROPERTY(P_HANDLERS, "handlers")
ZZZJS_END_PROPERTY_MAP()

bool Image::GetStaticProperty(JSContext *cx, int id, jsval *vp)
{
	if ( id == P_HANDLERS )
	{
        wxList handlers = wxImage::GetHandlers();
		size_t count = handlers.GetCount();
		JSObject *objHandlers = JS_NewArrayObject(cx, count, NULL);

		*vp = OBJECT_TO_JSVAL(objHandlers);

        size_t i = 0;
        for ( wxNode *node = handlers.GetFirst(); node; node = node->GetNext() )
        {
            wxImageHandler *handler = (wxImageHandler*) node->GetData();
            ImageHandlerPrivate *priv = new ImageHandlerPrivate(handler, false);
            jsval element = ImageHandler::CreateObject(cx, priv, NULL);
			JS_SetElement(cx, objHandlers, i++, &element);
        }
    }
    return true;
}

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Width" type=ZZZJS_TYPE_NUMBER>
 *    The width of the image.
 *   </arg>
 *   <arg name="Height" type=ZZZJS_TYPE_NUMBER>
 *    The height of the image.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="size" type="@wxSize">
 *    The size of the image.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>
 *    The name of a file from which to load the image.
 *   </arg>
 *   <arg name="Type" type=ZZZJS_TYPE_NUMBER default="wxBitmapType.ANY">
 *    The type of the image.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>
 *    The name of a file from which to load the image.
 *   </arg>
 *   <arg name="MimeType" type=ZZZJS_TYPE_STRING>
 *    The MIME type of the image.
 *   </arg>
 *  </function>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxImage, Image)
{
	wxImage* p = new wxImage();

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



ZZZJS_BEGIN_O2I(wxImage, Image)
{

	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}


	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
	{
 		//wxImage (const wxSize &sz, bool clear=true)
 		//wxImage (const wxSize &sz, unsigned char *data, bool static_data=false)
 		//wxImage (const wxSize &sz, unsigned char *data, unsigned char *alpha, bool static_data=false)

		zzzJsPtr<wxSize> apSize;

		// size
		ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_SIZE);
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_DATA), &v) == JS_TRUE )  
		{
			// dataの指定がある。

			bool static_data=false;

			// bits
			if( v.isObjectOrNull() == false ) {
				ReportError_PropTypeError(cx, PROP_NM_DATA, "Uint8ClampedArray");
				return NULL;
			}
			JSObject* pObj = v.toObjectOrNull();
			if( JS_IsUint8ClampedArray(pObj) == JS_FALSE ) {
				ReportError_PropTypeError(cx, PROP_NM_DATA, "Uint8ClampedArray");
				return NULL;
			}
			uint32_t length_ = JS_GetTypedArrayLength(pObj);
			uint8_t *data = JS_GetUint8ArrayData(pObj);

			// static_data
			ZZZJS_PROP_FROMJS_IF_EXIST(static_data, obj, PROP_NM_STATIC_DATA, WXJS_TYPE_BOOLEAN)

			if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_ALPHA), &v) == JS_TRUE )  
			{

				if( v.isObjectOrNull() == false ) {
					ReportError_PropTypeError(cx, PROP_NM_ALPHA, "Uint8ClampedArray");
					return NULL;
				}
				JSObject* pObj = v.toObjectOrNull();
				if( JS_IsUint8ClampedArray(pObj) == JS_FALSE ) {
					ReportError_PropTypeError(cx, PROP_NM_ALPHA, "Uint8ClampedArray");
					return NULL;
				}
				uint32_t length_alpha = JS_GetTypedArrayLength(pObj);
				uint8_t *alpha = JS_GetUint8ArrayData(pObj);


				
				bAllocation = true;
				return new wxImage(*(apSize.get()), data, alpha, static_data);
			} 
			else 
			{
				bAllocation = true;
				return new wxImage(*(apSize.get()), data, static_data);
			}
		} else {
			bool clear=true;

			// clear
			ZZZJS_PROP_FROMJS_IF_EXIST(clear, obj, PROP_NM_STATIC_DATA, WXJS_TYPE_BOOLEAN)


			bAllocation = true;
			return new wxImage(*(apSize.get()), clear);
		}
	}

	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_WIDTH), &v) == JS_TRUE )  
	{
        int width;
        int height;
		bool clear=true;

 		//wxImage (int width, int height, bool clear=true)
 		//wxImage (int width, int height, unsigned char *data, bool static_data=false)
 		//wxImage (int width, int height, unsigned char *data, unsigned char *alpha, bool static_data=false)

		// width
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER)		
		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
		
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_DATA), &v) == JS_TRUE )  
		{
			// dataの指定がある。

			bool static_data=false;

			// bits
			if( v.isObjectOrNull() == false ) {
				ReportError_PropTypeError(cx, PROP_NM_DATA, "Uint8ClampedArray");
				return NULL;
			}
			JSObject* pObj = v.toObjectOrNull();
			if( JS_IsUint8ClampedArray(pObj) == JS_FALSE ) {
				ReportError_PropTypeError(cx, PROP_NM_DATA, "Uint8ClampedArray");
				return NULL;
			}
			uint32_t length_ = JS_GetTypedArrayLength(pObj);
			uint8_t *data = JS_GetUint8ArrayData(pObj);

			// static_data
			ZZZJS_PROP_FROMJS_IF_EXIST(static_data, obj, PROP_NM_STATIC_DATA, WXJS_TYPE_BOOLEAN)

			if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_ALPHA), &v) == JS_TRUE )  
			{

				if( v.isObjectOrNull() == false ) {
					ReportError_PropTypeError(cx, PROP_NM_ALPHA, "Uint8ClampedArray");
					return NULL;
				}
				JSObject* pObj = v.toObjectOrNull();
				if( JS_IsUint8ClampedArray(pObj) == JS_FALSE ) {
					ReportError_PropTypeError(cx, PROP_NM_ALPHA, "Uint8ClampedArray");
					return NULL;
				}
				uint32_t length_alpha = JS_GetTypedArrayLength(pObj);
				uint8_t *alpha = JS_GetUint8ArrayData(pObj);


				
				bAllocation = true;
				return new wxImage(width, height, data, alpha, static_data);
			} 
			else 
			{
				bAllocation = true;
				return new wxImage(width, height, data, static_data);
			}
		} else {
			bool clear=true;

			// clear
			ZZZJS_PROP_FROMJS_IF_EXIST(clear, obj, PROP_NM_STATIC_DATA, WXJS_TYPE_BOOLEAN)


			bAllocation = true;
			return new wxImage(width, height, clear);
		}
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_FILEPATH), &v) == JS_TRUE )  
	{
		wxString filepath;
		int index=-1;

		// filepath
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(filepath, obj, PROP_NM_WIDTH, WXJS_TYPE_STRING);
		// index
		ZZZJS_PROP_FROMJS_IF_EXIST(index, obj, PROP_NM_INDEX, WXJS_TYPE_NUMBER);
		
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_TYPE), &v) == JS_TRUE )  
		{
			int type=wxBITMAP_TYPE_ANY;

			// width
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
			
			bAllocation = true;
			return new wxImage(filepath, (wxBitmapType)type, index);
		}
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_MIMETYPE), &v) == JS_TRUE )  
		{
			wxString mimetype;

			// mimetype
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(mimetype, obj, PROP_NM_MIMETYPE, WXJS_TYPE_NUMBER);
			
			bAllocation = true;
			return new wxImage(filepath, mimetype, index);
		}
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_STREAM), &v) == JS_TRUE )  
	{
		/*
 		wxImage (wxInputStream &stream, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 		wxImage (wxInputStream &stream, const wxString &mimetype, int index=-1)
		*/
		int index=-1;
		zzzJs::io::Stream* pStream= zzzJs::io::InputStream::GetPrivate(cx, v);
		if( pStream == NULL ) {
			ReportError_PropTypeError(cx, PROP_NM_STREAM, "InputStream");
		}
		
		wxInputStream* pIStrem = (wxInputStream*)pStream->GetStream();

		// index
		ZZZJS_PROP_FROMJS_IF_EXIST(index, obj, PROP_NM_INDEX, WXJS_TYPE_NUMBER);
		
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_TYPE), &v) == JS_TRUE )  
		{
			int type=wxBITMAP_TYPE_ANY;

			// width
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
			
			bAllocation = true;
			return new wxImage(*pIStrem, (wxBitmapType)type, index);
		}
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_MIMETYPE), &v) == JS_TRUE )  
		{
			wxString mimetype;

			// mimetype
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(mimetype, obj, PROP_NM_MIMETYPE, WXJS_TYPE_NUMBER);
			
			bAllocation = true;
			return new wxImage(*pIStrem, mimetype, index);
		}
	}

	return NULL;
}
ZZZJS_END_O2I

ZZZJS_BEGIN_METHOD_MAP(Image)
    ZZZJS_METHOD("create", create, 1)
    ZZZJS_METHOD("destroy", destroy, 0)
    ZZZJS_METHOD("copy", copy, 0)
    ZZZJS_METHOD("getSubImage", getSubImage, 1)
    ZZZJS_METHOD("paste", paste, 1)
    ZZZJS_METHOD("blur", blur, 1)
    ZZZJS_METHOD("blurHorizontal", blurHorizontal, 1)
    ZZZJS_METHOD("blurVertical", blurVertical, 1)
    ZZZJS_METHOD("scale", scale, 1)
    ZZZJS_METHOD("rescale", rescale, 1)
    ZZZJS_METHOD("rotate", rotate, 2)
    ZZZJS_METHOD("rotate90", rotate90, 0)
    ZZZJS_METHOD("rotate180", rotate180, 0)
    ZZZJS_METHOD("rotateHue", rotateHue, 1)
    ZZZJS_METHOD("mirror", mirror, 0)
    ZZZJS_METHOD("replace", replace, 1)
    ZZZJS_METHOD("size", _size, 1)
	// Conversion functions
    ZZZJS_METHOD("convertToMono", convertToMono, 1)
    ZZZJS_METHOD("convertAlphaToMask", convertAlphaToMask, 0)
    ZZZJS_METHOD("convertToGreyscale", convertToGreyscale, 0)
    ZZZJS_METHOD("convertToDisabled", convertToDisabled, 0)
	// 
    ZZZJS_METHOD("setRGB", setRGB, 1)
    ZZZJS_METHOD("getRed", getRed, 1)
    ZZZJS_METHOD("getGreen", getGreen, 1)
    ZZZJS_METHOD("getBlue", getBlue, 1)
    ZZZJS_METHOD("getColour", getColour, 1)
    ZZZJS_METHOD("findFirstUnusedColour", findFirstUnusedColour, 1)
    ZZZJS_METHOD("setMaskFromImage", setMaskFromImage, 1)
    ZZZJS_METHOD("loadFile", loadFile, 1)
    ZZZJS_METHOD("saveFile", saveFile, 1)
    ZZZJS_METHOD("setMaskColour", setMaskColour, 1)
    ZZZJS_METHOD("setOption", setOption, 1)
    ZZZJS_METHOD("getOption", getOption, 1)
    ZZZJS_METHOD("getOptionInt", getOptionInt, 1)
    ZZZJS_METHOD("hasOption", hasOption, 1)
ZZZJS_END_METHOD_MAP()



JSBool Image::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
ZZZJS_FUNC_ENT
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;


	if( argc == 0 ) 
	{
		return JS_TRUE;
	}
	/*
 	wxImage ()
 	wxImage (int width, int height, bool clear=true)
 	wxImage (const wxSize &sz, bool clear=true)
 	wxImage (int width, int height, unsigned char *data, bool static_data=false)
 	wxImage (const wxSize &sz, unsigned char *data, bool static_data=false)
 	wxImage (int width, int height, unsigned char *data, unsigned char *alpha, bool static_data=false)
 	wxImage (const wxSize &sz, unsigned char *data, unsigned char *alpha, bool static_data=false)
 	wxImage (const char *const *xpmData)
 	wxImage (const wxString &name, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 	wxImage (const wxString &name, const wxString &mimetype, int index=-1)
 	wxImage (wxInputStream &stream, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 	wxImage (wxInputStream &stream, const wxString &mimetype, int index=-1)
	*/
	/*
	bool 	Create (const wxSize &sz, bool clear=true)
	bool 	Create (const wxSize &sz, unsigned char *data, bool static_data=false)
	bool 	Create (const wxSize &sz, unsigned char *data, unsigned char *alpha, bool static_data=false)
	bool 	Create (int width, int height, bool clear=true)
	bool 	Create (int width, int height, unsigned char *data, bool static_data=false)
	bool 	Create (int width, int height, unsigned char *data, unsigned char *alpha, bool static_data=false)
	*/
	/*
	virtual bool 	LoadFile (wxInputStream &stream, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
	virtual bool 	LoadFile (const wxString &name, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
	virtual bool 	LoadFile (const wxString &name, const wxString &mimetype, int index=-1)
	virtual bool 	LoadFile (wxInputStream &stream, const wxString &mimetype, int index=-1)
	*/
	
	int argIndex = 0;


	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);

	rval->setBoolean( JS_FALSE );

    if( ZZZJS_ARG_GET_AP(apSize, Size) == true )
    {
		// wxImage (const wxSize &sz, bool clear=true)
		ZZZJS_CHECK_ARG_COUNT(1, 2);

		bool clear=true;
		
		argIndex = argc-1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(clear, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}
		if( p->Create( apSize->GetWidth(), apSize->GetHeight(), clear) == false ) {
			return JS_FALSE;
		}
		rval->setBoolean( JS_TRUE );
		return JS_TRUE;
    }
	else
    if ( JSVAL_IS_INT(argv[argIndex]) )
    {
		// wxImage (int width, int height, bool clear=true)
		ZZZJS_CHECK_ARG_COUNT(2, 3);

        int width;
        int height;
		bool clear=true;

		argIndex = 0;
		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		// 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;
		
		
		argIndex = argc-1;
		switch( argc ) 
		{
		case 3:
			// 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(clear, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}
		
		if( p->Create(width, height, clear) == false ) {
			return JS_FALSE;
		}
		rval->setBoolean( JS_TRUE );
		return JS_TRUE;
    }
	else
    if ( JSVAL_IS_STRING(argv[argIndex]) )
    {
 		//	wxImage (const wxString &name, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 		//	wxImage (const wxString &name, const wxString &mimetype, int index=-1)

		ZZZJS_CHECK_ARG_COUNT(1, 3);

		wxString name;
		
		argIndex = 0;
		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex++;
		
		if( argc == 1 ) {

			if( p->LoadFile(name) == false ) {
				return JS_FALSE;
			}
			rval->setBoolean( JS_TRUE );
			return JS_TRUE;
		}
		ZZZJS_CHECK_ARG_COUNT(2, 3);
		if ( JSVAL_IS_INT(argv[argIndex]) ) 
		{
			int type=wxBITMAP_TYPE_ANY;
			int index=-1;
			
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);
			argIndex = argc -1;
			switch( argc ) 
			{
			case 3:
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
				argIndex--;
			}
			if( p->LoadFile(name, (wxBitmapType)type, index) == false ) {
				return JS_FALSE;
			}
			rval->setBoolean( JS_TRUE );
			return JS_TRUE;
		}
		else
		if ( JSVAL_IS_STRING(argv[argIndex]) )
		{
			wxString mimetype;
			int index=-1;
			
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mimetype, WXJS_TYPE_STRING);
			argIndex = argc -1;
			switch( argc ) 
			{
			case 3:
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
				argIndex--;
			}
			if( p->LoadFile(name, mimetype, index) == false ) {
				return JS_FALSE;
			}
			rval->setBoolean( JS_TRUE );
			return JS_TRUE;
		}
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			zzzJs::io::Stream* pStream= zzzJs::io::InputStream::GetPrivate(cx, pObj);
			if( pStream != NULL ) 
			{
 				//wxImage (wxInputStream &stream, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 				//wxImage (wxInputStream &stream, const wxString &mimetype, int index=-1)

				wxInputStream* pIStrem = (wxInputStream*)pStream->GetStream();
				if( argc == 1 ) 
				{
					if( p->LoadFile(*pIStrem) == false ) {
						return JS_FALSE;
					}
					rval->setBoolean( JS_TRUE );
					return JS_TRUE;
				}

				argIndex++;
				if ( JSVAL_IS_INT(argv[argIndex]) )
				{

					int type=wxBITMAP_TYPE_ANY;
					int index=-1;
			
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);
					argIndex = argc -1;
					switch( argc ) 
					{
					case 3:
						ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
						argIndex--;
					}
					if( p->LoadFile(*pIStrem, (wxBitmapType)type, index) == false ) {
						return JS_FALSE;
					}
					rval->setBoolean( JS_TRUE );
					return JS_TRUE;
				}
				else
				if ( JSVAL_IS_STRING(argv[argIndex]) )
				{
					wxString mimetype;
					int index=-1;
			
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mimetype, WXJS_TYPE_STRING);
					argIndex = argc -1;
					switch( argc ) 
					{
					case 3:
						ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
						argIndex--;
					}
					if( p->LoadFile(*pIStrem, mimetype, index) == false ) {
						return JS_FALSE;
					}
					rval->setBoolean( JS_TRUE );
					return JS_TRUE;
				}
			} else {
				zzzJsPtr<wxImage> apImage;

				if( apImage.set( 
					Image::getObject2Instance(cx, pObj, apImage.bAllocation) ) == true 
				) {
					delete p;
					
					if( apImage.bAllocation == true ) {
						p =  apImage.release();
					} else {
						p = new wxImage(*apImage.get());
					}
					SetPrivate(cx, obj, p);
					rval->setBoolean( JS_TRUE );
					return JS_TRUE;
				}
			}
		} while( 0 );
	}
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
/***
 * <method name="create">
 *  <function>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the image.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the image.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Size" type="@wxSize">
 *    The size of the image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh image with the given size.
 *  </desc>
 * </method>
 */
//JSBool Image::create(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(Image, create )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);
}
ZZZJS_END_METHOD

/***
 * <method name="destroy">
 *  <function />
 *  <desc>
 *   Destroys the image data.
 *  </desc>
 * </method>
 */
JSBool Image::destroy(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
    
    p->Destroy();
    return JS_TRUE;
}

/***
 * <method name="copy">
 *  <function returns="wxImage" />
 *  <desc>
 *   Returns an identical copy of image.
 *  </desc>
 * </method>
 */
JSBool Image::copy(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
    
    *vp = CreateObject(cx, new wxImage(p->Copy()));
    return JS_TRUE;
}

/***
 * <method name="getSubImage">
 *  <function returns="wxImage">
 *   <arg name="Rect" type="@wxRect" />
 *  </function>
 *  <desc>
 *   Returns a sub image of the current one as long as the rect belongs entirely to the image.
 *  </desc>
 * </method>
 */
JSBool Image::getSubImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
    
	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;

	if( ZZZJS_ARG_GET_AP(apRect, Rect) == true )
	{
        *vp = CreateObject(cx, new wxImage(p->GetSubImage(*(apRect.get()))));
        return JS_TRUE;
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="paste">
 *  <function>
 *   <arg name="Image" type="wxImage">
 *    The image to paste.
 *   </arg>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>
 *    The x position.
 *   </arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>
 *    The y position.
 *   </arg>
 *  </function>
 *  <desc>
 *   Pastes image into this instance and takes care of
 *   the mask colour and out of bounds problems.
 *  </desc>
 * </method>
 */
JSBool Image::paste(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// void 	Paste (const wxImage &image, int x, int y)
	
	int argIndex = 0;
	zzzJsPtr<wxImage> apImage;
	
	if( ZZZJS_PROP_GET_AP(apImage, Image, argv[argIndex]) == true ) 
	{
		int x = 0;
		int y = 0;
		ZZZJS_CHECK_ARG_COUNT(3, 3);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;

		p->Paste(*(apImage.get()), x, y);

		return JS_TRUE;
	} 
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			/*
			{
				  image: Image
				, x: Number
				, y: Number
			}
			*/

			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_IMAGE), &v) == JS_TRUE )  
			{
				int x = 0;
				int y = 0;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apImage, pObj, Image, PROP_NM_IMAGE);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER);

				
				p->Paste(*(apImage.get()), x, y);

				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

JSBool Image::blur(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// wxImage 	Blur (int blurRadius) const
	int argIndex = 0;
	int blurRadius = 0;

	ZZZJS_ARG_FROMJS_CHK_AND_ERROR(blurRadius, WXJS_TYPE_NUMBER);
	
	*vp = CreateObject(cx, new wxImage(p->Blur(blurRadius)));
	return JS_TRUE;
}

JSBool Image::blurHorizontal(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// wxImage 	BlurHorizontal (int blurRadius) const
	int argIndex = 0;
	int blurRadius = 0;

	ZZZJS_ARG_FROMJS_CHK_AND_ERROR(blurRadius, WXJS_TYPE_NUMBER);
	
	*vp = CreateObject(cx, new wxImage(p->BlurHorizontal(blurRadius)));
	return JS_TRUE;
}

JSBool Image::blurVertical(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// wxImage 	BlurVertical (int blurRadius) const
	int argIndex = 0;
	int blurRadius = 0;

	ZZZJS_ARG_FROMJS_CHK_AND_ERROR(blurRadius, WXJS_TYPE_NUMBER);
	
	*vp = CreateObject(cx, new wxImage(p->BlurVertical(blurRadius)));
	return JS_TRUE;
}

/***
 * <method name="scale">
 *  <function returns="wxImage">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the new image.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the new image.
 *   </arg>
 *  </function>
 *  <function returns="wxImage">
 *   <arg name="Size" type="@wxSize">
 *    The size of the new image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Returns a scaled version of the image with size Width * Height.
 *  </desc>
 * </method>
 */
JSBool Image::scale(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	/*
	wxImage Scale(int width, int height, wxImageResizeQuality quality=wxIMAGE_QUALITY_NORMAL) const
 		Returns a scaled version of the image.
	*/

	int argIndex = 0;
	zzzJsPtr<wxSize> apSize;
	if( argv[argIndex].isNumber() == true ) 
	{
		int x = 0;
		int y = 0;
		int quality = wxIMAGE_QUALITY_NORMAL;
		
		ZZZJS_CHECK_ARG_COUNT(2, 3);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(quality, WXJS_TYPE_NUMBER);
			argIndex--;
		}

        *vp = CreateObject(cx, new wxImage(p->Scale(x, y, (wxImageResizeQuality)quality )));
        return JS_TRUE;
	}
	else
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true )
	{

		int quality = wxIMAGE_QUALITY_NORMAL;
		
		ZZZJS_CHECK_ARG_COUNT(1, 2);


		argIndex = argc - 1;
		switch( argc ) 
		{
		case 1:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(quality, WXJS_TYPE_NUMBER);
			argIndex--;
		}

        *vp = CreateObject(cx, new wxImage(p->Scale(apSize->GetWidth(), apSize->GetHeight(), (wxImageResizeQuality)quality )));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			int quality = wxIMAGE_QUALITY_NORMAL;

			// qualityは、共通なので、指定があれば、ここで取得しておく。
			ZZZJS_PROP_FROMJS_IF_EXIST(quality, pObj, PROP_NM_QUALITY, WXJS_TYPE_NUMBER)	
			
			/*
			{
					size: Size
				,	quality: Number[Option]
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_SIZE);

				*vp = CreateObject(cx, new wxImage(p->Scale(apSize->GetWidth(), apSize->GetHeight(), (wxImageResizeQuality)quality )));
				return JS_TRUE;
			}

			/*
					width: Number
				,	height: Number
				,	quality: Number[Option]
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_WIDTH), &v) == JS_TRUE )  
			{
				int x = 0;
				int y = 0;

				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER);

				*vp = CreateObject(cx, new wxImage(p->Scale(x, y, (wxImageResizeQuality)quality )));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="rescale">
 *  <function returns="wxImage">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the new image.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the new image.
 *   </arg>
 *  </function>
 *  <function returns="wxImage">
 *   <arg name="Size" type="@wxSize">
 *    The size of the new image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Changes the size of the image in-place: after a call to this function, 
 *   the image will have the given width and height.
 *   Returns the (modified) image itself.
 *  </desc>
 * </method>
 */
JSBool Image::rescale(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// wxImage & 	Rescale (int width, int height, wxImageResizeQuality quality=wxIMAGE_QUALITY_NORMAL)

	
	int argIndex = 0;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == false )
    {

		int quality = wxIMAGE_QUALITY_NORMAL;
		
		ZZZJS_CHECK_ARG_COUNT(1, 2);


		argIndex = argc - 1;
		switch( argc ) 
		{
		case 1:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(quality, WXJS_TYPE_NUMBER);
			argIndex--;
		}


        *vp = CreateObject(cx, new wxImage(p->Rescale(apSize->GetWidth(), apSize->GetHeight(), (wxImageResizeQuality)quality )));
        return JS_TRUE;
    }
    else 	
	if( argv[argIndex].isNumber() == true ) 
	{
		int x = 0;
		int y = 0;
		int quality = wxIMAGE_QUALITY_NORMAL;
		
		ZZZJS_CHECK_ARG_COUNT(2, 3);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(quality, WXJS_TYPE_NUMBER);
			argIndex--;
		}

        *vp = CreateObject(cx, new wxImage(p->Rescale(x, y, (wxImageResizeQuality)quality )));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			int quality = wxIMAGE_QUALITY_NORMAL;

			// qualityは、共通なので、指定があれば、ここで取得しておく。
			ZZZJS_PROP_FROMJS_IF_EXIST(quality, pObj, PROP_NM_QUALITY, WXJS_TYPE_NUMBER)	
			
			/*
			{
					size: Size
				,	quality: Number[Option]
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_SIZE);

				*vp = CreateObject(cx, new wxImage(p->Rescale(apSize->GetWidth(), apSize->GetHeight(), (wxImageResizeQuality)quality )));
				return JS_TRUE;
			}

			/*
					width: Number
				,	height: Number
				,	quality: Number[Option]
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_WIDTH), &v) == JS_TRUE )  
			{
				int x = 0;
				int y = 0;

				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER);

				*vp = CreateObject(cx, new wxImage(p->Rescale(x, y, (wxImageResizeQuality)quality )));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="rotate">
 *  <function returns="wxImage">
 *   <arg name="Angle" type=WXJS_TYPE_DOUBLE>
 *    The rotation angle.
 *   </arg>
 *   <arg name="Center" type="@wxPoint">
 *    The height of the new image.
 *   </arg>
 *   <arg name="InterPol" type="Boolean" default="true">
 *    Interpolates the new image.
 *   </arg>
 *   <arg name="Offset" type="@wxPoint" default="null" />
 *  </function>
 *  <desc>
 *   Rotates the image about the given point, by angle radians. Passing true for interpolating 
 *   results in better image quality, but is slower. If the image has a mask, then the mask colour 
 *   is used for the uncovered pixels in the rotated image background. Else, black will be used.
 *   Returns the rotated image, leaving this image intact.
 *  </desc>
 * </method>
 */
JSBool Image::rotate(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// wxImage 	Rotate (double angle, const wxPoint &rotationCentre, bool interpolating=true, wxPoint *offsetAfterRotation=NULL) const

	
	int argIndex = 0;
    zzzJsPtr<wxPoint> offset;
    bool interpol = true;

	
	if( argv[argIndex].isDouble() == true ) 
	{
		double angle = 0.0;
		bool interpolating = true ;
		zzzJsPtr<wxPoint> center;
		zzzJsPtr<wxPoint> offsetAfterRotation;


		ZZZJS_CHECK_ARG_COUNT(2, 4);


		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(angle, WXJS_TYPE_DOUBLE);
		argIndex++;
		ZZZJS_ARG_AP_CHK_AND_ERROR(center, zzzJs::ext::Point);
		argIndex++;

		argIndex = argc - 1;
		switch( argc )
		{
		case 4:
			ZZZJS_ARG_AP_CHK_AND_ERROR(offsetAfterRotation, zzzJs::ext::Point);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(interpolating, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}


        *vp = CreateObject(cx, new wxImage(p->Rotate(angle, *(center.get()), interpol, offsetAfterRotation.get())));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			/*
			{
					angle:Double
				,	center:Point
				,	interpolating : Boolean[Option=true]
				,	offsetAfterRotation : Point
			}
			*/
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_ANGLE), &v) == JS_TRUE )  
			{
				double angle = 0.0;
				zzzJsPtr<wxPoint> center;
				bool interpolating = true ;
				zzzJsPtr<wxPoint> offsetAfterRotation;

		
				// depth
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(angle, pObj, PROP_NM_ANGLE, WXJS_TYPE_DOUBLE);
				// center
				ZZZJS_PROP_AP_CHK_AND_ERROR(center, pObj, zzzJs::ext::Point, PROP_NM_CENTER);
				// depth
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(interpolating, pObj, PROP_NM_INTERPOLATING, WXJS_TYPE_BOOLEAN);
				// offsetAfterRotation
				ZZZJS_PROP_AP_CHK_AND_ERROR(offsetAfterRotation, pObj, zzzJs::ext::Point, PROP_NM_OFFSET_AFTER_RORATION);

				*vp = CreateObject(cx, new wxImage(p->Rotate(angle, *(center.get()), interpol, offsetAfterRotation.get())));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="rotate90">
 *  <function returns="wxImage">
 *   <arg name="ClockWise" type="Boolean" default="true">
 *    The direction of the rotation. Default is true.
 *   </arg>
 *  </function>
 *  <desc>
 *   Returns a copy of the image rotated 90 degrees in the direction indicated by clockwise.
 *  </desc>
 * </method>
 */
JSBool Image::rotate90(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    bool clockwise = true;
    if (    argc > 0 
         && ! FromJS(cx, argv[0], clockwise) )
        return JS_FALSE;

    *vp = CreateObject(cx, new wxImage(p->Rotate90(clockwise)));
    return JS_TRUE;
}

JSBool Image::rotate180(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = CreateObject(cx, new wxImage(p->Rotate180()));
    return JS_TRUE;
}
JSBool Image::rotateHue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
    double angle = 0.0;
	
	ZZZJS_ARG_FROMJS_CHK_AND_ERROR(angle, WXJS_TYPE_DOUBLE);

    p->RotateHue(angle);
    return JS_TRUE;
}



/***
 * <method name="mirror">
 *  <function returns="wxImage">
 *   <arg name="Horizontally" type="Boolean" default="Y">
 *    The orientation.
 *   </arg>
 *  </function>
 *  <desc>
 *   Returns a mirrored copy of the image. The parameter horizontally indicates the orientation.
 *  </desc>
 * </method>
 */
JSBool Image::mirror(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	// wxImage 	Mirror (bool horizontally=true) const
	int argIndex = 0;
    bool hor = true;
    if ( argc > 0 ) {
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(hor, WXJS_TYPE_DOUBLE);
	}
        // && ! FromJS(cx, argv[argIndex], hor) )
        //return JS_FALSE;

    *vp = CreateObject(cx, new wxImage(p->Mirror(hor)));
    return JS_TRUE;
}



/***
 * <method name="replace">
 *  <function>
 *   <arg name="R1" type=WXJS_TYPE_NUMBER />
 *   <arg name="G1" type=WXJS_TYPE_NUMBER />
 *   <arg name="B1" type=WXJS_TYPE_NUMBER />
 *   <arg name="R2" type=WXJS_TYPE_NUMBER />
 *   <arg name="G2" type=WXJS_TYPE_NUMBER />
 *   <arg name="B2" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *   <arg name="Colour1" type="@wxColour" />
 *   <arg name="Colour2" type="@wxColour" />
 *  </function>
 *  <desc>
 *   Replaces the colour with another colour.
 *  </desc>
 * </method>
 */
JSBool Image::replace(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	// void 	Replace (unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2)
	
	int argIndex = 0;

	zzzJsPtr<wxColour> apCplor1;
	
	if( ZZZJS_ARG_GET_AP(apCplor1, Colour) == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		// Colour, Colour
		zzzJsPtr<wxColour> apCplor2;

		argIndex++;
		ZZZJS_ARG_AP_CHK_AND_ERROR(apCplor2, Colour);
		argIndex++;


        p->Replace(apCplor1.get()->Red(), apCplor1.get()->Green(), apCplor1.get()->Blue(),
                    apCplor2.get()->Red(), apCplor2.get()->Green(), apCplor2.get()->Blue());
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isNumber() == true ) 
	{
		int r1 = 0, g1 = 0, b1 = 0;
		int r2 = 0, g2 = 0, b2 = 0;

		ZZZJS_CHECK_ARG_COUNT(4, 4);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r1, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g1, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b1, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r2, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g2, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b2, WXJS_TYPE_NUMBER);
		argIndex++;

        p->Replace((unsigned char)r1, (unsigned char)g1, (unsigned char)b1,
                    (unsigned char)r2, (unsigned char)g2, (unsigned char)b2);

        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
					colour1 : Color
				,	colour2 : Color
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR1), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxColour> apCplor2;
				// colour1 : Color
				ZZZJS_PROP_AP_CHK_AND_ERROR(apCplor1, pObj, Colour, PROP_NM_COLOUR1);
				// colour2 : Color
				ZZZJS_PROP_AP_CHK_AND_ERROR(apCplor2, pObj, Colour, PROP_NM_COLOUR2);


				p->Replace(apCplor1.get()->Red(), apCplor1.get()->Green(), apCplor1.get()->Blue(),
							apCplor2.get()->Red(), apCplor2.get()->Green(), apCplor2.get()->Blue());
				return JS_TRUE;
			}
			/*
			{
					r1 : Number
				,	g1 : Number
				,	b1 : Number
				,	r2 : Number
				,	g2 : Number
				,	b2 : Number
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_R1), &v) == JS_TRUE )  
			{
				int r1 = 0, g1 = 0, b1 = 0;
				int r2 = 0, g2 = 0, b2 = 0;
				
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(r1, pObj, PROP_NM_R1, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g1, pObj, PROP_NM_G1, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b1, pObj, PROP_NM_B1, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(r2, pObj, PROP_NM_R2, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g2, pObj, PROP_NM_G2, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b2, pObj, PROP_NM_B2, WXJS_TYPE_NUMBER);


				p->Replace((unsigned char)r1, (unsigned char)g1, (unsigned char)b1,
							(unsigned char)r2, (unsigned char)g2, (unsigned char)b2);

				return JS_TRUE;				
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;

/*
    if ( argc == 2 )
    {
        wxColour *colour1;
        wxColour *colour2;
        
        if (    (colour1 = Colour::GetPrivate(cx, argv[0])) != NULL
             && (colour2 = Colour::GetPrivate(cx, argv[1])) != NULL )
        {
            p->Replace(colour1->Red(), colour1->Green(), colour1->Blue(),
                       colour2->Red(), colour2->Green(), colour2->Blue());
            return JS_TRUE;
        }
    }
    else if ( argc == 6 )
    {
        int r1, g1, b1, r2, g2, b2;
        if (    FromJS(cx, argv[0], r1)
             && FromJS(cx, argv[1], g1)
             && FromJS(cx, argv[2], b1)
             && FromJS(cx, argv[3], r2)
             && FromJS(cx, argv[4], g2)
             && FromJS(cx, argv[5], b2) )
        {
            p->Replace(r1, g1, b1, r2, g2, b2);
            return JS_TRUE;
        }
    }

    return JS_FALSE;
*/
}

JSBool Image::_size(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	// wxImage 	Size (const wxSize &size
	//		, const wxPoint &pos
	//		, int red=-1
	//		, int green=-1
	//		, int blue=-1) const
 	//  Returns a resized version of this image without scaling it by adding either a border with the given colour or cropping as necessary.
	
	int argIndex = 0;

	zzzJsPtr<wxSize> apSize;
	
	if( ZZZJS_ARG_GET_AP(apSize, Size) == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 5);

		zzzJsPtr<wxPoint> apPoint;
		int red=-1;
		int green=-1;
		int blue=-1;

		argIndex++;
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(blue, WXJS_TYPE_NUMBER);
			argIndex--;
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(green, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(red, WXJS_TYPE_NUMBER);
			argIndex--;
		}

		*vp = CreateObject(cx, new wxImage(p->Size( *(apSize.get()), *(apPoint.get()), red, green, blue)));
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
					size : Size
				,	pos : Point
				,	red : Number[Option. Default=-1]
				,	green : Number[Option. Default=-1]
				,	blue : Number[Option. Default=-1]
			}
			*/

			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxPoint> apPoint;
				int red=-1;
				int green=-1;
				int blue=-1;
				// colour1 : Color
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE);
				// colour2 : Color
				ZZZJS_PROP_AP_CHK_AND_ERROR(apPoint, pObj, zzzJs::ext::Point, PROP_NM_POS);

				
				ZZZJS_PROP_FROMJS_IF_EXIST(red, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(green, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(blue, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER);
				
				*vp = CreateObject(cx, new wxImage(p->Size( *(apSize.get()), *(apPoint.get()), red, green, blue)));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}
/***
 * <method name="convertToMono">
 *  <function returns="wxImage">
 *   <arg name="R" type=WXJS_TYPE_NUMBER />
 *   <arg name="G" type=WXJS_TYPE_NUMBER />
 *   <arg name="B" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function returns="wxImage">
 *   <arg name="Colour" type="@wxColour" />
 *  </function>
 *  <desc>
 *   Converts to a monochrome image. The returned image has white colour where the original has (r,g,b) 
 *   colour and black colour everywhere else.
 *  </desc>
 * </method>
 */
JSBool Image::convertToMono(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	//wxImage 	ConvertToMono (unsigned char r, unsigned char g, unsigned char b) const
	
	int argIndex = 0;
	
	zzzJsPtr<wxColour> apColour;
	
	if( ZZZJS_ARG_GET_AP(apColour, Colour) == true ) 
	{
        *vp = CreateObject(cx, new wxImage(p->ConvertToMono(apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue())));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isNumber() == true ) 
	{
		int red=-1;
		int green=-1;
		int blue=-1;
		ZZZJS_CHECK_ARG_COUNT(3, 3);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(red, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(green, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(blue, WXJS_TYPE_NUMBER);
		argIndex++;

        *vp = CreateObject(cx, new wxImage(p->ConvertToMono(red, green, blue)));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
					colour : Colour
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_COLOUR);
				
				*vp = CreateObject(cx, new wxImage(p->ConvertToMono(apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue())));
				return JS_TRUE;
			}
			/*
			{
					red : Number[Option. Default=-1]
				,	green : Number[Option. Default=-1]
				,	blue : Number[Option. Default=-1]
			}
			*/			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_TRUE )  
			{
				int red=-1;
				int green=-1;
				int blue=-1;				
				ZZZJS_PROP_FROMJS_IF_EXIST(red, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(green, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(blue, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER);
				
				 *vp = CreateObject(cx, new wxImage(p->ConvertToMono(red, green, blue)));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

JSBool Image::convertAlphaToMask(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	//bool 	ConvertAlphaToMask (unsigned char threshold=wxIMAGE_ALPHA_THRESHOLD)
	//bool 	ConvertAlphaToMask (unsigned char mr, unsigned char mg, unsigned char mb, unsigned char threshold=wxIMAGE_ALPHA_THRESHOLD)
	
	if( argc == 0 ) 
	{
		vp->setBoolean( p->ConvertAlphaToMask() );
		return JS_TRUE;
	}


	int argIndex = 0;
	
	zzzJsPtr<wxColour> apColour;
	
	if( ZZZJS_ARG_GET_AP(apColour, Colour) == true ) 
	{
		int threshold = wxIMAGE_ALPHA_THRESHOLD;
		
		ZZZJS_CHECK_ARG_COUNT(1, 2);


		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(threshold, WXJS_TYPE_NUMBER);
			argIndex--;
		}
        vp->setBoolean( 
			p->ConvertAlphaToMask(
				apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue()
				, threshold
			) 
		);
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isNumber() == true ) 
	{
		int red=-1;
		int green=-1;
		int blue=-1;
		int threshold = wxIMAGE_ALPHA_THRESHOLD;
		ZZZJS_CHECK_ARG_COUNT(3, 4);
		

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(threshold, WXJS_TYPE_NUMBER);
			argIndex--;
		}
        vp->setBoolean( 
			p->ConvertAlphaToMask(red, green, blue, threshold) 
		);
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			int threshold = wxIMAGE_ALPHA_THRESHOLD;

			// threshold
			ZZZJS_PROP_FROMJS_IF_EXIST(threshold, pObj, PROP_NM_THRESHOLD, WXJS_TYPE_NUMBER );
			/*
			{
					colour : Colour
					threshold : Number[Option. Default=wx.IMAGE_ALPHA_THRESHOLD
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_COLOUR);
				
				vp->setBoolean( 
					p->ConvertAlphaToMask(
						apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue()
						, threshold
					) 
				);
				return JS_TRUE;
			}
			/*
			{
					red : Number[Option. Default=-1]
				,	green : Number[Option. Default=-1]
				,	blue : Number[Option. Default=-1]
			}
			*/			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_TRUE )  
			{
				int red=-1;
				int green=-1;
				int blue=-1;				
				ZZZJS_PROP_FROMJS_IF_EXIST(red,   pObj, PROP_NM_RED,   WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(green, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(blue,  pObj, PROP_NM_BLUE,  WXJS_TYPE_NUMBER);
				
				vp->setBoolean( 
					p->ConvertAlphaToMask(red, green, blue, threshold) 
				);
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

JSBool Image::convertToGreyscale(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	//wxImage 	ConvertToGreyscale (double weight_r, double weight_g, double weight_b) const
	// 	Returns a greyscale version of the image. More...
	//wxImage 	ConvertToGreyscale () const
	// 	Returns a greyscale version of the image.
	
	if( argc == 0 ) 
	{
		*vp = CreateObject(cx, new wxImage(p->ConvertToGreyscale()));
		return JS_TRUE;
	}


	int argIndex = 0;
	
	if( argv[argIndex].isDouble() == true ) 
	{
		double weight_r = 0, weight_g = 0, weight_b = 0;


		ZZZJS_CHECK_ARG_COUNT(3, 3);
		
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(weight_r, WXJS_TYPE_DOUBLE);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(weight_g, WXJS_TYPE_DOUBLE);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(weight_b, WXJS_TYPE_DOUBLE);
		argIndex++;

		*vp = CreateObject(cx, new wxImage(p->ConvertToGreyscale(weight_r, weight_g, weight_b)));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			int threshold = wxIMAGE_ALPHA_THRESHOLD;

			/*
			{
					weight_r : Double
				,	weight_g : Double
				,	weight_b : Double
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_WEIGHT_R), &v) == JS_TRUE )  
			{
				double weight_r = 0, weight_g = 0, weight_b = 0;
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(weight_r, pObj, PROP_NM_WEIGHT_R, WXJS_TYPE_DOUBLE);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(weight_g, pObj, PROP_NM_WEIGHT_G, WXJS_TYPE_DOUBLE);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(weight_b, pObj, PROP_NM_WEIGHT_B, WXJS_TYPE_DOUBLE);
				
				*vp = CreateObject(cx, new wxImage(p->ConvertToGreyscale(weight_r, weight_g, weight_b)));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}


JSBool Image::convertToDisabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	//wxImage 	ConvertToMono (unsigned char r, unsigned char g, unsigned char b) const
	// 	Returns monochromatic version of the image. More...
	// 
	//wxImage 	ConvertToDisabled (unsigned char brightness=255) const
	// 	Returns disabled (dimmed) version of the image. More...
	
	if( argc == 0 ) 
	{
		*vp = CreateObject(cx, new wxImage(p->ConvertToDisabled()));
		return JS_TRUE;
	}
	int argIndex = 0;
	
	if( argv[argIndex].isNumber() == true ) 
	{
		int brightness=255;
		ZZZJS_CHECK_ARG_COUNT(1, 1);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(brightness, WXJS_TYPE_NUMBER);

        *vp = CreateObject(cx, new wxImage(p->ConvertToDisabled(brightness)));
        return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
					brightness : Number
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_BRIGHTNESS), &v) == JS_TRUE )  
			{
				int brightness=255;
				ZZZJS_PROP_FROMJS_IF_EXIST(brightness, pObj, PROP_NM_BRIGHTNESS, WXJS_TYPE_NUMBER);
				
				*vp = CreateObject(cx, new wxImage(p->ConvertToDisabled(brightness)));
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="setRGB">
 *  <function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>The x position</arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>The y position</arg>
 *   <arg name="R" type=WXJS_TYPE_NUMBER />
 *   <arg name="G" type=WXJS_TYPE_NUMBER />
 *   <arg name="B" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>The x position</arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>The y position</arg>
 *   <arg name="Colour" type="@wxColour" />
 *  </function>
 *  <desc>
 *   Sets the colour of the pixel at the given coordinate. 
 *   This routine performs bounds-checks for the coordinate so it can be considered a safe way 
 *   to manipulate the data, but in some cases this might be too slow.
 *  </desc>
 * </method>
 */
JSBool Image::setRGB(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	void 	SetRGB (int x, int y, unsigned char r, unsigned char g, unsigned char b)
 		Set the color of the pixel at the given x and y coordinate. More...
	void 	SetRGB (const wxRect &rect, unsigned char red, unsigned char green, unsigned char blue)
 		Sets the colour of the pixels within the given rectangle.
	*/
	
	int argIndex = 0;
	
	zzzJsPtr<wxRect> apRect;
	zzzJsPtr<wxColour> apColour;

    int x = 0;
    int y = 0;
	
	if( ZZZJS_ARG_GET_AP(apRect, Rect) == true ) 
	{
		argIndex++;
		if( argc < 2 ) {
			// 最低でも、２は必要
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}
		if( ZZZJS_ARG_GET_AP(apColour, Colour) == true ) 
		{
			p->SetRGB(*(apRect.get()), apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue());
			return JS_TRUE;
		}
		else
		if( argv[argIndex].isNumber() == true ) 
		{
			int r = 0, g = 0, b = 0;

			ZZZJS_CHECK_ARG_COUNT(4, 4);

			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b, WXJS_TYPE_NUMBER);
			argIndex++;
			
			p->SetRGB(*(apRect.get()), r, g, b);
			return JS_TRUE;
		}
	}
	else
	if( argv[argIndex].isNumber() == true ) 
	{
		int x = 0, y = 0;
		int r = 0, g = 0, b = 0;
		
		if( argc < 3 ) {
			// 最低でも、3は必要
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;

		if( ZZZJS_ARG_GET_AP(apColour, Colour) == true ) 
		{
			p->SetRGB(x, y, apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue());
			return JS_TRUE;
		}
		else
		if( argv[argIndex].isNumber() == true ) 
		{
			ZZZJS_CHECK_ARG_COUNT(5, 5);
			
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b, WXJS_TYPE_NUMBER);
			argIndex++;
			
			p->SetRGB(x, y, r, g, b);
			return JS_TRUE;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}


			/*
			{
					x : Number
				,	y : Number
				,	red : Number
				,	green : Number
				,	blue : Number
			}
			*/
			/*
			{
					x : Number
				,	y : Number
				,	colour : Colour
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				int x = 0, y = 0;
				ZZZJS_PROP_FROMJS_IF_EXIST(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER);
				
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_TRUE )  
				{				
					int r = 0, g = 0, b = 0;
					ZZZJS_PROP_FROMJS_IF_EXIST(r, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
					ZZZJS_PROP_FROMJS_IF_EXIST(g, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
					ZZZJS_PROP_FROMJS_IF_EXIST(b, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER);

					p->SetRGB(x, y, r, g, b);
					return JS_TRUE;
				}
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
				{				
					ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_COLOUR);


					p->SetRGB(x, y, apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue());
					return JS_TRUE;
				}
			}
			/*
			{
					rect : Rect
				,	red : Number
				,	green : Number
				,	blue : Number
			}
			*/
			/*
			{
					rect : Rect
				,	colour : Colour
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RECT), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_AP_CHK_AND_ERROR(apRect, pObj, Rect, PROP_NM_RECT);



				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_TRUE )  
				{				
					int r = 0, g = 0, b = 0;
					ZZZJS_PROP_FROMJS_IF_EXIST(r, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
					ZZZJS_PROP_FROMJS_IF_EXIST(g, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
					ZZZJS_PROP_FROMJS_IF_EXIST(b, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER);

					p->SetRGB(*(apRect.get()), r, g, b);
					return JS_TRUE;
				}
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
				{				
					ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_COLOUR);


					p->SetRGB(*(apRect.get()), apColour.get()->Red(), apColour.get()->Green(), apColour.get()->Blue());
					return JS_TRUE;
				}

			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="getRed">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>The x position</arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>The y position</arg>
 *  </function>
 *  <desc>
 *   Returns the red intensity at the given coordinate.
 *  </desc>
 * </method>
 */
JSBool Image::getRed(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int x = 0;
	int y = 0;
	bool bFind = false;
	int argIndex = 0;
	

	if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		bFind = true;
	} else
	if( Size::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxSize> apSize;
		if( ZZZJS_ARG_GET_AP(apSize, Size) == true ) 
		{
			x = apSize->GetX();
			y = apSize->GetY();
			bFind = true;
		}
	} else
	if( zzzJs::ext::Point::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxPoint> apPoint;
		if( ZZZJS_ARG_GET_AP(apPoint, zzzJs::ext::Point) == true ) 
		{
			x = apPoint->x;
			y = apPoint->y;
			bFind = true;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_IF_EXIST(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER);
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxSize> apSize;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE);
				x = apSize->GetX();
				y = apSize->GetY();
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_POS), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxPoint> apPoint;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apPoint, pObj, zzzJs::ext::Point, PROP_NM_POS);
				x = apPoint->x;
				y = apPoint->y;
				bFind = true;
			}

		} while( 0 );
	}


	if( bFind == false)
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}



	*vp = ToJS(cx, (int) p->GetRed(x, y));
	return JS_TRUE;
}

/***
 * <method name="getGreen">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>The x position</arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>The y position</arg>
 *  </function>
 *  <desc>
 *   Returns the green intensity at the given coordinate.
 *  </desc>
 * </method>
 */
JSBool Image::getGreen(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int x = 0;
	int y = 0;
	bool bFind = false;
	int argIndex = 0;
	

	if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		bFind = true;
	} else
	if( Size::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxSize> apSize;
		if( ZZZJS_ARG_GET_AP(apSize, Size) == true ) 
		{
			x = apSize->GetX();
			y = apSize->GetY();
			bFind = true;
		}
	} else
	if( zzzJs::ext::Point::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxPoint> apPoint;
		if( ZZZJS_ARG_GET_AP(apPoint, zzzJs::ext::Point) == true ) 
		{
			x = apPoint->x;
			y = apPoint->y;
			bFind = true;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_IF_EXIST(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER);
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxSize> apSize;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE);
				x = apSize->GetX();
				y = apSize->GetY();
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_POS), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxPoint> apPoint;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apPoint, pObj, zzzJs::ext::Point, PROP_NM_POS);
				x = apPoint->x;
				y = apPoint->y;
				bFind = true;
			}

		} while( 0 );
	}


	if( bFind == false)
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	*vp = ToJS(cx, (int) p->GetGreen(x, y));
	return JS_TRUE;
}

/***
 * <method name="getBlue">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>The x position</arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>The y position</arg>
 *  </function>
 *  <desc>
 *   Returns the blue intensity at the given coordinate.
 *  </desc>
 * </method>
 */
JSBool Image::getBlue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int x = 0;
	int y = 0;
	bool bFind = false;
	int argIndex = 0;
	

	if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		bFind = true;
	} else
	if( Size::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxSize> apSize;
		if( ZZZJS_ARG_GET_AP(apSize, Size) == true ) 
		{
			x = apSize->GetX();
			y = apSize->GetY();
			bFind = true;
		}
	} else
	if( zzzJs::ext::Point::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxPoint> apPoint;
		if( ZZZJS_ARG_GET_AP(apPoint, zzzJs::ext::Point) == true ) 
		{
			x = apPoint->x;
			y = apPoint->y;
			bFind = true;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_IF_EXIST(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER);
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxSize> apSize;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE);
				x = apSize->GetX();
				y = apSize->GetY();
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_POS), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxPoint> apPoint;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apPoint, pObj, zzzJs::ext::Point, PROP_NM_POS);
				x = apPoint->x;
				y = apPoint->y;
				bFind = true;
			}

		} while( 0 );
	}


	if( bFind == false)
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

    *vp = ToJS(cx, (int) p->GetBlue(x, y));
    return JS_TRUE;
}

/***
 * <method name="getColour">
 *  <function returns="@wxColour">
 *   <arg name="X" type=WXJS_TYPE_NUMBER>The x position</arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>The y position</arg>
 *  </function>
 *  <desc>
 *   Returns the colour of the given coordinate.
 *  </desc>
 * </method>
 */
JSBool Image::getColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
	int x = 0;
	int y = 0;
	bool bFind = false;
	

	if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		bFind = true;
	} else
	if( Size::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxSize> apSize;
		if( ZZZJS_ARG_GET_AP(apSize, Size) == true ) 
		{
			x = apSize->GetX();
			y = apSize->GetY();
			bFind = true;
		}
	} else
	if( zzzJs::ext::Point::HasPrototype(cx, argv[argIndex]) == true ) 
	{
		zzzJsPtr<wxPoint> apPoint;
		if( ZZZJS_ARG_GET_AP(apPoint, zzzJs::ext::Point) == true ) 
		{
			x = apPoint->x;
			y = apPoint->y;
			bFind = true;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_IF_EXIST(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_IF_EXIST(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER);
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxSize> apSize;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE);
				x = apSize->GetX();
				y = apSize->GetY();
				bFind = true;
			} else
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_POS), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxPoint> apPoint;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apPoint, pObj, zzzJs::ext::Point, PROP_NM_POS);
				x = apPoint->x;
				y = apPoint->y;
				bFind = true;
			}

		} while( 0 );
	}


	if( bFind == false)
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

    *vp = Colour::CreateObject(cx, new wxColour(p->GetRed(x, y), p->GetGreen(x, y), p->GetBlue(x, y)));
    return JS_TRUE;
}

/***
 * <method name="findFirstUnusedColour">
 *  <function returns="Boolean">
 *   <arg name="Colour" type="@wxColour">
 *    The colour found. Only updated when a colour is found.
 *   </arg>
 *   <arg name="StartColour" type="@wxColour">
 *    The start colour.
 *   </arg>
 *  </function>
 *  <desc>
 *   Finds the first colour that is never used in the image. The search begins at given start 
 *   colour and continues by increasing R, G and B components (in this order) by 1 until an 
 *   unused colour is found or the colour space exhausted. 
 *   Returns true on success. False when there are no colours left.
 *   JavaScript can't pass primitive values by reference, so this method uses @wxColour
 *   instead of separate r, g, b arguments.
 *  </desc>
 * </method>
 */
JSBool Image::findFirstUnusedColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	bool 	FindFirstUnusedColour (
		unsigned char *r, 
		unsigned char *g, 
		unsigned char *b, 
		unsigned char startR=1, 
		unsigned char startG=0, 
		unsigned char startB=0) const
 	Finds the first colour that is never used in the image.*/
	
	int argIndex = 0;
    wxColour *colour = Colour::GetPrivate(cx, argv[argIndex]);
	int startR = 1;
	int startG = 0;
	int startB = 0;
	bool bFind = false;
	if( colour != NULL ) 
	{
		argIndex++;
		if( argc == 1 ) {
			bFind  = true;
		} else {
			zzzJsPtr<wxColour> apColour;
			if( ZZZJS_PROP_GET_AP(apColour, Colour, argv[argIndex]) == true )
			{
				startR = apColour->Red();
				startG = apColour->Green();
				startB = apColour->Blue();
				bFind  = true;
			} else
			if( argv[argIndex].isNumber() == true ) 
			{
				ZZZJS_CHECK_ARG_COUNT(2, 4);
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(startR, WXJS_TYPE_NUMBER);
				argIndex++;
				
				argIndex = argc - 1;
				switch( argc )
				{
				case 4:
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(startB, WXJS_TYPE_NUMBER);
					argIndex--;
				case 3:
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(startG, WXJS_TYPE_NUMBER);
					argIndex--;
				}
				bFind  = true;
			}
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			/*
			{
					colour : Colour
				,	startR : Number[Option. Default=1]
				,	startG : Number[Option. Default=0]
				,	startB : Number[Option. Default=0]
			}
			*/
			/*
			{
					colour : Colour
				,	start : Colour[Option.]
			}
			*/
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_FALSE )  
			{
				// colourは必須
				break;
			}
			// colourは、Colourのインスタンスでないといけない。
			colour = Colour::GetPrivate(cx, v);
			if( colour == NULL ) 
			{
				break;
			}
				
			bFind  = true;
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_START), &v) == JS_TRUE )  
			{
				// colourは必須
				zzzJsPtr<wxColour> apColour;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_START);
				startR = apColour->Red();
				startG = apColour->Green();
				startB = apColour->Blue();
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_START_R), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(startR, pObj, PROP_NM_START_R, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(startG, pObj, PROP_NM_START_G, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(startB, pObj, PROP_NM_START_B, WXJS_TYPE_NUMBER);
			}
		} while( 0 );
	}




	if( bFind == false || colour == NULL)
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

    unsigned char r, g, b;

    if ( p->FindFirstUnusedColour(&r, &g, &b, startR, startG, startB) )
    {
        *vp = JSVAL_TRUE;
        colour->Set(r, g, b);
    }
    else
    {
        *vp = JSVAL_FALSE;
    }
    return JS_TRUE;
}

/***
 * <method name="setMaskFromImage">
 *  <function returns="Boolean">
 *   <arg name="Image" type="wxImage">
 *    The mask image to extract mask shape from. Must have same dimensions as the image.
 *   </arg>
 *   <arg name="R" type=WXJS_TYPE_NUMBER />
 *   <arg name="G" type=WXJS_TYPE_NUMBER />
 *   <arg name="B" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Image" type="wxImage">
 *    The mask image to extract mask shape from. Must have same dimensions as the image.
 *   </arg>
 *   <arg name="Colour" type="@wxColour" />
 *  </function>
 *  <desc>
 *   Sets image's mask so that the pixels that have RGB value of r,g,b (or colour) in mask
 *   will be masked in the image. This is done by first finding an unused colour in the image,
 *   setting this colour as the mask colour and then using this colour to draw all pixels in 
 *   the image whose corresponding pixel in mask has given RGB value.
 *   Returns false if mask does not have same dimensions as the image or if there is no unused 
 *   colour left. Returns true if the mask was successfully applied.
 *  </desc>
 * </method>
 */
JSBool Image::setMaskFromImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	bool wxImage::SetMaskFromImage	(	const wxImage & 	mask,
		unsigned char 	mr,
		unsigned char 	mg,
		unsigned char 	mb 
	)	
	*/
	int argIndex = 0;

	bool bFind = false;
	zzzJsPtr<wxImage> apImage;
	int r = 0, g = 0, b = 0;


	if( ZZZJS_PROP_GET_AP(apImage, Image, argv[argIndex]) == true )
	{
		zzzJsPtr<wxColour> apColour;
		argIndex++;

		if( argc < 2 ) {
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}

		if( ZZZJS_PROP_GET_AP(apColour, Colour, argv[argIndex]) == true )
		{
			r = apColour->Red();
			g = apColour->Green();
			b = apColour->Blue();
			bFind = true;
		}
		else
		if( argv[argIndex].isNumber() == true ) 
		{
			ZZZJS_CHECK_ARG_COUNT(4, 4);
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b, WXJS_TYPE_NUMBER);
			argIndex++;
			bFind = true;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MASK), &v) == JS_FALSE )  
			{
				break;
			}
			ZZZJS_PROP_AP_CHK_AND_ERROR(apImage, pObj, Image, PROP_NM_MASK);
			
			bFind = true;
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxColour> apColour;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_START);
				r = apColour->Red();
				g = apColour->Green();
				b = apColour->Blue();
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(r, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER);
			}
		} while( 0 );
	}



	if( bFind == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	*vp = ToJS(cx, p->SetMaskFromImage(*(apImage.get()), r, g, b));
	
    return JS_TRUE;
}

/***
 * <method name="loadFile">
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>The name of a file</arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER default="wxBitmapType.ANY">
 *    The type of the image.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>The name of a file</arg>
 *   <arg name="MimeType" type=WXJS_TYPE_STRING default="wxBitmapType.ANY">
 *    The MIME type of the image.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Stream" type="@wxInputStream">
 *    Opened input stream from which to load the image. Currently, the stream must support seeking.
 *   </arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER default="wxBitmapType.ANY">
 *    The type of the image.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Stream" type="@wxInputStream">
 *    Opened input stream from which to load the image. Currently, the stream must support seeking.
 *   </arg>
 *   <arg name="MimeType" type=WXJS_TYPE_STRING default="wxBitmapType.ANY">
 *    The MIME type of the image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Loads an image from a file.
 *  </desc>
 * </method>
 */
JSBool Image::loadFile(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/* 
	virtual bool 	LoadFile (const wxString &name, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 		Loads an image from a file. More...
 
	virtual bool 	LoadFile (const wxString &name, const wxString &mimetype, int index=-1)
 		Loads an image from a file. More...
 
	virtual bool 	LoadFile (wxInputStream &stream, wxBitmapType type=wxBITMAP_TYPE_ANY, int index=-1)
 		Loads an image from an input stream. More...

	virtual bool 	LoadFile (wxInputStream &stream, const wxString &mimetype, int index=-1)
 		Loads an image from an input stream.
	*/
	int argIndex = 0;
	int index=-1;

    if ( zzzJs::HasPrototype(cx, argv[argIndex], "InputStream") )
    {
		ZZZJS_CHECK_ARG_COUNT(2, 3);
		

        io::Stream *stream = (io::Stream *) JS_GetPrivate(/*cx,*/ JSVAL_TO_OBJECT(argv[argIndex]));
        if ( stream == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "InputStream");
            return JS_FALSE;
		}
        wxInputStream *in = dynamic_cast<wxInputStream *>(stream->GetStream());
        if ( in == NULL )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "InputStream");
            return JS_FALSE;
        }

		// 先に第3のオプションが共通なので、取得する。
		if( argc == 3 ) 
		{
			argIndex = 2;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
		}

		
		argIndex = 1;
		if ( argv[argIndex].isNumber() )
        {
            long type = wxBITMAP_TYPE_ANY;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);

            *vp = ToJS(cx, p->LoadFile(*in, (wxBitmapType)type, index));
			return JS_TRUE;
        }
        else
		if ( argv[argIndex].isString() )
        {
            wxString mimetype;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mimetype, WXJS_TYPE_STRING);
            *vp = ToJS(cx, p->LoadFile(*in, mimetype, index));
			return JS_TRUE;
        }
    }
    else
	if ( argv[argIndex].isString() )
    {
        wxString name;
		int index=-1;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex++;
			
		ZZZJS_CHECK_ARG_COUNT(1, 3);

		if( argc == 1 ) 
		{
            *vp = ToJS(cx, p->LoadFile(name));
		}
		else
		{

			// 先に第3のオプションが共通なので、取得する。
			if( argc == 3 ) 
			{
				argIndex = 2;
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
			}

			argIndex = 1;
			if ( argv[argIndex].isNumber() )
			{
				long type = wxBITMAP_TYPE_ANY;
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);

				*vp = ToJS(cx, p->LoadFile(name, (wxBitmapType)type, index));
				return JS_TRUE;
			}
			else
			if ( argv[argIndex].isString() )
			{
				wxString mimetype;
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mimetype, WXJS_TYPE_STRING);

				*vp = ToJS(cx, p->LoadFile(name, mimetype, index));
				return JS_TRUE;
			}
		}
    }
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			// index
			ZZZJS_PROP_FROMJS_IF_EXIST(index, pObj, PROP_NM_INDEX, WXJS_TYPE_NUMBER);


			/*
			{
					stream : InputStream
				,	type : Number
				,	index : Number[Option. Default=-1.]
			}
			{
					stream : InputStream
				,	mimetype : String
				,	index : Number[Option. Default=-1.]
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_STREAM), &v) == JS_TRUE )  
			{
				io::Stream *stream = (io::Stream *) JS_GetPrivate(/*cx,*/ JSVAL_TO_OBJECT(v));
				if ( stream == NULL )
				{
					ReportError_PropTypeError(cx, PROP_NM_STREAM, "InputStream");
					break;
				}
				wxInputStream *in = dynamic_cast<wxInputStream *>(stream->GetStream());
				if ( in == NULL )
				{
					ReportError_PropTypeError(cx, PROP_NM_STREAM, "InputStream");
					break;
				}
				
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_TYPE), &v) == JS_TRUE )  
				{
					long type = wxBITMAP_TYPE_ANY;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, pObj, PROP_NM_TYPE, WXJS_TYPE_NUMBER);
					
					*vp = ToJS(cx, p->LoadFile(*in, (wxBitmapType)type, index));
					return JS_TRUE;
				} else
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MIMETYPE), &v) == JS_TRUE )  
				{
					wxString mimetype;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(mimetype, pObj, PROP_NM_MIMETYPE, WXJS_TYPE_STRING);
					
					*vp = ToJS(cx, p->LoadFile(*in, mimetype, index));
					return JS_TRUE;
				}
			}
			/*
			{
					filepath : String
				,	type : Number
				,	index : Number[Option. Default=-1.]
			}
			{
					filepath : String
				,	mimetype : String
				,	index : Number[Option. Default=-1.]
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_FILEPATH), &v) == JS_TRUE )  
			{
				wxString name;
				ZZZJS_PROP_FROMJS_IF_EXIST(name, pObj, PROP_NM_FILEPATH, WXJS_TYPE_STRING);


				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_TYPE), &v) == JS_TRUE )  
				{
					long type = wxBITMAP_TYPE_ANY;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, pObj, PROP_NM_TYPE, WXJS_TYPE_NUMBER);
					
					*vp = ToJS(cx, p->LoadFile(name, (wxBitmapType)type, index));
					return JS_TRUE;
				} else
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MIMETYPE), &v) == JS_TRUE )  
				{
					wxString mimetype;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(mimetype, pObj, PROP_NM_MIMETYPE, WXJS_TYPE_STRING);
					
					*vp = ToJS(cx, p->LoadFile(name, mimetype, index));
					return JS_TRUE;
				} else
				{					
					*vp = ToJS(cx, p->LoadFile(name));
					return JS_TRUE;
				}
			}
		} while( 0 );
	}
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="saveFile">
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>The name of a file</arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER default="wxBitmapType.ANY">
 *    The type of the image.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>The name of a file</arg>
 *   <arg name="MimeType" type=WXJS_TYPE_STRING default="wxBitmapType.ANY">
 *    The MIME type of the image.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Stream" type="@wxOutputStream">
 *    Opened input stream from which to load the image. Currently, the stream must support seeking.
 *   </arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER default="wxBitmapType.ANY">
 *    The type of the image.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Stream" type="@wxOutputStream">
 *    Opened input stream from which to load the image. Currently, the stream must support seeking.
 *   </arg>
 *   <arg name="MimeType" type=WXJS_TYPE_STRING default="wxBitmapType.ANY">
 *    The MIME type of the image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Saves an image to a file.
 *  </desc>
 * </method>
 */
JSBool Image::saveFile(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	/* 
	virtual bool 	SaveFile (wxOutputStream &stream, const wxString &mimetype) const
 		Saves an image in the given stream. More...

	virtual bool 	SaveFile (wxOutputStream &stream, wxBitmapType type) const
 		Saves an image in the given stream.


	virtual bool 	SaveFile (const wxString &name, wxBitmapType type) const
 		Saves an image in the named file. More...
 
	virtual bool 	SaveFile (const wxString &name, const wxString &mimetype) const
 		Saves an image in the named file. More...
 
	virtual bool 	SaveFile (const wxString &name) const
 		Saves an image in the named file. More...
	*/
	int argIndex = 0;
	
    if ( zzzJs::HasPrototype(cx, argv[argIndex], "OutputStream") )
    {
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		
        io::Stream *stream = (io::Stream *) JS_GetPrivate(JSVAL_TO_OBJECT(argv[argIndex]));
        if ( stream == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "OutputStream");
            return JS_FALSE;
		}

        wxOutputStream *out = dynamic_cast<wxOutputStream *>(stream->GetStream());
        if ( out == NULL )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "OutputStream");
            return JS_FALSE;
        }

		argIndex++;
		if( argv[argIndex].isNumber() == true ) 
		{
            long type = wxBITMAP_TYPE_ANY;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);

            *vp = ToJS(cx, p->SaveFile(*out, (wxBitmapType)type));
			return JS_TRUE;

		}
		else
		if( argv[argIndex].isString() == true ) 
		{
            wxString mimetype;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mimetype, WXJS_TYPE_STRING);
            *vp = ToJS(cx, p->SaveFile(*out, mimetype));
			return JS_TRUE;
		}
	}
    else
	if ( argv[argIndex].isString() )
    {
        wxString name;
			
		ZZZJS_CHECK_ARG_COUNT(1, 2);
		
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex++;
		if( argc == 1 ) 
		{
            *vp = ToJS(cx, p->SaveFile(name));
		}
		else
		{
			argIndex = 1;
			if ( argv[argIndex].isNumber() )
			{
				long type = wxBITMAP_TYPE_ANY;
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(type, WXJS_TYPE_NUMBER);

				*vp = ToJS(cx, p->SaveFile(name, (wxBitmapType)type));
				return JS_TRUE;
			}
			else
			if ( argv[argIndex].isString() )
			{
				wxString mimetype;
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mimetype, WXJS_TYPE_STRING);

				*vp = ToJS(cx, p->SaveFile(name, mimetype));
				return JS_TRUE;
			}
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
					stream : OutputStream
				,	type : Number
			}
			{
					stream : OutputStream
				,	mimetype : String
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_STREAM), &v) == JS_TRUE )  
			{
				io::Stream *stream = (io::Stream *) JS_GetPrivate(/*cx,*/ JSVAL_TO_OBJECT(v));
				if ( stream == NULL )
				{
					ReportError_PropTypeError(cx, PROP_NM_STREAM, "OutputStream");
					break;
				}
				wxOutputStream *out = dynamic_cast<wxOutputStream *>(stream->GetStream());
				if ( out == NULL )
				{
					ReportError_PropTypeError(cx, PROP_NM_STREAM, "OutputStream");
					break;
				}
				
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_TYPE), &v) == JS_TRUE )  
				{
					long type = wxBITMAP_TYPE_ANY;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, pObj, PROP_NM_TYPE, WXJS_TYPE_NUMBER);
					
					*vp = ToJS(cx, p->SaveFile(*out, (wxBitmapType)type));
					return JS_TRUE;
				} else
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MIMETYPE), &v) == JS_TRUE )  
				{
					wxString mimetype;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(mimetype, pObj, PROP_NM_MIMETYPE, WXJS_TYPE_STRING);
					
					*vp = ToJS(cx, p->SaveFile(*out, mimetype));
					return JS_TRUE;
				}
			}
			/*
			{
					filepath : String
				,	type : Number
			}
			{
					filepath : String
				,	mimetype : String
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_FILEPATH), &v) == JS_TRUE )  
			{
				wxString name;
				ZZZJS_PROP_FROMJS_IF_EXIST(name, pObj, PROP_NM_FILEPATH, WXJS_TYPE_STRING);


				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_TYPE), &v) == JS_TRUE )  
				{
					long type = wxBITMAP_TYPE_ANY;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(type, pObj, PROP_NM_TYPE, WXJS_TYPE_NUMBER);
					
					*vp = ToJS(cx, p->SaveFile(name, (wxBitmapType)type));
					return JS_TRUE;
				} else
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MIMETYPE), &v) == JS_TRUE )  
				{
					wxString mimetype;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(mimetype, pObj, PROP_NM_MIMETYPE, WXJS_TYPE_STRING);
					
					*vp = ToJS(cx, p->SaveFile(name, mimetype));
					return JS_TRUE;
				} else
				{					
					*vp = ToJS(cx, p->SaveFile(name));
					return JS_TRUE;
				}
			}
		} while( 0 );
	}
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="setMaskColour">
 *  <function>
 *   <arg name="R" type=WXJS_TYPE_NUMBER />
 *   <arg name="G" type=WXJS_TYPE_NUMBER />
 *   <arg name="B" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *   <arg name="Colour" type="@wxColour" />
 *  </function>
 *  <desc>
 *   Sets the mask colour for this image (and tells the image to use the mask).
 *  </desc>
 * </method>
 */
JSBool Image::setMaskColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	/*
	void 	SetMaskColour (unsigned char red, unsigned char green, unsigned char blue)
 		Sets the mask colour for this image (and tells the image to use the mask).
	*/
	int argIndex = 0;

	
	bool bFind = false;
	zzzJsPtr<wxColour> apColour;
	int r = 0, g = 0, b = 0;

	if( ZZZJS_PROP_GET_AP(apColour, Colour, argv[argIndex]) == true )
	{
		r = apColour->Red();
		g = apColour->Green();
		b = apColour->Blue();
		bFind = true;
	}
	else
	if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(3, 3);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(r, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(g, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(b, WXJS_TYPE_NUMBER);
		argIndex++;
		bFind = true;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxColour> apColour;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, pObj, Colour, PROP_NM_START);
				r = apColour->Red();
				g = apColour->Green();
				b = apColour->Blue();
				bFind = true;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RED), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(r, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(g, pObj, PROP_NM_GREEN, WXJS_TYPE_NUMBER);
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(b, pObj, PROP_NM_BLUE, WXJS_TYPE_NUMBER);
				bFind = true;
			}
		} while( 0 );
	}
	


	if( bFind == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	
	p->SetMaskColour(r, g, b);

	return JS_TRUE;
}

/***
 * <method name="setOption">
 *  <function>
 *   <arg name="Name" type=WXJS_TYPE_STRING>Name of the option</arg>
 *   <arg name="Value" type=WXJS_TYPE_STRING>Value of the option</arg>
 *  </function>
 *  <function>
 *   <arg name="Name" type=WXJS_TYPE_STRING>Name of the option</arg>
 *   <arg name="Value" type=WXJS_TYPE_NUMBER>Value of the option</arg>
 *  </function>
 *  <desc>
 *   Sets a user-defined option. The function is case-insensitive to name.
 *   For example, when saving as a JPEG file, the option quality is used, 
 *   which is a number between 0 and 100 (0 is terrible, 100 is very good).
 *   See @wxImage#getOption, @wxImage#getOptionInt, @wxImage#hasOption.
 *  </desc>
 * </method>
 */
JSBool Image::setOption(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImage *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	/*
	void 	SetOption (const wxString &name, const wxString &value)
 		Sets a user-defined option. More...
 
	void 	SetOption (const wxString &name, int value)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
	*/
	
	int argIndex = 0;
    wxString name;


	if( argv[argIndex].isString() == true )
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex++;
		if( argv[argIndex].isString() == true )
		{
			wxString value;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(value, WXJS_TYPE_STRING);
			p->SetOption(name, value);
			return JS_TRUE;
		}
		else
		if( argv[argIndex].isNumber() == true )
		{
			int value;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(value, WXJS_TYPE_NUMBER);
			p->SetOption(name, value);
			return JS_TRUE;
		}
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
					name : String
				,	value : String or Value
			}
			*/

			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_VALUE), &v) == JS_TRUE )  
				{
					if( v.isString() == true ) 
					{
						wxString value;
						FromJS(cx, v, value ) ;
						p->SetOption(name, value);
						return JS_TRUE;
					}
					else
					if( v.isNumber() == true ) 
					{
						p->SetOption(name, v.toInt32());
						return JS_TRUE;
					} 
					else
					{
						ReportError_PropTypeError(cx, PROP_NM_VALUE, "String or Number");
						return JS_FALSE;
					}
				}
				else
				{
					ReportError_PropMustError(cx, PROP_NM_VALUE);
					return JS_FALSE;
				}
			}

		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="getOption">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the option.
 *   </arg>
 *  </function>
 *  <desc>
 *   Gets a user-defined option. The function is case-insensitive to name.
 *   See @wxImage#setOption, @wxImage#getOptionInt, @wxImage#hasOption
 *  </desc>
 * </method>
 */
JSBool Image::getOption(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argIndex = 0;
    wxString name;


	if( argv[argIndex].isString() == true )
	{
		*vp = ToJS(cx, p->GetOption(name));
		return JS_TRUE;

	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
				name : String
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				*vp = ToJS(cx, p->GetOption(name));
				return JS_TRUE;
			}

		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="getOptionInt">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the option.
 *   </arg>
 *  </function>
 *  <desc>
 *   Gets a user-defined option. The function is case-insensitive to name.
 *   See @wxImage#setOption, @wxImage#getOptionString, @wxImage#hasOption
 *  </desc>
 * </method>
 */
JSBool Image::getOptionInt(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argIndex = 0;
    wxString name;


	if( argv[argIndex].isString() == true )
	{
		*vp = ToJS(cx, p->GetOptionInt(name));
		return JS_TRUE;

	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
				name : String
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				*vp = ToJS(cx, p->GetOptionInt(name));
				return JS_TRUE;
			}

		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="hasOption">
 *  <function returns="Boolean">
 *   <arg name="Name" type=WXJS_TYPE_STRING>
 *    The name of the option.
 *   </arg>
 *  </function>
 *  <desc>
 *   Returns true if the given option is present. The function is case-insensitive to name.
 *   See @wxImage#setOption, @wxImage#getOptionInt, @wxImage#hasOption
 *  </desc>
 * </method>
 */
JSBool Image::hasOption(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argIndex = 0;
    wxString name;


	if( argv[argIndex].isString() == true )
	{
		*vp = ToJS(cx, p->HasOption(name));
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
				name : String
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_NAME), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(name, pObj, PROP_NM_RED, WXJS_TYPE_NUMBER);
				*vp = ToJS(cx, p->HasOption(name));
				return JS_TRUE;
			}

		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

ZZZJS_BEGIN_STATIC_METHOD_MAP(Image)
    ZZZJS_METHOD("canRead", canRead, 1)
    ZZZJS_METHOD("addHandler", addHandler, 1)
    ZZZJS_METHOD("cleanUpHandlers", cleanUpHandlers, 0)
    ZZZJS_METHOD("removeHandler", removeHandler, 1)
    ZZZJS_METHOD("findHandler", findHandler, 1)
    ZZZJS_METHOD("findHandlerMime", findHandlerMime, 1)
    ZZZJS_METHOD("insertHandler", insertHandler, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <class_method name="addHandler">
 *  <function>
 *   <arg name="Handler" type="@wxImageHandler" />
 *  </function>
 *  <desc>
 *   Adds a handler to the end of the static list of format handlers.
 *   There is usually only one instance of a given handler class in an application session.
 *   See @wxImage#handlers and @wxInitAllImageHandlers
 *  </desc>
 * </class_method>
 */
JSBool Image::addHandler(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    ImageHandlerPrivate *p = ImageHandler::GetPrivate(cx, argv[0]);
    if ( p == NULL )
        return JS_FALSE;

    p->SetOurs(false);
    wxImage::AddHandler(p->GetHandler());

    return JS_TRUE;
}

/***
 * <class_method name="canRead">
 *  <function returns="Boolean">
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>
 *    A filename.
 *   </arg>
 *  </function>
 *  <desc>
 *   Returns true when the file can be read.
 *  </desc>
 * </class_method>
 */
JSBool Image::canRead(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxString name;
    FromJS(cx, argv[0], name);
    *vp = ToJS(cx, wxImage::CanRead(name));
    return JS_TRUE;
}

/***
 * <class_method name="cleanUpHandlers">
 *  <function />
 *  <desc>
 *   Removes all handlers. Is called automatically by wxWindows.
 *  </desc>
 * </class_method>
 */
JSBool Image::cleanUpHandlers(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxImage::CleanUpHandlers();
    return JS_TRUE;
}

/***
 * <class_method name="findHandler">
 *  <function returns="@wxImageHandler">
 *   <arg name="Name" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <function returns="@wxImageHandler">
 *   <arg name="Extension" type=ZZZJS_TYPE_STRING />
 *   <arg name="Type" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <function returns="@wxImageHandler">
 *   <arg name="Type" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Searches a handler
 *  </desc>
 * </class_method>
 */
JSBool Image::findHandler(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImageHandler *handler = NULL;
    if ( JSVAL_IS_STRING(argv[0]) )
    {
        wxString str;
        FromJS(cx, argv[0], str);

        if ( argc == 2 )
        {
            long type;
            if ( FromJS(cx, argv[1], type) )
            {
                handler = wxImage::FindHandler(str, (wxBitmapType)type);
            }
            else
                return JS_FALSE;
        }
        else
            handler = wxImage::FindHandler(str);
    }
    else
    {
        long type;
        if ( FromJS(cx, argv[1], type) )
        {
            handler = wxImage::FindHandler((wxBitmapType)type);
        }
        else
            return JS_FALSE;
    }

    if ( handler == NULL )
        *vp = JSVAL_VOID;
    else
    {
        *vp = ImageHandler::CreateObject(cx, new ImageHandlerPrivate(handler, false));
    }
    
    return JS_TRUE;
}

/***
 * <class_method name="findHandlerMime">
 *  <function returns="@wxImageHandler">
 *   <arg name="Type" type=ZZZJS_TYPE_STRING>
 *    A mime type.
 *   </arg>
 *  </function>
 *  <desc>
 *   Finds the handler associated with the given MIME type.
 *  </desc>
 * </class_method>
 */
JSBool Image::findHandlerMime(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxString mime;
    FromJS(cx, argv[0], mime);

    wxImageHandler *handler = wxImage::FindHandlerMime(mime);
    if ( handler == NULL )
        *vp = JSVAL_VOID;
    else
    {
        *vp = ImageHandler::CreateObject(cx, new ImageHandlerPrivate(handler, false));
    }
    return JS_TRUE;
}

/***
 * <class_method name="removeHandler">
 *  <function returns="Boolean">
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>
 *    The name of the handler.
 *   </arg>
 *  </function>
 *  <desc>
 *   Remove the given handler.
 *  </desc>
 * </class_method>
 */
JSBool Image::removeHandler(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxString name;
	FromJS(cx, argv[0], name);

	*vp = ToJS(cx, wxImage::RemoveHandler(name));
	return JS_TRUE;
}

/***
 * <class_method name="insertHandler">
 *  <function>
 *   <arg name="Handler" type="@wxImageHandler" />
 *  </function>
 *  <desc>
 *   Adds a handler at the start of the static list of format handlers.
 *   There is usually only one instance of a given handler class in an application session.
 *   See @wxImage#handlers
 *  </desc>
 * </class_method>
 */
JSBool Image::insertHandler(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	ImageHandlerPrivate *p = ImageHandler::GetPrivate(cx, argv[0]);
	if ( p == NULL )
		return JS_FALSE;

	p->SetOurs(false);
	wxImage::InsertHandler(p->GetHandler());

	return JS_TRUE;
}
