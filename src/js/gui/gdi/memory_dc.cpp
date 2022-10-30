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
#include "js/gui/gdi/memory_dc.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::gdi;

WXJS_INIT_CLASS(MemoryDC, "MemoryDC", 0)

/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(MemoryDC)
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxMemoryDC, MemoryDC)
{

	return true;
}
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxMemoryDC, MemoryDC)
{
	return true;
}
WXJS_END_SET_PROP
	


WXJS_BEGIN_GET_SET_STR_PROP(wxMemoryDC, MemoryDC)
	DC::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
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
 *   Constructs a new wxMemoryDC object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxMemoryDC, MemoryDC)
{
	
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if( argc == 0 ) {
		return new wxMemoryDC();
	}
	
	zzzJsPtr<wxBitmap> apBitmap;
	wxDC* pDc = DC::GetPrivate(cx, argv[0], false);
	if( pDc != NULL ) {
		return new wxMemoryDC(pDc);
	}

	if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[0], apBitmap.bAllocation)) == true ) {
		return new wxMemoryDC(*(apBitmap.get()));
	}
	JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "DC or Bitmp");
	return NULL;
}
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxMemoryDC, MemoryDC)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(MemoryDC)
	WXJS_METHOD("selectObject", selectObject, 1)
	WXJS_METHOD("selectObjectAsSource", selectObjectAsSource, 1)
WXJS_END_METHOD_MAP()



JSBool MemoryDC::selectObject(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxMemoryDC *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;

	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SelectObject( *(apBitmap.get()) );

	return JS_TRUE;
}



JSBool MemoryDC::selectObjectAsSource(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxMemoryDC *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;

	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	p->SelectObjectAsSource( *(apBitmap.get()) );

	return JS_TRUE;
}