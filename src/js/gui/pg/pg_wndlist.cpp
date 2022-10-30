/*
 * wxJavaScript - pg_prop_array_string.cpp
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
#include "js/gui/errors.h"
#include "js/gui/pg/pg_wndlist.h"
#include "js/gui/control/window.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	WindowList
//--------------------------------------------------------
WXJS_INIT_CLASS(WindowList, "WindowList", 0)
	

//WXJS_BEGIN_DESTRUCTOR(wxPGWindowList, WindowList)
//
//WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxPGWindowList, WindowList)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow*   primary = NULL;
    wxWindow*   secondary = NULL;

	if( argc > 2 ) {
		argc = 2;
	}

	switch( argc ) {
	case 2:
		secondary = Window::GetPrivate(cx, argv[1], false);
		if( secondary == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Window");
			return JS_FALSE;
		}
	case 1:
		primary = Window::GetPrivate(cx, argv[0], false);
		if( primary == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Window");
			return JS_FALSE;
		}
	}


	wxPGWindowList *p = new wxPGWindowList(primary, secondary);
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	

	
// メソッドの定義
WXJS_BEGIN_METHOD_MAP(WindowList)
	WXJS_METHOD("setSecondary", setSecondary, 1 )
WXJS_END_METHOD_MAP()

JSBool WindowList::setSecondary(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGWindowList *p = GetPrivate(cx, obj );
    if ( p == NULL )
        return JS_FALSE;

	wxWindow* pWnd = Window::GetPrivate(cx, argv[0], false);
	if( pWnd == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Window");
		return JS_FALSE;
	}

	p->SetSecondary(pWnd);

	
	return JS_TRUE;
}