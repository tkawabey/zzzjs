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
#include "js/gui/pg/pg_grid_page.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_grid_if.h"
#include "js/gui/misc/size.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	GridPage
//--------------------------------------------------------
WXJS_INIT_CLASS(GridPage, "GridPage", 0)
	
// プロパティー
WXJS_BEGIN_PROPERTY_MAP(GridPage)
  WXJS_READONLY_PROPERTY(P_INDEX, "index")
  WXJS_READONLY_PROPERTY(P_FIT_COLUMNS, "fitColmns")
  WXJS_READONLY_PROPERTY(P_ROOT, "root")
  WXJS_READONLY_PROPERTY(P_TOOL_ID, "toolId")
WXJS_END_PROPERTY_MAP()

// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPropertyGridPage, GridPage)
	switch (id) 
	{
	case P_INDEX:
		ToJSVal(cx, vp, p->GetIndex ());
		break;
	case P_FIT_COLUMNS:
		{
			wxSize sz = p->FitColumns();
			vp.set( Size::CreateObject(cx, new wxSize(sz)) );
		}
		break;
	case P_ROOT:
		{
			wxPGProperty* pProp = p->GetRoot ();
			if( pProp != NULL ) {
				vp.set( Property::CreateObject(cx, pProp) );
			} else {
				vp.setNull();
			}

		}
		break;
	case P_TOOL_ID:
		ToJSVal(cx, vp, p->GetToolId());
		break;
	}
	return true;
WXJS_END_GET_PROP

// プロパティー set の実装
WXJS_BEGIN_SET_PROP(wxPropertyGridPage, GridPage)

	return true;
WXJS_END_SET_PROP

// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPropertyGridPage, GridPage)

	JS_ReportError(cx, "GridPage is abstruct class");

	return NULL;
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxPropertyGridPage, GridPage)

WXJS_END_DESTRUCTOR
	


// メソッドの定義
WXJS_BEGIN_METHOD_MAP(GridPage)
	WXJS_METHOD("getSplitterPosition", getSplitterPosition, 0)
	WXJS_METHOD("setSplitterPosition", setSplitterPosition, 1)


	//-----------------------------------------------
	//	wxPropertyGridInterface
	//-----------------------------------------------
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

JSBool GridPage::getSplitterPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridPage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int col=0; 
	if( argc != 0 ) {
		if( FromJS(cx, argv[0], col) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
			return false;
		}
	}
	
	// APIの実行と戻り値の設定
	vp->setInt32( p->GetSplitterPosition(col) );

	return JS_TRUE;
}


JSBool GridPage::setSplitterPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridPage *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int splitterPos;
	int col=0;

	if( argc >= 2  ) {
		if( FromJS(cx, argv[1], col) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return false;
		}
	}
	if( FromJS(cx, argv[0], splitterPos) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return false;
	}

	p->SetSplitterPosition(splitterPos, col);

	return JS_TRUE;
}

//-----------------------------------------------
//	wxPropertyGridInterface
//-----------------------------------------------
#define MY_IMPLE_GRID_IF(X) JSBool GridPage::## X ## (JSContext *cx, unsigned argc, JS::Value *vp) \
{\
	JSObject *obj = JS_THIS_OBJECT(cx, vp);\
	JS::CallArgs argv = CallArgsFromVp(argc, vp);\
    wxPropertyGridPage *p = GetPrivate(cx, obj);\
    if ( p == NULL )\
        return JS_FALSE;\
	return GridInterface::impl_## X ##(cx, argc, vp, p);\
}
MY_IMPLE_GRID_IF(append)
MY_IMPLE_GRID_IF(appendIn)
MY_IMPLE_GRID_IF(beginAddChildren)
MY_IMPLE_GRID_IF(clear)
MY_IMPLE_GRID_IF(clearSelection)
MY_IMPLE_GRID_IF(clearModifiedStatus)
MY_IMPLE_GRID_IF(collapse)
MY_IMPLE_GRID_IF(collapseAll)
MY_IMPLE_GRID_IF(changePropertyValue)
MY_IMPLE_GRID_IF(deleteProperty)
MY_IMPLE_GRID_IF(disableProperty)
MY_IMPLE_GRID_IF(editorValidate)
MY_IMPLE_GRID_IF(enableProperty)
MY_IMPLE_GRID_IF(endAddChildren)
MY_IMPLE_GRID_IF(expand)
MY_IMPLE_GRID_IF(expandAll)
MY_IMPLE_GRID_IF(getColumnProportion)
MY_IMPLE_GRID_IF(getFirstChild)
MY_IMPLE_GRID_IF(getProperty)
//MY_IMPLE_GRID_IF(getPropertiesWithFlag) TODO...
MY_IMPLE_GRID_IF(getPropertyAttribute)
//MY_IMPLE_GRID_IF(getPropertyAttributes)  TODO...
MY_IMPLE_GRID_IF(getPropertyBackgroundColour)
MY_IMPLE_GRID_IF(getPropertyCategory)
//MY_IMPLE_GRID_IF(getPropertyClientData) ... TODO,,,
MY_IMPLE_GRID_IF(getPropertyByLabel)
MY_IMPLE_GRID_IF(getPropertyByName)
MY_IMPLE_GRID_IF(getPropertyEditor)
MY_IMPLE_GRID_IF(getPropertyHelpString)
MY_IMPLE_GRID_IF(getPropertyImage)
MY_IMPLE_GRID_IF(getPropertyLabel)
MY_IMPLE_GRID_IF(getPropertyName)
MY_IMPLE_GRID_IF(getPropertyParent)
MY_IMPLE_GRID_IF(getPropertyTextColour)
MY_IMPLE_GRID_IF(getPropertyValidator)
MY_IMPLE_GRID_IF(getPropertyValue)
MY_IMPLE_GRID_IF(getPropertyValueAsArrayInt)
MY_IMPLE_GRID_IF(getPropertyValueAsArrayString)
MY_IMPLE_GRID_IF(getPropertyValueAsBool)
MY_IMPLE_GRID_IF(getPropertyValueAsDateTime)
MY_IMPLE_GRID_IF(getPropertyValueAsDouble)
MY_IMPLE_GRID_IF(getPropertyValueAsInt)
MY_IMPLE_GRID_IF(getPropertyValueAsLong)
//MY_IMPLE_GRID_IF(getPropertyValueAsLongLong)
MY_IMPLE_GRID_IF(getPropertyValueAsString)
MY_IMPLE_GRID_IF(getPropertyValueAsULong)
//MY_IMPLE_GRID_IF(getPropertyValueAsULongLong)
MY_IMPLE_GRID_IF(getPropertyValues)
//MY_IMPLE_GRID_IF(getVIterator) TODO...
MY_IMPLE_GRID_IF(hideProperty)
MY_IMPLE_GRID_IF(insert)
MY_IMPLE_GRID_IF(isPropertyCategory)
MY_IMPLE_GRID_IF(isPropertyEnabled)
MY_IMPLE_GRID_IF(isPropertyExpanded)
MY_IMPLE_GRID_IF(isPropertyModified)
MY_IMPLE_GRID_IF(isPropertySelected)
MY_IMPLE_GRID_IF(isPropertyShown)
MY_IMPLE_GRID_IF(isPropertyValueUnspecified)
MY_IMPLE_GRID_IF(limitPropertyEditing)
//MY_IMPLE_GRID_IF(refreshGrid) TODO...
MY_IMPLE_GRID_IF(removeProperty)
MY_IMPLE_GRID_IF(replaceProperty)
MY_IMPLE_GRID_IF(restoreEditableState)
MY_IMPLE_GRID_IF(saveEditableState)
MY_IMPLE_GRID_IF(setColumnProportion)
MY_IMPLE_GRID_IF(setPropertyAttribute)
MY_IMPLE_GRID_IF(setPropertyAttributeAll)
MY_IMPLE_GRID_IF(setPropertyBackgroundColour)
MY_IMPLE_GRID_IF(setPropertyCell)
//MY_IMPLE_GRID_IF(setPropertyClientData) TODO...
MY_IMPLE_GRID_IF(setPropertyColoursToDefault)
MY_IMPLE_GRID_IF(setPropertyEditor)
MY_IMPLE_GRID_IF(setPropertyLabel)
MY_IMPLE_GRID_IF(setPropertyName)
MY_IMPLE_GRID_IF(setPropertyReadOnly)
MY_IMPLE_GRID_IF(setPropertyValueUnspecified)
//MY_IMPLE_GRID_IF(setPropertyValues) TODO...
MY_IMPLE_GRID_IF(setPropertyHelpString)
MY_IMPLE_GRID_IF(setPropertyImage)
MY_IMPLE_GRID_IF(setPropertyMaxLength)
MY_IMPLE_GRID_IF(setPropertyTextColour)
MY_IMPLE_GRID_IF(setPropertyValidator)
MY_IMPLE_GRID_IF(setPropertyValue)
MY_IMPLE_GRID_IF(setPropertyValueString)
MY_IMPLE_GRID_IF(setPropVal)
MY_IMPLE_GRID_IF(setValidationFailureBehavior)
MY_IMPLE_GRID_IF(sort)
MY_IMPLE_GRID_IF(sortChildren)
MY_IMPLE_GRID_IF(refreshProperty)
#undef MY_IMPLE_GRID_IF
