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
#include "js/gui/pg/pg_prop_flags.h"
#include "js/gui/pg/pg_choices.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	FlagsProperty
//--------------------------------------------------------
WXJS_INIT_CLASS(FlagsProperty, "FlagsProperty", 0)
	

WXJS_BEGIN_DESTRUCTOR(wxFlagsProperty, FlagsProperty)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxFlagsProperty, FlagsProperty)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString label = wxPG_LABEL;
	wxString name = wxPG_LABEL;
	int value=0;
	wxArrayInt values = wxArrayInt();
	wxArrayString labels;
	wxPGChoices* pPGChoices = NULL;


	if( argc > 5 ) {
		argc = 5;
	}

/*
wxFlagsProperty (
	const wxString &label, 
	const wxString &name, 
	wxPGChoices &choices, 
	long value=0)
 
wxFlagsProperty (
	const wxString &label=wxPG_LABEL, 
	const wxString &name=wxPG_LABEL, 
	const wxArrayString &labels=wxArrayString(), 
	const wxArrayInt &values=wxArrayInt(), 
	int value=0)
*/
	switch( argc ) {
	case 5:
		if( FromJS(cx, argv[4], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 5, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 4:
		if( argv[3].isNumber() == true ) {
			if( FromJS(cx, argv[3], value) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
		} else {
			if( FromJS(cx, argv[3], values) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, "Array(Number)");
				return JS_FALSE;
			}
		}
	case 3:
		if( argv[2].isObjectOrNull() == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Object");
			return JS_FALSE;
		}
		{
			JSObject *obj = argv[1].toObjectOrNull();
			if( obj == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Object is null.");
				return JS_FALSE;
			}
			if( JS_IsArrayObject(cx, obj ) == JS_TRUE ) {
				if( FromJS(cx, argv[3], labels) == false ) {
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Array(String)");
					return JS_FALSE;
				}
			} else {
				pPGChoices = Choices::GetPrivate(cx, argv[2], false);
				if( pPGChoices == NULL ) {
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Choices");
					return JS_FALSE;
				}
			}
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



	wxFlagsProperty *p = NULL;
	if( pPGChoices != NULL ) {
		p = new wxFlagsProperty(label, name, *pPGChoices, value);
	} else 
	if( labels.GetCount() != 0 ) {
		p = new wxFlagsProperty(label, name, labels, values, value);
	} else  {
		p = new wxFlagsProperty(label, name);
	}
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
	


WXJS_BEGIN_GET_SET_STR_PROP(wxFlagsProperty, FlagsProperty)
	Property::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

	
WXJS_BEGIN_PROPERTY_MAP(FlagsProperty)
  WXJS_PROPERTY(P_ITEM_COUNT , "itemCount")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxFlagsProperty, FlagsProperty)
	switch (id) 
	{
	case P_ITEM_COUNT:
		ToJSVal(cx, vp, p->GetItemCount ());
		break;
	}
	return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_METHOD_MAP(FlagsProperty)
	WXJS_METHOD("getLabel", getLabel, 1)
WXJS_END_METHOD_MAP()


JSBool FlagsProperty::getLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxFlagsProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	size_t idt = 0;

	if( FromJS(cx, argv[0], idt) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	*vp = ToJS(cx, p->GetLabel(idt));

	return JS_TRUE;
}
