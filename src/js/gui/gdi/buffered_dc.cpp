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
#include "js/gui/gdi/buffered_dc.h"
#include "js/gui/gdi/memory_dc.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::gdi;

WXJS_INIT_CLASS(BufferedDC, "BufferedDC", 0)

/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(BufferedDC)
  WXJS_PROPERTY(P_STYLE, "style")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxBufferedDC, BufferedDC)
{	
	switch (id) 
	{
	case P_STYLE:
		vp.set( ToJS(cx, p->GetStyle()) );
		break;
	}
	return true;
}
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxBufferedDC, BufferedDC)
{
	switch (id) 
	{
	case P_STYLE:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetStyle(iVal);
			}
		}
		break;
	}
	return true;
}
WXJS_END_SET_PROP
	


WXJS_BEGIN_GET_SET_STR_PROP(wxBufferedDC, BufferedDC)
	MemoryDC::SetStringProperty(p, cx,  obj, propertyName, vp);
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
 *   Constructs a new wxBufferedDC object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxBufferedDC, BufferedDC)
{
	
	wxBufferedDC *p = new wxBufferedDC();
	
    SetPrivate(cx, obj, p);
	if( argc == 0 ) {
		return p;
	}
	
    if ( argc > 0 )
    {
        if ( ! init(cx, argc, vp) )
        {
			return NULL;
        }
    }
	return p;
}
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxBufferedDC, BufferedDC)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(BufferedDC)
	WXJS_METHOD("unMask", unMask, 0)
	WXJS_METHOD("init", init, 1)
WXJS_END_METHOD_MAP()



JSBool BufferedDC::unMask(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxBufferedDC *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	p->UnMask();

	return JS_TRUE;
}



JSBool BufferedDC::init(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxBufferedDC *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// à¯êîÇÃéÊìæ

	int argIndex = 0;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);


	// 0
	wxDC* pDc = DC::GetPrivate(cx, argv[0], false);
	if( pDc == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
		return NULL;
	}
	argIndex++;

	// 1
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true )
	{
		// wxBufferedDC (wxDC *dc, const wxSize &area, int style=wxBUFFER_CLIENT_AREA)

		int style=wxBUFFER_CLIENT_AREA;

		argIndex++;

		if( argc > 3 ) {
			argc = 3;
		}
		if( argc < 2 ) {
			JS_ReportError(cx, "invalid arguments.");
			return NULL;
		}
		if( argc == 2 ) {
			ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		}

		p->Init(pDc, *(apSize.get()), style);
	} else {
		// wxBufferedDC (wxDC *dc, wxBitmap &buffer=wxNullBitmap, int style=wxBUFFER_CLIENT_AREA)
		zzzJsPtr<wxBitmap> apBitmap;
		int style=wxBUFFER_CLIENT_AREA;

		if( argc > 3 ) {
			argc = 3;
		}
		argIndex = argc - 1;
		switch( argc ) {
		case 3:
			if( FromJS(cx, argv[argIndex], style) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return NULL;
			}
			argIndex--;
		case 2:
			{
				if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
					return NULL;
				}
			}
			argIndex--;
		}

		p->Init(pDc, apBitmap.get() != NULL ? *(apBitmap.get()) : wxNullBitmap, style);
	}

	return JS_TRUE;
}