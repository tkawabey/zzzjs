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
#include "js/gui/pg/pg_prop_colour.h"
#include "js/gui/pg/pg_prop_system_colour.h"
#include "js/gui/misc/colour.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	ColourProperty
//--------------------------------------------------------
WXJS_INIT_CLASS(ColourProperty, "ColourProperty", 1)
	

WXJS_BEGIN_DESTRUCTOR(wxColourProperty, ColourProperty)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxColourProperty, ColourProperty)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString label = wxPG_LABEL;
	wxString name = wxPG_LABEL;
	wxColour value=*wxWHITE;

	if( argc > 3 ) {
		argc = 3;
	}

	/*
	wxColourProperty (
		const wxString &label=wxPG_LABEL, 
		const wxString &name=wxPG_LABEL, 
		const wxArrayString &labels=wxArrayString(), 
		const wxArrayInt &values=wxArrayInt(), 
		const wxString &value=wxEmptyString)
 
	wxColourProperty (
		const wxString &label, 
		const wxString &name, 
		wxPGChoices &choices, 
		const wxString &value=wxEmptyString)
 
	*/

	switch( argc ) {
	case 3:
		{
			wxColour* pCPV = Colour::GetPrivate(cx, argv[2], false);
			if( pCPV == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Colour");
				return JS_FALSE;
			}
			value = *pCPV;
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



	wxColourProperty *p = new wxColourProperty(label, name, value);
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxColourProperty, ColourProperty)
	SystemColourProperty::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


