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
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_prop_category.h"
#include "js/gui/control/window.h"
#include "js/gui/misc/font.h"





using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	PropertyCategory
//--------------------------------------------------------
WXJS_INIT_CLASS(PropertyCategory, "PropertyCategory", 1)
	

WXJS_BEGIN_DESTRUCTOR(wxPropertyCategory, PropertyCategory)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxPropertyCategory, PropertyCategory)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString label = wxPG_LABEL;
	wxString name = wxPG_LABEL;

	if( argc > 2 ) {
		argc = 2;
	}

	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[1], name) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	case 1:
		if( FromJS(cx, argv[0], label) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	}


	wxPropertyCategory *p = new wxPropertyCategory(label, name);
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxPropertyCategory, PropertyCategory)
	Property::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP



	
WXJS_BEGIN_METHOD_MAP(PropertyCategory)
	WXJS_METHOD("getTextExtent", getTextExtent, 2)
WXJS_END_METHOD_MAP()



JSBool PropertyCategory::getTextExtent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyCategory *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argIndex = 0;
	wxWindow* pWnd = NULL;
	zzzJsPtr<wxFont> apFont;

	// 1: pWnd
	pWnd = Window::GetPrivate(cx, argv[argIndex], false );
	if( pWnd == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	// 2: pFont
	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);

	vp->setInt32( p->GetTextExtent(pWnd, *(apFont.get())) );

	return JS_TRUE;
}