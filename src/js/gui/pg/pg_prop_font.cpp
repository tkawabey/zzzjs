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
#include "js/gui/pg/pg_prop_font.h"
#include "js/gui/misc/font.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	FontProperty
//--------------------------------------------------------
WXJS_INIT_CLASS(FontProperty, "FontProperty", 1)
	

WXJS_BEGIN_DESTRUCTOR(wxFontProperty, FontProperty)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxFontProperty, FontProperty)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int argIndex = 0;
	wxString label = wxPG_LABEL;
	wxString name = wxPG_LABEL;
	wxFont value = wxFont();

	if( argc > 3 ) {
		argc = 3;
	}

	argIndex = argc - 1;
	switch( argc ) {
	case 3:
		{
			zzzJsPtr<wxFont> apFont;
			ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
			value = *(apFont.get());
		}
		argIndex--;
	case 2:
		if( FromJS(cx, argv[argIndex], name) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		argIndex--;
	case 1:
		if( FromJS(cx, argv[argIndex], label) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
		argIndex--;
	}


	wxFontProperty *p = new wxFontProperty(label, name, value);
	SetPrivate(cx, obj, p);
	return p;
}
WXJS_END_CONSTRUCTOR
	
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxFontProperty, FontProperty)
	Property::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP






