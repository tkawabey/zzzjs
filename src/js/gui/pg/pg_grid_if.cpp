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
#include "js/gui/errors.h"
#include "js/gui/pg/pg_grid_if.h"
#include "js/gui/pg/pg_arg_id.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_prop_category.h"
#include "js/gui/pg/pg_editor.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/validate.h"



using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	GridInterface
//--------------------------------------------------------
WXJS_INIT_CLASS(GridInterface, "GridInterface", 0)
	
// プロパティー
WXJS_BEGIN_PROPERTY_MAP(GridInterface)
  WXJS_READONLY_PROPERTY(P_SELECTED_PROPERTY, "selectedProperty")
  WXJS_READONLY_PROPERTY(P_SELECTION, "selection")
WXJS_END_PROPERTY_MAP()

// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPropertyGridInterface, GridInterface)
	switch (id) 
	{
	case P_SELECTED_PROPERTY:
		{
			JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
			JS::RootedObject jsvaArray(cx, objArray);
			const wxArrayPGProperty & ar = p->GetSelectedProperties();
			for(size_t i = 0; i < ar.GetCount(); i++ ) {
				wxPGProperty* prop = ar.Item( i );
				JS::Value element = Property::CreateObject(cx, prop, NULL);
				JS_SetElement(cx, objArray, i, &element);
			}
			vp.setObjectOrNull(objArray);
		}
		break;
	case P_SELECTION:
		{
			wxPGProperty *pProp =  p->GetSelection();
			if( pProp == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pProp, NULL) );
			}
		}
		break;
	}
	return true;
WXJS_END_GET_PROP

// プロパティー set の実装
WXJS_BEGIN_SET_PROP(wxPropertyGridInterface, GridInterface)
	return true;
WXJS_END_SET_PROP

// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPropertyGridInterface, GridInterface)

	JS_ReportError(cx, "GridInterface is abstruct class");
	
	return NULL;
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxPropertyGridInterface, GridInterface)

WXJS_END_DESTRUCTOR
	


// メソッドの定義
WXJS_BEGIN_METHOD_MAP(GridInterface)
	WXJS_METHOD("append", append, 1 )
	WXJS_METHOD("appendIn", appendIn, 2 )
	WXJS_METHOD("beginAddChildren", beginAddChildren, 1 )
	WXJS_METHOD("clear", clear, 0 )
	WXJS_METHOD("clearSelection", clearSelection, 0 )
	WXJS_METHOD("clearModifiedStatus", clearModifiedStatus, 0 )
	WXJS_METHOD("collapse", collapse, 1 )
	WXJS_METHOD("collapseAll", collapseAll, 0 )
	WXJS_METHOD("changePropertyValue", changePropertyValue, 2 )
	WXJS_METHOD("deleteProperty", deleteProperty, 1 )
	WXJS_METHOD("disableProperty", disableProperty, 1 )
	WXJS_METHOD("editorValidate", editorValidate, 0 )
	WXJS_METHOD("enableProperty", enableProperty, 1 )
	WXJS_METHOD("endAddChildren", endAddChildren, 1 )
	WXJS_METHOD("expand", expand, 1 )
	WXJS_METHOD("expandAll", expandAll, 0 )
	WXJS_METHOD("getColumnProportion", getColumnProportion, 1 )
	WXJS_METHOD("getFirstChild", getFirstChild, 1 )
	WXJS_METHOD("getProperty", getProperty, 1 )
	WXJS_METHOD("getPropertyAttribute", getPropertyAttribute, 2 )
	WXJS_METHOD("getPropertyBackgroundColour", getPropertyBackgroundColour, 1 )
	WXJS_METHOD("getPropertyCategory", getPropertyCategory, 1 )
	WXJS_METHOD("getPropertyByLabel", getPropertyByLabel, 1 )
	WXJS_METHOD("getPropertyByName", getPropertyByName, 1 )
	WXJS_METHOD("getPropertyEditor", getPropertyEditor, 1 )
	WXJS_METHOD("getPropertyHelpString", getPropertyHelpString, 1 )
	WXJS_METHOD("getPropertyImage", getPropertyImage, 1 )
	WXJS_METHOD("getPropertyLabel", getPropertyLabel, 1 )
	WXJS_METHOD("getPropertyName", getPropertyName, 1 )
	WXJS_METHOD("getPropertyParent", getPropertyParent, 1 )
	WXJS_METHOD("getPropertyTextColour", getPropertyTextColour, 1 )
	WXJS_METHOD("getPropertyValidator", getPropertyValidator, 1 )
	WXJS_METHOD("getPropertyValue", getPropertyValue, 1 )
	WXJS_METHOD("getPropertyValueAsArrayInt", getPropertyValueAsArrayInt, 1 )
	WXJS_METHOD("getPropertyValueAsArrayString", getPropertyValueAsArrayString, 1 )
	WXJS_METHOD("getPropertyValueAsBool", getPropertyValueAsBool, 1 )
	WXJS_METHOD("getPropertyValueAsDateTime", getPropertyValueAsDateTime, 1 )
	WXJS_METHOD("getPropertyValueAsDouble", getPropertyValueAsDouble, 1 )
	WXJS_METHOD("getPropertyValueAsInt", getPropertyValueAsInt, 1 )
	WXJS_METHOD("getPropertyValueAsLong", getPropertyValueAsLong, 1 )
	WXJS_METHOD("getPropertyValueAsString", getPropertyValueAsString, 1 )
	WXJS_METHOD("getPropertyValueAsULong", getPropertyValueAsULong, 1 )
	WXJS_METHOD("getPropertyValues", getPropertyValues, 1 )
	WXJS_METHOD("hideProperty", hideProperty, 1 )
	WXJS_METHOD("insert", insert, 2 )
	WXJS_METHOD("isPropertyCategory", isPropertyCategory, 1 )
	WXJS_METHOD("isPropertyEnabled", isPropertyEnabled, 1 )
	WXJS_METHOD("isPropertyExpanded", isPropertyExpanded, 1 )
	WXJS_METHOD("isPropertyModified", isPropertyModified, 1 )
	WXJS_METHOD("isPropertySelected", isPropertySelected, 1 )
	WXJS_METHOD("isPropertyShown", isPropertyShown, 1 )
	WXJS_METHOD("isPropertyValueUnspecified", isPropertyValueUnspecified, 1 )
	WXJS_METHOD("limitPropertyEditing", limitPropertyEditing, 1 )
	WXJS_METHOD("removeProperty", removeProperty, 1 )
	WXJS_METHOD("replaceProperty", replaceProperty, 2 )
	WXJS_METHOD("restoreEditableState", restoreEditableState, 1 )
	WXJS_METHOD("saveEditableState", saveEditableState, 0 )
	WXJS_METHOD("setColumnProportion", setColumnProportion, 2 )
	WXJS_METHOD("setPropertyAttribute", setPropertyAttribute, 3 )
	WXJS_METHOD("setPropertyAttributeAll", setPropertyAttributeAll, 2 )
	WXJS_METHOD("setPropertyBackgroundColour", setPropertyBackgroundColour, 2 )
	WXJS_METHOD("setPropertyCell", setPropertyCell, 2 )
	WXJS_METHOD("setPropertyColoursToDefault", setPropertyColoursToDefault, 1 )
	WXJS_METHOD("setPropertyEditor", setPropertyEditor, 2 )
	WXJS_METHOD("setPropertyLabel", setPropertyLabel, 2 )
	WXJS_METHOD("setPropertyName", setPropertyName, 2 )
	WXJS_METHOD("setPropertyReadOnly", setPropertyReadOnly, 1 )
	WXJS_METHOD("setPropertyValueUnspecified", setPropertyValueUnspecified, 1 )
	WXJS_METHOD("setPropertyHelpString", setPropertyHelpString, 2 )
	WXJS_METHOD("setPropertyImage", setPropertyImage, 2 )
	WXJS_METHOD("setPropertyMaxLength", setPropertyMaxLength, 2 )
	WXJS_METHOD("setPropertyTextColour", setPropertyTextColour, 2 )
	WXJS_METHOD("setPropertyValidator", setPropertyValidator, 2 )
	WXJS_METHOD("setPropertyValue", setPropertyValue, 2 )
	WXJS_METHOD("setPropertyValueString", setPropertyValueString, 2 )
	WXJS_METHOD("setPropVal", setPropVal, 2 )
	WXJS_METHOD("setValidationFailureBehavior", setValidationFailureBehavior, 1 )
	WXJS_METHOD("sort", sort, 0 )
	WXJS_METHOD("sortChildren", sortChildren, 1 )
	WXJS_METHOD("refreshProperty", refreshProperty, 1)

WXJS_END_METHOD_MAP()

JSBool GridInterface::append(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;

	return GridInterface::impl_append(cx, argc, vp, p);
}

JSBool GridInterface::impl_append(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxPGProperty* pProp = Property::GetPrivate(cx, argv[0], false);
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "pg.Property");
		return JS_FALSE;
	}
	// APIの実行と戻り値の設定
	wxPGProperty *pRet = p->Append(pProp);
	if( pRet != NULL ) {
		*vp = Property::CreateObject(cx, pRet, NULL);
	} else {
		vp->setNull();
	}

	return JS_TRUE;
}



JSBool GridInterface::appendIn(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	
	return GridInterface::impl_appendIn(cx, argc, vp, p);
}
JSBool GridInterface::impl_appendIn(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int argIndex = 0;
	GridInterface_ArgID	argId;
	// 0:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// 1: 
	argIndex++;
	wxPGProperty* pProp = Property::GetPrivate(cx, argv[argIndex], false);
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	wxPGProperty *pRet = p->AppendIn( argId.get(), pProp );

	if( pRet != NULL ) {
		*vp = Property::CreateObject(cx, pRet, NULL);
	} else {
		vp->setNull();
	}

	return JS_TRUE;
}



JSBool GridInterface::beginAddChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	
	return GridInterface::impl_beginAddChildren(cx, argc, vp, p);
}
JSBool GridInterface::impl_beginAddChildren(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int argIndex = 0;
	GridInterface_ArgID	argId;
	// 0:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	p->BeginAddChildren( argId.get() );


	return JS_TRUE;
}
JSBool GridInterface::clear(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;

	
	return GridInterface::impl_clear(cx, argc, vp, p);
}
JSBool GridInterface::impl_clear(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// APIの実行
	p->Clear();

	return JS_TRUE;
}

JSBool GridInterface::clearSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	
	return GridInterface::impl_clearSelection(cx, argc, vp, p);
}
JSBool GridInterface::impl_clearSelection(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int argIndex = 0;
	bool bVal = false;

	if( argc != 0 ) {
		// 1:
		if( FromJS(cx, argv[argIndex], bVal) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return false;
		}
	}

	// APIの実行
	p->ClearSelection(bVal);


	return JS_TRUE;
}

JSBool GridInterface::clearModifiedStatus(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
		
	return GridInterface::impl_clearModifiedStatus(cx, argc, vp, p);
}
JSBool GridInterface::impl_clearModifiedStatus(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// APIの実行
	p->ClearModifiedStatus();


	return JS_TRUE;
}

JSBool GridInterface::collapse(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	
	return GridInterface::impl_clearModifiedStatus(cx, argc, vp, p);
}
JSBool GridInterface::impl_collapse(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int argIndex = 0;
	GridInterface_ArgID	argId;
	// 0:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}

	// APIの実行
	vp->setBoolean( p->Collapse(argId.get()) );


	return JS_TRUE;
}


JSBool GridInterface::collapseAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_collapseAll(cx, argc, vp, p);
}
JSBool GridInterface::impl_collapseAll(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	// APIの実行
	vp->setBoolean( p->CollapseAll() );


	return JS_TRUE;
}



JSBool GridInterface::changePropertyValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_changePropertyValue(cx, argc, vp, p);
}
JSBool GridInterface::impl_changePropertyValue(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxVariant			value;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// 2:
	argIndex++;
	if( FromJS(cx, argv[argIndex], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}

	// APIの実行
	vp->setBoolean( p->ChangePropertyValue(argId.get(), value ) );


	return JS_TRUE;
}



JSBool GridInterface::deleteProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_deleteProperty(cx, argc, vp, p);
}
JSBool GridInterface::impl_deleteProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	p->DeleteProperty( argId.get() );


	return JS_TRUE;
}



JSBool GridInterface::disableProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_disableProperty(cx, argc, vp, p);
}
JSBool GridInterface::impl_disableProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	vp->setBoolean(p->DisableProperty( argId.get() ) );


	return JS_TRUE;
}



JSBool GridInterface::editorValidate(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_editorValidate(cx, argc, vp, p);
}
JSBool GridInterface::impl_editorValidate(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// APIの実行
	vp->setBoolean(p->EditorValidate());


	return JS_TRUE;
}



JSBool GridInterface::enableProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_enableProperty(cx, argc, vp, p);
}
JSBool  GridInterface::impl_enableProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	bool enable=true;


	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// 2:
	argIndex++;
	if( FromJS(cx, argv[argIndex], enable) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}


	// APIの実行
	vp->setBoolean(p->EnableProperty( argId.get(), enable ) );


	return JS_TRUE;
}



JSBool GridInterface::endAddChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_endAddChildren(cx, argc, vp, p);
}
JSBool  GridInterface::impl_endAddChildren(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int argIndex = 0;
	GridInterface_ArgID	argId;

	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	p->EndAddChildren( argId.get() );


	return JS_TRUE;
}


JSBool GridInterface::expand(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_expand(cx, argc, vp, p);
}
JSBool  GridInterface::impl_expand(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	GridInterface_ArgID	argId;

	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	vp->setBoolean( p->Expand( argId.get() ) );


	return JS_TRUE;
}



JSBool GridInterface::expandAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_expandAll(cx, argc, vp, p);
}
JSBool  GridInterface::impl_expandAll(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	bool expand=true;

	// 1:
	if( FromJS(cx, argv[argIndex], expand) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
		return false;
	}


	// APIの実行
	vp->setBoolean( p->Expand( expand ) );


	return JS_TRUE;
}



JSBool GridInterface::getColumnProportion(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getColumnProportion(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getColumnProportion(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	unsigned int column=0;

	// 1:
	if( FromJS(cx, argv[argIndex], column) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return false;
	}


	// APIの実行
	vp->setInt32( p->GetColumnProportion( column ) );


	return JS_TRUE;
}



JSBool GridInterface::getFirstChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getFirstChild(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getFirstChild(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	GridInterface_ArgID	argId;

	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	wxPGProperty *pRet = p->GetFirstChild( argId.get() );
	if( pRet == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, pRet, NULL);
	}


	return JS_TRUE;
}


JSBool GridInterface::getProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getProperty(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxString name;

	// 1:
	if( FromJS(cx, argv[argIndex], name) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}



	// APIの実行
	wxPGProperty *pRet = p->GetProperty( name );
	if( pRet == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, pRet, NULL);
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyAttribute(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyAttribute(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxString name;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// 2:
	argIndex++;
	if( FromJS(cx, argv[argIndex], name) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}



	// APIの実行
	wxVariant 	ret = p->GetPropertyAttribute( argId.get(), name );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}



JSBool GridInterface::getPropertyBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyBackgroundColour(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}



	// APIの実行
	wxColour 	ret = p->GetPropertyBackgroundColour( argId.get() );
	*vp = Colour::CreateObject(cx, new wxColour(ret));

	return JS_TRUE;
}



JSBool GridInterface::getPropertyCategory(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyCategory(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyCategory(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}



	// APIの実行
	wxPropertyCategory * 	ret = p->GetPropertyCategory( argId.get() );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = PropertyCategory::CreateObject(cx, ret, NULL);
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyByLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyByLabel(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyByLabel(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	wxString label;
	
	// 1:
	if( FromJS(cx, argv[argIndex], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}



	// APIの実行
	wxPGProperty  * 	ret = p->GetPropertyByLabel( label );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, ret, NULL);
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyByName(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyByName(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyByName(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxString name;
	wxString subName;
	
	// 1:
	if( FromJS(cx, argv[argIndex], name) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	if( argc >= 2 ) {
		argIndex++;
		// 1:
		if( FromJS(cx, argv[argIndex], subName) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return false;
		}
	}


	// APIの実行
	wxPGProperty  * 	ret = NULL;
	if( argc >= 2 ) {
		ret = p->GetPropertyByName( name, subName );
	} else {
		ret = p->GetPropertyByName( name );
	}
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, ret, NULL);
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyEditor(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyEditor(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyEditor(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}



	// APIの実行
	const wxPGEditor* pRet = p->GetPropertyEditor(argId.get());
	if( pRet == NULL ) {
		vp->setNull();
	} else {
		*vp = Editor::CreateObject(cx, (wxPGEditor*)pRet, NULL);
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyHelpString(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyHelpString(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyHelpString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}



	// APIの実行
	wxString ret = p->GetPropertyHelpString( argId.get() );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}




JSBool GridInterface::getPropertyImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyImage(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyImage(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}



	// APIの実行
	wxBitmap * ret = p->GetPropertyImage( argId.get() );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Bitmap::CreateObject( cx, new wxBitmap(*ret));
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyLabel(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyLabel(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}



	// APIの実行
	wxString ret = p->GetPropertyLabel( argId.get() );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyName(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyName(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyName(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxString ret = p->GetPropertyName( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyParent(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyParent(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyParent(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxPGProperty  * 	ret = p->GetPropertyParent( pProp );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, ret, NULL);
	}

	return JS_TRUE;
}



JSBool GridInterface::getPropertyTextColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyTextColour(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyTextColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxColour ret = p->GetPropertyTextColour ( pProp );
	*vp = Colour::CreateObject(cx, new wxColour(ret), NULL);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValidator(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValidator(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyValidator(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxValidator * ret = p->GetPropertyValidator ( pProp );



	*vp = Validator::CreateObject(cx, new wxValidator(*ret), NULL);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValue(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyValue(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxVariant ret = p->GetPropertyValue( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValueAsArrayInt(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsArrayInt(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyValueAsArrayInt(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxArrayInt 	ret = p->GetPropertyValueAsArrayInt( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValueAsArrayString(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsArrayString(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyValueAsArrayString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxArrayString ret = p->GetPropertyValueAsArrayString( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValueAsBool(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsBool(cx, argc, vp, p);
}
JSBool  GridInterface::impl_getPropertyValueAsBool(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	bool ret = p->GetPropertyValueAsBool( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValueAsDateTime(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsDateTime(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValueAsDateTime(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxDateTime ret = p->GetPropertyValueAsDateTime( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValueAsDouble(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsDouble(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValueAsDouble(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	double  ret = p->GetPropertyValueAsDouble( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}


JSBool GridInterface::getPropertyValueAsInt(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsInt(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValueAsInt(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	int ret = p->GetPropertyValueAsInt( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}



JSBool GridInterface::getPropertyValueAsLong(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsLong(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValueAsLong(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	long  ret = p->GetPropertyValueAsLong( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}



JSBool GridInterface::getPropertyValueAsString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsString(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValueAsString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	wxString ret = p->GetPropertyValueAsString( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}






JSBool GridInterface::getPropertyValueAsULong(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValueAsULong(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValueAsULong(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;
	
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}



	// APIの実行
	unsigned long ret = p->GetPropertyValueAsULong( pProp );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}



JSBool GridInterface::getPropertyValues(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_getPropertyValues(cx, argc, vp, p);
}
JSBool     GridInterface::impl_getPropertyValues(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	wxString listname=wxEmptyString;;
	wxPGProperty *baseparent=NULL;
	long flags=0;
	
	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	 case 2:
		baseparent = Property::GetPrivate(cx, argv[argIndex]);
		if( baseparent == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
			return false;
		}
		argIndex--;
	 case 1:
		if( FromJS(cx, argv[argIndex], listname) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return false;
		}
		argIndex--;

	}

	// APIの実行
	wxVariant  ret = p->GetPropertyValues( listname, baseparent, flags );
	*vp = ToJS(cx, ret);

	return JS_TRUE;
}



JSBool GridInterface::hideProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_hideProperty(cx, argc, vp, p);
}
JSBool     GridInterface::impl_hideProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	bool hide=true;
	int flags=wxPG_RECURSE;
	GridInterface_ArgID	argId;
	
	


	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	 case 2:
		if( FromJS(cx, argv[argIndex], hide) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return false;
		}
		argIndex--;
	}
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行
	vp->setBoolean( p->HideProperty( argId.get(), hide, flags ) );

	return JS_TRUE;
}


JSBool GridInterface::insert(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_insert(cx, argc, vp, p);
}
JSBool     GridInterface::impl_insert(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxPGProperty *newProperty = NULL;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	newProperty = Property::GetPrivate( cx, argv[argIndex], false);
	if( newProperty == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}

	// APIの実行
	wxPGProperty* ret =  p->Insert( argId.get(), newProperty );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, ret, NULL);
	}
	return JS_TRUE;
}


JSBool GridInterface::isPropertyCategory(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertyCategory(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertyCategory(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertyCategory( argId.get() ) );
	return JS_TRUE;
}


JSBool GridInterface::isPropertyEnabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertyEnabled(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertyEnabled(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertyEnabled( argId.get() ) );
	return JS_TRUE;
}


JSBool GridInterface::isPropertyExpanded(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertyExpanded(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertyExpanded(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertyExpanded( argId.get() ) );
	return JS_TRUE;
}


JSBool GridInterface::isPropertyModified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertyModified(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertyModified(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertyModified( argId.get() ) );
	return JS_TRUE;
}


JSBool GridInterface::isPropertySelected(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertySelected(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertySelected(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertySelected( argId.get() ) );
	return JS_TRUE;
}



JSBool GridInterface::isPropertyShown(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertyShown(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertyShown(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertyShown( argId.get() ) );
	return JS_TRUE;
}



JSBool GridInterface::isPropertyValueUnspecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_isPropertyValueUnspecified(cx, argc, vp, p);
}
JSBool     GridInterface::impl_isPropertyValueUnspecified(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	vp->setBoolean( p->IsPropertyValueUnspecified( argId.get() ) );
	return JS_TRUE;
}



JSBool GridInterface::limitPropertyEditing(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_limitPropertyEditing(cx, argc, vp, p);
}
JSBool     GridInterface::impl_limitPropertyEditing(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	if( argc > 2 ) {
		argc = 2;
	}
	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	bool limit=true;
	
	argIndex = argc-1;
	switch( argc ) {
	 case 2:
		if( FromJS(cx, argv[argIndex], limit) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return false;
		}
		argIndex--;
	}
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	p->LimitPropertyEditing( argId.get(), limit );

	return JS_TRUE;
}



JSBool GridInterface::removeProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_removeProperty(cx, argc, vp, p);
}
JSBool     GridInterface::impl_removeProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	// APIの実行
	wxPGProperty* ret = p->RemoveProperty( argId.get() );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, ret);
	}
	return JS_TRUE;
}


JSBool GridInterface::replaceProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_replaceProperty(cx, argc, vp, p);
}
JSBool     GridInterface::impl_replaceProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);



	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxPGProperty *pProp = NULL;


	// 1:
	argIndex = 0;
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	pProp = Property::GetPrivate(cx, argv[argIndex], false);
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}

	// APIの実行
	wxPGProperty* ret = p->ReplaceProperty( argId.get(), pProp );
	if( ret == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, ret);
	}
	return JS_TRUE;
}


JSBool GridInterface::restoreEditableState(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_restoreEditableState(cx, argc, vp, p);
}
JSBool     GridInterface::impl_restoreEditableState(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	wxString src;
	int restoreStates=wxPropertyGridInterface::AllStates;
	
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	 case 2:
		if( FromJS(cx, argv[argIndex], restoreStates) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	}
	// 1:
	argIndex = 0;
	if( FromJS(cx, argv[argIndex], src) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}


	// APIの実行
	vp->setBoolean( p->RestoreEditableState( src, restoreStates ) );

	return JS_TRUE;
}


JSBool GridInterface::saveEditableState(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_saveEditableState(cx, argc, vp, p);
}
JSBool     GridInterface::impl_saveEditableState(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	int restoreStates=wxPropertyGridInterface::AllStates;
	
	
	// 1:
	argIndex = 0;
	if( FromJS(cx, argv[argIndex], restoreStates) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}


	// APIの実行
	*vp = ToJS(cx, p->SaveEditableState( restoreStates ));

	return JS_TRUE;
}


JSBool GridInterface::setColumnProportion(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setColumnProportion(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setColumnProportion(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	unsigned int column = 0;
	int proportion = 0;
	
	
	// 1:
	argIndex = 0;
	if( FromJS(cx, argv[argIndex], column) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return false;
	}
	argIndex++;
	// 1:
	if( FromJS(cx, argv[argIndex], proportion) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return false;
	}


	// APIの実行
	*vp = ToJS(cx, p->SetColumnProportion( column, proportion ));

	return JS_TRUE;
}


JSBool GridInterface::setPropertyAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyAttribute(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyAttribute(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxString attrName;
	wxVariant value;
	long argFlags=0;
	
	if( argc > 4 ) {
		argc = 4;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 4:
		if( FromJS(cx, argv[argIndex], argFlags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], attrName) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;
	// 3:
	if( FromJS(cx, argv[argIndex], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}


	// APIの実行
	p->SetPropertyAttribute( argId.get(), attrName, value, argFlags );

	return JS_TRUE;
}


JSBool GridInterface::setPropertyAttributeAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyAttributeAll(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyAttributeAll(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	wxString attrName;
	wxVariant value;
	
	argIndex = 0;
	// 1:
	if( FromJS(cx, argv[argIndex], attrName) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}


	// APIの実行
	p->SetPropertyAttributeAll( attrName, value );

	return JS_TRUE;
}


JSBool GridInterface::setPropertyBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyBackgroundColour(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	wxString attrName;
	wxColour *colour = NULL;
	int flags=wxPG_RECURSE;
	
	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 4:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	}



	argIndex = 0;
	// 1:
	if( FromJS(cx, argv[argIndex], attrName) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;
	// 2:
	colour = Colour::GetPrivate(cx, argv[argIndex], false);
	if( colour == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Colour");
		return false;
	}


	// APIの実行
	p->SetPropertyBackgroundColour( attrName, *colour, flags );

	return JS_TRUE;
}




JSBool GridInterface::setPropertyCell(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyCell(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyCell(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	int column;
	wxString text=wxEmptyString;
	wxBitmap bitmap=wxNullBitmap;
	wxColour fgCol=wxNullColour;
	wxColour bgCol=wxNullColour;
	
	if( argc > 6 ) {
		argc = 6;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 6:
		{
			wxColour* pColor = Colour::GetPrivate(cx, argv[argIndex], false);
			if( pColor == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Colour");
				return false;
			}
			bgCol = *pColor;
		}
		argIndex--;
	case 5:
		{
			wxColour* pColor = Colour::GetPrivate(cx, argv[argIndex], false);
			if( pColor == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Colour");
				return false;
			}
			fgCol = *pColor;
		}
		argIndex--;
	case 4:
		{
			zzzJsPtr<wxBitmap> apBitmap;
			if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
				return false;
			}
			bitmap = *(apBitmap.get());
		}
		argIndex--;
	case 3:
		if( FromJS(cx, argv[argIndex], text) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return false;
		}
		argIndex--;
	}



	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], column) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return false;
	}


	// APIの実行
	p->SetPropertyCell(argId.get(), column, text, bitmap, fgCol, bgCol  );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyColoursToDefault(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyColoursToDefault(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyColoursToDefault(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	int flags=wxPG_DONT_RECURSE;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return false;
		}
		argIndex--;
	}



	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;


	// APIの実行
	p->SetPropertyColoursToDefault(argId.get(), flags );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyEditor(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyColoursToDefault(cx, argc, vp, p);
}
#include <wx/propgrid/advprops.h>
JSBool     GridInterface::impl_setPropertyEditor(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxString strLabel(_T(""));
	wxPGEditor *editor = NULL;


	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;

	// 2:
	if( argv[argIndex].isString() ) {
		
		if( FromJS(cx, argv[argIndex], strLabel) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return false;
		}
	} else {
		editor = Editor::GetPrivate(cx, argv[argIndex], false);
		if( editor == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Editor");
			return false;
		}
	}


	// APIの実行
	if( editor == NULL ) {
		p->SetPropertyEditor(argId.get(), strLabel );
	} else {
		p->SetPropertyEditor(argId.get(), editor );
	}

	return JS_TRUE;
}


JSBool GridInterface::setPropertyLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyLabel(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyLabel(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxString newproplabel;
	




	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], newproplabel) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}

	// APIの実行
	p->SetPropertyLabel(argId.get(), newproplabel );

	return JS_TRUE;
}




JSBool GridInterface::setPropertyName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyName(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyName(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxString newproplabel;
	




	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], newproplabel) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}

	// APIの実行
	p->SetPropertyName(argId.get(), newproplabel );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyReadOnly(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyReadOnly(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyReadOnly(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	bool set=true;
	int flags=wxPG_RECURSE;
	


	
	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	case 2:
		if( FromJS(cx, argv[argIndex], set) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolena");
			return false;
		}
		argIndex--;
	}

	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyReadOnly(argId.get(), set, flags  );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyValueUnspecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyValueUnspecified(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyValueUnspecified(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	



	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyValueUnspecified(argId.get() );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyHelpString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyHelpString(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyHelpString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxString helpString;



	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], helpString) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyHelpString(argId.get(), helpString );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyImage(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyImage(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	zzzJsPtr<wxBitmap> apBitmap;

	
	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
		return false;
	}

	// APIの実行
	p->SetPropertyImage(argId.get(), *(apBitmap.get()));

	return JS_TRUE;
}



JSBool GridInterface::setPropertyMaxLength(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyMaxLength(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyMaxLength(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	 int maxLen = 0;

	
	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], maxLen) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyMaxLength(argId.get(), maxLen);

	return JS_TRUE;
}



JSBool GridInterface::setPropertyTextColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyTextColour(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyTextColour(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxColour* colour = NULL;
	int flags=wxPG_RECURSE;

	
	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex--;
	case 2:
		colour = Colour::GetPrivate(cx, argv[argIndex], false);
		if( colour == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Colour");
			return false;
		}
		argIndex--;
	}

	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyTextColour(argId.get(), *colour, flags );

	return JS_TRUE;
}



JSBool GridInterface::setPropertyValidator(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyValidator(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyValidator(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxValidator * validator = NULL;


	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	validator = Validator::GetPrivate(cx, argv[argIndex], false);
	if( validator == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Validator");
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyValidator(argId.get(), *validator);

	return JS_TRUE;
}





JSBool GridInterface::setPropertyValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyValue(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyValue(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxVariant v;


	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], v) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyValue(argId.get(), v);

	return JS_TRUE;
}

JSBool GridInterface::setPropertyValueString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropertyValueString(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropertyValueString(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxString v;


	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], v) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetPropertyValueString(argId.get(), v);


	return JS_TRUE;
}



JSBool GridInterface::setPropVal(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setPropVal(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setPropVal(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxVariant v;


	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2:
	if( FromJS(cx, argv[argIndex], v) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetPropVal(argId.get(), v);

	return JS_TRUE;
}



JSBool GridInterface::setValidationFailureBehavior(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_setValidationFailureBehavior(cx, argc, vp, p);
}
JSBool     GridInterface::impl_setValidationFailureBehavior(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	int vfbFlags = 0;


	argIndex = 0;
	// 1:
	if( FromJS(cx, argv[argIndex], vfbFlags) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return false;
	}
	argIndex++;

	// APIの実行
	p->SetValidationFailureBehavior(vfbFlags);

	return JS_TRUE;
}



JSBool GridInterface::sort(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_sort(cx, argc, vp, p);
}
JSBool     GridInterface::impl_sort(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	int flags=0;


	argIndex = 0;
	if( argc != 0 ) {
		// 1:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
			return false;
		}
		argIndex++;
	}

	// APIの実行
	p->Sort(flags);

	return JS_TRUE;
}



JSBool GridInterface::sortChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_sortChildren(cx, argc, vp, p);
}
JSBool     GridInterface::impl_sortChildren(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

		
	int argIndex = 0;
	GridInterface_ArgID	argId;
	int flags=0;


	argIndex = 0;
	// 1:
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	if( argc >= 2 ) {
		// 2:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return false;
		}
		argIndex++;
	}

	// APIの実行
	p->SortChildren(argId.get(), flags);

	return JS_TRUE;
}



JSBool GridInterface::refreshProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxPropertyGridInterface *p = GetPrivate(cx, JS_THIS_OBJECT(cx, vp) );
    if ( p == NULL )
        return JS_FALSE;
	return GridInterface::impl_refreshProperty(cx, argc, vp, p);
}
JSBool     GridInterface::impl_refreshProperty(JSContext *cx, unsigned argc, JS::Value *vp, wxPropertyGridInterface *p)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


		
	int argIndex = 0;
	wxPGProperty *pProp = NULL;


	argIndex = 0;
	// 1:
	pProp = Property::GetPrivate(cx, argv[argIndex], false);
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return false;
	}
	argIndex++;

	// APIの実行
	p->RefreshProperty(pProp);

	return JS_TRUE;
}


