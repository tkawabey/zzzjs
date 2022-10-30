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
#include "js/gui/pg/pg_prop_multi_choice.h"
#include "js/gui/pg/pg_choices.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	MultiChoiceProperty
//--------------------------------------------------------
WXJS_INIT_CLASS(MultiChoiceProperty, "MultiChoiceProperty", 1)
	

WXJS_BEGIN_DESTRUCTOR(wxMultiChoiceProperty, MultiChoiceProperty)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxMultiChoiceProperty, MultiChoiceProperty)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


/*
wxMultiChoiceProperty (
	const wxString &label, 
	const wxString &name, 
	const wxArrayString &strings, 
	const wxArrayString &value)
 
wxMultiChoiceProperty (
	const wxString &label, 
	const wxString &name, 
	const wxPGChoices &choices, 
	const wxArrayString &value=wxArrayString())
 
wxMultiChoiceProperty (
	const wxString &label=wxPG_LABEL, 
	const wxString &name=wxPG_LABEL, 
	const wxArrayString &value=wxArrayString())
*/

	wxString label = wxPG_LABEL;
	wxString name = wxPG_LABEL;
	wxArrayString strings=wxArrayString();
	wxArrayString value=wxArrayString();
	wxPGChoices* pPGChoices = NULL;

	if( argc > 4 ) {
		argc = 4;
	}

	switch( argc ) {
	case 4:
		if( FromJS(cx, argv[3], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, "Array(String)");
			return JS_FALSE;
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
				if( argc == 4 ) {
					if( FromJS(cx, argv[3], strings) == false ) {
						JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Array(String)");
						return JS_FALSE;
					}
				} else {
					if( FromJS(cx, argv[3], value) == false ) {
						JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Array(String)");
						return JS_FALSE;
					}
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
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_DOUBLE);
			return JS_FALSE;
		}
	}


	wxMultiChoiceProperty *p = NULL;
	if( argc == 4 ) {
		if( pPGChoices != NULL ) {
			p = new wxMultiChoiceProperty(label, name, *pPGChoices, value);
		} else {
			p = new wxMultiChoiceProperty(label, name, strings, value);
		}
	} else {
		if( pPGChoices != NULL ) {
			p = new wxMultiChoiceProperty(label, name, *pPGChoices);
		} else {
			p = new wxMultiChoiceProperty(label, name, strings);
		}
	}
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
WXJS_BEGIN_PROPERTY_MAP(MultiChoiceProperty)
  WXJS_READONLY_PROPERTY(P_VALUE_ARRAY_INT, "valueArrayInt")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxMultiChoiceProperty, MultiChoiceProperty)
	switch (id) 
	{
	case P_VALUE_ARRAY_INT:
		{
			vp.set( ToJS(cx, p->GetValueAsArrayInt()) );
		}
		break;
	}
	return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxMultiChoiceProperty, MultiChoiceProperty)
	Property::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP






