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
#include "js/gui/pg/pg_cell.h"
#include "js/gui/pg/pg_choice_entry.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/bitmap.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	ChoiceEntry
//--------------------------------------------------------
WXJS_INIT_CLASS(ChoiceEntry, "ChoiceEntry", 1)
	

WXJS_BEGIN_DESTRUCTOR(wxPGChoiceEntry, ChoiceEntry)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxPGChoiceEntry, ChoiceEntry)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	/*
		wxPGChoiceEntry (
			const wxString &label
			, int value
			, const wxBitmap &bitmap
			, const wxColour &fgCol=wxNullColour
			, const wxColour &bgCol=wxNullColour)

		wxPGChoiceEntry (
			const wxString &label
			, int value=INT_MAX)
	*/
	int argIndex = 0;
	wxString	label = wxPG_LABEL;
	wxString	name = wxPG_LABEL;
	zzzJsPtr<wxBitmap> apBitmap;
	wxColour	fgCol=wxNullColour;
	wxColour	bgCol=wxNullColour;
	int			value=INT_MAX;
	bool		bHaveBmp = false;
	

	if( argc > 5 ) {
		argc = 5;
	}

	argIndex = argc - 1;
	switch( argc ) {
	case 5:
		{
			wxColour* pColor = Colour::GetPrivate(cx, argv[4], false);
			if( pColor == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Colour");
				return JS_FALSE;

			}
			bgCol = *pColor;
			argIndex--;
		}
	case 4:
		{
			wxColour* pColor = Colour::GetPrivate(cx, argv[3], false);
			if( pColor == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Colour");
				return JS_FALSE;

			}
			bgCol = *pColor;
			argIndex--;
		}
	case 3:
		{
			if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
				return JS_FALSE;
			}
			bHaveBmp = true;
			argIndex--;
		}
	case 2:
		if( FromJS(cx, argv[1], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	argIndex = 0;
	// label
	if( FromJS(cx, argv[argIndex], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	wxPGChoiceEntry *p = NULL;
	if( bHaveBmp == false ) {
		p = new wxPGChoiceEntry(label, value);
	} else {
		//
		// 実装時のバージョンでは、まだ未対応です。
		//
		p = new wxPGChoiceEntry(label, value);
//		p = new wxPGChoiceEntry(label, value, bitmap, fgCol, bgCol);
	}
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
WXJS_BEGIN_PROPERTY_MAP(ChoiceEntry)
  WXJS_PROPERTY(P_VALUE, "value")
WXJS_END_PROPERTY_MAP()
	
WXJS_BEGIN_GET_PROP(wxPGChoiceEntry, ChoiceEntry)
	switch (id) 
	{
	case P_VALUE:
		ToJSVal(cx, vp, p->GetValue());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxPGChoiceEntry, ChoiceEntry)
	switch (id) 
	{
	case P_VALUE:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetValue( val );
		}
		break;
	}
	return true;
WXJS_END_SET_PROP


WXJS_BEGIN_GET_SET_STR_PROP(wxPGChoiceEntry, ChoiceEntry)
	Cell::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP






