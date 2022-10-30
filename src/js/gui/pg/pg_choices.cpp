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
#include "js/gui/pg/pg_choices.h"
#include "js/gui/pg/pg_choice_entry.h"
#include "js/gui/misc/bitmap.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	Choices
//--------------------------------------------------------
WXJS_INIT_CLASS(Choices, "Choices", 1)
	

WXJS_BEGIN_DESTRUCTOR(wxPGChoices, Choices)
{
	delete p;
}
WXJS_END_DESTRUCTOR

WXJS_BEGIN_CONSTRUCTOR(wxPGChoices, Choices)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	/*
	引数無し。
 	wxPGChoices ()
 	Default constructor. More...
	
	第一引数が、　Choices
 	wxPGChoices (const wxPGChoices &a)
 	Copy constructor, uses reference counting. More...
 
	第1引数が、　Array
	大2引数が、　Array
 	wxPGChoices (const wxArrayString &labels, const wxArrayInt &values=wxArrayInt())
 	Constructor. More...

	*/
	wxPGChoices*pC = NULL;
	wxArrayString	arrayString;
	wxArrayInt		arrayInt = wxArrayInt();

	if( argc > 2 ) {
		argc = 2;
	}

	switch( argc ) {
	case 2:
		if( argv[1].isObjectOrNull() == true ) {
			JSObject *obj = argv[1].toObjectOrNull();
			if( obj != NULL && JS_IsArrayObject(cx, obj ) == JS_TRUE ) {
				uint32_t length = 0;
				JS_GetArrayLength(cx, obj, &length);
				for(uint32_t i =0; i < length; i++)
				{
					JS::Value element;
					JS_GetElement(cx, obj, i, &element);
					int iElement;
					if ( FromJS(cx, element, iElement) )
						arrayInt.Add( iElement );
				}
			}
		}
	case 1:
		if( argv[0].isObjectOrNull() == true ) {
			JSObject *obj = argv[1].toObjectOrNull();
			if( obj != NULL && JS_IsArrayObject(cx, obj ) == JS_TRUE ) {
				if( FromJS(cx, argv[1], arrayString) == false ) {
					return NULL;
				}
			} else {
				wxPGChoices*pC = Choices::GetPrivate(cx, obj, false);
			}
		}
	}

	wxPGChoices *p = NULL;
	if( pC != NULL ) {
		p = new wxPGChoices(*pC);
	} else 
	if( arrayString.GetCount() != 0 ) {
		p = new wxPGChoices(arrayString, arrayInt);
	} else {
		p = new wxPGChoices();
	}
	SetPrivate(cx, obj, p);
	return p;
WXJS_END_CONSTRUCTOR
	
	
WXJS_BEGIN_PROPERTY_MAP(Choices)
  WXJS_READONLY_PROPERTY(P_COUNT, "count")
  WXJS_READONLY_PROPERTY(P_IS_OK, "isOk")
  WXJS_READONLY_PROPERTY(P_LABELS, "labels")
WXJS_END_PROPERTY_MAP()
	
WXJS_BEGIN_GET_PROP(wxPGChoices, Choices)
	switch (id) 
	{
	case P_COUNT:
		ToJSVal(cx, vp, p->GetCount());
		break;
	case P_IS_OK:
		ToJSVal(cx, vp, p->IsOk());
		break;
	case P_LABELS:
		ToJSVal(cx, vp, p->GetLabels());
		break;
	}
	return true;
WXJS_END_GET_PROP


	
WXJS_BEGIN_METHOD_MAP(Choices)
	WXJS_METHOD("add", add, 1)
	WXJS_METHOD("addAsSorted", addAsSorted, 1)
	WXJS_METHOD("clear", clear, 0)
	WXJS_METHOD("ensureData", ensureData, 0)
	WXJS_METHOD("getLabel", getLabel, 1)
	WXJS_METHOD("getValue", getValue, 1)
	WXJS_METHOD("getValuesFromStrings", getValuesFromStrings, 1)
	WXJS_METHOD("getIndicesForStrings", getIndicesForStrings, 1)
	WXJS_METHOD("index", index, 1)
	WXJS_METHOD("insert", insert, 1)
	WXJS_METHOD("item", item, 1)
	WXJS_METHOD("removeAt", removeAt, 1)
	WXJS_METHOD("set", set, 1)
WXJS_END_METHOD_MAP()



	
JSBool Choices::add(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	/*
	void 	Add (const wxArrayString &arr, const wxArrayInt &arrint)
 		Adds to current. More...
 
	wxPGChoiceEntry & 	Add (const wxString &label, int value=wxPG_INVALID_VALUE)
 		Adds a single choice item. More...
 
	wxPGChoiceEntry & 	Add (const wxString &label, const wxBitmap &bitmap, int value=wxPG_INVALID_VALUE)
 		Adds a single item, with bitmap. More...
 
	wxPGChoiceEntry & 	Add (const wxPGChoiceEntry &entry)
 		Adds a single item with full entry information. More...
	*/

	if( argc > 3 ) {
		argc = 3;
	}
	
	int argIndex = 0;

	int value = wxPG_INVALID_VALUE;
	wxArrayString		arr;
	wxArrayInt			arrayInt;
//	wxBitmap*			bmp = NULL;
	wxPGChoiceEntry*	pChoiceEntry = NULL;
	wxString			label;
	wxPGChoiceEntry*	pRetEntry = NULL; 
	zzzJsPtr<wxBitmap> apBitmap;

	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[2], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 2:
		if( argv[1].isNumber() == true ) {
			if( FromJS(cx, argv[1], value) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
		} else
		if( argv[1].isObjectOrNull() == true ) {
			JSObject *obj = argv[1].toObjectOrNull();
			if( obj == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Object is null.");
				return JS_FALSE;
			}
			if( JS_IsArrayObject(cx, obj ) == JS_TRUE ) {
				uint32_t length = 0;
				JS_GetArrayLength(cx, obj, &length);
				for(uint32_t i =0; i < length; i++)
				{
					JS::Value element;
					JS_GetElement(cx, obj, i, &element);
					int iElement;
					if ( FromJS(cx, element, iElement) )
						arrayInt.Add( iElement );
				}
			} else
			if( JS_GetClass(obj) == Bitmap::GetClass() ) {
				if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Bitmap");
					return JS_FALSE;
				}
				if( apBitmap.get() == NULL ) {

				}
			}
		} else {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Integer or Array(Integer) or Bitmap");
			return JS_FALSE;

		}
	}
	
	if( argv[0].isObjectOrNull() == true ) {
		JSObject *obj = argv[0].toObjectOrNull();
		if( obj == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Object is null.");
			return JS_FALSE;
		}
		if( JS_IsArrayObject(cx, obj ) == JS_TRUE ) {
			if( FromJS(cx, argv[0], arr) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Array(String)");
				return JS_FALSE;
			}
		} else
		if( JS_GetClass(obj) == ChoiceEntry::GetClass() ) {
			pChoiceEntry = ChoiceEntry::GetPrivate(cx, argv[1], false);
			if( pChoiceEntry == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "ChoiceEntry.");
				return JS_FALSE;
			}
		} else {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Object is Array(String) or ChoiceEntry.");
			return JS_FALSE;
		}
	} else
	if( argv[0].isString() == true ) {
		if( FromJS(cx, argv[0], label) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	} else {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "String or Object");
		return JS_FALSE;
	}

	
//	wxPGChoiceEntry*	pRetEntry = NULL; 
	if( arr.GetCount() != 0 ) {
		if( arrayInt.GetCount() != 0 ) {
			if( arrayInt.GetCount() != arr.GetCount() ) {
				JS_ReportError(cx, "missing array count.");
				return JS_FALSE;
			}
		}
		p->Add(arr, arrayInt);
	} else 
	if( pChoiceEntry != NULL ) {
		wxPGChoiceEntry& ret = p->Add( *pChoiceEntry );
		pRetEntry = &ret; 
	} else {
		if( label.Length() == 0 ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "label is not specify.");
			return JS_FALSE;
		}
		if( apBitmap.get() != NULL ) {
			wxPGChoiceEntry& ret = p->Add(label, *(apBitmap.get()), value);
			pRetEntry = &ret; 
		} else {
			wxPGChoiceEntry& ret = p->Add(label, value);
			pRetEntry = &ret; 
		}
	}

	if( pRetEntry != NULL ) {
		*vp = ChoiceEntry::CreateObject(cx, pRetEntry, NULL);
	} else {
		vp->setUndefined();
	}
	return JS_TRUE;
}
	
JSBool Choices::addAsSorted(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	if( argc > 2 ) {
		argc = 2;
	}

	int value = wxPG_INVALID_VALUE;
	wxString			label;

	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[1], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	
	if( FromJS(cx, argv[0], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	wxPGChoiceEntry& ret = p->AddAsSorted(label, value);
	
	*vp = ChoiceEntry::CreateObject(cx, &ret, NULL);

	return JS_TRUE;
}
	
JSBool Choices::clear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	p->Clear();

	return JS_TRUE;
}
	
JSBool Choices::ensureData(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	p->EnsureData();

	return JS_TRUE;
}
	
JSBool Choices::getLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	unsigned int ind = -1;
	if( FromJS(cx, argv[0], ind) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	*vp = ToJS(cx, p->GetLabel(ind));
	return JS_TRUE;
}
	
JSBool Choices::getValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	unsigned int ind = -1;
	if( FromJS(cx, argv[0], ind) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	*vp = ToJS(cx, p->GetValue(ind));
	return JS_TRUE;
}
	
JSBool Choices::getValuesFromStrings(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	wxArrayString  arr;
	if( FromJS(cx, argv[0], arr) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	wxArrayInt 	arrInt = p->GetValuesForStrings(arr);


	*vp = ToJS(cx, arrInt);
	return JS_TRUE;
}
	
JSBool Choices::getIndicesForStrings(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	wxArrayString  arr;
	if( FromJS(cx, argv[0], arr) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	wxArrayInt 	arrInt = p->GetIndicesForStrings(arr);


	*vp = ToJS(cx, arrInt);
	return JS_TRUE;
}
	
JSBool Choices::index(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int idx =  wxPG_INVALID_VALUE;
	wxString strLabel;

	
	if( argc > 3 ) {
		argc = 3;
	}
	if( argv[0].isString() == true ) {
		if( FromJS(cx, argv[0], strLabel) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	} else {
		if( FromJS(cx, argv[0], idx) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	if( idx !=  wxPG_INVALID_VALUE ) {
		*vp = ToJS(cx, p->Index(idx));
	} else {
		*vp = ToJS(cx, p->Index(strLabel));
	}
	
	return JS_TRUE;
}
	
JSBool Choices::insert(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int value = wxPG_INVALID_VALUE;
	int index = -1;
	wxString			label;
	wxPGChoiceEntry*	pChoiceEntry = NULL;
	wxPGChoiceEntry*	pRetEntry = NULL; 

	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[2], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 2: 
	if( FromJS(cx, argv[1], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 1:
	if( argv[0].isObjectOrNull() != false ) {
		pChoiceEntry = ChoiceEntry::GetPrivate(cx, argv[0], false);
		if( pChoiceEntry == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "ChoiceEntry.");
			return JS_FALSE;
		}
	} else {
		if( FromJS(cx, argv[0], label) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	}

	if( pChoiceEntry != NULL ) {
		wxPGChoiceEntry& ret = p->Insert( *pChoiceEntry, index );
		pRetEntry = &ret; 
	} else {
		wxPGChoiceEntry& ret = p->Insert( label, index, value );
		pRetEntry = &ret; 
	}
	

	if( pRetEntry != NULL ) {
		*vp = ChoiceEntry::CreateObject(cx, pRetEntry, NULL);
	} else {
		vp->setUndefined();
	}
	return JS_TRUE;
}
	
JSBool Choices::item(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	unsigned int i;
	// 1: 
	if( FromJS(cx, argv[0], i) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	wxPGChoiceEntry& ret = p->Item(i);

	*vp = ChoiceEntry::CreateObject(cx, &ret, NULL);

	return JS_TRUE;
}
	
JSBool Choices::removeAt(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	if( argc > 2 ) {
		argc = 2;
	}
	size_t nIndex = 0;
	size_t count=1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[1], count) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: 
	if( FromJS(cx, argv[0], nIndex) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	p->RemoveAt(nIndex, count);

	return JS_TRUE;
}
	
JSBool Choices::set(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGChoices *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	if( argc > 2 ) {
		argc = 2;
	}
	wxArrayInt values=wxArrayInt();
	wxArrayString labels;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[1], values) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Array(Number)");
			return JS_FALSE;
		}
	}
	// 1: 
	if( FromJS(cx, argv[0], labels) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	p->Set(labels, values);

	return JS_TRUE;
}


