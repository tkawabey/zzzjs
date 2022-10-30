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
#include "js/gui/pg/pg_prop_file.h"
#include "js/io/filename.h"



using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	FileProperty
//--------------------------------------------------------
WXJS_INIT_CLASS(FileProperty, "FileProperty", 0)
	

WXJS_BEGIN_DESTRUCTOR(wxFileProperty, FileProperty)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxFileProperty, FileProperty)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString label = wxPG_LABEL;
	wxString name = wxPG_LABEL;
	wxString value=wxEmptyString;

	if( argc > 3 ) {
		argc = 3;
	}


	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[2], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
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



	wxFileProperty *p = new wxFileProperty(label, name, value);
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
	
WXJS_BEGIN_PROPERTY_MAP(FileProperty)
  WXJS_PROPERTY(P_FILE_NAME, "fileName")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxFileProperty, FileProperty)
	switch (id) 
	{
	case P_FILE_NAME:
		vp.set( zzzJs::io::FileName::CreateObject(cx, new wxFileName( p->GetFileName())) );
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_GET_SET_STR_PROP(wxFileProperty, FileProperty)
	Property::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


	