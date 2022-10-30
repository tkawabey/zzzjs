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

#include "js/gui/misc/size.h"
#include "js/gui/gdi/metafile.h"
#include "js/gui/gdi/dc.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::gdi;

WXJS_INIT_CLASS(Metafile, "Metafile", 0)

/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Metafile)
  WXJS_READONLY_PROPERTY(P_ISOK, "isOk")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxMetafile, Metafile)
{
	switch (id) 
	{
	case P_ISOK:
		vp.set( ToJS(cx, p->IsOk()) );
		break;
	}
	return true;
}
WXJS_END_GET_PROP


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
 *   Constructs a new wxMetafile object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxMetafile, Metafile)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxString filename = wxEmptyString;

	if( argc >= 1 ) {

		if( FromJS(cx, argv[0], filename) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return NULL;
		}
	}

	return new wxMetafile(filename);
}
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_METHOD_MAP(Metafile)
	WXJS_METHOD("play", play, 1)
	WXJS_METHOD("setClipboard", setClipboard, 0)
WXJS_END_METHOD_MAP()


JSBool Metafile::play(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxMetafile *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	wxDC *pSrc=NULL;

	pSrc = DC::GetPrivate(cx, argv[argIndex], false);
	if( pSrc == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	vp->setBoolean(  p->Play( pSrc ) );

	return JS_TRUE;
}

JSBool Metafile::setClipboard(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxMetafile *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int width=0, height=0;

	if( argc > 2 ) {
		argc = 2;
	}

	argIndex = argc -1;
	switch( argc ) {
	case 2:
		if ( ! FromJS(cx, argv[argIndex], height) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 1:
		if ( ! FromJS(cx, argv[argIndex], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}
	

	// APIの実行と戻り値の設定
	vp->setBoolean(  p->SetClipboard( width, height ) );



	return JS_TRUE;
}


