/*
 * wxJavaScript - region.cpp
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
 * $Id: region.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/ext/point.h"
#include "js/gui/misc/region.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/image.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/mask.h"
#include "js/gui/misc/pallet.h"
#include "js/gui/misc/mask.h"
#include "js/gui/errors.h"
#include "js/common/jsutil.h"
#include "js/gui/misc/colour.h"
#include "js/gui/gdi/dc.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>misc/bitmap</file>
 * <module>gui</module>
 * <class name="wxRegion">
 *  This class encapsulates the concept of a platform-dependent bitmap, either monochrome or colour.
 *  See @wxIcon and @wxBitmapType
 * </class>
 */
ZZZJS_INIT_CLASS(Region, "Region", 0)

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
ZZZJS_BEGIN_PROPERTY_MAP(Region)
  ZZZJS_READONLY_PROPERTY(P_IsEMPTY, "isEmpty")
  ZZZJS_READONLY_PROPERTY(P_BOX, "box")
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Region)
  ZZZJS_METHOD("contains", contains, 1)
  ZZZJS_METHOD("convertToBitmap", convertToBitmap, 0)
  ZZZJS_METHOD("intersect", intersect, 1)
  ZZZJS_METHOD("isEqual", isEqual, 1)
  ZZZJS_METHOD("subtract", subtract, 1)
  ZZZJS_METHOD("__union", __union, 1)
  ZZZJS_METHOD("xor", xor, 1)
  ZZZJS_METHOD("offset", offset, 1)
ZZZJS_END_METHOD_MAP()


ZZZJS_BEGIN_GET_PROP(wxRegion, Region)
{
    switch(id) 
	{
	case P_IsEMPTY:
		ToJSVal(cx, vp, p->IsEmpty());
		break;
	case P_BOX:
		{
			wxCoord x = 0;
			wxCoord y = 0;
			wxCoord width = 0;
			wxCoord height = 0;

			vp.set( Rect::CreateObject( cx, new wxRect(x, y, width, height)) );
		}
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxRegion, Region)
{
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
 *   Constructs a new wxRegion object.
 *   See @wxBitmapType
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxRegion, Region)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	/*
 	wxRegion ()
 	Default constructor. More...
 
 	wxRegion (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 	Constructs a rectangular region with the given position and size. More...
 
 	wxRegion (const wxPoint &topLeft, const wxPoint &bottomRight)
 	Constructs a rectangular region from the top left point and the bottom right point. More...
 
 	wxRegion (const wxRect &rect)
 	Constructs a rectangular region a wxRect object. More...
 
 	wxRegion (const wxRegion &region)
 	Copy constructor, uses Reference Counting. More...
 
 	wxRegion (size_t n, const wxPoint *points, wxPolygonFillMode fillStyle=wxODDEVEN_RULE)
 	Constructs a region corresponding to the polygon made of n points in the provided array. More...
 
 	wxRegion (const wxBitmap &bmp)
 	Constructs a region using a bitmap. More...
 
 	wxRegion (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
 	Constructs a region using the non-transparent pixels of a bitmap.
	*/
	int argIndex = 0;
	
	bool bAllocation = false;
	wxImage* pImage = NULL;
	wxBitmap* pBitmap = NULL;
	zzzJsPtr<wxPoint> pPoint;
	zzzJsPtr<wxRect> apRect;
	wxRegion* pRecgion= NULL;


	if( argc == 0 ) {
		return new wxRegion();
	}


	if( (ZZZJS_ARG_GET_PRIVATE(pBitmap, Bitmap)) != NULL ) {
		/*
 			wxRegion (const wxBitmap &bmp) 
 			wxRegion (const wxBitmap &bmp
				, const wxColour &transColour
				, int tolerance=0
			)
		*/
		
		ZZZJS_CHECK_ARG_COUNT(1, 3);

		if( argc == 1 ) {
			return new wxRegion(*pBitmap);
		}
		zzzJsPtr<wxColour> apColour;
		int tolerance=0;

		// 
		ZZZJS_ARG_AP_CHK_AND_ERROR(apColour, Colour);

		
		argIndex = argc -1;
		switch( argc ) 
		{
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(tolerance, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		}
		// wxRegion (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
		return new wxRegion(*pBitmap, *(apColour.get()), tolerance);
	}
	else
	if( (ZZZJS_PROP_GET_AP(pPoint, zzzJs::ext::Point, argv[argIndex])) == true ) {
		/*
 			wxRegion (const wxPoint &topLeft, const wxPoint &bottomRight)
		*/
		ZZZJS_CHECK_ARG_COUNT(2, 2);

		argIndex++;
		
		zzzJsPtr<wxPoint> bottomRight;
		ZZZJS_ARG_AP_CHK_AND_ERROR(bottomRight, zzzJs::ext::Point);


		// wxRegion (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
		return new wxRegion(*(pPoint.get()), *(bottomRight.get()));
	}
	else
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == true )
	{
		return new wxRegion(*(apRect.get()));
	}
	else
	if( (ZZZJS_ARG_GET_PRIVATE(pRecgion, Region)) != NULL ) {
		// wxRegion (const wxRegion &region)
		return new wxRegion(*pRecgion);
	}
	else
	if( argv[argIndex].isNumber() == true ) {
		//wxRegion (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		ZZZJS_CHECK_ARG_COUNT(4, 4);

		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		// 2
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		// 3
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;


		return new wxRegion(x, y, width, height);
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			if( JS_IsArrayObject(cx, pObj) == JS_FALSE ) {
				// wxRegion (size_t n, const wxPoint *points, wxPolygonFillMode fillStyle=wxODDEVEN_RULE)

				wxPoint *points = NULL;
				uint32_t length = 0;
				int fillStyle=(int)wxODDEVEN_RULE;

				
				ZZZJS_CHECK_ARG_COUNT(1, 2);

				// 先に、　fillStyleの値を取得。そうでないと、new wxPoint[length]で確保したメモリーが、
				// ZZZJS_ARG_FROMJS_CHK_AND_ERRORマクロからリターンすると、コールされなくてメモリーリークが発生するため。
				argIndex = argc -1;
				switch( argc ) 
				{
				case 2:
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(fillStyle, WXJS_TYPE_NUMBER);
					argIndex--;
					break;
				}

				argIndex = 0;


				// points
				JS_GetArrayLength(cx, pObj, &length);

				if( length == 0 ) {
					break;
				}

				points = new wxPoint[length];
				if( points == NULL ) {
					break;
				}

				for(uint32_t i =0; i < length; i++)
				{
					JS::Value element;
					JS_GetElement(cx, pObj, i, &element);

					zzzJsPtr<wxPoint> pt;
		
					if ( ! ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point, element) == false )
					{
						JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "not Array List.");
						return JS_FALSE;
					}
					points[i] = *(pt.get());
				}
				
				argIndex++;
				
				wxRegion *pRegion = new wxRegion(length, points, (wxPolygonFillMode)fillStyle);
				delete []points;

				return pRegion;
			} else {
				//
				//	その他オブジェクトの場合
				//
				wxRegion *pRegion = Region::getObject2Instance(cx, pObj, bAllocation);
				if( pRegion != NULL ) {
					if( bAllocation == true ) {
						return  pRegion;
					} else {
						return new wxRegion(*pRegion);
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
wxRegion* Region::getObject2Instance(JSContext *cx, JS::Value v, bool& bAllocation)
{
	bAllocation = false;
	if( v.isObjectOrNull() == false ) {
		return NULL;
	}
	return Region::getObject2Instance(cx, v.toObjectOrNull(), bAllocation);
}
wxRegion* Region::getObject2Instance(JSContext *cx, JSObject *obj, bool& bAllocation)
{
	jsval v;
	wxRegion* pRet = NULL;


	bAllocation = false;


	pRet = Region::GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}


	// wxRegion (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
	/*
	{
		x: Number,
		y: Number,
		width: Number,
		height: Number,
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T("x"), &v) == JS_TRUE )  
	{
		// wxRegion (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
		wxCoord x = 0;
		wxCoord y = 0;
		wxCoord width = 0;
		wxCoord height = 0;
		
		// x
		if( FromJS(cx, v, x) == false ) {
			// データ型が合わない場合は、エラー出力
			ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// y
		ZZZJS_PROP_FROMJS_IF_EXIST(y, obj, "y", WXJS_TYPE_NUMBER)	
		// width
		ZZZJS_PROP_FROMJS_IF_EXIST(width, obj, "width", WXJS_TYPE_NUMBER)	
		// height
		ZZZJS_PROP_FROMJS_IF_EXIST(height, obj, "height", WXJS_TYPE_NUMBER)	


		bAllocation = true;
		return new  wxRegion(x, y, width, height);
	}

	// wxRegion (const wxPoint &topLeft, const wxPoint &bottomRight)
	/*
	{
		topLeft: Point,
		bottomRight: Point,
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T("topLeft"), &v) == JS_TRUE )  
	{
		zzzJsPtr<wxPoint> topLeft, bottomRight;
		
		// topLeft
		if( ZZZJS_PROP_GET_AP(topLeft, zzzJs::ext::Point, v) == false ) {
			// データ型が合わない場合は、エラー出力
			ReportError_PropTypeError(cx, "topLeft", zzzJs::ext::Point::getClassName());
			return JS_FALSE;
		}
		// bottomRight
		ZZZJS_PROP_AP_CHK_AND_ERROR(bottomRight, obj, zzzJs::ext::Point, "bottomRight")	;



		bAllocation = true;
		return new  wxRegion(*(topLeft.get()), *(bottomRight.get()));
	}

	// wxRegion (const wxRect &rect)
	/*
	{
		rect: Rect
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T("rect"), &v) == JS_TRUE )  
	{
		zzzJsPtr<wxRect> apRect;
		// rect		
		if( ZZZJS_PROP_GET_AP(apRect, Rect, v) == false ) {
			// データ型が合わない場合は、エラー出力
			ReportError_PropTypeError(cx, "rect", Rect::getClassName());
			return JS_FALSE;
		}
		bAllocation = true;
		return new  wxRegion(  *(apRect.get())  );
	}

 	// wxRegion (const wxBitmap &bmp)
 	// wxRegion (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
	/*
		{
			bmp:Bitmap
		}
		    OR
		{
			bmp:Bitmap,
			transColour:Colour,
			tolerance:Number
		}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T("bmp"), &v) == JS_TRUE )  
	{
		zzzJsPtr<wxBitmap> apBitmap;

		if( ZZZJS_PROP_GET_AP(apBitmap, Bitmap, v) == false ) 
		{
			// データ型が合わない場合は、エラー出力
			ReportError_PropTypeError(cx, "bmp", Bitmap::getClassName());
			return JS_FALSE;
		}

		
		if( GetPropertyWhenPresent( cx, obj, _T("transColour"), &v) == JS_TRUE )  
		{
			zzzJsPtr<wxColour> apColour;
			int tolerance=0;

			// transColour
			if( apColour.set( Colour::getObject2Instance(cx, v, apColour.bAllocation) ) == false ) {
				// データ型が合わない場合は、エラー出力
				ReportError_PropTypeError(cx, "transColour", Colour::getClassName());
				return JS_FALSE;
			}

			
			// tolerance
			ZZZJS_PROP_FROMJS_IF_EXIST(tolerance, obj, "tolerance", WXJS_TYPE_NUMBER)	
				

			bAllocation = true;
			return new  wxRegion(*(apBitmap.get()), tolerance, tolerance);
		} else {

			bAllocation = true;
			return new  wxRegion(*(apBitmap.get()));
		}
	}

	return NULL;
}



/***
 * <method name="contains">
 * </method>
 */
JSBool Region::contains(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		wxRegionContain 	Contains (wxCoord x, wxCoord y) const
 			Returns a value indicating whether the given point is contained within the region. More...
 
		wxRegionContain 	Contains (const wxPoint &pt) const
 			Returns a value indicating whether the given point is contained within the region. More...
 
		wxRegionContain 	Contains (wxCoord x, wxCoord y, wxCoord width, wxCoord height) const
 			Returns a value indicating whether the given rectangle is contained within the region. More...
 
		wxRegionContain 	Contains (const wxRect &rect) const
 			Returns a value indicating whether the given rectangle is contained within the region.
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxPoint>  pt;
	zzzJsPtr<wxRect> apRect;


	if( argv[argIndex].isNumber() == true ) {
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;

		
		ZZZJS_CHECK_ARG_COUNT(2, 4);
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER)
		argIndex++;

		if( argc == 4 ) {
			// wxRegionContain 	Contains (wxCoord x, wxCoord y, wxCoord width, wxCoord height) const
			// 2
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER)
			argIndex++;
			// 3
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER)
			argIndex++;


			wxRegionContain ret = p->Contains(x, y, width, height);
			vp->setInt32( (int)ret );
			
			return JS_TRUE;
		} else {
			// wxRegionContain 	Contains (wxCoord x, wxCoord y, wxCoord width, wxCoord height) const
			wxRegionContain ret = p->Contains(x, y);
			vp->setInt32( (int)ret );
			
			return JS_TRUE;
		}
	}
	else if( ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex]) == true ) {
		// wxRegionContain 	Contains (const wxRect &rect) const
		wxRegionContain ret = p->Contains(  *(apRect.get())  );
		vp->setInt32( (int)ret );
			
		return JS_TRUE;
	}
	else if( ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point, argv[argIndex]) == true ) {
		// wxRegionContain 	Contains (const wxPoint &pt) const
		wxRegionContain ret = p->Contains(*(pt.get()));
		vp->setInt32( (int)ret );
			
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}


			jsval v;
			wxCoord x = 0;
			wxCoord y = 0;
			wxRegionContain	ret;

			if( GetPropertyWhenPresent( cx, pObj, _T("x"), &v) == JS_TRUE )  
			{
				/*
					wxRegionContain 	Contains (wxCoord x, wxCoord y) const
				*/

				// x
				if( FromJS(cx, v, x) == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
					return JS_FALSE;
				}
				// y
				ZZZJS_PROP_FROMJS_IF_EXIST(y, pObj, "y", WXJS_TYPE_NUMBER)	

				if( GetPropertyWhenPresent( cx, pObj, _T("width"), &v) == JS_TRUE )  
				{
					/* 
						wxRegionContain 	Contains (wxCoord x, wxCoord y, wxCoord width, wxCoord height) const
					*/
					wxCoord width = 0;
					wxCoord height = 0;
					
					// width
					ZZZJS_PROP_FROMJS_IF_EXIST(width, pObj, "width", WXJS_TYPE_NUMBER)	
					// height
					ZZZJS_PROP_FROMJS_IF_EXIST(height, pObj, "height", WXJS_TYPE_NUMBER)	
					ret = p->Contains(x, y, width, height);
				} 
				else
				{
					ret = p->Contains(x, y);
				}
				vp->setInt32(ret);
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T("pt"), &v) == JS_TRUE || 
				GetPropertyWhenPresent( cx, pObj, _T("point"), &v) == JS_TRUE )  
			{
				wxRegionContain	ret;
				/*
					wxRegionContain 	Contains (const wxPoint &pt) const
				*/

				// x
				if( ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point, v) == false ) 
				{
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "pt", zzzJs::ext::Point::getClassName() );
					return JS_FALSE;
				}
				ret = p->Contains(*(pt.get()));				
				vp->setInt32(ret);
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T("rect"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, pObj, _T("rc"), &v) == JS_TRUE )  
			{		

				wxRegionContain	ret;
				// wxRegionContain 	Contains (const wxRect &rect) const

				// rect
				if( ZZZJS_PROP_GET_AP(apRect, Rect, v) == false ) 
				{
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "rect", Rect::getClassName() );
					return JS_FALSE;
				}
				ret = p->Contains( *(apRect.get())  );				
				vp->setInt32(ret);
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}
	



/***
 * <method name="convertToBitmap">
 * </method>
 */
JSBool Region::convertToBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		wxBitmap 	ConvertToBitmap () const
 			Convert the region to a black and white bitmap with the white pixels being inside the region. 
	*/
	wxBitmap bmp = p->ConvertToBitmap();
	if( bmp.IsOk() == false ) {
		vp->setNull();
	} else {
		*vp = Bitmap::CreateObject(cx, new wxBitmap(bmp));
	}
	
	return JS_FALSE;
}



/***
 * <method name="intersect">
 * </method>
 */
JSBool Region::intersect(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		bool 	Intersect (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 			Finds the intersection of this region and another, rectangular region, specified using position and size. More...
 
		bool 	Intersect (const wxRect &rect)
 			Finds the intersection of this region and another, rectangular region. More...
 
		bool 	Intersect (const wxRegion &region)
 			Finds the intersection of this region and another region.
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	zzzJsPtr<wxRegion> apRegion;
	

	if( argv[argIndex].isNumber() == true ) {
		// bool 	Intersect (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;

		
		ZZZJS_CHECK_ARG_COUNT(4, 4);
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER)
		argIndex++;
		// 2
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER)
		argIndex++;
		// 3
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER)
		argIndex++;


		vp->setBoolean( 
			p->Intersect(x, y, width, height)	
		);
			
		return JS_TRUE;
	}
	if( ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex]) == false ) 
	{
//	else if( ZZZJS_ARG_FROMJS(rect) == true ) {
		// bool 	Intersect (const wxRect &rect)
		vp->setBoolean( 
			p->Intersect(  *(apRect.get())  )	
		);
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apRegion, Region) == true ) {
		// bool 	Intersect (const wxRegion &region)
		vp->setBoolean( 
			p->Intersect(*(apRegion.get()))	
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* obj = argv[argIndex].toObjectOrNull();
			if( obj == NULL ) {
				break;
			}


			jsval v;

			if( GetPropertyWhenPresent( cx, obj, _T("x"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
				int x = 0;
				int y = 0;
				int width = 0;
				int height = 0;


				// x
				if( FromJS(cx, v, x) == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
					return JS_FALSE;
				}
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, obj, "y", WXJS_TYPE_NUMBER)	
				// width
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, "width", WXJS_TYPE_NUMBER)	
				// height
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, "height", WXJS_TYPE_NUMBER)	
				
				vp->setBoolean( 
					p->Intersect(x, y, width, height)	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("rect"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, obj, _T("rc"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRect &rect)
				/* 
					wxRegionContain 	Contains (const wxRect &rect) const				*/

				// x
				if( ZZZJS_PROP_GET_AP(apRect, Rect, v) == false ) 
				{
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "rect", Rect::getClassName());
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Intersect(  *(apRect.get()) )	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("region"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRegion &region)
				// region
				if( ZZZJS_ARG_GET_AP(apRegion, Region)  == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "region", "Region");
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Intersect( *(apRegion.get()) )	
				);			
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}




/***
 * <method name="isEqual">
 * </method>
 */
JSBool Region::isEqual(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		bool 	IsEqual (const wxRegion &region) const
 			Returns true if the region is equal to, i.e. covers the same area as, another one. More...
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxRegion> apRegion;
	
	if( ZZZJS_ARG_GET_AP(apRegion, Region) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Region");
		return JS_FALSE;
	}

	vp->setBoolean(
		p->IsEqual( *(apRegion.get()) )	
	);

    return JS_TRUE;
}



/***
 * <method name="subtract">
 * </method>
 */
JSBool Region::subtract(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		bool 	Subtract (const wxRect &rect)
 			Subtracts a rectangular region from this region. More...
 
		bool 	Subtract (const wxRegion &region)
 			Subtracts a region from this region.
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	zzzJsPtr<wxRegion> apRegion;
	

//	if( ZZZJS_ARG_FROMJS(rect) == true ) {
	if( ZZZJS_ARG_GET_AP(apRect, Rect) == false ) {
		// bool 	Subtract (const wxRect &rect)
		vp->setBoolean( 
			p->Subtract( *(apRect.get()) )	
		);
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apRegion, Region) == true ) {
		// bool 	Subtract (const wxRegion &region)
		vp->setBoolean( 
			p->Subtract(*(apRegion.get()))	
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* obj = argv[argIndex].toObjectOrNull();
			if( obj == NULL ) {
				break;
			}


			jsval v;

			if( GetPropertyWhenPresent( cx, obj, _T("rect"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, obj, _T("rc"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRect &rect)
//				wxRect rect;
				zzzJsPtr<wxRect> apRect;
				/* 
					wxRegionContain 	Contains (const wxRect &rect) const				*/

				// x
				if( ZZZJS_PROP_GET_AP(apRect, Rect, v) == false ) 
				{
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "rect", Rect::getClassName());
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Subtract( *(apRect.get()) )	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("region"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRegion &region)
				// region
				if( ZZZJS_ARG_GET_AP(apRegion, Region)  == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "region", "Region");
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Subtract( *(apRegion.get()) )	
				);			
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}



/***
 * <method name="union">
 * </method>
 */
JSBool Region::__union(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		bool 	Union (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 			Finds the union of this region and another, rectangular region, specified using position and size. More...
 
		bool 	Union (const wxRect &rect)
 			Finds the union of this region and another, rectangular region. More...
 
		bool 	Union (const wxRegion &region)
 			Finds the union of this region and another region. More...
 
		bool 	Union (const wxBitmap &bmp)
 			Finds the union of this region and the non-transparent pixels of a bitmap. More...
 
		bool 	Union (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
 			Finds the union of this region and the non-transparent pixels of a bitmap.
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	zzzJsPtr<wxRegion> apRegion;
	zzzJsPtr<wxBitmap> apBitmap;

	if( argv[argIndex].isNumber() == true ) {
		// bool 	Union (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;

		
		ZZZJS_CHECK_ARG_COUNT(4, 4);
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER)
		argIndex++;
		// 2
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER)
		argIndex++;
		// 3
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER)
		argIndex++;


		vp->setBoolean( 
			p->Union(x, y, width, height)	
		);
			
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apRect, Rect) == false ) {
		// bool 	Union (const wxRect &rect)
		vp->setBoolean( 
			p->Union( *(apRect.get()) )	
		);
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apRegion, Region) == true ) {
		// bool 	Union (const wxRegion &region)
		vp->setBoolean( 
			p->Union(*(apRegion.get()))	
		);
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap)== true   ) {
		// bool 	Union (const wxBitmap &bmp)
		// bool 	Union (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
		
		ZZZJS_CHECK_ARG_COUNT(1, 3);
		if( argc >= 2 ) {
			zzzJsPtr<wxColour> apColour;
			int tolerance=0;

			argIndex++;
			// 1
			ZZZJS_ARG_AP_CHK_AND_ERROR(apColour, Colour)
			
			argIndex = argc -1;
			switch( argc ) {
			case 2:
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(tolerance, WXJS_TYPE_NUMBER)
				break;
			}
			vp->setBoolean( 
				p->Union(*(apBitmap.get()), *(apColour.get()), tolerance)	
			);
		} else {
			vp->setBoolean( 
				p->Union(*(apBitmap.get()))	
			);
		}
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* obj = argv[argIndex].toObjectOrNull();
			if( obj == NULL ) {
				break;
			}


			jsval v;

			if( GetPropertyWhenPresent( cx, obj, _T("x"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
				int x = 0;
				int y = 0;
				int width = 0;
				int height = 0;


				// x
				if( FromJS(cx, v, x) == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
					return JS_FALSE;
				}
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, obj, "y", WXJS_TYPE_NUMBER)	
				// width
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, "width", WXJS_TYPE_NUMBER)	
				// height
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, "height", WXJS_TYPE_NUMBER)	
				
				vp->setBoolean( 
					p->Union(x, y, width, height)	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("rect"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, obj, _T("rc"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRect &rect)
				zzzJsPtr<wxRect> apRect;
				/* 
					wxRegionContain 	Contains (const wxRect &rect) const				*/

				// x
				if( ZZZJS_PROP_GET_AP(apRect, Rect, v) == false ) 
				{
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "rect", "Rect");
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Union( *(apRect.get()) )	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("region"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRegion &region)
				// region
				if( ZZZJS_PROP_GET_AP(apRegion, Region, v)  == false )
				{
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "region", Region::getClassName());
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Union( *(apRegion.get()) )	
				);			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("bmp"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, obj, _T("bitmap"), &v) == JS_TRUE )  
			{
				// bool 	Union (const wxBitmap &bmp)
				// bool 	Union (const wxBitmap &bmp, const wxColour &transColour, int tolerance=0)
				// region
				if( ZZZJS_PROP_GET_AP(apBitmap, Bitmap, v) == false  ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "bmp", Bitmap::getClassName());
					return JS_FALSE;
				}

				if( GetPropertyWhenPresent( cx, obj, _T("transColour"), &v) == JS_TRUE ) {
					zzzJsPtr<wxColour> apColour;
					int tolerance=0;

					// transColour
					if( apColour.set( Colour::getObject2Instance(cx, v, apColour.bAllocation) ) == false ) 
					{
						ReportError_PropTypeError(cx, "transColour", Colour::getClassName());
						return JS_FALSE;
					}

					// 
					ZZZJS_PROP_FROMJS_IF_EXIST(tolerance, obj, "tolerance", WXJS_TYPE_NUMBER);

					vp->setBoolean( 
						p->Union(*(apBitmap.get()), *(apColour.get()), tolerance)	
					);
				} else {
					vp->setBoolean( 
						p->Union( *(apRegion.get()) )	
					);		
				}
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}



/***
 * <method name="xor">
 * </method>
 */
JSBool Region::xor(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		bool 	Xor (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 			Finds the Xor of this region and another, rectangular region, specified using position and size. More...
 
		bool 	Xor (const wxRect &rect)
 			Finds the Xor of this region and another, rectangular region. More...
 
		bool 	Xor (const wxRegion &region)
 			Finds the Xor of this region and another region. 
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	zzzJsPtr<wxRegion> apRegion;

	if( argv[argIndex].isNumber() == true ) {
		// bool 	Xor (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;

		
		ZZZJS_CHECK_ARG_COUNT(4, 4);
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER)
		argIndex++;
		// 2
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER)
		argIndex++;
		// 3
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER)
		argIndex++;


		vp->setBoolean( 
			p->Xor(x, y, width, height)	
		);
			
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apRect, Rect) == false ) {
		// bool 	Union (const wxRect &rect)
		vp->setBoolean( 
			p->Xor( *(apRect.get()) )	
		);
		return JS_TRUE;
	}
	else if( ZZZJS_ARG_GET_AP(apRegion, Region) == true ) {
		// bool 	Union (const wxRegion &region)
		vp->setBoolean( 
			p->Xor(*(apRegion.get()))	
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* obj = argv[argIndex].toObjectOrNull();
			if( obj == NULL ) {
				break;
			}


			jsval v;

			if( GetPropertyWhenPresent( cx, obj, _T("x"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
				int x = 0;
				int y = 0;
				int width = 0;
				int height = 0;


				// x
				if( FromJS(cx, v, x) == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
					return JS_FALSE;
				}
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, obj, "y", WXJS_TYPE_NUMBER)	
				// width
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, "width", WXJS_TYPE_NUMBER)	
				// height
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, "height", WXJS_TYPE_NUMBER)	
				
				vp->setBoolean( 
					p->Xor(x, y, width, height)	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("rect"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, obj, _T("rc"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRect &rect)
				zzzJsPtr<wxRect> apRect;
				/* 
					wxRegionContain 	Contains (const wxRect &rect) const				*/

				// x
				if( ZZZJS_PROP_GET_AP(apRect, Rect, v) == false )  {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "rect", Rect::getClassName());
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Xor( *(apRect.get()) )	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("region"), &v) == JS_TRUE )  
			{
				// bool 	Intersect (const wxRegion &region)
				// region
				if( ZZZJS_PROP_GET_AP(apRegion, Region, v)  == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "region", Region::getClassName());
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Xor( *(apRegion.get()) )	
				);			
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}



/***
 * <method name="offset">
 * </method>
 */
JSBool Region::offset(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *pObj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRegion *p = GetPrivate(cx, pObj);

	/*
		bool 	Offset (wxCoord x, wxCoord y)
 			Moves the region by the specified offsets in horizontal and vertical directions. More...
 
		bool 	Offset (const wxPoint &pt)
 			Moves the region by the specified offsets in horizontal and vertical directions.
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> pt;
	zzzJsPtr<wxRegion> apRegion;

	if( argv[argIndex].isNumber() == true ) {
		// bool 	Offset (wxCoord x, wxCoord y)
		int x = 0;
		int y = 0;

		
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER)
		argIndex++;


		vp->setBoolean( 
			p->Offset(x, y)	
		);
			
		return JS_TRUE;
	}
	else if( ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point , argv[argIndex]) == true ) {
		// bool 	Offset (const wxPoint &pt)
		vp->setBoolean( 
			p->Offset(*(pt.get()))	
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* obj = argv[argIndex].toObjectOrNull();
			if( obj == NULL ) {
				break;
			}


			jsval v;

			if( GetPropertyWhenPresent( cx, obj, _T("x"), &v) == JS_TRUE )  
			{
				// bool 	Offset (wxCoord x, wxCoord y)
				int x = 0;
				int y = 0;


				// x
				if( FromJS(cx, v, x) == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
					return JS_FALSE;
				}
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, obj, "y", WXJS_TYPE_NUMBER)	
				
				vp->setBoolean( 
					p->Offset(x, y)	
				);
			
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, obj, _T("pt"), &v) == JS_TRUE ||
				GetPropertyWhenPresent( cx, obj, _T("point"), &v) == JS_TRUE )  
			{
				// bool 	Offset (const wxPoint &pt)
				// x
				if( ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point , v) == false ) {
					// データ型が合わない場合は、エラー出力
					ReportError_PropTypeError(cx, "rect", "Rect");
					return JS_FALSE;
				}
				vp->setBoolean( 
					p->Offset(*(pt.get()))	
				);
			
				return JS_TRUE;
			}
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}








