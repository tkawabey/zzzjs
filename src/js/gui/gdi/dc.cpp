/*
 * wxJavaScript - bmpbtn.cpp
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
 * $Id: bmpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/common/clntdata.h"
#include "js/common/jsutil.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"

#include "js/gui/misc/size.h"
#include "js/gui/gdi/dc.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/region.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/brush.h"
#include "js/gui/misc/pen.h"
#include "js/gui/misc/rect.h"
#include "js/gui/control/button.h"
#include "js/gui/control/control.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::gdi;

WXJS_INIT_CLASS(DC, "DC", 0)

/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(DC)
  WXJS_READONLY_PROPERTY(P_DEPTH, "depth")
  WXJS_PROPERTY(P_DeviceOrigin, "deviceOrigin")
  WXJS_PROPERTY(P_LogicalFunction, "logicalFunction")
  WXJS_READONLY_PROPERTY(P_PPI, "PPI")
  WXJS_READONLY_PROPERTY(P_SIZE, "size")
  WXJS_READONLY_PROPERTY(P_SIZEMM, "sizeMM")
  WXJS_PROPERTY(P_UserScale, "userScale")
  WXJS_PROPERTY(P_LogicalScale, "logicalScale")
  WXJS_READONLY_PROPERTY(P_ISOK, "isOk")
  WXJS_PROPERTY(P_ClippingBox, "clippingBox")
  WXJS_READONLY_PROPERTY(P_CharHeight, "charHeight")
  WXJS_READONLY_PROPERTY(P_CharWidth,  "charWidth")
  WXJS_PROPERTY(P_BackgroundMode, "backgroundMode")
  WXJS_PROPERTY(P_Font, "font")
  WXJS_PROPERTY(P_LayoutDirection, "layoutDirection")
  WXJS_PROPERTY(P_TextBackground, "textBackground")
  WXJS_PROPERTY(P_TextForeground, "textForeground")
  WXJS_READONLY_PROPERTY(P_MaxX,  "maxX")
  WXJS_READONLY_PROPERTY(P_MaxY,  "maxY")
  WXJS_READONLY_PROPERTY(P_MinX,  "minX")
  WXJS_READONLY_PROPERTY(P_MinY,  "minY")
  WXJS_PROPERTY(P_Background, "Background")
  WXJS_PROPERTY(P_Brush, "brush")
  WXJS_PROPERTY(P_Pen, "pen")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDC, DC)
{
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	switch (id) 
	{
	case P_DEPTH:
		vp.set( ToJS(cx, p->GetDepth()) );
		break;
	case P_DeviceOrigin:
		{
			wxPoint pt = p->GetDeviceOrigin();
			vp.set( zzzJs::ext::Point::CreateObject(cx, new wxPoint(pt), NULL) );
		}
		break;
	case P_LogicalFunction:
		vp.set( ToJS(cx, (int)p->GetLogicalFunction()) );
		break;
	case P_MapMode:
		vp.set( ToJS(cx, (int)p->GetMapMode()) );
		break;
	case P_PPI:
		{
			wxSize sz = p->GetPPI();
			vp.set( Size::CreateObject(cx, new wxSize(sz), NULL) );
		}
		break;
	case P_SIZE:
		{
			wxSize sz = p->GetSize();
			vp.set( Size::CreateObject(cx, new wxSize(sz), NULL) );
		}
		break;
	case P_SIZEMM:
		{
			wxSize sz = p->GetSizeMM();
			vp.set( Size::CreateObject(cx, new wxSize(sz), NULL) );
		}
		break;
	case P_UserScale:
		{
			double x = 0, y = 0;

			p->GetUserScale(&x, &y);
			
			JSObject *objAttr = JS_NewObject(cx, NULL/*Attr::GetClass()*/, NULL, NULL);
			JS::RootedObject jsvaAttr(cx, objAttr);
			{
				wxString strName(_T("x"));
				jsval attrValue = ToJS(cx, x );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			{
				wxString strName(_T("y"));
				jsval attrValue = ToJS(cx, y );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			vp.setObjectOrNull(objAttr);
		}
		break;
	case P_LogicalScale:
		{
			double x = 0, y = 0;

			p->GetLogicalScale(&x, &y);
			
			JSObject *objAttr = JS_NewObject(cx, NULL/*Attr::GetClass()*/, NULL, NULL);
			JS::RootedObject jsvaAttr(cx, objAttr);
			{
				wxString strName(_T("x"));
				jsval attrValue = ToJS(cx, x );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			{
				wxString strName(_T("y"));
				jsval attrValue = ToJS(cx, y );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			vp.setObjectOrNull(objAttr);
		}
		break;
	case P_ISOK:
		vp.set( ToJS(cx, p->IsOk()) );
		break;
	case P_ClippingBox:
		{
			wxRect rc;
			p->GetClippingBox(rc);
			vp.set( Rect::CreateObject(cx, new wxRect(rc), NULL) );
		}
		break;
	case P_CharHeight:
		vp.set( ToJS(cx, (int)p->GetCharHeight()) );
		break;
	case P_CharWidth:
		vp.set( ToJS(cx, (int)p->GetCharWidth()) );
		break;
	case P_BackgroundMode:
		vp.set( ToJS(cx, (int)p->GetBackgroundMode()) );
		break;
	case P_Font:
		{
			const wxFont& font = p->GetFont();
			vp.set( Font::CreateObject(cx, new wxFont(font), NULL) );
		}
		break;
	case P_LayoutDirection:
		vp.set( ToJS(cx, (int)p->GetLayoutDirection()) );
		break;
	case P_TextBackground:
		{
			const wxColour& font = p->GetTextBackground();
			vp.set( Colour::CreateObject(cx, new wxColour(font), NULL) );
		}
		break;
	case P_TextForeground:
		{
			const wxColour& font = p->GetTextForeground();
			vp.set( Colour::CreateObject(cx, new wxColour(font), NULL) );
		}
		break;
	case P_MaxX:
		vp.set( ToJS(cx, (int)p->MaxX()) );
		break;
	case P_MaxY:
		vp.set( ToJS(cx, (int)p->MaxY()) );
		break;
	case P_MinX:
		vp.set( ToJS(cx, (int)p->MinX()) );
		break;
	case P_MinY:
		vp.set( ToJS(cx, (int)p->MinY()) );
		break;
	case P_Background:
		{
			const wxBrush& brush = p->GetBackground();
			vp.set( Brush::CreateObject(cx, new wxBrush(brush), NULL) );
		}
		break;
	case P_Brush:
		{
			const wxBrush& brush = p->GetBrush();
			vp.set( Brush::CreateObject(cx, new wxBrush(brush), NULL) );
		}
		break;
	case P_Pen:
		{
			const wxPen& pen = p->GetPen();
			vp.set( Pen::CreateObject(cx, new wxPen(pen), NULL) );
		}
		break;
	}
	return true;
}
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDC, DC)
{
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	switch (id) 
	{
	case P_DeviceOrigin:
		{
			zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
			if( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, vp ) == true ) {
				p->SetDeviceOrigin( apPoint->x, apPoint->y );
			}
		}
		break;
	case P_LogicalFunction:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetLogicalFunction((wxRasterOperationMode)iVal);
			}
		}
		break;
	case P_MapMode:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetMapMode((wxMappingMode)iVal);
			}
		}
		break;
	case P_UserScale:
		{
			double x = 0, y = 0;
			jsval v;
			do {
				if( vp.isObject() == false ) {
					break;
				}
				JSObject *pObjHasProp = JSVAL_TO_OBJECT(vp);
				
				// x
				if( GetPropertyWhenPresent(cx, pObjHasProp, _T("x"), &v) == JS_FALSE ) {
					return JS_FALSE;
				}
				if( FromJS(cx, v, x ) == false ) {
					return JS_FALSE;
				}

				
				// y
				if( GetPropertyWhenPresent(cx, pObjHasProp, _T("y"), &v) == JS_FALSE ) {
					return JS_FALSE;
				}
				if( FromJS(cx, v, y ) == false ) {
					return JS_FALSE;
				}
				


				p->SetUserScale( x, y);
			} while( 0 );
		}
		break;
	case P_LogicalScale:
		{
			double x = 0, y = 0;
			jsval v;
			do {
				if( vp.isObject() == false ) {
					break;
				}
				JSObject *pObjHasProp = JSVAL_TO_OBJECT(vp);
				
				// x
				if( GetPropertyWhenPresent(cx, pObjHasProp, _T("x"), &v) == JS_FALSE ) {
					return JS_FALSE;
				}
				if( FromJS(cx, v, x ) == false ) {
					return JS_FALSE;
				}

				
				// y
				if( GetPropertyWhenPresent(cx, pObjHasProp, _T("y"), &v) == JS_FALSE ) {
					return JS_FALSE;
				}
				if( FromJS(cx, v, y ) == false ) {
					return JS_FALSE;
				}


				p->SetLogicalScale( x, y);
			} while( 0 );
		}
		break;
	case P_BackgroundMode:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetBackgroundMode(iVal);
			}
		}
		break;
	case P_Font:
		{
			zzzJsPtr<wxFont> apFont;

			if( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true ) 
			{
				p->SetFont( *(apFont.get()) );
			}
		}
		break;
	case P_LayoutDirection:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetLayoutDirection((wxLayoutDirection)iVal);
			}
		}
		break;
	case P_TextBackground:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetTextBackground( *(apColour.get()) );
			}
		}
		break;
	case P_TextForeground:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetTextForeground( *(apColour.get()) );
			}
		}
		break;
	case P_Background:
		{
			wxBrush* pBrush = Brush::GetPrivate(cx, vp, false);
			if( pBrush != NULL ) {
				p->SetBackground( *pBrush );
			}
		}
		break;
	case P_Brush:
		{
			wxBrush* pBrush = Brush::GetPrivate(cx, vp, false);
			if( pBrush != NULL ) {
				p->SetBrush( *pBrush );
			}
		}
		break;
	case P_Pen:
		{
			wxPen* pPen = Pen::GetPrivate(cx, vp, false);
			if( pPen != NULL ) {
				p->SetPen( *pPen );
			}
		}
		break;
	}
	return true;
}
WXJS_END_SET_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Bitmap" type="@wxBitmap">The bitmap to display</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTO_DRAW">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxDC object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxDC, DC)
	return NULL;
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxDC, DC)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DC)
	WXJS_METHOD("release", release, 0)
	WXJS_METHOD("copyAttributes", copyAttributes, 1)
	WXJS_METHOD("getPixel", getPixel, 2)
	WXJS_METHOD("setAxisOrientation", setAxisOrientation, 2)
	WXJS_METHOD("getAsBitmap", getAsBitmap, 0)
	WXJS_METHOD("deviceToLogicalX", deviceToLogicalX, 1)
	WXJS_METHOD("deviceToLogicalY", deviceToLogicalY, 1)
	WXJS_METHOD("deviceToLogicalXReal", deviceToLogicalXRel, 1)
	WXJS_METHOD("deviceToLogicalYReal", deviceToLogicalYRel, 1)
	WXJS_METHOD("logicalToDeviceX", logicalToDeviceX, 1)
	WXJS_METHOD("logicalToDeviceY", logicalToDeviceY, 1)
	WXJS_METHOD("logicalToDeviceXReal", logicalToDeviceXRel, 1)
	WXJS_METHOD("logicalToDeviceYReal", logicalToDeviceYRel, 1)
	WXJS_METHOD("clear", clear, 0)
	WXJS_METHOD("drawArc", drawArc, 3)
	WXJS_METHOD("drawBitmap", drawBitmap, 2)
	WXJS_METHOD("drawCheckMark", drawCheckMark, 1)
	WXJS_METHOD("drawCircle", drawCircle, 2)
	WXJS_METHOD("drawEllipse", drawEllipse, 1)
	WXJS_METHOD("drawEllipticArc", drawEllipticArc, 4)
	WXJS_METHOD("drawIcon", drawIcon, 2)
	WXJS_METHOD("drawLabel", drawLabel, 2)
	WXJS_METHOD("drawLine", drawLine, 2)
	WXJS_METHOD("drawLines", drawLines, 1)
	WXJS_METHOD("drawPoint", drawPoint, 1)
	WXJS_METHOD("drawPolygon", drawPolygon, 1)
	WXJS_METHOD("drawPolyPolygon", drawPolyPolygon, 1)
	WXJS_METHOD("drawRectangle", drawRectangle, 1)
	WXJS_METHOD("drawRotatedText", drawRotatedText, 3)
	WXJS_METHOD("drawRoundedRectangle", drawRoundedRectangle, 3)
	WXJS_METHOD("drawSpline", drawSpline, 1)
	WXJS_METHOD("drawText", drawText, 2)
	WXJS_METHOD("gradientFillConcentric", gradientFillConcentric, 3)
	WXJS_METHOD("gradientFillLinear", gradientFillLinear, 3)
	WXJS_METHOD("floodFill", floodFill, 2)
	WXJS_METHOD("crossHair", crossHair, 1)
	WXJS_METHOD("destroyClippingRegion", destroyClippingRegion, 0)
	WXJS_METHOD("setClippingRegion", setClippingRegion, 1)
	WXJS_METHOD("setDeviceClippingRegion", setDeviceClippingRegion, 1)
	WXJS_METHOD("getMultiLineTextExtent", getMultiLineTextExtent, 1)
	WXJS_METHOD("getPartialTextExtents", getPartialTextExtents, 1)
	WXJS_METHOD("getTextExtent", getTextExtent, 1)
	WXJS_METHOD("calcBoundingBox", calcBoundingBox, 2)
	WXJS_METHOD("resetBoundingBox", resetBoundingBox, 0)
	WXJS_METHOD("startDoc", startDoc, 1)
	WXJS_METHOD("startPage", startPage, 0)
	WXJS_METHOD("endDoc", endDoc, 0)
	WXJS_METHOD("endPage", endPage, 0)
	WXJS_METHOD("blit", blit, 7)
	WXJS_METHOD("stretchBlit", stretchBlit, 9)
	WXJS_METHOD("getPen", getPen, 0)
	WXJS_METHOD("setPen", setPen, 1)
	WXJS_METHOD("getBrush", getBrush, 0)
	WXJS_METHOD("setBrush", setBrush, 1)
	WXJS_METHOD("canUseTransformMatrix", canUseTransformMatrix, 0)
	WXJS_METHOD("resetTransformMatrix", resetTransformMatrix, 0)
	WXJS_METHOD("canDrawBitmap", canDrawBitmap, 0)
	WXJS_METHOD("canGetTextExtent", canGetTextExtent, 0)
WXJS_END_METHOD_MAP()

JSBool DC::release(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_TRUE;
	delete p;
	JS_SetPrivate(obj, NULL);
	return JS_TRUE;
}

JSBool DC::copyAttributes(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxDC *pSrc=NULL;

	pSrc = DC::GetPrivate(cx, argv[argIndex], false);
	if( pSrc == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->CopyAttributes( *pSrc );

	return JS_TRUE;
}

JSBool DC::getPixel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord x = 0;
	wxCoord y = 0;
	wxColour colour;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	bool	bHasPt = false;

	// 0
	if( argv[argIndex].isNumber() == true ) {
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Number or Point");
			return JS_FALSE;
		}
	} else {
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		bHasPt = true;
	}
	argIndex++;
	// 1
	if ( ! FromJS(cx, argv[argIndex], y) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	





	// APIの実行と戻り値の設定
	bool bRet = false;
	if( bHasPt == true ) {
		bRet = p->GetPixel(*(apPoint.get()), &colour);
	} else {
		bRet = p->GetPixel(x, y, &colour);
	}

	if( bRet == false ) {
		vp->setNull();
	} else {
		*vp = Colour::CreateObject(cx, new wxColour(colour), NULL);
	}


	return JS_TRUE;
}

JSBool DC::setAxisOrientation(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	bool xLeftRight = false;
	bool yBottomUp = false;

	// 0
	if ( ! FromJS(cx, argv[argIndex], xLeftRight) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if ( ! FromJS(cx, argv[argIndex], yBottomUp) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
		return JS_FALSE;
	}
	





	// APIの実行と戻り値の設定
	p->SetAxisOrientation(xLeftRight, yBottomUp);

	return JS_TRUE;
}

JSBool DC::getAsBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxRect* pRect = NULL;
	zzzJsPtr<wxRect> apRect;
	// 0
	if( argc != 0 ) {
		if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == false )
//		if ( ! FromJS(cx, argv[argIndex], rc) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName() );
			return JS_FALSE;
		}
		pRect = apRect.get();
	}



	// APIの実行と戻り値の設定
	wxBitmap bmp = p->GetAsBitmap(  pRect );
	*vp = Bitmap::CreateObject(cx, new wxBitmap(), NULL);

	return JS_TRUE;
}

JSBool DC::deviceToLogicalX(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->DeviceToLogicalX(val) );

	return JS_TRUE;
}

JSBool DC::deviceToLogicalY(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->DeviceToLogicalY(val) );

	return JS_TRUE;
}

JSBool DC::deviceToLogicalXRel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->DeviceToLogicalXRel(val) );

	return JS_TRUE;
}

JSBool DC::deviceToLogicalYRel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->DeviceToLogicalYRel(val) );

	return JS_TRUE;
}

JSBool DC::logicalToDeviceX(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->LogicalToDeviceX(val) );

	return JS_TRUE;
}

JSBool DC::logicalToDeviceY(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->LogicalToDeviceY(val) );

	return JS_TRUE;
}

JSBool DC::logicalToDeviceXRel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->LogicalToDeviceXRel(val) );

	return JS_TRUE;
}

JSBool DC::logicalToDeviceYRel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	

	// 引数の取得
	int argIndex = 0;
	wxCoord val = 0;

	// 0
	if ( ! FromJS(cx, argv[argIndex], val) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	vp->setInt32(  p->LogicalToDeviceYRel(val) );

	return JS_TRUE;
}

JSBool DC::clear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	



	// APIの実行と戻り値の設定
	p->Clear();

	return JS_TRUE;
}

JSBool DC::drawArc(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawArc (wxCoord xStart, wxCoord yStart, wxCoord xEnd, wxCoord yEnd, wxCoord xc, wxCoord yc)
 	Draws an arc from the given start to the given end point. More...
 
	void 	DrawArc (const wxPoint &ptStart, const wxPoint &ptEnd, const wxPoint &centre)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;

	if( argc >= 6 ) {
		argc = 6;

		wxCoord xStart = 0;
		wxCoord yStart = 0;
		wxCoord xEnd = 0;
		wxCoord yEnd = 0;
		wxCoord xc = 0;
		wxCoord yc = 0;
		
		// 0
		if ( ! FromJS(cx, argv[argIndex], xStart) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], yStart) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], xEnd) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], yEnd) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 4
		if ( ! FromJS(cx, argv[argIndex], xc) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 5
		if ( ! FromJS(cx, argv[argIndex], yc) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;

		p->DrawArc(xStart, yStart, xEnd, yEnd, xc, yc);
	} else {		
		zzzJsPtr<wxPoint> apPtStart(NULL, &wxDefaultPosition);
		zzzJsPtr<wxPoint> apPtEnd(NULL, &wxDefaultPosition);
		zzzJsPtr<wxPoint> apPtCenter(NULL, &wxDefaultPosition);

		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPtStart, zzzJs::ext::Point);
		argIndex++;
		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPtEnd, zzzJs::ext::Point);
		argIndex++;
		// 2
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPtCenter, zzzJs::ext::Point);
		argIndex++;


		p->DrawArc(*(apPtStart.get()), *(apPtEnd.get()), *(apPtCenter.get()));
	}


	// APIの実行と戻り値の設定
	
	return JS_TRUE;
}

JSBool DC::drawBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawBitmap (const wxBitmap &bitmap, wxCoord x, wxCoord y, bool useMask=false)
 	Draw a bitmap on the device context at the specified point. More...
 
	void 	DrawBitmap (const wxBitmap &bmp, const wxPoint &pt, bool useMask=false)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;
	bool useMask=false;
	
	if( argc >= 4 ) {
		argc = 4;
	}


	// 0
	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
		return JS_FALSE;
	}
	if( apBitmap->IsOk() == false ) {
		JS_ReportError(cx, "spesified bitmap is invalid.");
		return JS_FALSE;
	}
	argIndex++;
	
	
	// 1
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x = 0;
		wxCoord y = 0;
		if( argc < 3 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}


		// 1
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;

		if( argc == 4 ) {
			if ( ! FromJS(cx, argv[argIndex], useMask) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
				return JS_FALSE;
			}
			argIndex++;
		}
		p->DrawBitmap(*(apBitmap.get()), x, y, useMask);
	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;

		
		if( argc >= 3 ) {
			if ( ! FromJS(cx, argv[argIndex], useMask) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
				return JS_FALSE;
			}
			argIndex++;
		}
				
		p->DrawBitmap(*(apBitmap.get()), *(apPoint.get()), useMask);
	}



	// APIの実行と戻り値の設定


	return JS_TRUE;
}

JSBool DC::drawCheckMark(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawCheckMark (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 	Draws a check mark inside the given rectangle. More...
 
	void 	DrawCheckMark (const wxRect &rect)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	
	if( argc >= 4 ) {
		argc = 4;
	}


	// 0
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x = 0;
		wxCoord y = 0;
		wxCoord width = 0;
		wxCoord height = 0;
		if( argc < 4 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}


		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], height) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;


		p->DrawCheckMark(x, y, width, height);
	} else {
		zzzJsPtr<wxRect> apRect;
//		if ( ! FromJS(cx, argv[argIndex], rc) )
		if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName() );
			return JS_FALSE;
		}
		argIndex++;

			
		p->DrawCheckMark( *(apRect.get()) );
	}
	
	// APIの実行と戻り値の設定
	
	return JS_TRUE;
}

JSBool DC::drawCircle(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawCircle (wxCoord x, wxCoord y, wxCoord radius)
 	Draws a circle with the given centre and radius. More...
 
	void 	DrawCircle (const wxPoint &pt, wxCoord radius)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	
	if( argc >= 3 ) {
		argc = 3;
	}


	// 0
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x = 0;
		wxCoord y = 0;
		wxCoord radius = 0;
		if( argc < 3 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}


		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], radius) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;


		p->DrawCircle(x, y, radius);
	} else {
		if( argc < 2 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		wxCoord radius = 0;
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], radius) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;

			
		p->DrawCircle(*(apPoint.get()), radius);
	}
	
	// APIの実行と戻り値の設定
	
	return JS_TRUE;
}

JSBool DC::drawEllipse(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawEllipse (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 	Draws an ellipse contained in the rectangle specified either with the given top left corner and the given size or directly. More...
 
	void 	DrawEllipse (const wxPoint &pt, const wxSize &size)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
 
	void 	DrawEllipse (const wxRect &rect)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. 
	*/

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	
	if( argc >= 4 ) {
		argc = 4;
	}


	// 0
	if( argv[argIndex].isNumber() == true ) {
		// void 	DrawEllipse (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
		wxCoord x = 0;
		wxCoord y = 0;
		wxCoord width = 0;
		wxCoord height = 0;
		if( argc < 4 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}


		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], height) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;


		p->DrawEllipse(x, y, width, height);
	} else
//	if( FromJS(cx, argv[argIndex], rc) ) 
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == true )
	{
		// void 	DrawEllipse (const wxRect &rect)

			
		p->DrawEllipse(  *(apRect.get()) );
	} else {
		// void 	DrawEllipse (const wxPoint &pt, const wxSize &size)

		if( argc < 2 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);

		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex++;



		p->DrawEllipse(*(apPoint.get()), *(apSize.get()));
	}
	
	// APIの実行と戻り値の設定
	
	return JS_TRUE;
}

JSBool DC::drawEllipticArc(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawEllipticArc (wxCoord x, wxCoord y, wxCoord width, wxCoord height, double start, double end)
 	Draws an arc of an ellipse. More...
 
	void 	DrawEllipticArc (const wxPoint &pt, const wxSize &sz, double sa, double ea)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	
	if( argc >= 6 ) {
		argc = 6;
	}


	// 0
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x = 0;
		wxCoord y = 0;
		wxCoord width = 0;
		wxCoord height = 0;
		double start = 0;
		double end = 0;
		if( argc < 6 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}


		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], height) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 4
		if ( ! FromJS(cx, argv[argIndex], start) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex++;
		// 5
		if ( ! FromJS(cx, argv[argIndex], end) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex++;

		p->DrawEllipticArc(x, y, width, height, start, end);
	} else {
		if( argc < 4 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}
		double sa = 0;
		double ea = 0;
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);


		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], sa) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], ea) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex++;

			
		p->DrawEllipticArc(*(apPoint.get()), *(apSize.get()), sa, ea);
	}	
	// APIの実行と戻り値の設定
	
	return JS_TRUE;
}

JSBool DC::drawIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawIcon (const wxIcon &icon, wxCoord x, wxCoord y)
 	Draw an icon on the display (does nothing if the device context is PostScript). More...
 
	void 	DrawIcon (const wxIcon &icon, const wxPoint &pt)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxIcon* pIcon = NULL;
	
	if( argc >= 3 ) {
		argc = 3;
	}


	// 0
	pIcon = Icon::GetPrivate(cx, argv[argIndex], false);
	if( pIcon == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Icon");
		return JS_FALSE;
	}
	argIndex++;
	
	// 1
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x = 0;
		wxCoord y = 0;
		if( argc < 3 ) {
			JS_ReportError(cx, "invalid arguments.");
			return false;
		}


		// 1
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;


		p->DrawIcon(*pIcon, x, y);
	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		
		p->DrawIcon(*pIcon, *(apPoint.get()));
	}

	// APIの実行と戻り値の設定

	return JS_TRUE;
}

JSBool DC::drawLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawLabel (
		const wxString &text, 
		const wxBitmap &bitmap, 
		const wxRect &rect, 
		int alignment=wxALIGN_LEFT|wxALIGN_TOP, 
		int indexAccel=-1, 
		wxRect *rectBounding=NULL)
 	Draw optional bitmap and the text into the given rectangle and aligns it as specified by alignment parameter; it also will emphasize the character with the given index if it is != -1 and return the bounding rectangle if required. More...
 
	void 	DrawLabel (
		const wxString &text, 
		const wxRect &rect, 
		int alignment=wxALIGN_LEFT|wxALIGN_TOP, 
		int indexAccel=-1)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. 
	*/

	// 引数の取得
	int argIndex = 0;
	wxString text;
	zzzJsPtr<wxBitmap> apBitmap;
	
	if( argc >= 6 ) {
		argc = 6;
	}


	// 0
	if ( ! FromJS(cx, argv[argIndex], text) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	
	
	// 1
	if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[argIndex], apBitmap.bAllocation)) == true ) {
		if( argc >= 6 ) {
			argc = 6;
		}
		if( argc < 3 ) {
			JS_ReportError(cx, "invalid arguments.");
			return JS_FALSE;
		}


		zzzJsPtr<wxRect> apRect;
		int alignment=wxALIGN_LEFT|wxALIGN_TOP;
		int indexAccel=-1;
//		wxRect rectBounding;
		zzzJsPtr<wxRect> apRectBounding;

		
		argIndex++;


		//2
		if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName() );
			return JS_FALSE;
		}
		argIndex++;

		argIndex = argc -1;
		switch( argc ) {
		case 6:
//			if( FromJS(cx, argv[argIndex], rectBounding) == false ) 
			if( (ZZZJS_PROP_GET_AP(apRectBounding, Rect, argv[argIndex])) == false )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName() );
				return JS_FALSE;
			}
			argIndex--;
		case 5:
			if ( ! FromJS(cx, argv[argIndex], indexAccel) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex--;
		case 4:
			if ( ! FromJS(cx, argv[argIndex], alignment) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex--;
			break;
		}


		p->DrawLabel(text, *(apBitmap.get()), *(apRect.get()), alignment, indexAccel, apRectBounding.get() );

	} else {
		int alignment=wxALIGN_LEFT|wxALIGN_TOP;
		int indexAccel=-1;
		zzzJsPtr<wxRect> apRect;


		if( argc >= 4 ) {
			argc = 4;
		}
		if( argc < 2 ) {
			JS_ReportError(cx, "invalid arguments.");
			return JS_FALSE;
		}
		// 2
		if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName());
			return JS_FALSE;
		}
		argIndex++;
		

		argIndex = argc -1;
		switch( argc ) {
		case 4:
			if ( ! FromJS(cx, argv[argIndex], indexAccel) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			if ( ! FromJS(cx, argv[argIndex], alignment) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex--;
			break;
		}


		p->DrawLabel(text, *(apRect.get()), alignment, indexAccel );
	}

	// APIの実行と戻り値の設定

	return JS_TRUE;
}

JSBool DC::drawLine(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawLine (wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2)
 	Draws a line from the first point to the second. More...
 
	void 	DrawLine (const wxPoint &pt1, const wxPoint &pt2)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. 
	*/

	// 引数の取得
	int argIndex = 0;
	
	if( argc >= 4 ) {
		argc = 4;
	}

	
	// 1
	if( argv[argIndex].isNumber() ) {
		if( argc < 4 ) {
			JS_ReportError(cx, "invalid arguments.");
			return JS_FALSE;
		}
		wxCoord x1,  y1,  x2,  y2;

		// 0
		if ( ! FromJS(cx, argv[argIndex], x1) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		
		// 1
		if ( ! FromJS(cx, argv[argIndex], y1) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		
		// 2
		if ( ! FromJS(cx, argv[argIndex], x2) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		
		// 3
		if ( ! FromJS(cx, argv[argIndex], y2) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		
		
		p->DrawLine(x1,  y1,  x2,  y2 );
	} else {
		if( argc < 2 ) {
			JS_ReportError(cx, "invalid arguments.");
			return JS_FALSE;
		}
		zzzJsPtr<wxPoint> apPoint1(NULL, &wxDefaultPosition);
		zzzJsPtr<wxPoint> apPoint2(NULL, &wxDefaultPosition);
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint1, zzzJs::ext::Point);
		argIndex++;
		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint2, zzzJs::ext::Point);
		argIndex++;
		
		p->DrawLine(*(apPoint1.get()), *(apPoint2.get()) );
	}

	// APIの実行と戻り値の設定

	return JS_TRUE;
}
JSBool DC::drawLines(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawLines (const wxPointList *points, wxCoord xoffset=0, wxCoord yoffset=0)
 	This method uses a list of wxPoints, adding the optional offset coordinate.
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord xoffset=0;
	wxCoord yoffset=0;
	std::vector<wxPoint>	cntPoints;
	
	if( argc >= 3 ) {
		argc = 3;
	}


	if( argv[argIndex].isObjectOrNull() == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
    JSObject *objItems = JSVAL_TO_OBJECT(argv[argIndex]);
	if( objItems == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	if( JS_IsArrayObject(cx, objItems) == JS_FALSE ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}

	wxPointList to;
	uint32_t length = 0;
	JS_GetArrayLength(cx, objItems, &length);
	for(uint32_t i =0; i < length; i++)
	{
		JS::Value element;
		JS_GetElement(cx, objItems, i, &element);

		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		
		if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, element) == false )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "not Array List.");
			return JS_FALSE;
		}
		cntPoints.push_back(*(apPoint.get()));

		wxPoint& refPt = cntPoints[cntPoints.size()-1];

		to.push_back( &refPt );
	}

	argIndex = argc -1;
	switch( argc ) {
	case 3:
		if ( ! FromJS(cx, argv[argIndex], yoffset) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 2:
		if ( ! FromJS(cx, argv[argIndex], xoffset) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}

	// APIの実行と戻り値の設定
	p->DrawLines(&to, xoffset, yoffset);

	return JS_TRUE;
}


JSBool DC::drawPoint(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawPoint (wxCoord x, wxCoord y)
 	Draws a point using the color of the current pen. More...
 
	void 	DrawPoint (const wxPoint &pt)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxString text;
	
	if( argc >= 2 ) {
		argc = 2;
	}


	// 0
	if ( ! FromJS(cx, argv[argIndex], text) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	
	
	// 1
	if( argv[argIndex].isNumber() ) {
		if( argc < 2 ) {
			JS_ReportError(cx, "invalid arguments.");
			return JS_FALSE;
		}
		wxCoord x,  y;

		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		

		p->DrawPoint(x,  y);
	} else {
		if( argc < 1 ) {
			JS_ReportError(cx, "invalid arguments.");
			return JS_FALSE;
		}
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		
		p->DrawPoint(*(apPoint.get()));
	}

	// APIの実行と戻り値の設定

	return JS_TRUE;
}

JSBool DC::drawPolygon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawPolygon (
		const wxPointList *points, 
		wxCoord xoffset=0, 
		wxCoord yoffset=0, 
		wxPolygonFillMode fill_style=wxODDEVEN_RULE)

 	This method draws a filled polygon using a list of wxPoints, adding the optional offset coordinate. 
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord xoffset=0;
	wxCoord yoffset=0;
	wxPolygonFillMode fill_style=wxODDEVEN_RULE;

	if( argc >= 4 ) {
		argc = 4;
	}

	// 0
	if( argv[argIndex].isObjectOrNull() == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
    JSObject *objItems = JSVAL_TO_OBJECT(argv[argIndex]);
	if( objItems == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	if( JS_IsArrayObject(cx, objItems) == JS_FALSE ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}

	wxPoint* pTo = NULL;
	uint32_t length = 0;
	JS_GetArrayLength(cx, objItems, &length);

	pTo = new wxPoint[length];
	for(uint32_t i =0; i < length; i++)
	{
		JS::Value element;
		JS_GetElement(cx, objItems, i, &element);


		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		if( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, element ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "x attribute in Array item must be Number");
			return false;
		}

		pTo[i] = *(apPoint.get());
	}




	argIndex = argc -1;
	switch( argc ) {
	case 4:
		{	int ifill_style = 0;
			if ( ! FromJS(cx, argv[argIndex], ifill_style) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			fill_style = (wxPolygonFillMode)ifill_style;
		}
		argIndex--;
	case 3:
		if ( ! FromJS(cx, argv[argIndex], yoffset) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 2:
		if ( ! FromJS(cx, argv[argIndex], xoffset) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}

	// APIの実行と戻り値の設定
	p->DrawPolygon(length, pTo, xoffset, yoffset, fill_style);
	delete []pTo;

	return JS_TRUE;
}


JSBool DC::drawPolyPolygon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawPolyPolygon (
		int n, 
		const int count[], 
		const wxPoint points[], 
		wxCoord xoffset=0, 
		wxCoord yoffset=0, 
		wxPolygonFillMode fill_style=wxODDEVEN_RULE)

	*/



	// 引数の取得
	int argIndex = 0;
	uint32_t lengthCount = 0;
	uint32_t lengthPoint = 0;
	wxCoord xoffset=0;
	wxCoord yoffset=0;
	wxPolygonFillMode fill_style=wxODDEVEN_RULE;
	std::vector<wxPoint>	cntPolyD;
	std::vector<int>		cntCount;



	if( argc >= 5 ) {
		argc = 5;
	}
	// 0
	/*
		第一
		[number, number, ...]
	*/
	if( argv[argIndex].isObjectOrNull() == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
    JSObject *objCount = JSVAL_TO_OBJECT(argv[argIndex]);
	if( objCount == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	if( JS_IsArrayObject(cx, objCount) == JS_FALSE ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	JS_GetArrayLength(cx, objCount, &lengthCount);
	for(uint32_t i =0; i < lengthCount; i++)
	{
		jsval element;
		JS_GetElement(cx, objCount, i, &element);
		if( element.isNumber() == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array item must be Number Array");
			return JS_FALSE;
		}
		cntCount.push_back( element.toInt32() );
	}
	if( cntCount.size() < 2 ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "argumets error.");
		return JS_FALSE;
	}
	argIndex++;

	// 1
	/*
		第二
		new Array(
			{x:2, y:3}, {x:2, y:3}
		);
	*/
	if( argv[argIndex].isObjectOrNull() == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
    JSObject *objItems = JSVAL_TO_OBJECT(argv[argIndex]);
	if( objItems == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	if( JS_IsArrayObject(cx, objItems) == JS_FALSE ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	JS_GetArrayLength(cx, objItems, &lengthPoint);
	for(uint32_t i =0; i < lengthPoint; i++)
	{
		// {count:1, x:2, y:3}
		jsval element;
		JS_GetElement(cx, objItems, i, &element);

		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		if( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, element ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "x attribute in Array item must be Number");
			return false;
		}
		cntPolyD.push_back( *(apPoint.get()) );
	}
	if( cntPolyD.size() < 2 ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "argumets error.");
		return JS_FALSE;

	}



	argIndex = argc -1;
	switch( argc ) {
	case 5:
		{	int ifill_style = 0;
			if ( ! FromJS(cx, argv[argIndex], ifill_style) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			fill_style = (wxPolygonFillMode)ifill_style;
		}
		argIndex--;
	case 4:
		if ( ! FromJS(cx, argv[argIndex], yoffset) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 3:
		if ( ! FromJS(cx, argv[argIndex], xoffset) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}

	// APIの実行と戻り値の設定
	int*     pCount  = new int[cntCount.size()];
	wxPoint* pPoint = new wxPoint[cntPolyD.size()];

	for(size_t ii = 0; ii < cntCount.size(); ii++ ) {
		pCount[ii] = cntCount[ii];
	}
	for(size_t ii = 0; ii < cntPolyD.size(); ii++ ) {
		pPoint[ii] = cntPolyD[ii];
	}
	p->DrawPolyPolygon(cntCount.size(), pCount, pPoint, xoffset, yoffset, fill_style);

	delete []pCount;
	delete []pPoint;

	return JS_TRUE;
}

JSBool DC::drawRectangle(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawRectangle (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 		Draws a rectangle with the given top left corner, and with the given size. More...
 
	void 	DrawRectangle (const wxPoint &pt, const wxSize &sz)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
 
	void 	DrawRectangle (const wxRect &rect)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxRect* pRect = NULL;
	zzzJsPtr<wxRect> apRect;
	

	// 0
	if( argv[argIndex].isNumber() == true ) {
		if( argc < 4 ) {
			JS_ReportError(cx, "Arguments error.");
			return JS_FALSE;
		}
		wxCoord x,  y,  width,  height;

		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], height) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		
		p->DrawRectangle(x,  y,  width,  height);

	} else 
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == true ) {
		// void 	DrawRectangle (const wxRect &rect)
		p->DrawRectangle( *(apRect.get()) );

	} else {
		// void 	DrawRectangle (const wxPoint &pt, const wxSize &sz)
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		
		if( argc < 2 ) {
			JS_ReportError(cx, "Arguments error.");
			return JS_FALSE;
		}	
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex++;

		
		p->DrawRectangle(*(apPoint.get()), *(apSize.get()));
	}

	// APIの実行と戻り値の設定

	return JS_TRUE;
}

JSBool DC::drawRotatedText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawRotatedText (
		const wxString &text, 
		wxCoord x, 
		wxCoord y, 
		double angle)

 		Draws the text rotated by angle degrees (positive angles are counterclockwise; the full angle is 360 degrees). More...
 
	void 	DrawRotatedText (
		const wxString &text, 
		const wxPoint &point, 
		double angle)

 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxString text;
	
	
	// 0
	if ( ! FromJS(cx, argv[argIndex], text) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;

	// 1
	if( argv[argIndex].isNumber() == true ) {
		if( argc < 4 ) {
			JS_ReportError(cx, "Arguments error.");
			return JS_FALSE;
		}
		wxCoord x,  y;
		double angle = 0;

		// 1
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], angle) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex++;
		
		p->DrawRotatedText(text, x,  y, angle);
	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		double angle = 0;
		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;


		// 2
		if ( ! FromJS(cx, argv[argIndex], angle) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}

		p->DrawRotatedText(text, *(apPoint.get()), angle);
	}
	// APIの実行と戻り値の設定

	return JS_TRUE;
}

JSBool DC::drawRoundedRectangle(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawRoundedRectangle (wxCoord x, wxCoord y, wxCoord width, wxCoord height, double radius)
 		Draws a rectangle with the given top left corner, and with the given size. More...
 
	void 	DrawRoundedRectangle (const wxPoint &pt, const wxSize &sz, double radius)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;


	// 1
	if( argv[argIndex].isNumber() == true ) {
		if( argc < 5 ) {
			JS_ReportError(cx, "Arguments error.");
			return JS_FALSE;
		}
		wxCoord x,  y,  width,  height;
		double radius = 0;

		// 0
		if ( ! FromJS(cx, argv[argIndex], x) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if ( ! FromJS(cx, argv[argIndex], y) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if ( ! FromJS(cx, argv[argIndex], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if ( ! FromJS(cx, argv[argIndex], height) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 4
		if ( ! FromJS(cx, argv[argIndex], radius) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex++;
		
		p->DrawRoundedRectangle (x,  y,  width,  height, radius);
	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		double radius = 0;
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;

		// 1
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex++;

		// 2
		if ( ! FromJS(cx, argv[argIndex], radius) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		
		p->DrawRoundedRectangle(*(apPoint.get()), *(apSize.get()), radius);
	}
	// APIの実行と戻り値の設定

	return JS_TRUE;
}



JSBool DC::drawSpline(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawSpline (const wxPointList *points)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	std::vector<wxPoint> cntPts;

	// 0
	if( argv[argIndex].isObjectOrNull() == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
    JSObject *objItems = JSVAL_TO_OBJECT(argv[argIndex]);
	if( objItems == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	if( JS_IsArrayObject(cx, objItems) == JS_FALSE ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array");
		return JS_FALSE;
	}
	wxPointList to;
	uint32_t length = 0;
	JS_GetArrayLength(cx, objItems, &length);
	wxPoint* pPoints = new wxPoint[length];
	for(uint32_t i =0; i < length; i++)
	{
		JS::Value element;
		JS_GetElement(cx, objItems, i, &element);

		if( element.isObjectOrNull() == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array item must be Object");
			return JS_FALSE;
		}
		JSObject *objItem = JSVAL_TO_OBJECT(element);
		if( objItem == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array item must be Object");
			return JS_FALSE;
		}

		int x, y;
		jsval v;		
		// x
		if( GetPropertyWhenPresent(cx, objItem, _T("x"), &v) == JS_FALSE) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array item must be Object");
			return false;
		}
		if( FromJS(cx, v, x ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "x attribute in Array item must be Number");
			return false;
		}
		
		// y
		if( GetPropertyWhenPresent(cx, objItem, _T("y"), &v) == JS_FALSE) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Array item must be Object");
			return false;
		}
		if( FromJS(cx, v, y ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "y attribute in Array item must be Number");
			return false;
		}
		pPoints[i].x = x;
		pPoints[i].y = y;
//		cntPts.push_back( wxPoint(x,y) );
//		wxPoint& pt = cntPts[cntPts.size()-1];
//		to.push_back( &pt );
		to.push_back( &pPoints[i] );
	}



	// APIの実行と戻り値の設定
	p->DrawSpline(&to);
	if( pPoints != NULL ) {
		delete []pPoints;
	}
	return JS_TRUE;
}



JSBool DC::drawText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DrawText (const wxString &text, wxCoord x, wxCoord y)
 		Draws a text string at the specified point, using the current text font, and the current text foreground and background colours. More...
 
	void 	DrawText (const wxString &text, const wxPoint &pt)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxString		text;
	
	if( argc > 3 ) {
		argc = 3;
	}
	// 0
	if( FromJS(cx, argv[argIndex], text ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;

	
	// 1
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x, y;

		if( argc < 3 ) {
			JS_ReportError(cx, "arguments error.");
			return JS_FALSE;
		}
		// 1		
		if( FromJS(cx, argv[argIndex], x ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if( FromJS(cx, argv[argIndex], y ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;

		p->DrawText(text, x, y);
	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		// 1		
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;

		
		p->DrawText(text, *(apPoint.get()));
	}

	// APIの実行と戻り値の設定

	return JS_TRUE;
}



JSBool DC::gradientFillConcentric(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	GradientFillConcentric (
			const wxRect &rect, 
			const wxColour &initialColour, 
			const wxColour &destColour)
 		Fill the area specified by rect with a radial gradient, starting from initialColour at the centre of the circle and fading to destColour on the circle outside. More...
 
	void 	GradientFillConcentric (
			const wxRect &rect, 
			const wxColour &initialColour, 
			const wxColour &destColour, 
			const wxPoint &circleCenter)
 		Fill the area specified by rect with a radial gradient, starting from initialColour at the centre of the circle and fading to destColour on the circle outside. 
	*/

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	//wxColour*	pinitialColour = NULL;
	//wxColour*	pdestColour = NULL;
	zzzJsPtr<wxColour> apInitialColour;
	zzzJsPtr<wxColour> apDestColour;

	if( argc > 4 ) {
		argc = 4;
	}
	// 0
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == false )
//	if( FromJS(cx, argv[argIndex], rc ) == false )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName());
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( ZZZJS_ARG_GET_AP(apInitialColour, Colour) == false  ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Color");
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( ZZZJS_ARG_GET_AP(apDestColour, Colour) == false  ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Color");
		return JS_FALSE;
	}
	argIndex++;
	if( argc == 4 ) {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		// 4
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;

		p->GradientFillConcentric(*(apRect.get()), *(apInitialColour.get()), *(apDestColour.get()), *(apPoint.get()));
	} else {
		p->GradientFillConcentric(*(apRect.get()), *(apInitialColour.get()), *(apDestColour.get()));
	}
	
	// APIの実行と戻り値の設定

	return JS_TRUE;
}



JSBool DC::gradientFillLinear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	GradientFillLinear (
		const wxRect &rect, 
		const wxColour &initialColour, 
		const wxColour &destColour, 
		wxDirection nDirection=wxRIGHT)
 		Fill the area specified by rect with a linear gradient, starting from initialColour and eventually fading to destColour.
	*/

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;
	zzzJsPtr<wxColour> apInitialColour;
	zzzJsPtr<wxColour> apDestColour;
	wxDirection nDirection=wxRIGHT;

	if( argc > 4 ) {
		argc = 4;
	}
	// 0
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == false )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Rect::getClassName() );
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( ZZZJS_ARG_GET_AP(apInitialColour, Colour ) == false )  {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Color");
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( ZZZJS_ARG_GET_AP(apDestColour, Colour ) == false )  {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Color");
		return JS_FALSE;
	}
	argIndex++;
	if( argc == 4 ) {
		int inDirection;
		// 4
		if( FromJS(cx, argv[argIndex], inDirection ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		nDirection = (wxDirection)inDirection;
	}
	
	// APIの実行と戻り値の設定
	p->GradientFillLinear(*(apRect.get()), *(apInitialColour.get()), *(apDestColour.get()), nDirection);
	return JS_TRUE;
}



JSBool DC::floodFill(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	FloodFill (
		wxCoord x, 
		wxCoord y, 
		const wxColour &colour, 
		wxFloodFillStyle style=wxFLOOD_SURFACE)
 	Flood fills the device context starting from the given point, using the current brush colour, and using a style: More...
 
	bool 	FloodFill (
		const wxPoint &pt, 
		const wxColour &col, 
		wxFloodFillStyle style=wxFLOOD_SURFACE)
 	This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord x;
	wxCoord y; 
	zzzJsPtr<wxColour> apColour;
	wxFloodFillStyle style=wxFLOOD_SURFACE;

	if( argc > 4 ) {
		argc = 4;
	}
	// 0
	if( argv[argIndex].isNumber() == true ) {
		if( argc < 3 ) {
			JS_ReportError(cx, "arguments error.");
			return JS_FALSE;
		}
		// 0
		if( FromJS(cx, argv[argIndex], x ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if( FromJS(cx, argv[argIndex], y ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;


		// 2
		if( ZZZJS_ARG_GET_AP(apColour, Colour) == false  ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Colour::getClassName());
			return JS_FALSE;
		}
		argIndex++;
		if( argc == 4 ) {
			int inDirection;
			// 4
			if( FromJS(cx, argv[argIndex], inDirection ) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex++;
			style = (wxFloodFillStyle)inDirection;
		}

	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);

		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		x = apPoint->x;
		y = apPoint->y;


		// 1
		if( ZZZJS_ARG_GET_AP(apColour, Colour) == false  ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Colour::getClassName());
			return JS_FALSE;
		}
		argIndex++;
		if( argc == 3 ) {
			int inDirection;
			// 2
			if( FromJS(cx, argv[argIndex], inDirection ) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex++;
			style = (wxFloodFillStyle)inDirection;
		}

	}
	
	// APIの実行と戻り値の設定
	p->FloodFill(x, y, *(apColour.get()), style);
	return JS_TRUE;
}



JSBool DC::crossHair(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	CrossHair (wxCoord x, wxCoord y)
 		Displays a cross hair using the current pen. More...
 
	void 	CrossHair (const wxPoint &pt)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord x;
	wxCoord y; 

	if( argc > 2 ) {
		argc = 2;
	}
	// 0
	if( argv[argIndex].isNumber() == true ) {
		if( argc < 2 ) {
			JS_ReportError(cx, "arguments error.");
			return JS_FALSE;
		}
		// 0
		if( FromJS(cx, argv[argIndex], x ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if( FromJS(cx, argv[argIndex], y ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;


	} else {
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);

		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		x = apPoint->x;
		y = apPoint->y;


	}
	
	// APIの実行と戻り値の設定
	p->CrossHair(x, y);
	return JS_TRUE;
}



JSBool DC::destroyClippingRegion(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	DestroyClippingRegion ()
 		Destroys the current clipping region so that none of the DC is clipped.
	*/



	
	// APIの実行と戻り値の設定
	p->DestroyClippingRegion();
	return JS_TRUE;
}



JSBool DC::setClippingRegion(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	SetClippingRegion (wxCoord x, wxCoord y, wxCoord width, wxCoord height)
 		Sets the clipping region for this device context to the intersection of the given region described by the parameters of this method and the previously set clipping region. More...
 
	void 	SetClippingRegion (const wxPoint &pt, const wxSize &sz)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
 
	void 	SetClippingRegion (const wxRect &rect)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts.
	*/

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxRect> apRect;

	if( argc > 4 ) {
		argc = 4;
	}
	// 0
	if( argv[argIndex].isNumber() == true ) {
		wxCoord x;
		wxCoord y; 
		wxCoord width; 
		wxCoord height; 

		if( argc < 4 ) {
			JS_ReportError(cx, "arguments error.");
			return JS_FALSE;
		}
		// 0
		if( FromJS(cx, argv[argIndex], x ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 1
		if( FromJS(cx, argv[argIndex], y ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 2
		if( FromJS(cx, argv[argIndex], width ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;
		// 3
		if( FromJS(cx, argv[argIndex], height ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex++;

		p->SetClippingRegion (x, y, width, height);
	} else 	
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[argIndex])) == true )
	{
		// void 	SetClippingRegion (const wxRect &rect)
		p->SetClippingRegion (  *(apRect.get())  );
	} else {
		// void 	SetClippingRegion (const wxPoint &pt, const wxSize &sz)
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		if( argc < 2 ) {
			JS_ReportError(cx, "arguments error.");
			return JS_FALSE;
		}
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex++;
		// 0
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex++;


		p->SetClippingRegion(*(apPoint.get()), *(apSize.get()));
	}
	
	// APIの実行と戻り値の設定

	return JS_TRUE;
}




JSBool DC::setDeviceClippingRegion(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*

		void wxDC::SetDeviceClippingRegion	(	const wxRegion & 	region	)	

	*/
	// 引数の取得
	int argIndex = 0;
	bool bAllocation = false;
	zzzJsPtr<wxRegion>	apRexion;


	apRexion = Region::getObject2Instance(cx, argv[argIndex],  apRexion.bAllocation);
	if( apRexion.get() == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Region");
		return JS_FALSE;
	}

		
	// APIの実行と戻り値の設定
	p->SetDeviceClippingRegion( *(apRexion.get()) );

	return JS_TRUE;
}


JSBool DC::getMultiLineTextExtent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	GetMultiLineTextExtent (const wxString &string, wxCoord *w, wxCoord *h, wxCoord *heightLine=NULL, const wxFont *font=NULL) const
 		Gets the dimensions of the string using the currently selected font.
	*/

	// 引数の取得
	int argIndex = 0;
	wxString str;
	zzzJsPtr<wxFont> apFont;
	wxCoord w, h, heightLine;

	if( argc > 2 ) {
		argc = 2;
	}
	// 0
	if( FromJS(cx, argv[argIndex], str ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	if( argc == 2 ) {
		ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
		argIndex++;
	}
	
	// APIの実行と戻り値の設定
	p->GetMultiLineTextExtent(str, &w, &h, &heightLine, (apFont.get()));


	JSObject *objAttr = JS_NewObject(cx, NULL/*Attr::GetClass()*/, NULL, NULL);
	JS::RootedObject jsvaAttr(cx, objAttr);
	{
		wxString strName(_T("w"));
		jsval attrValue = ToJS(cx, w );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T("h"));
		jsval attrValue = ToJS(cx, h );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T("heightLine"));
		jsval attrValue = ToJS(cx, heightLine );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	vp->setObjectOrNull(objAttr);

	return JS_TRUE;
}



JSBool DC::getPartialTextExtents(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	GetPartialTextExtents (const wxString &text, wxArrayInt &widths) const
 	Fills the widths array with the widths from the beginning of text to the corresponding character of text. 
	*/

	// 引数の取得
	int argIndex = 0;
	wxString str;
	wxArrayInt widths;

	if( argc > 2 ) {
		argc = 2;
	}
	// 0
	if( FromJS(cx, argv[argIndex], str ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	p->GetPartialTextExtents(str, widths);

	*vp = ToJS(cx, widths);

	return JS_TRUE;
}



JSBool DC::getTextExtent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	GetTextExtent (
			const wxString &string, 
			wxCoord *w, 
			wxCoord *h, 
			wxCoord *descent=NULL, 
			wxCoord *externalLeading=NULL, 
			const wxFont *font=NULL) const
 		Gets the dimensions of the string using the currently selected font. 
	*/

	// 引数の取得
	int argIndex = 0;
	wxString str;
	zzzJsPtr<wxFont> apFont;
	wxCoord w, h, descent, externalLeading;

	if( argc > 2 ) {
		argc = 2;
	}
	// 0
	if( FromJS(cx, argv[argIndex], str ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	if( argc == 2 ) {
		ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
		argIndex++;
	}
	
	// APIの実行と戻り値の設定
	p->GetTextExtent(str, &w, &h, &descent, &externalLeading, apFont.get());


	JSObject *objAttr = JS_NewObject(cx, NULL/*Attr::GetClass()*/, NULL, NULL);
	JS::RootedObject jsvaAttr(cx, objAttr);
	{
		wxString strName(_T("w"));
		jsval attrValue = ToJS(cx, w );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T("h"));
		jsval attrValue = ToJS(cx, h );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T("descent"));
		jsval attrValue = ToJS(cx, descent );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	{
		wxString strName(_T("externalLeading"));
		jsval attrValue = ToJS(cx, externalLeading );
		JS_SetUCProperty(cx, 
			objAttr, 
			(const jschar *) strName.c_str(), 
			strName.Length(), &attrValue);
	}
	vp->setObjectOrNull(objAttr);

	return JS_TRUE;
}



JSBool DC::calcBoundingBox(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	CalcBoundingBox (wxCoord x, wxCoord y)
 		Adds the specified point to the bounding box which can be retrieved with MinX(), MaxX() and MinY(), MaxY() functions.
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord x, y;

	if( argc > 2 ) {
		argc = 2;
	}
	// 0
	if( FromJS(cx, argv[argIndex], x ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// y
	if( FromJS(cx, argv[argIndex], y ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->CalcBoundingBox(x, y);


	return JS_TRUE;
}



JSBool DC::resetBoundingBox(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	ResetBoundingBox ()
 		Resets the bounding box: after a call to this function, the bounding box doesn't contain anything.
	*/

	// APIの実行と戻り値の設定
	p->ResetBoundingBox();


	return JS_TRUE;
}



JSBool DC::startDoc(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	StartDoc (const wxString &message)
 		Starts a document (only relevant when outputting to a printer). 
	*/

	// 引数の取得
	int argIndex = 0;
	wxString message;

	
	// 0
	if( FromJS(cx, argv[argIndex], message ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	vp->setBoolean( p->StartDoc(message) );

	return JS_TRUE;
}



JSBool DC::startPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	StartPage ()
 		Starts a document page (only relevant when outputting to a printer).
	*/
	// APIの実行と戻り値の設定
	p->StartPage();

	return JS_TRUE;
}



JSBool DC::endDoc(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	EndDoc ()
 		Ends a document (only relevant when outputting to a printer).
	*/
	// APIの実行と戻り値の設定
	p->EndDoc ();

	return JS_TRUE;
}



JSBool DC::endPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	EndPage ()
 		Ends a document page (only relevant when outputting to a printer).
	*/
	// APIの実行と戻り値の設定
	p->EndPage ();

	return JS_TRUE;
}



JSBool DC::blit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	Blit (
			wxCoord xdest, 
			wxCoord ydest, 
			wxCoord width, 
			wxCoord height, 
			wxDC *source, 
			wxCoord xsrc, 
			wxCoord ysrc, 
			wxRasterOperationMode logicalFunc=wxCOPY, 
			bool useMask=false, 
			wxCoord xsrcMask=wxDefaultCoord, 
			wxCoord ysrcMask=wxDefaultCoord
		)
 		Copy from a source DC to this DC. 
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord xdest; 
	wxCoord ydest; 
	wxCoord width; 
	wxCoord height; 
	wxDC *source; 
	wxCoord xsrc; 
	wxCoord ysrc; 
	wxRasterOperationMode logicalFunc=wxCOPY; 
	bool useMask=false; 
	wxCoord xsrcMask=wxDefaultCoord; 
	wxCoord ysrcMask=wxDefaultCoord;

	
	if( argc > 11 ) {
		argc = 11;
	}
	argIndex = argc - 1;
	// オプションのパラメータを先に取得
	switch( argc ) {
	case 11:
		// 10
		if( FromJS(cx, argv[argIndex], ysrcMask ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 10:
		// 9
		if( FromJS(cx, argv[argIndex], xsrcMask ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 9:
		// 8
		if( FromJS(cx, argv[argIndex], useMask ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	case 8:
		// 7
		{
			int ilogicalFunc = 0;
			if( FromJS(cx, argv[argIndex], ilogicalFunc ) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			logicalFunc = (wxRasterOperationMode)ilogicalFunc;
		}
		argIndex--;
	}
	/*
	wxCoord xdest; 
	wxCoord ydest; 
	wxCoord width; 
	wxCoord height; 
	wxDC *source; 
	wxCoord xsrc; 
	wxCoord ysrc; 
	*/
	argIndex = 0;
	// 0
	if( FromJS(cx, argv[argIndex], xdest ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( FromJS(cx, argv[argIndex], ydest ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( FromJS(cx, argv[argIndex], width ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 3
	if( FromJS(cx, argv[argIndex], height ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 4
	source = DC::GetPrivate(cx, argv[argIndex], false);
	if( source == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
		return JS_FALSE;
	}
	argIndex++;
	// 5
	if( FromJS(cx, argv[argIndex], xsrc ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 6
	if( FromJS(cx, argv[argIndex], ysrc ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	vp->setBoolean( 
		p->Blit( 
			xdest, 
			ydest, 
			width, 
			height, 
			source, 
			xsrc, 
			ysrc, 
			logicalFunc,
			useMask,
			xsrcMask,
			ysrcMask
		)
	);
	return JS_TRUE;
}




JSBool DC::stretchBlit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	StretchBlit (
			wxCoord xdest, 
			wxCoord ydest, 
			wxCoord dstWidth, 
			wxCoord dstHeight, 
			wxDC *source, 
			wxCoord xsrc, 
			wxCoord ysrc, 
			wxCoord srcWidth, 
			wxCoord srcHeight, 
			wxRasterOperationMode logicalFunc=wxCOPY, 
			bool useMask=false, 
			wxCoord xsrcMask=wxDefaultCoord, 
			wxCoord ysrcMask=wxDefaultCoord)
 		Copy from a source DC to this DC possibly changing the scale. 
	*/

	// 引数の取得
	int argIndex = 0;
	wxCoord xdest; 
	wxCoord ydest; 
	wxCoord width; 
	wxCoord height; 
	wxDC *source; 
	wxCoord xsrc; 
	wxCoord ysrc; 
	wxCoord srcWidth;  
	wxCoord srcHeight; 
	wxRasterOperationMode logicalFunc=wxCOPY; 
	bool useMask=false; 
	wxCoord xsrcMask=wxDefaultCoord; 
	wxCoord ysrcMask=wxDefaultCoord;

	
	if( argc > 13 ) {
		argc = 13;
	}
	argIndex = argc - 1;
	// オプションのパラメータを先に取得
	switch( argc ) {
	case 13:
		// 12
		if( FromJS(cx, argv[argIndex], ysrcMask ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 12:
		// 11
		if( FromJS(cx, argv[argIndex], xsrcMask ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 11:
		// 10
		if( FromJS(cx, argv[argIndex], useMask ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	case 10:
		// 9
		{
			int ilogicalFunc = 0;
			if( FromJS(cx, argv[argIndex], ilogicalFunc ) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			logicalFunc = (wxRasterOperationMode)ilogicalFunc;
		}
		argIndex--;
	}
	/*
	wxCoord xdest; 
	wxCoord ydest; 
	wxCoord width; 
	wxCoord height; 
	wxDC *source; 
	wxCoord xsrc; 
	wxCoord ysrc; 
	wxCoord srcWidth;  
	wxCoord srcHeight; 
	*/
	argIndex = 0;
	// 0
	if( FromJS(cx, argv[argIndex], xdest ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( FromJS(cx, argv[argIndex], ydest ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( FromJS(cx, argv[argIndex], width ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 3
	if( FromJS(cx, argv[argIndex], height ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 4
	source = DC::GetPrivate(cx, argv[argIndex], false);
	if( source == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
		return JS_FALSE;
	}
	argIndex++;
	// 5
	if( FromJS(cx, argv[argIndex], xsrc ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 6
	if( FromJS(cx, argv[argIndex], ysrc ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 7
	if( FromJS(cx, argv[argIndex], srcWidth ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 8
	if( FromJS(cx, argv[argIndex], srcHeight ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	vp->setBoolean( 
		p->StretchBlit( 
			xdest, 
			ydest, 
			width, 
			height, 
			source, 
			xsrc, 
			ysrc, 
			srcWidth,
			srcHeight,
			logicalFunc,
			useMask,
			xsrcMask,
			ysrcMask
		)
	);
	return JS_TRUE;
}




JSBool DC::getPen(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	const wxPen& pen = p->GetPen();
	*vp = Pen::CreateObject(cx, new wxPen(pen), NULL);
	return JS_TRUE;
}




JSBool DC::setPen(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	int argIndex = 0;
	wxPen workPen;
	zzzJsPtr<wxPen> apPen;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apPen, Pen);

	// APIの実行と戻り値の設定
	p->SetPen( *(apPen.get()) );

	return JS_TRUE;
}




JSBool DC::getBrush(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	const wxBrush& brush = p->GetBrush();
	*vp = Brush::CreateObject(cx, new wxBrush(brush), NULL);
	return JS_TRUE;
}




JSBool DC::setBrush(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	int argIndex = 0;
	wxBrush workBrush;
	zzzJsPtr<wxBrush>  apBrush;

	if( apBrush.set(Brush::getObject2Instance(cx, argv[0], apBrush.bAllocation)) == false) 
	{
//	wxBrush* pBrush = Brush::getConv(cx, argv[argIndex], workBrush);
//	if( pBrush == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Brush");
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->SetBrush( *(apBrush.get()) );

	return JS_TRUE;
}




JSBool DC::canUseTransformMatrix(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	CanUseTransformMatrix () const
 		Check if the use of transformation matrix is supported by the current system.
	*/

	
	// APIの実行と戻り値の設定
	vp->setBoolean( 
		p->CanUseTransformMatrix()
	);
	return JS_TRUE;
}




JSBool DC::resetTransformMatrix(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	void 	ResetTransformMatrix ()
 		Revert the transformation matrix to identity matrix.
	*/

	
	// APIの実行と戻り値の設定
	p->ResetTransformMatrix();
	return JS_TRUE;
}




JSBool DC::canDrawBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	CanDrawBitmap () const
 		Does the DC support drawing bitmaps?
	*/

	
	// APIの実行と戻り値の設定
	vp->setBoolean( 
		p->CanDrawBitmap()
	);
	return JS_TRUE;
}




JSBool DC::canGetTextExtent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDC *p = GetPrivate(cx, obj);
    if ( p == NULL ) {
		JS_ReportError(cx, WXJS_ALREADY_RELEASE);
        return JS_FALSE;
	}
	
	/*
	bool 	CanGetTextExtent () const
 		Does the DC support calculating the size required to draw text?
	*/

	
	// APIの実行と戻り値の設定
	vp->setBoolean( 
		p->CanGetTextExtent()
	);
	return JS_TRUE;
}





