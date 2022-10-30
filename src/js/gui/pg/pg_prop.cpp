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
#include "js/gui/errors.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_cell.h"
#include "js/gui/pg/pg_choices.h"
#include "js/gui/pg/pg_validation_info.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/size.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	Property
//--------------------------------------------------------
WXJS_INIT_CLASS(Property, "Property", 1)

void Property::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{

}

//
//	オーバーライト
//
void Property::OnSetValue()
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		wxPGProperty::OnSetValue();
		return ;
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onSetValue", &fval) == JS_FALSE )
	{
		wxPGProperty::OnSetValue();
		return ;
	}
	jsval rval;
	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_TRUE )
	{

	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
		wxPGProperty::OnSetValue();
	}	
}

//bool Property::ValidateValue( wxVariant& value,
//                wxPGValidationInfo& validationInfo ) const
//{
//
//	JavaScriptClientData *data 
//		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
//	if( data == NULL ) {
//		return wxPGProperty::ValidateValue(value, validationInfo);
//	}
//	JSContext *cx = data->GetContext();
//	JSObject *obj = data->GetObject();
//
//
//	jsval fval;
//	if ( GetFunctionProperty(cx, obj, "onValidateValue", &fval) == JS_FALSE )
//	{
//		return wxPGProperty::ValidateValue(value, validationInfo);
//		return ;
//	}
//	wxPGValidationInfo* pVi = new wxPGValidationInfo();
//	jsval rval;
//	jsval argv[] = { ToJS(cx, value), ToJS(cx, value) };
//
//	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_TRUE )
//	{
//		bool ret = false;
//
//		FromJS(cx, rval, ret);
//
//		return ret;
//	} else {
//		if ( JS_IsExceptionPending(cx) )
//		{
//			JS_ReportPendingException(cx);
//		}
//	}
//	return wxPGProperty::ValidateValue(value, validationInfo);
//}

bool Property::StringToValue( wxVariant& variant,
                                const wxString& text,
                                int argFlags /*= 0*/ ) const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::StringToValue(variant, text, argFlags);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onStringToValue", &fval) == JS_FALSE )
	{
		return wxPGProperty::StringToValue(variant, text, argFlags);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, variant), ToJS(cx, text), ToJS(cx, argFlags) };

	if ( JS_CallFunctionValue(cx, obj, fval, 3, argv, &rval) == JS_TRUE )
	{
		bool ret = false;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::StringToValue(variant, text, argFlags);
}

bool Property::IntToValue( wxVariant& value,
                             int number,
                             int argFlags /*= 0*/ ) const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::IntToValue(value, number, argFlags);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onIntToValue", &fval) == JS_FALSE )
	{
		return wxPGProperty::IntToValue(value, number, argFlags);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, value), ToJS(cx, number), ToJS(cx, argFlags) };

	if ( JS_CallFunctionValue(cx, obj, fval, 3, argv, &rval) == JS_TRUE )
	{
		bool ret = false;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::IntToValue(value, number, argFlags);
}

wxString Property::ValueToString( wxVariant& value, int argFlags /*= 0*/ ) const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::ValueToString(value, argFlags);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onValueToString", &fval) == JS_FALSE )
	{
		return wxPGProperty::ValueToString(value, argFlags);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, value),  ToJS(cx, argFlags) };

	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{
		wxString ret;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::ValueToString(value, argFlags);
}
wxSize Property::OnMeasureImage( int item /*= -1*/ ) const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::OnMeasureImage(item);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onMeasureImage", &fval) == JS_FALSE )
	{
		return wxPGProperty::OnMeasureImage(item);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, item) };

	if ( JS_CallFunctionValue(cx, obj, fval, 1, argv, &rval) == JS_TRUE )
	{
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		wxSize ret;
		if( ZZZJS_PROP_GET_AP(apSize, Size, rval) == false )
		{
			ret = *(apSize.get());
		}
		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::OnMeasureImage(item);
}
int Property::GetChoiceSelection() const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::GetChoiceSelection();
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onGetChoiceSelection", &fval) == JS_FALSE )
	{
		return wxPGProperty::GetChoiceSelection();
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
//	jsval argv[] = { ToJS(cx, item) };

	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL/*argv*/, &rval) == JS_TRUE )
	{
		int ret = 0;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	
	return wxPGProperty::GetChoiceSelection();
}
void Property::RefreshChildren()
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		wxPGProperty::RefreshChildren();
		return ;
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onRefreshChildren", &fval) == JS_FALSE )
	{
		wxPGProperty::RefreshChildren();
		return ;
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
//	jsval argv[] = { ToJS(cx, item) };

	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL/*argv*/, &rval) == JS_TRUE )
	{
		return ;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	
	wxPGProperty::RefreshChildren();
	return ;
}
bool Property::DoSetAttribute( const wxString& name, wxVariant& value )
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::DoSetAttribute(name, value);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onDoSetAttribute", &fval) == JS_FALSE )
	{
		return wxPGProperty::DoSetAttribute(name, value);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, name),  ToJS(cx, value) };

	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{
		bool ret = false;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::DoSetAttribute(name, value);
}
wxVariant Property::DoGetAttribute( const wxString& name ) const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::DoGetAttribute(name);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onDoGetAttribute", &fval) == JS_FALSE )
	{
		return wxPGProperty::DoGetAttribute(name);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, name) };

	if ( JS_CallFunctionValue(cx, obj, fval, 1, argv, &rval) == JS_TRUE )
	{
		wxVariant ret;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::DoGetAttribute(name);
}
void Property::OnValidationFailure( wxVariant& pendingValue )
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		wxPGProperty::OnValidationFailure(pendingValue);
		return ;
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onValidationFailure", &fval) == JS_FALSE )
	{
		wxPGProperty::OnValidationFailure(pendingValue);
		return ;
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, pendingValue) };

	if ( JS_CallFunctionValue(cx, obj, fval, 1, argv, &rval) == JS_TRUE )
	{
		//wxVariant ret;

		//FromJS(cx, rval, ret);

		//return ret;
		return ;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGProperty::OnValidationFailure(pendingValue);
	//return wxPGProperty::DoGetAttribute(name);
}
wxString Property::GetValueAsString( int argFlags /*= 0*/ ) const
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if( data == NULL ) {
		return wxPGProperty::GetValueAsString(argFlags);
	}
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();


	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onGetValueAsString", &fval) == JS_FALSE )
	{
		return wxPGProperty::GetValueAsString(argFlags);
	}
	wxPGValidationInfo* pVi = new wxPGValidationInfo();
	jsval rval;
	jsval argv[] = { ToJS(cx, argFlags) };

	if ( JS_CallFunctionValue(cx, obj, fval, 1, argv, &rval) == JS_TRUE )
	{
		wxString ret;

		FromJS(cx, rval, ret);

		return ret;
	} else {
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGProperty::GetValueAsString(argFlags);
}
//WXJS_BEGIN_CONSTANT_MAP(Property)
//  WXJS_CONSTANT(wxAUI_MGR_, ALLOW_FLOATING)
//  WXJS_CONSTANT(wxAUI_MGR_, ALLOW_ACTIVE_PANE)
//  WXJS_CONSTANT(wxAUI_MGR_, TRANSPARENT_DRAG )
//  WXJS_CONSTANT(wxAUI_MGR_, TRANSPARENT_HINT )
//  WXJS_CONSTANT(wxAUI_MGR_, VENETIAN_BLINDS_HINT )
//  WXJS_CONSTANT(wxAUI_MGR_, RECTANGLE_HINT )
//  WXJS_CONSTANT(wxAUI_MGR_, HINT_FADE )
//  WXJS_CONSTANT(wxAUI_MGR_, NO_VENETIAN_BLINDS_FADE )
//  WXJS_CONSTANT(wxAUI_MGR_, LIVE_RESIZE )
//  WXJS_CONSTANT(wxAUI_MGR_, DEFAULT )
//
//
//
//  WXJS_CONSTANT(wxAUI_, INSERT_PANE )
//  WXJS_CONSTANT(wxAUI_, INSERT_ROW )
//  WXJS_CONSTANT(wxAUI_, INSERT_DOCK )
//WXJS_END_CONSTANT_MAP()
/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Property)
  WXJS_PROPERTY(P_CHOICE_SELECTION, "choiceSelection")
  WXJS_PROPERTY(P_ENABLE, "enable")
  WXJS_PROPERTY(P_LABEL, "label")
  WXJS_READONLY_PROPERTY(P_BASENAME, "baseName")
  WXJS_READONLY_PROPERTY(P_CHILED_COUNT, "childCount")
  WXJS_PROPERTY(P_CLIENT_DATA, "clientData")
  WXJS_PROPERTY(P_CLIENT_OBJECT, "clientObject")
  WXJS_PROPERTY(P_COMMON_VALUE, "commonValue")
  WXJS_READONLY_PROPERTY(P_DISPLAY_STRING, "displayString")
  WXJS_READONLY_PROPERTY(P_HINT_TEXT, "hintString")
  WXJS_PROPERTY(P_HELP_STRING, "helpString")
  WXJS_READONLY_PROPERTY(P_INDEX_PARENT, "indexInParent")
  WXJS_READONLY_PROPERTY(P_LAST_VISIBLE_SUBITEM, "lastVisibleSubItem")
  WXJS_READONLY_PROPERTY(P_MAIN_PARENT, "mainParent")
  WXJS_PROPERTY(P_MAX_LENGTH, "maxLength")
  WXJS_PROPERTY(P_NAME, "name")
  WXJS_READONLY_PROPERTY(P_PARENT, "parent")
  WXJS_READONLY_PROPERTY(P_VALUE_TYPE, "valueType")
  WXJS_READONLY_PROPERTY(P_Y, "y")
  WXJS_READONLY_PROPERTY(P_IS_CATEGPRY, "isCategory")
  WXJS_PROPERTY(P_EXPANDED, "expanded")
  WXJS_READONLY_PROPERTY(P_IS_ROOT, "isRoot")
  WXJS_READONLY_PROPERTY(P_IS_SUB_PROP, "isSubProp")
  WXJS_READONLY_PROPERTY(P_IS_TEXT_EDIT_ABLE, "isTextEditAble")
  WXJS_READONLY_PROPERTY(P_IS_VALUE_UNSPECIFIED, "isValueUnSpecified")
  WXJS_READONLY_PROPERTY(P_IS_VISIBLE, "isVisible")
  WXJS_READONLY_PROPERTY(P_LAST, "last")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxPGProperty, Property)
	switch (id) 
	{
	case P_CHOICE_SELECTION:
		ToJSVal(cx, vp, p->GetChoiceSelection());
		break;
	case P_ENABLE:
		ToJSVal(cx, vp, p->IsEnabled());
		break;
	case P_LABEL:
		ToJSVal(cx, vp, p->GetLabel());
		break;
	case P_BASENAME:
		ToJSVal(cx, vp, p->GetBaseName());
		break;
	case P_CHILED_COUNT:
		ToJSVal(cx, vp, (int)p->GetChildCount ());
		break;
	case P_CLIENT_DATA:
		{
			MyClientData* pClientData = (MyClientData*)p->GetClientData();
			if( pClientData == NULL ) {
				vp.setUndefined();
			} else {
				vp.set( pClientData->GetJSVal() );
			}
		}
		break;
	case P_CLIENT_OBJECT:
		{
			MyClientData* pClientData = (MyClientData*)p->GetClientObject();
			if( pClientData == NULL ) {
				vp.setUndefined();
			} else {
				vp.set( pClientData->GetJSVal() );
			}
		}
		break;
	case P_DEFAULT_VALUE:
		ToJSVal(cx, vp, p->GetDefaultValue());
		break;
	case P_COMMON_VALUE:
		ToJSVal(cx, vp, p->GetCommonValue());
		break;
	case P_DISPLAY_STRING:
		ToJSVal(cx, vp, p->GetDisplayedString());
		break;
	case P_HINT_TEXT:
		ToJSVal(cx, vp, p->GetHintText());
		break;
	case P_HELP_STRING:
		ToJSVal(cx, vp, p->GetHelpString());
		break;
	case P_INDEX_PARENT:
		ToJSVal(cx, vp, p->GetIndexInParent());
		break;
	case P_LAST_VISIBLE_SUBITEM:
		{
			const wxPGProperty* pProp = p->GetLastVisibleSubItem();
			if( pProp != NULL ) {
				vp.set(  Property::CreateObject(cx, (wxPGProperty*)pProp, NULL) );
			} else {
				vp.setUndefined();
			}
		}
		break;
	case P_MAIN_PARENT:
		{
			wxPGProperty* pProp = p->GetMainParent();
			if( pProp != NULL ) {
				vp.set(  Property::CreateObject(cx, pProp, NULL) );
			} else {
				vp.setUndefined();
			}
		}
		break;
	case P_MAX_LENGTH:
		ToJSVal(cx, vp, p->GetMaxLength());
		break;
	case P_NAME:
		ToJSVal(cx, vp, p->GetName());
		break;
	case P_PARENT:
		{
			wxPGProperty* pProp = p->GetParent();
			if( pProp != NULL ) {
				vp.set(  Property::CreateObject(cx, pProp, NULL) );
			} else {
				vp.setNull();
			}
		}
		break;
	case P_VALUE_TYPE:
		ToJSVal(cx, vp, p->GetValueType());
		break;
	case P_Y:
		ToJSVal(cx, vp, p->GetY());
		break;
	case P_IS_CATEGPRY:
		ToJSVal(cx, vp, p->IsCategory());
		break;
	case P_EXPANDED:
		ToJSVal(cx, vp, p->IsExpanded());
		break;
	case P_IS_ROOT:
		ToJSVal(cx, vp, p->IsRoot());
		break;
	case P_IS_SUB_PROP:
		ToJSVal(cx, vp, p->IsSubProperty());
		break;
	case P_IS_TEXT_EDIT_ABLE:
		ToJSVal(cx, vp, p->IsTextEditable());
		break;
	case P_IS_VALUE_UNSPECIFIED:
		ToJSVal(cx, vp, p->IsValueUnspecified());
		break;
	case P_IS_VISIBLE:
		ToJSVal(cx, vp, p->IsVisible());
		break;
	case P_LAST:
		{
			wxPGProperty* pProp = p->Last();
			if( pProp != NULL ) {
				vp.set(  Property::CreateObject(cx, (wxPGProperty*)pProp, NULL) );
			} else {
				vp.setUndefined();
			}
		}
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxPGProperty, Property)
	switch (id) 
	{
	case P_CHOICE_SELECTION:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetChoiceSelection( val );
		}
		break;
	case P_ENABLE:
		{
			bool val = false;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->Enable( val );
		}
		break;
	case P_LABEL:
		{
			wxString val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetLabel( val );
		}
		break;
	case P_CLIENT_DATA:
		{
			MyClientData* pClientData = (MyClientData*)p->GetClientData();//new MyClientData(cx, vp);
			if( pClientData != NULL ) {
				delete pClientData;
			}
			pClientData = new MyClientData(cx, vp);
			p->SetClientData( pClientData );
		}
		break;
	case P_CLIENT_OBJECT:
		{
			MyClientData* pClientData = new MyClientData(cx, vp);
			p->SetClientObject( pClientData );
		}
		break;
	case P_DEFAULT_VALUE:
		{
			wxVariant val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetDefaultValue( val );
		}
		break;
	case P_COMMON_VALUE:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetCommonValue( val );
		}
		break;
	case P_HELP_STRING:
		{
			wxString val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetHelpString( val );
		}
		break;
	case P_MAX_LENGTH:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetMaxLength( val );
		}
		break;
	case P_NAME:
		{
			wxString val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetName( val );
		}
		break;
	case P_EXPANDED:
		{
			bool val = false;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetExpanded ( val );
		}
		break;
	}
	return true;
WXJS_END_SET_PROP




WXJS_BEGIN_DESTRUCTOR(wxPGProperty, Property)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Property)
	WXJS_METHOD("doGetValue", doGetValue, 0)
	WXJS_METHOD("validateValue", validateValue, 2)
	WXJS_METHOD("stringToValue", stringToValue, 1)
	WXJS_METHOD("intToValue", intToValue, 1)
	WXJS_METHOD("valueToString", valueToString, 1)
	WXJS_METHOD("setValueFromString", setValueFromString, 1)
	WXJS_METHOD("setValueFromInt", setValueFromInt, 1)
	WXJS_METHOD("childChanged", childChanged, 3)
	WXJS_METHOD("refreshChildren", refreshChildren, 0)
	WXJS_METHOD("doSetAttribute", doSetAttribute, 2)
	WXJS_METHOD("doGetAttribute", doGetAttribute, 1)
	WXJS_METHOD("addChoice", addChoice, 1)
	WXJS_METHOD("addPrivateChild", addPrivateChild, 1)
	WXJS_METHOD("adaptListToValue", adaptListToValue, 1)
	WXJS_METHOD("appendChild", appendChild, 1)
	WXJS_METHOD("areAllChildrenSpecified", areAllChildrenSpecified, 0)
	WXJS_METHOD("areChildrenComponents", areChildrenComponents, 0)
	WXJS_METHOD("changeFlag", changeFlag, 1)
	WXJS_METHOD("deleteChildren", deleteChildren, 0)
	WXJS_METHOD("deleteChoice", deleteChoice, 1)
	WXJS_METHOD("enableCommonValue", enableCommonValue, 0)
	WXJS_METHOD("generateComposedValue", generateComposedValue, 0)
	WXJS_METHOD("getAttribute", getAttribute, 1)
	WXJS_METHOD("getAttributeAsLong", getAttributeAsLong, 2)
	WXJS_METHOD("getAttributeAsDouble", getAttributeAsDouble, 2)
	WXJS_METHOD("getAttributes", getAttributes, 0)
	WXJS_METHOD("getCell", getCell, 1)
	WXJS_METHOD("getOrCreateCell", getOrCreateCell, 1)
	WXJS_METHOD("getChildrenHeight", getChildrenHeight, 1)
	WXJS_METHOD("getChoices", getChoices, 0)
	WXJS_METHOD("getFlagsAsString", getFlagsAsString, 1)
	WXJS_METHOD("getPropertyByName", getPropertyByName, 1)
	WXJS_METHOD("getValue", getValue, 0)
	WXJS_METHOD("getValueImage", getValueImage, 0)
	WXJS_METHOD("getValueAsString", getValueAsString, 0)
	WXJS_METHOD("getImageOffset", getImageOffset, 1)
	WXJS_METHOD("hasFlag", hasFlag, 1)
	WXJS_METHOD("hasFlagsExact", hasFlagsExact, 1)
	WXJS_METHOD("hasVisibleChildren", hasVisibleChildren, 0)
	WXJS_METHOD("hide", hide, 1)
	WXJS_METHOD("index", index, 1)
	WXJS_METHOD("insertChild", insertChild, 2)
	WXJS_METHOD("insertChoice", insertChoice, 2)
	WXJS_METHOD("isSomeParent", isSomeParent, 1)
	WXJS_METHOD("item", item, 1)
	WXJS_METHOD("recreateEditor", recreateEditor, 0)
	WXJS_METHOD("refreshEditor", refreshEditor, 0)
	WXJS_METHOD("setAttribute", setAttribute, 0)
	WXJS_METHOD("setAutoUnspecified", setAutoUnspecified, 0)
	WXJS_METHOD("setBackgroundColour", setBackgroundColour, 1)
	WXJS_METHOD("setCell", setCell, 2)
	WXJS_METHOD("setChoices", setChoices, 1)
	WXJS_METHOD("setFlagsFromString", setFlagsFromString, 1)
	WXJS_METHOD("setFlagRecursively", setFlagRecursively, 2)
	WXJS_METHOD("setModifiedStatus", setModifiedStatus, 1)
	WXJS_METHOD("setParentalType", setParentalType, 1)
	WXJS_METHOD("setTextColour", setTextColour, 1)
	WXJS_METHOD("setDefaultColours", setDefaultColours, 0)
	WXJS_METHOD("setValue", setValue, 1)
	WXJS_METHOD("setValueImage", setValueImage, 1)
	WXJS_METHOD("setValueInEvent", setValueInEvent, 1)
	WXJS_METHOD("SetValueToUnspecified", SetValueToUnspecified, 0)
	WXJS_METHOD("setWasModified", setWasModified, 0)
	WXJS_METHOD("updateParentValues", updateParentValues, 0)
	WXJS_METHOD("usesAutoUnspecified", usesAutoUnspecified, 0)
WXJS_END_METHOD_MAP()

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent of the button.</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Text" type=WXJS_TYPE_STRING>The label of the button</arg>
 *   <arg name="Pos" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the button on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the button.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTODRAW">
 *    The button style
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="wxDefaultValidator" />
 *  </function>
 *  <desc>
 *   Constructs a new wxButton object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxPGProperty, Property)
	//JS::CallArgs argv = CallArgsFromVp(argc, vp);
	//wxPGProperty *p = new wxPGProperty();
	//
 //   SetPrivate(cx, obj, p);

 //   if ( argc > 0 )
 //   {
 //       jsval rval;
 //       if ( ! _innerCreate(cx, obj, argc, vp, &rval) )
 //       {
 //         return NULL;
 //       }
 //   }

	//return p;
	return NULL;
WXJS_END_CONSTRUCTOR
	
	
JSBool Property::doGetValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxVariant val = p->DoGetValue();
	*vp = ToJS(cx, val);

	return JS_TRUE;
}

JSBool Property::validateValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	wxVariant value;
	wxPGValidationInfo *pValidation = NULL;

	// 1: variant
	if( FromJS(cx, argv[0], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
		return JS_FALSE;
	}
	// 2: PGValidationInf
	pValidation = ValidationInfo::GetPrivate(cx, argv[1], false);
	if( pValidation == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "pg.ValidationInfo");
		return JS_FALSE;
	}

	vp->setBoolean( p->ValidateValue(value, *pValidation) );

	return JS_TRUE;
}

JSBool Property::stringToValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argFlags = 0;
	wxString text;
	wxVariant value;

	if( argc > 2 ) {
		argc = 2;
	}

	if( argc == 2 ) {
		// 2: argFlags
		if( FromJS(cx, argv[1], argFlags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: text
	if( FromJS(cx, argv[0], text) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	if( p->StringToValue(value, text, argFlags) == true ) {
		*vp = ToJS(cx, value);
	} else {
		vp->setUndefined();
	}

	return JS_TRUE;
}

JSBool Property::intToValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argFlags = 0;
	 int number = 0;
	wxVariant value;

	if( argc > 2 ) {
		argc = 2;
	}

	if( argc == 2 ) {
		// 2: argFlags
		if( FromJS(cx, argv[1], argFlags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: number
	if( FromJS(cx, argv[0], number) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	if( p->IntToValue(value, number, argFlags) == true ) {
		*vp = ToJS(cx, value);
	} else {
		vp->setUndefined();
	}

	return JS_TRUE;
}

JSBool Property::valueToString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int argFlags = 0;
	wxVariant value;

	if( argc > 2 ) {
		argc = 2;
	}

	if( argc == 2 ) {
		// 2: argFlags
		if( FromJS(cx, argv[1], argFlags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: value
	if( FromJS(cx, argv[0], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	*vp = ToJS(cx, p->ValueToString(value, argFlags));

	return JS_TRUE;
}

JSBool Property::setValueFromString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int flags = wxPG_PROGRAMMATIC_VALUE;
	wxString text;

	if( argc > 2 ) {
		argc = 2;
	}

	if( argc == 2 ) {
		// 2: flags
		if( FromJS(cx, argv[1], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: text
	if( FromJS(cx, argv[0], text) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	vp->setBoolean( p->SetValueFromString(text, flags));

	return JS_TRUE;
}

JSBool Property::setValueFromInt(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int flags = 0;
	long value = 0;

	if( argc > 2 ) {
		argc = 2;
	}

	if( argc == 2 ) {
		// 2: flags
		if( FromJS(cx, argv[1], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: text
	if( FromJS(cx, argv[0], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	vp->setBoolean( p->SetValueFromInt(value, flags));

	return JS_TRUE;
}

JSBool Property::childChanged(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	wxVariant	thisValue;
	int			childIndex = 0;
	wxVariant	childValue;

	// 1: thisValue
	if( FromJS(cx, argv[0], thisValue) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Valiant");
		return JS_FALSE;
	}
	// 2: childIndex
	if( FromJS(cx, argv[1], childIndex) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 3: childValue
	if( FromJS(cx, argv[2], childValue) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, "Valiant");
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	wxVariant ret = p->ChildChanged(thisValue, childIndex, childValue);

	*vp = ToJS(cx, ret);;

	return JS_TRUE;
}

JSBool Property::refreshChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	p->RefreshChildren();

	return JS_TRUE;
}

JSBool Property::doSetAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	wxString name;
	wxVariant value;

	// 1: name
	if( FromJS(cx, argv[0], name) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// 2: value
	if( FromJS(cx, argv[1], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Variant");
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	vp->setBoolean( p->DoSetAttribute(name, value) );


	return JS_TRUE;
}

JSBool Property::doGetAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	wxString name;

	// 1: name
	if( FromJS(cx, argv[0], name) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// APIの実行と、戻り値の設定
	wxVariant ret = p->DoGetAttribute(name);

	*vp = ToJS(cx, ret);;

	return JS_TRUE;
}


JSBool Property::addChoice(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	wxString label;
	int value=wxPG_INVALID_VALUE;

	if( argc > 2 ) {
		argc = 2;
	}

	if( argc == 2 ) {
		// 2: value
		if( FromJS(cx, argv[1], value) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	// 1: label
	if( FromJS(cx, argv[0], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// APIの実行と、戻り値の設定
	vp->setInt32( p->AddChoice(label, value) );
	
	return JS_TRUE;
}


JSBool Property::addPrivateChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	wxVariant list;
	wxVariant value;
	

	// 1: list
	if( FromJS(cx, argv[0], list) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
		return JS_FALSE;
	}

	p->AdaptListToValue(list, &value);
	
	*vp = ToJS(cx, value);
	
	return JS_TRUE;
}


JSBool Property::adaptListToValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	wxVariant list;
	wxVariant value;
	

	// 1: list
	if( FromJS(cx, argv[0], list) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
		return JS_FALSE;
	}

	p->AdaptListToValue(list, &value);
	
	*vp = ToJS(cx, value);
	
	return JS_TRUE;
}


JSBool Property::appendChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxPGProperty *childProperty = NULL;
	

	// 1: childProperty
	childProperty = Property::GetPrivate(cx, argv[0]);
	if( childProperty == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Property");
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	wxPGProperty* pRet = p->AppendChild( childProperty );
	if( pRet != NULL ) {
		*vp = Property::CreateObject(cx, pRet);
	} else {
		vp->setUndefined();
	}
	
	return JS_TRUE;
}


JSBool Property::areAllChildrenSpecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	wxVariant pendingList;
	bool bIsHaveArg = false;

	if( argc != 0 ) {
		if( FromJS(cx, argv[0], pendingList ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
			return JS_FALSE;
		}
		bIsHaveArg = true;
	}


	// APIの実行と、戻り値の設定
	vp->setBoolean(
		p->AreAllChildrenSpecified( bIsHaveArg == true ? &pendingList : NULL )
	);
	
	return JS_TRUE;
}


JSBool Property::areChildrenComponents(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	// APIの実行と、戻り値の設定
	vp->setBoolean(
		p->AreChildrenComponents()
	);
	
	return JS_TRUE;
}


JSBool Property::changeFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	int flag = 0;
	bool set = false;

	// 1: flag
	if( FromJS(cx, argv[0], flag ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 2: flag
	if( FromJS(cx, argv[1], set ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Boolean");
		return JS_FALSE;
	}


	// APIの実行
	p->ChangeFlag((wxPGPropertyFlags )flag, set);

	return JS_TRUE;
}


JSBool Property::deleteChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;



	// APIの実行
	p->DeleteChildren();

	return JS_TRUE;
}


JSBool Property::deleteChoice(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	int index = 0;

	// 1: index
	if( FromJS(cx, argv[0], index ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行
	p->DeleteChoice(index);

	return JS_TRUE;
}


JSBool Property::enableCommonValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	bool enable=true;
	if( argc != 0 ) {
		// 1: enable
		if( FromJS(cx, argv[0], enable ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
			return JS_FALSE;
		}
	}

	// APIの実行
	p->EnableCommonValue (enable);

	return JS_TRUE;
}


JSBool Property::generateComposedValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;



	// APIの実行
	wxString strRet  = p->GenerateComposedValue();
	*vp = ToJS(cx, strRet);

	return JS_TRUE;
}


JSBool Property::getAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	if( argc > 2 ) {
		argc = 2;
	}

	wxString name;
	wxString strDef;
	bool haveDef = false;
	if( argc == 2 ) {
		// 2: strDef
		if( FromJS(cx, argv[1], strDef ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		haveDef = true;
	}
	// 1: name
	if( FromJS(cx, argv[0], name ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	if( haveDef == true ) {
		wxString strRet = p->GetAttribute(name, strDef);
		*vp = ToJS(cx, strRet);
	} else {
		wxVariant ret = p->GetAttribute(name);
		*vp = ToJS(cx, ret);
	}

	return JS_TRUE;
}


JSBool Property::getAttributeAsLong(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	if( argc > 2 ) {
		argc = 2;
	}

	wxString name;
	long defVal = 0;
	
	// 1: name
	if( FromJS(cx, argv[0], name ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// 2: defVal
	if( FromJS(cx, argv[1], defVal ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	vp->setInt32( p->GetAttributeAsLong(name, defVal) );

	return JS_TRUE;
}


JSBool Property::getAttributeAsDouble(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	if( argc > 2 ) {
		argc = 2;
	}

	wxString name;
	double defVal = 0;
	
	// 1: name
	if( FromJS(cx, argv[0], name ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// 2: defVal
	if( FromJS(cx, argv[1], defVal ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_DOUBLE);
		return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	vp->setDouble( p->GetAttributeAsDouble (name, defVal) );


	return JS_TRUE;
}


JSBool Property::getAttributes(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	const wxPGAttributeStorage &strage = p->GetAttributes();
	wxPGAttributeStorage::const_iterator ite = strage.StartIteration();




	JSObject *objAttr = JS_NewObject(cx, NULL, NULL, NULL);
	JS::RootedObject jsvaArray(cx, objAttr);
	do {
		wxVariant value;
		if( strage.GetNext(ite, value) == false ) {
			break;
		}
		JS::Value element = ToJS(cx, value);
		wxString strName = value.GetName();

		JS_SetUCProperty(cx, objAttr, (const jschar *)strName.c_str(),strName.Length(), &element);

	}while( true );

	
	// APIの実行と戻り値の設定
	vp->setObjectOrNull(objAttr);


	return JS_TRUE;
}


JSBool Property::getCell(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int column = 0;
	double defVal = 0;
	
	// 1: column
	if( FromJS(cx, argv[0], column ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	wxPGCell &cell = p->GetCell(column);
	*vp = Cell::CreateObject(cx, &cell, false);

	return JS_TRUE;
}


JSBool Property::getOrCreateCell(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int column = 0;
	double defVal = 0;
	
	// 1: column
	if( FromJS(cx, argv[0], column ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}



	// APIの実行と戻り値の設定
	wxPGCell &cell = p->GetOrCreateCell(column);
	*vp = Cell::CreateObject(cx, &cell, false);

	return JS_TRUE;
}



JSBool Property::getChildrenHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	if( argc > 2 ) {
		argc = 2;
	}
	int lh = 0;
	int iMax = -1;
	
	// 1: lh
	if( FromJS(cx, argv[0], lh ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	if( argc == 2 ) {
		// 2: iMax
		if( FromJS(cx, argv[1], iMax ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	// APIの実行と戻り値の設定
	vp->setInt32( p->GetChildrenHeight(lh, iMax) );

	return JS_TRUE;
}



JSBool Property::getChoices(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// APIの実行と戻り値の設定
	const wxPGChoices&c  = p->GetChoices();
	*vp = Choices::CreateObject(cx, new wxPGChoices(c), false);

	return JS_TRUE;
}


JSBool Property::getFlagsAsString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int flagsMask = 0;
	
	// 1: flagsMask
	if( FromJS(cx, argv[0], flagsMask ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	*vp = ToJS(cx, p->GetFlagsAsString(flagsMask));

	return JS_TRUE;
}


JSBool Property::getPropertyByName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxString name;
	
	// 1: name
	if( FromJS(cx, argv[0], name ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	wxPGProperty *pParent = p->GetPropertyByName(name);
	if( pParent == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, pParent, NULL);
	}

	return JS_TRUE;
}


JSBool Property::getValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	// APIの実行と戻り値の設定
	*vp = ToJS(cx, p->GetValue());

	return JS_TRUE;
}


JSBool Property::getValueImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	// APIの実行と戻り値の設定
	wxBitmap * pImage = p->GetValueImage();
	if( pImage != NULL ) {
		*vp = Bitmap::CreateObject(cx, new wxBitmap(*pImage), NULL);
	} else {
		vp->setNull();
	}

	return JS_TRUE;
}


JSBool Property::getValueAsString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argFlags=0;
	
	if( argc != 0 ) {
		// 1: argFlags
		if( FromJS(cx, argv[0], argFlags ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	// APIの実行と戻り値の設定
	*vp = ToJS(cx, p->GetValueAsString(argFlags));

	return JS_TRUE;
}


JSBool Property::getImageOffset(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int imageWidth=0;
	
	// 1: imageWidth
	if( FromJS(cx, argv[0], imageWidth ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	*vp = ToJS(cx, p->GetImageOffset(imageWidth));

	return JS_TRUE;
}


JSBool Property::getItemAtY(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	unsigned int y=0;
	
	// 1: imageWidth
	if( FromJS(cx, argv[0], y ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	wxPGProperty *pProp = p->GetItemAtY( y );
	if( pProp != NULL ) {
		*vp = Property::CreateObject(cx, (wxPGProperty*)pProp, NULL);
	} else {
		vp->setUndefined();
	}

	return JS_TRUE;
}


JSBool Property::hasFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int flag=0;
	
	// 1: flag
	if( FromJS(cx, argv[0], flag ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	vp->setBoolean( p->HasFlag((wxPGPropertyFlags)flag));

	return JS_TRUE;
}


JSBool Property::hasFlagsExact(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int flag=0;
	
	// 1: flag
	if( FromJS(cx, argv[0], flag ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	vp->setBoolean( p->HasFlagsExact((wxPGProperty::FlagType)flag));

	return JS_TRUE;
}


JSBool Property::hasVisibleChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	//int flag=0;
	//
	//// 1: flag
	//if( FromJS(cx, argv[0], flag ) ) {
	//	JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
	//	return JS_FALSE;
	//}


	// APIの実行と戻り値の設定
	vp->setBoolean( p->HasVisibleChildren());

	return JS_TRUE;
}


JSBool Property::hide(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	if( argc > 2 ) {
		argc = 2;
	}

	bool hide = false;
	int flags = wxPG_RECURSE;
	
	// 1: hide
	if( FromJS(cx, argv[0], hide ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}
	if( argc == 2 ) {
		// 2: flags
		if( FromJS(cx, argv[1], flags ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}


	// APIの実行と戻り値の設定
	vp->setBoolean( p->Hide(hide, flags));

	return JS_TRUE;
}


JSBool Property::index(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	wxPGProperty *pProp = NULL;
	
	// 1: hide
	pProp = Property::GetPrivate(cx, argv[0]);
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "pg.Property");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	vp->setInt32( p->Index(pProp));

	return JS_TRUE;
}


JSBool Property::insertChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	int index = 0;
	wxPGProperty *childProperty = NULL;
	
	// 1: index
	if( FromJS(cx, argv[0], index ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 2: childProperty
	childProperty = Property::GetPrivate(cx, argv[1]);
	if( childProperty == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "pg.Property");
		return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	wxPGProperty *pProp = p->InsertChild(index, childProperty );
	if( pProp != NULL ) {
		*vp = Property::CreateObject(cx, (wxPGProperty*)pProp, NULL);
	} else {
		vp->setUndefined();
	}

	return JS_TRUE;
}


JSBool Property::insertChoice(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	if( argc > 3 ) {
		argc = 3;
	}

	wxString label;
	int index = 0;
	int value = wxPG_INVALID_VALUE;
	
	// 1: label
	if( FromJS(cx, argv[0], label ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// 2: index
	if( FromJS(cx, argv[1], index ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	if( argc == 3 ) {
		if( FromJS(cx, argv[2], value ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	
	// APIの実行と戻り値の設定
	vp->setInt32( p->InsertChoice(label, index, value ) );

	return JS_TRUE;
}


JSBool Property::isSomeParent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxPGProperty *pProp = NULL;
	wxString label;
	int index = 0;
	int value = wxPG_INVALID_VALUE;
	
	// 1: label
	pProp = Property::GetPrivate(cx, argv[0]);
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "pg.Property");
		return JS_FALSE;
	}

	
	// APIの実行と戻り値の設定
	vp->setBoolean( p->IsSomeParent(pProp ) );

	return JS_TRUE;
}


JSBool Property::item(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	unsigned int i = 0;
	
	// 1: index
	if( FromJS(cx, argv[0], i ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	wxPGProperty *pProp = p->Item(i);
	if( pProp != NULL ) {
		*vp = Property::CreateObject(cx, (wxPGProperty*)pProp, NULL);
	} else {
		vp->setUndefined();
	}

	return JS_TRUE;
}


JSBool Property::recreateEditor(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// APIの実行と戻り値の設定
	vp->setBoolean( p->RecreateEditor() );

	return JS_TRUE;
}


JSBool Property::refreshEditor(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// APIの実行と戻り値の設定
	p->RefreshEditor();

	return JS_TRUE;
}



JSBool Property::setAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxString name;
	wxVariant value;
	
	// 1: index
	if( FromJS(cx, argv[0], name ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// 2: value
	if( FromJS(cx, argv[1], value ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Variant");
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->SetAttribute(name, value);

	return JS_TRUE;
}



JSBool Property::setAutoUnspecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	bool enable=true;
	
	if( argc != 0 ) {
		// 1: enable
		if( FromJS(cx, argv[0], enable ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
			return JS_FALSE;
		}
	}
	
	// APIの実行と戻り値の設定
	p->SetAutoUnspecified(enable);

	return JS_TRUE;
}



JSBool Property::setBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxColour* colour;
	int flags=wxPG_RECURSE;
	
	// 1: enable
	colour = Colour::GetPrivate(cx, argv[0]);
	if( colour == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Color");
		return JS_FALSE;
	}
	if( argc > 2 ) {
		if( FromJS(cx, argv[1], flags ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	
	// APIの実行と戻り値の設定
	p->SetBackgroundColour(*colour, flags);

	return JS_TRUE;
}



JSBool Property::setCell(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int column = 0;
	wxPGCell* cell = NULL;
	
	// 1: column
	if( FromJS(cx, argv[0], column ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 2: cell
	cell = Cell::GetPrivate(cx, argv[1], false);
	if( cell == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "pg.Cell");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetCell(column, *cell);

	return JS_TRUE;
}


JSBool Property::setChoices(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxPGChoices * pChoces = NULL;
	
	// 1: cell
	pChoces = Choices::GetPrivate(cx, argv[0], false);
	if( pChoces == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "pg.Choices");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetChoices(*pChoces);

	return JS_TRUE;
}



JSBool Property::setFlagsFromString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxString str;
	
	// 1: str
	if( FromJS(cx, argv[0], str ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetFlagsFromString(str);

	return JS_TRUE;
}



JSBool Property::setFlagRecursively(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int flag = 0;
	bool set = false;
	
	// 1: flag
	if( FromJS(cx, argv[0], flag ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 2: set
	if( FromJS(cx, argv[1], set ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Boolean");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetFlagRecursively((wxPGPropertyFlags)flag, set);

	return JS_TRUE;
}



JSBool Property::setModifiedStatus(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	bool modified = 0;
	
	// 1: flag
	if( FromJS(cx, argv[0], modified ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetModifiedStatus(modified);

	return JS_TRUE;
}



JSBool Property::setParentalType(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int flag = 0;
	
	// 1: flag
	if( FromJS(cx, argv[0], flag ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetParentalType(flag);

	return JS_TRUE;
}



JSBool Property::setTextColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	if( argc > 2 ) {
		argc = 2;
	}
	 wxColour *colour = NULL;
	 int flags=wxPG_RECURSE;
	
	// 1: colour
	colour = Colour::GetPrivate(cx, argv[0]);
	if( colour == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Color");
		return JS_FALSE;
	}
	
	if( argc == 2 ) {
		// s: flags
		if( FromJS(cx, argv[1], flags ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}


	// APIの実行と戻り値の設定
	p->SetTextColour(*colour,flags );

	return JS_TRUE;
}



JSBool Property::setDefaultColours(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	if( argc > 1) {
		argc = 1;
	}
	
	wxColour *colour = NULL;
	int flags=wxPG_RECURSE;
	
	if( argc == 1 ) {
		// s: flags
		if( FromJS(cx, argv[1], flags ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}
	 
	// APIの実行と戻り値の設定
	p->SetDefaultColours(flags );

	return JS_TRUE;
}


JSBool Property::setValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	if( argc > 3) {
		argc = 3;
	}
	
	wxVariant value;
	wxVariant *pList=NULL;
	wxVariant valianList;
	int flags=wxPG_SETVAL_REFRESH_EDITOR;


	switch( argc ) {
	case 3:
		{
			// 3: flags
			if( FromJS(cx, argv[2], flags ) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
		}
	case 2:
		{			
			// 2: flags
			if( FromJS(cx, argv[1], valianList ) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Variant");
				return JS_FALSE;
			}
			pList = &valianList;
		}	
	}	
	// 1: value
	if( FromJS(cx, argv[0], value ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
		return JS_FALSE;
	}

	 
	// APIの実行と戻り値の設定
	p->SetValue(value, pList, flags );

	return JS_TRUE;
}


JSBool Property::setValueImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;

	// 1: value
	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
		return JS_FALSE;
	}
		 
	// APIの実行と戻り値の設定
	p->SetValueImage(*(apBitmap.get()));

	return JS_TRUE;
}


JSBool Property::setValueInEvent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	wxVariant value;
	
	// 1: value
	if( FromJS(cx, argv[1], value ) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
		return JS_FALSE;
	}

	 
	// APIの実行と戻り値の設定
	p->SetValueInEvent(value);

	return JS_TRUE;
}


JSBool Property::SetValueToUnspecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	 
	// APIの実行と戻り値の設定
	p->SetValueToUnspecified();

	return JS_TRUE;
}


JSBool Property::setWasModified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	bool set=true;
	
	if( argc > 1 ) {
		// 1: value
		if( FromJS(cx, argv[1], set ) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
			return JS_FALSE;
		}
	}

	 
	// APIの実行と戻り値の設定
	p->SetWasModified (set);

	return JS_TRUE;
}


JSBool Property::updateParentValues(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	 
	// APIの実行と戻り値の設定
	wxPGProperty *pProp = p->UpdateParentValues();
	if( pProp == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, pProp);
	}
	return JS_TRUE;
}


JSBool Property::usesAutoUnspecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGProperty *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	 
	// APIの実行と戻り値の設定
	vp->setBoolean( p->UsesAutoUnspecified() );

	return JS_TRUE;
}










