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
#include "js/gui/errors.h"
#include "js/common/jsutil.h"
#include "js/gui/misc/mask.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/image.h"
#include "js/gui/misc/colour.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_BITMAP					"bitmap"
#define PROP_NM_INDEX					"index"
#define PROP_NM_COLOUR					"colour"



/***
 * <file>misc/bitmap</file>
 * <module>gui</module>
 * <class name="wxMask">
 *  This class encapsulates the concept of a platform-dependent bitmap, either monochrome or colour.
 *  See @wxIcon and @wxBitmapType
 * </class>
 */
ZZZJS_INIT_CLASS(Mask, "Mask", 0)

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
ZZZJS_BEGIN_PROPERTY_MAP(Mask)
  ZZZJS_READONLY_PROPERTY(P_BITMAP, "bitmap")
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Mask)
  ZZZJS_METHOD("create", create, 1)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxMask, Mask)
{
    switch(id) 
	{
	case P_BITMAP:
		{
			wxBitmap bmp = p->GetBitmap();
			vp.set( Bitmap::CreateObject(cx, new wxBitmap( bmp ), NULL) );
		}
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
 *   Constructs a new wxMask object.
 *   See @wxBitmapType
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxMask, Mask)
{
	wxMask *p = new wxMask();
	
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

JSBool Mask::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{

	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxMask *p = GetPrivate(cx, obj);
    *rval = JSVAL_FALSE;


	// 引数の取得
	int argIndex = 0;

	/*
 	wxMask (const wxBitmap &bitmap, int index)
 	Constructs a mask from a bitmap and a palette index that indicates the background. More...
 
 	wxMask (const wxBitmap &bitmap)
 	Constructs a mask from a monochrome bitmap. More...
 
 	wxMask (const wxBitmap &bitmap, const wxColour &colour)
 	Constructs a mask from a bitmap and a colour that indicates the background.
	*/
	zzzJsPtr<wxBitmap> apBitmap;


	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == true ) {
		ZZZJS_CHECK_ARG_COUNT(1, 2);
		
		argIndex++;

		if( argc == 1 )
		{
			vp->setBoolean(
				p->Create(*(apBitmap.get()))
			);
			return JS_TRUE;
		}
		
		zzzJsPtr<wxColour> apColour;
		if( argv[argIndex].isNumber() == true ) 
		{
			int index = 0;

			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
			vp->setBoolean(
				p->Create(*(apBitmap.get()), index)
			);
			return JS_TRUE;
		}
		else
		if( ZZZJS_ARG_GET_AP(apColour, Colour) == true )
		{
			vp->setBoolean(
				p->Create(*(apBitmap.get()), *(apColour.get()))
			);
			return JS_TRUE;
		}
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_BITMAP), &v) == JS_TRUE )  
			{
				zzzJsPtr<wxBitmap> apBitmap;
				ZZZJS_PROP_AP_CHK_AND_ERROR(apBitmap, obj, Bitmap, PROP_NM_BITMAP);


				if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_INDEX), &v) == JS_TRUE )  
				{
					int index = 0;
					ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, obj, PROP_NM_INDEX, WXJS_TYPE_NUMBER);
										
					vp->setBoolean(
						p->Create(*(apBitmap.get()), index)
					);
					return JS_TRUE;
				}
				else
				if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
				{
					zzzJsPtr<wxColour> apColour;
					ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, obj, Colour, PROP_NM_COLOUR);
										
					vp->setBoolean(
						p->Create(*(apBitmap.get()),  *(apColour.get()))
					);
					return JS_TRUE;
				}
				else
				{
					vp->setBoolean(
						p->Create(*(apBitmap.get()))
					);
					return JS_TRUE;
				}
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}


ZZZJS_BEGIN_O2I(wxMask, Mask)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}
	
	/*
	wxMask ()
 		Default constructor. More...
 
 	wxMask (const wxBitmap &bitmap, int index)
 		Constructs a mask from a bitmap and a palette index that indicates the background. More...
 
 	wxMask (const wxBitmap &bitmap)
 		Constructs a mask from a monochrome bitmap. More...
 
 	wxMask (const wxBitmap &bitmap, const wxColour &colour)
 		Constructs a mask from a bitmap and a colour that indicates the background.
	*/


	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_BITMAP), &v) == JS_TRUE )  
	{
		zzzJsPtr<wxBitmap> apBitmap;
		ZZZJS_PROP_AP_CHK_AND_ERROR(apBitmap, obj, Bitmap, PROP_NM_BITMAP);


		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_INDEX), &v) == JS_TRUE )  
		{
			int index = 0;
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, obj, PROP_NM_INDEX, WXJS_TYPE_NUMBER);

			bAllocation = true;
			return new wxMask(*(apBitmap.get()), index);
		}
		else
		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLOUR), &v) == JS_TRUE )  
		{
			zzzJsPtr<wxColour> apColour;
			ZZZJS_PROP_AP_CHK_AND_ERROR(apColour, obj, Colour, PROP_NM_COLOUR);

			bAllocation = true;
			return new wxMask(*(apBitmap.get()), *(apColour.get()));
		}
		else
		{
			bAllocation = true;
			return new wxMask(*(apBitmap.get()));
		}
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
JSBool Mask::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
