/*
 * wxJavaScript - rect.cpp
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
 * $Id: rect.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// rect.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 




#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "wx/wxprec.h"

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/size.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"


using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_X				"x"
#define PROP_NM_Y				"y"
#define PROP_NM_HEIGHT			"height"
#define PROP_NM_WIDTH			"width"
#define PROP_NM_TOP_LEFT		"topLeft"
#define PROP_NM_BOTTOM_RIGHT	"bottomRight"
#define PROP_NM_POS				"pos"
#define PROP_NM_SIZE			"size"
#define PROP_NM_RECT			"rect"
#define PROP_NM_DIFF			"diff"

/***
 * <file>misc/rect</file>
 * <module>gui</module>
 * <class name="wxRect">
 *	A class for manipulating rectangles
 * </class>
 */
ZZZJS_INIT_CLASS(Rect, "Rect", 0)

/***
 * <properties>
 *	<property name="width" type=WXJS_TYPE_NUMBER>
 *	 The width of the rectangle
 *  </property>
 *	<property name="height" type=WXJS_TYPE_NUMBER>
 *	 The height of the rectangle
 *  </property>
 *	<property name="bottom" type=WXJS_TYPE_NUMBER>
 *	 The bottom
 *  </property>
 *  <property name="left" type=WXJS_TYPE_NUMBER />
 *  <property name="position" type="@wxPoint" readonly="Y" />
 *  <property name="right" type=WXJS_TYPE_NUMBER />
 *  <property name="size" type="@wxSize" readonly="Y" />
 *  <property name="top" type=WXJS_TYPE_NUMBER />
 *  <property name="x" type=WXJS_TYPE_NUMBER />
 *  <property name="y" type=WXJS_TYPE_NUMBER />
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Rect)
	ZZZJS_PROPERTY(P_WIDTH, "width")
	ZZZJS_PROPERTY(P_HEIGHT, "height")
	ZZZJS_PROPERTY(P_BOTTOM, "bottom")
	ZZZJS_READONLY_PROPERTY(P_LEFT, "left")
	ZZZJS_PROPERTY(P_POSITION, "position")
	ZZZJS_PROPERTY(P_RIGHT, "right")
	ZZZJS_READONLY_PROPERTY(P_SIZE, "size")
	ZZZJS_PROPERTY(P_TOP, "top")
	ZZZJS_PROPERTY(P_X, "x")
	ZZZJS_PROPERTY(P_Y, "y")
ZZZJS_END_PROPERTY_MAP()

//bool Rect::GetProperty(wxRect *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxRect, Rect)
	switch (id) 
	{
	case P_WIDTH:
		ToJSVal(cx, vp, p->GetWidth());
		break;
	case P_HEIGHT:
		ToJSVal(cx, vp, p->GetHeight());
		break;
	case P_BOTTOM:
		ToJSVal(cx, vp, p->GetBottom());
		break;
	case P_LEFT:
		ToJSVal(cx, vp, p->GetLeft());
		break;
	case P_POSITION:
		vp.set( zzzJs::ext::CreatePoint(cx, p->GetPosition()) );
		break;
	case P_RIGHT:
		ToJSVal(cx, vp, p->GetRight());
		break;
	case P_SIZE:
		vp.set(  Size::CreateObject(cx, new wxSize(p->GetSize())) );
		break;
	case P_TOP:
		ToJSVal(cx, vp, p->GetTop());
		break;
	case P_X:
		ToJSVal(cx, vp, p->GetX());
		break;
	case P_Y:
		ToJSVal(cx, vp, p->GetY());
		break;
	}
	return true;
ZZZJS_END_GET_PROP
	
ZZZJS_BEGIN_SET_PROP(wxRect, Rect)
	switch (id) 
	{
	case P_WIDTH:
		{
			int width;
			if ( FromJS(cx, vp, width) )
				p->SetWidth(width);
			break;
		}
	case P_HEIGHT:
		{
			int height;
			if ( FromJS(cx, vp, height) )
				p->SetHeight(height);
			break;
		}
	case P_BOTTOM:
		{
			int bottom;
			if ( FromJS(cx, vp, bottom) )
				p->SetBottom(bottom);
			break;
		}
	case P_LEFT:
		{
			int left;
			if ( FromJS(cx, vp, left) )
				p->SetLeft(left);
			break;
		}
	case P_RIGHT:
		{
			int right;
			if ( FromJS(cx, vp, right) )
				p->SetRight(right);
			break;
		}
	case P_TOP:
		{
			int top;
			if ( FromJS(cx, vp, top) )
				p->SetTop(top);
			break;
		}
	case P_X:
		{
			int x;
			if ( FromJS(cx, vp, x ) )
				p->SetX(x);
			break;
		}
	case P_Y:
		{
			int y;
			if ( FromJS(cx, vp, y) )
				p->SetY(y);
			break;
		}
	}
	return true;
ZZZJS_END_SET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>
 *	  X-coordinate of the top level corner
 *   </arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>
 *	  Y-coordinate of the top level corner
 *   </arg>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *	  The width of the rectangle
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *	  The height of the rectangle
 *   </arg>
 *  </function>
 *  <function>
 *	 <arg name="TopLeft" type="@wxPoint">
 *	  The top-left corner
 *   </arg>
 *	 <arg name="BottomRight" type="@wxPoint">
 *	  The bottom-right corner
 *   </arg>
 *  </function>
 *  <function>
 *	 <arg name="Position" type="@wxPoint" />
 *   <arg name="Size" type="@wxSize" />
 *  </function>
 *  <desc>
 *	 Constructs a new wxRect object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxRect, Rect)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    /*
 	wxRect ()
 	Default constructor. More...
 
 	wxRect (int x, int y, int width, int height)
 	Creates a wxRect object from x, y, width and height values. More...
 
 	wxRect (const wxPoint &topLeft, const wxPoint &bottomRight)
 	Creates a wxRect object from top-left and bottom-right points. More...
 
 	wxRect (const wxPoint &pos, const wxSize &size)
 	Creates a wxRect object from position pos and size values. More...
 
 	wxRect (const wxSize &size)
 	Creates a wxRect object from size values at the origin.

	+ 
	
 	wxRect (const wxRect &rc)
 	Creates a wxRect object from rc values at the origin.


	*/

	
	int argIndex = 0;
	if ( argc == 0 ) {
		return new wxRect();
	}

	zzzJsPtr<wxPoint> apPoint;

	if( argv[argIndex].isNumber() == true ) {
 		//wxRect (int x, int y, int width, int height)
 		//Creates a wxRect object from x, y, width and height values. More...
		if( argc > 4 ) {
			argc = 4;
		}
		if( argc != 4 ) {
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return NULL;
		}
		
		int x;
		int y;
		int width;
		int height;
		
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		// 2
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		// 3
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		// 4
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;

		return new wxRect(x, y, width, height);
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		// Objectの場合
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL ) {
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return NULL;
		}

		/*
 			wxRect (const wxRect &rc)
 			Creates a wxRect object from rc values at the origin.
		*/
		wxRect* pRc = Rect::GetPrivate(cx, pObj);
		if( pRc != NULL ) {
			return new wxRect(*pRc);
		}
		/*
 			wxRect (const wxSize &size)
 			Creates a wxRect object from size values at the origin.
		*/
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		if( ZZZJS_PROP_GET_AP(apSize, Size, pObj) == false )
		{
			return new wxRect(*(apSize.get()));
		}
	}
	else
	if( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == true ) 
	{
		/*
 			wxRect (const wxPoint &topLeft, const wxPoint &bottomRight)
 			Creates a wxRect object from top-left and bottom-right points. More...
 
 			wxRect (const wxPoint &pos, const wxSize &size)
 			Creates a wxRect object from position pos and size values. More...
		*/
		zzzJsPtr<wxPoint> apPoint2(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		bool bIsSz = false;

		ZZZJS_CHECK_ARG_COUNT(2, 2)

		argIndex++;
		if( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == false )
		{
			ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
			bIsSz = true;
		}

		if( bIsSz == true ) {
			return new wxRect(*(apPoint.get()), *(apSize.get()));
		} else {
			return new wxRect(*(apPoint.get()), *(apPoint2.get()));
		}
	} 
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			zzzJsPtr<wxRect> apRect;

			if( apRect.set( 
				Rect::getObject2Instance(cx, pObj, apRect.bAllocation) ) == true 
			) {
				if( apRect.bAllocation == true ) {
					return apRect.release();
				} else {
					return new wxRect(*apRect.get());
				}
			}
		} while( 0 );
	}
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(wxRect, Rect)
{

	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_X), &v) == JS_TRUE )  
	{
		// 	wxRect (int x, int y, int width, int height)
		int x;
		int y;
		int width;
		int height;

		// x
		if( FromJS(cx, v, x) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_X, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}

		// y
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, obj, PROP_NM_Y, WXJS_TYPE_NUMBER)	
			
		// width
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER)	
		
		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)	

		
		bAllocation = true;
		return new wxRect(x, y, width, height);
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_TOP_LEFT), &v) == JS_TRUE )  
	{
		// wxRect (const wxPoint &topLeft, const wxPoint &bottomRight)
		zzzJsPtr<wxPoint> topLeft;
		zzzJsPtr<wxPoint> bottomRight;

		if( ZZZJS_PROP_GET_AP(topLeft, zzzJs::ext::Point, v) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_TOP_LEFT, zzzJs::ext::Point::getClassName());
			return JS_FALSE;
		}
		// height
		ZZZJS_PROP_AP_CHK_AND_ERROR(bottomRight, obj, zzzJs::ext::Point, PROP_NM_BOTTOM_RIGHT)
			
		bAllocation = true;
		return new wxRect(*(topLeft.get()), *(bottomRight.get()));
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_POS), &v) == JS_TRUE )  
	{
		// wxRect (const wxPoint &pos, const wxSize &size)
		zzzJsPtr<wxPoint>  pos;
		zzzJsPtr<wxSize> apSize;

		
		if( ZZZJS_PROP_GET_AP(pos, zzzJs::ext::Point, v) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_POS,  zzzJs::ext::Point::getClassName());
			return JS_FALSE;
		}
		// height
		ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_SIZE);
		
		bAllocation = true;
		return new wxRect(*(pos.get()), *(apSize.get()));
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
	{
		// wxRect (const wxSize &size)
		zzzJsPtr<wxSize> apSize;
		
		if( apSize.set(Size::getObject2Instance(cx, v, apSize.bAllocation)) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_SIZE, Size::getClassName());
			return JS_FALSE;
		}
		
		bAllocation = true;
		return new wxRect(*(apSize.get()));
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_RECT), &v) == JS_TRUE )  
	{
		// wxRect (const wxRect &rect)
		zzzJsPtr<wxRect> apRect;
		
		if( apRect.set(Rect::getObject2Instance(cx, v, apRect.bAllocation)) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_RECT, Rect::getClassName());
			return JS_FALSE;
		}
		
		bAllocation = true;
		if( apRect.bAllocation == true ) 
		{
			return apRect.release();
		}
		return new wxRect(  *(apRect.get())  );
	}
	
	return NULL;
}
ZZZJS_END_O2I
//wxRect* Rect::getObject2Instance(JSContext *cx, JS::Value v, wxRect& workData)
//{
//	if( v.isObjectOrNull() == false ) {
//		return NULL;
//	}
//	return Rect::getObject2Instance(cx, v.toObjectOrNull(), workData);
//}
//wxRect* Rect::getObject2Instance(JSContext *cx, JSObject *obj, wxRect& workData)
//{
//	jsval v;
//	wxRect* pRet = NULL;
//	 /*
// 	wxRect ()
// 	Default constructor. More...
// 
// 	wxRect (int x, int y, int width, int height)
// 	Creates a wxRect object from x, y, width and height values. More...
// 
// 	wxRect (const wxPoint &topLeft, const wxPoint &bottomRight)
// 	Creates a wxRect object from top-left and bottom-right points. More...
// 
// 	wxRect (const wxPoint &pos, const wxSize &size)
// 	Creates a wxRect object from position pos and size values. More...
// 
// 	wxRect (const wxSize &size)
// 	Creates a wxRect object from size values at the origin.
//
//	+ 
//	
// 	wxRect (const wxRect &rc)
// 	Creates a wxRect object from rc values at the origin.
//
//
//	*/
//	if( GetPropertyWhenPresent( cx, obj, _T("x"), &v) == JS_TRUE )  
//	{
//		// 	wxRect (int x, int y, int width, int height)
//		int x;
//		int y;
//		int width;
//		int height;
//
//		// x
//		if( FromJS(cx, v, x) == false ) {
//			ReportError_PropTypeError(cx, "x", WXJS_TYPE_NUMBER);
//			return JS_FALSE;
//		}
//
//		// y
//		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, obj, "y", WXJS_TYPE_NUMBER)	
//			
//		// width
//		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, "width", WXJS_TYPE_NUMBER)	
//		
//		// height
//		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, "height", WXJS_TYPE_NUMBER)	
//
//
//		workData = wxRect(x, y, width, height);
//		pRet = &workData;
//		return pRet;
//	}
//	if( GetPropertyWhenPresent( cx, obj, _T("topLeft"), &v) == JS_TRUE )  
//	{
//		// wxRect (const wxPoint &topLeft, const wxPoint &bottomRight)
//		zzzJsPtr<wxPoint> topLeft;
//		zzzJsPtr<wxPoint> bottomRight;
//
//		if( ZZZJS_PROP_GET_AP(topLeft, zzzJs::ext::Point, v) == false ) {
//			ReportError_PropTypeError(cx, "topLeft", zzzJs::ext::Point::getClassName());
//			return JS_FALSE;
//		}
//		// height
//		ZZZJS_PROP_AP_CHK_AND_ERROR(bottomRight, obj, zzzJs::ext::Point, "bottomRight")
//
//		workData = wxRect(*(topLeft.get()), *(bottomRight.get()));
//		pRet = &workData;
//		return pRet;
//	}
//	if( GetPropertyWhenPresent( cx, obj, _T("pos"), &v) == JS_TRUE )  
//	{
//		// wxRect (const wxPoint &pos, const wxSize &size)
//		zzzJsPtr<wxPoint>  pos;
//		zzzJsPtr<wxSize> apSize;
//
//		
//		if( ZZZJS_PROP_GET_AP(pos, zzzJs::ext::Point, v) == false ) {
//			ReportError_PropTypeError(cx, "pos",  zzzJs::ext::Point::getClassName());
//			return JS_FALSE;
//		}
//		// height
//		ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, "size");
//
//		workData = wxRect(*(pos.get()), *(apSize.get()));
//		pRet = &workData;
//		return pRet;
//	}
//	if( GetPropertyWhenPresent( cx, obj, _T("size"), &v) == JS_TRUE )  
//	{
//		// wxRect (const wxSize &size)
//		zzzJsPtr<wxSize> apSize;
//		
//		if( apSize.set(Size::getObject2Instance(cx, v, apSize.bAllocation)) == false ) {
//			ReportError_PropTypeError(cx, "size", Size::getClassName());
//			return JS_FALSE;
//		}
//
//		workData = wxRect(*(apSize.get()));
//		pRet = &workData;
//		return pRet;
//	}
//	if( GetPropertyWhenPresent( cx, obj, _T("rect"), &v) == JS_TRUE )  
//	{
//		// wxRect (const wxRect &rect)
//		wxRect rc;
//
//		if( FromJS(cx, v, rc) == false ) {
//			ReportError_PropTypeError(cx, "rect", "Rect");
//			return JS_FALSE;
//		}
//
//		workData = wxRect(rc);
//		pRet = &workData;
//		return pRet;
//	}
//	return NULL;
//}


ZZZJS_BEGIN_METHOD_MAP(Rect)
  ZZZJS_METHOD("inflate", inflate, 1)
  ZZZJS_METHOD("deflate", deflate, 1)
  ZZZJS_METHOD("offset", offset, 1)
  ZZZJS_METHOD("intersect", intersect, 1)
  ZZZJS_METHOD("inside", inside, 1)
  ZZZJS_METHOD("intersects", intersects, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="inflate">
 *	<function>
 *	 <arg name="X" type=WXJS_TYPE_NUMBER />
 *	 <arg name="Y" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Increases the rectangle size by X in x direction and by Y in y direction.
 *	 When Y is not specified then the value of X is used. You can use negative
 *	 values to decrease the size.
 *  </desc>
 * </method>
 */
JSBool Rect::inflate(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRect *p = Rect::GetPrivate(cx, obj);

	/*
	wxRect & 	Inflate (wxCoord dx, wxCoord dy)
 		Increases the size of the rectangle. More...
 
	wxRect & 	Inflate (const wxSize &diff)
 		Increases the size of the rectangle. More...
 
	wxRect & 	Inflate (wxCoord diff)
 		Increases the size of the rectangle. More...
 
	wxRect 	Inflate (wxCoord dx, wxCoord dy) const
 		Increases the size of the rectangle.
	*/
	int argIndex = 0;
	zzzJsPtr<wxSize> apSize;


	if( argv[argIndex].isNumber() == true ) 
	{
		if( argc == 1 ) 
		{
			int diff = 0;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(diff, WXJS_TYPE_STRING);
			
			p->Inflate( diff );
			return JS_TRUE;
		}
		wxCoord x = 0;
		wxCoord y = 0;
		ZZZJS_CHECK_ARG_COUNT(2, 2);
	
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_STRING);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_STRING);
		argIndex++;

		
		 p->Inflate(x, y);
		 
		return JS_TRUE;
	}
	else
	if( ZZZJS_ARG_GET_AP(apSize, Size) == true )
	{
		 p->Inflate(*(apSize.get()));
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				wxCoord x = 0;
				wxCoord y = 0;
				// x
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER)
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER)
				
				 p->Inflate(x, y);
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_DIFF), &v) == JS_TRUE )  
			{
				wxCoord diff = 0;
				// diff
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(diff, pObj, PROP_NM_DIFF, WXJS_TYPE_NUMBER)
					
				 p->Inflate(diff);
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				// size
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE)
					
				 p->Inflate( *(apSize.get()) );
		 
				return JS_TRUE;
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="deflate">
 *	<function>
 *	 <arg name="X" type=WXJS_TYPE_NUMBER />
 *	 <arg name="Y" type=WXJS_TYPE_NUMBER default="X"/>
 *  </function>
 *  <desc>
 *	 Decreases the rectangle size by X in x direction and by Y in y direction.
 *	 When Y is not specified then the value of X is used. You can use negative
 *	 values to decrease the size.
 *  </desc>
 * </method>
 */
JSBool Rect::deflate(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRect *p = Rect::GetPrivate(cx, obj);

	/*
	wxRect & 	Deflate (wxCoord dx, wxCoord dy)
 		Decrease the rectangle size. More...
 
	wxRect & 	Deflate (const wxSize &diff)
 		Decrease the rectangle size. More...
 
	wxRect & 	Deflate (wxCoord diff)
 		Decrease the rectangle size. More...
 
	wxRect 	Deflate (wxCoord dx, wxCoord dy) const
 		Decrease the rectangle size.
	*/
	int argIndex = 0;
	zzzJsPtr<wxSize> apSize;


	if( argv[argIndex].isNumber() == true ) 
	{
		if( argc == 1 ) 
		{
			int diff = 0;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(diff, WXJS_TYPE_STRING);
			
			p->Deflate( diff );
			return JS_TRUE;
		}
		wxCoord x = 0;
		wxCoord y = 0;
		ZZZJS_CHECK_ARG_COUNT(2, 2);
	
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_STRING);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_STRING);
		argIndex++;

		
		 p->Deflate(x, y);
		 
		return JS_TRUE;
	}
	else
	if( ZZZJS_ARG_GET_AP(apSize, Size) == true )
	{
		 p->Deflate(*(apSize.get()));
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				wxCoord x = 0;
				wxCoord y = 0;
				// x
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER)
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER)
				
				 p->Deflate(x, y);
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_DIFF), &v) == JS_TRUE )  
			{
				wxCoord diff = 0;
				// diff
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(diff, pObj, PROP_NM_DIFF, WXJS_TYPE_NUMBER)
					
				 p->Deflate(diff);
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				// size
				ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, pObj, Size, PROP_NM_SIZE)
					
				 p->Deflate( *(apSize.get()) );
		 
				return JS_TRUE;
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="offset">
 *	<function>
 *	 <arg name="X" type=WXJS_TYPE_NUMBER />
 *	 <arg name="Y" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *   <arg name="Pt" type="@wxPoint" />
 *  </function>
 *  <desc>
 *	 Moves the rectangle.
 *  </desc>
 * </method>
 */
JSBool Rect::offset(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxRect *p = GetPrivate(cx, obj);
	
	/*
	void 	Offset (wxCoord dx, wxCoord dy)
 		Moves the rectangle by the specified offset. More...
 
	void 	Offset (const wxPoint &pt)
 		Moves the rectangle by the specified offset.
	*/
	int argIndex = 0;
	zzzJsPtr<wxPoint> pt;


	if( argv[argIndex].isNumber() == true )
	{
		wxCoord x = 0;
		wxCoord y = 0;
		ZZZJS_CHECK_ARG_COUNT(2, 2);
	
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_STRING);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_STRING);
		argIndex++;
		
		 p->Offset(x, y);
		 
		return JS_TRUE;
	}
	else
	if ( ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point, argv[argIndex]) == true )
	{

		 p->Offset( *(pt.get()) );
		 
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				wxCoord x = 0;
				wxCoord y = 0;
				// x
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER)
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER)
				
				 p->Offset(x, y);
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_POS), &v) == JS_TRUE )  
			{
				// pos
				ZZZJS_PROP_AP_CHK_AND_ERROR(pt, pObj, zzzJs::ext::Point, PROP_NM_POS)
				
				 p->Offset( *(pt.get()) );
		 
				return JS_TRUE;
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="intersect">
 *  <function returns="wxRect">
 *	 <arg name="Rect" type="wxRect" />
 *  </function>
 * </method>
 */
JSBool Rect::intersect(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxRect *p = GetPrivate(cx, obj);

	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apRect, Rect);

	*vp = CreateObject(cx, new wxRect(p->Intersect(*(apRect.get()))));

	return JS_TRUE;
}

/***
 * <method name="inside">
 *	<function returns="Boolean">
 *	 <arg name="X" type=WXJS_TYPE_NUMBER />
 *	 <arg name="Y" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *   <arg name="Pt" type="@wxPoint" />
 *  </function>
 *  <desc>
 *	 Returns true when the given coordinates are in the rectangle area.
 *  </desc>
 * </method>
 */
JSBool Rect::inside(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxRect *p = GetPrivate(cx, obj);

	/*
	bool 	Contains (int x, int y) const
 		Returns true if the given point is inside the rectangle (or on its boundary) and false otherwise. More...
 
	bool 	Contains (const wxPoint &pt) const
 		Returns true if the given point is inside the rectangle (or on its boundary) and false otherwise. More...
 
	bool 	Contains (const wxRect &rect) const
	*/

	int argIndex = 0;
	zzzJsPtr<wxPoint> pt;
	zzzJsPtr<wxRect> apRect;


	if( argv[argIndex].isNumber() == true )
	{
		wxCoord x = 0;
		wxCoord y = 0;
		ZZZJS_CHECK_ARG_COUNT(2, 2);
	
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_STRING);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_STRING);
		argIndex++;
		
		vp->setBoolean(p->Contains(x, y));
		 
		return JS_TRUE;
	}
	else
	if ( ZZZJS_PROP_GET_AP(pt, zzzJs::ext::Point, argv[argIndex]) == true )
	{

		vp->setBoolean( p->Contains( *(pt.get()) ) );
		 
		return JS_TRUE;
	}
	else
	if ( ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex]) == true )
	{

		vp->setBoolean( p->Contains( *(apRect.get()) ) );
		 
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_X), &v) == JS_TRUE )  
			{
				wxCoord x = 0;
				wxCoord y = 0;
				// x
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER)
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER)
				
				 vp->setBoolean(p->Contains(x, y));
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_POS), &v) == JS_TRUE )  
			{
				// pos
				ZZZJS_PROP_AP_CHK_AND_ERROR(pt, pObj, zzzJs::ext::Point, PROP_NM_POS)
				
				vp->setBoolean( p->Contains( *(pt.get()) ) );
		 
				return JS_TRUE;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_RECT), &v) == JS_TRUE )  
			{
				// rect
				ZZZJS_PROP_AP_CHK_AND_ERROR(apRect, pObj, Rect, PROP_NM_RECT)
				
				vp->setBoolean( p->Contains( *(apRect.get()) ) );
		 
				return JS_TRUE;
			}
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

/***
 * <method name="intersects">
 *	<function returns="Boolean">
 *	 <arg name="Rect" type="wxRect" />
 *  </function>
 *  <desc>
 *	 Returns true when the rectangles have a non empty intersection
 *  </desc>
 * </method>
 */
JSBool Rect::intersects(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxRect *p = GetPrivate(cx, obj);

	
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apRect, Rect);

	vp->setBoolean( p->Intersects(*(apRect.get())) );
//	*vp = CreateObject(cx, new wxRect(p->Intersects(*(apRect.get()))));

	return JS_TRUE;
}
