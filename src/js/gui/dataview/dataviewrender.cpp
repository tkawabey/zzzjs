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
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/rect.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/validate.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewrender.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"
#include "js/gui/dataview/dataviewcolmn.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewRenderer
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewRenderer, "DataViewRenderer", 0)

void DataViewRenderer::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{
}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewRenderer)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewRenderer)
  WXJS_PROPERTY(P_Alignment, "alignment")
  WXJS_PROPERTY(P_EllipsizeMode, "ellipsizeMode")
  WXJS_PROPERTY(P_Mode, "mode")
  WXJS_PROPERTY(P_Owner, "owner")
  WXJS_PROPERTY(P_VALUE, "value")
  WXJS_PROPERTY(P_VariantType, "variantType")
  WXJS_PROPERTY(P_HasEditorCtrl, "hasEditorCtrl")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewRenderer, DataViewRenderer)
	switch (id) 
	{
	case P_Alignment:
		ToJSVal(cx, vp, p->GetAlignment());
		break;
	case P_EllipsizeMode:
		ToJSVal(cx, vp, (int)p->GetEllipsizeMode ());
		break;
	case P_Mode:
		ToJSVal(cx, vp, (int)p->GetMode ());
		break;
	case P_Owner:
		{
			vp.set( DataViewColumn::CreateObject(cx, p->GetOwner()) );
		}
		break;
	case P_VALUE:
		{
			wxVariant  val;
			if( p->GetValue( val ) ) {
				jsval jsval;
				ConvertWxVariant2Js(cx, val, jsval);
				vp.set( jsval );
			}
			vp.set( DataViewColumn::CreateObject(cx, p->GetOwner()) );
		}
		break;
	case P_VariantType:
		ToJSVal(cx, vp, p->GetVariantType  ());
		break;
	case P_HasEditorCtrl:
		ToJSVal(cx, vp, p->HasEditorCtrl ());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDataViewRenderer, DataViewRenderer)
	switch (id) 
	{
	case P_Alignment:
		{
			int value = 0;
			if ( FromJS(cx, vp, value) )
			{
				p->SetAlignment(value);
			}	
		}
		break;
	case P_Owner:
		{
			wxDataViewColumn* pColmn = 
				DataViewColumn::GetPrivate(cx, vp);
			if( pColmn == NULL ) {

				return JS_FALSE;
			}
			p->SetOwner( pColmn );
		}
		break;
	case P_VALUE:
		{
			wxVariant  val;
			jsval jsval = vp;
			ConvertJs2WxVariant(cx, jsval, val);
			p->SetValue(val);
		}
		break;
	}
	return true;
WXJS_END_SET_PROP

WXJS_BEGIN_ADD_PROP(wxDataViewRenderer, DataViewRenderer)
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewRenderer, DataViewRenderer)
  return true;
WXJS_END_DEL_PROP



WXJS_BEGIN_METHOD_MAP(DataViewRenderer)
	WXJS_METHOD("setValueAdjuster", setValueAdjuster, 1)
	WXJS_METHOD("validate", validate, 1)
	WXJS_METHOD("createEditorCtrl", createEditorCtrl, 3)
	WXJS_METHOD("getValueFromEditorCtrl", getValueFromEditorCtrl, 1)
	WXJS_METHOD("startEditing", startEditing, 2)
	WXJS_METHOD("cancelEditing", cancelEditing, 0)
	WXJS_METHOD("getEditorCtrl", getEditorCtrl, 0)
WXJS_END_METHOD_MAP()


JSBool DataViewRenderer::setValueAdjuster(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	//int mode = wxELLIPSIZE_MIDDLE;

	//if( argc >= 1 ) {
	//	// 1.
	//	if ( ! FromJS(cx, argv[0], mode) )
	//	{
	//		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
	//		return JS_FALSE;
	//	}
	//}
	//
	//// 戻り値
	//p->EnableEllipsize((wxEllipsizeMode)mode);
	
	return JS_TRUE;
}

JSBool DataViewRenderer::validate(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxVariant value;
	if( ConvertJs2WxVariant(cx, *vp, value) == false ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->Validate(value)		
	);
	
	return JS_TRUE;
}

JSBool DataViewRenderer::createEditorCtrl(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxWindow	*parent = NULL;
	zzzJsPtr<wxRect> apRect;
	wxVariant	value;

	parent = Window::GetPrivate(cx, argv[0]);
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[1])) == true )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, Rect::getClassName());
		return JS_FALSE;
	}
	if ( ! FromJS(cx, argv[2], value) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	// 戻り値
	wxWindow* pNewWindow = p->CreateEditorCtrl(parent, *(apRect.get()), value);
	if( pNewWindow != NULL ) {
		*vp = Window::CreateObject(cx, pNewWindow);
	} else {
		*vp = JSVAL_VOID;
	}

	return JS_TRUE;
}

JSBool DataViewRenderer::getValueFromEditorCtrl(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxWindow	*parent = NULL;
	wxVariant	value;

	parent = Window::GetPrivate(cx, argv[0]);

	
	// 戻り値
	if( p->GetValueFromEditorCtrl( parent, value) == true ) {
		*vp = ToJS(cx, value);
	} else {
		*vp = JSVAL_VOID;
	}

	return JS_TRUE;
}

JSBool DataViewRenderer::startEditing(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem	*pItem = NULL;
	zzzJsPtr<wxRect> apRect;

	pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
//	if( FromJS(cx, argv[1], rect) == false)
	if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[1])) == false )
	{
		return JS_FALSE;
	}
	
	// 戻り値
	vp->setBoolean(
		p->StartEditing(*pItem, *(apRect.get()) )	
	);

	return JS_TRUE;
}

JSBool DataViewRenderer::cancelEditing(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	
	// 戻り値
	p->CancelEditing();

	return JS_TRUE;
}

JSBool DataViewRenderer::finishEditing(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	
	// 戻り値
	vp->setBoolean(
		p->FinishEditing()
	);
	

	return JS_TRUE;
}

JSBool DataViewRenderer::getEditorCtrl(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewRenderer *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	
	// 戻り値
	*vp = Window::CreateObject(cx, p->GetEditorCtrl() );

	return JS_TRUE;
}


