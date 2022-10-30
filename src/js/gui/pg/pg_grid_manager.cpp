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
#include "js/ext/point.h"
#include "js/gui/errors.h"
#include "js/gui/pg/pg_grid_manager.h"
#include "js/gui/pg/pg_grid_page.h"
#include "js/gui/pg/pg_grid.h"
#include "js/gui/pg/pg_grid_if.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_arg_id.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/control/window.h"
#include "js/gui/control/panel.h"
#include "js/gui/control/toolbar.h"



using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	GridManager
//--------------------------------------------------------
WXJS_INIT_CLASS(GridManager, "GridManager", 0)
	
void GridManager::InitClass(JSContext* WXUNUSED(cx), JSObject* WXUNUSED(obj), JSObject* WXUNUSED(proto))
{
    GridManagerEventHandler::InitConnectEventMap();
}



// プロパティー
WXJS_BEGIN_PROPERTY_MAP(GridManager)
  WXJS_READONLY_PROPERTY(P_GRID, "grid")
  WXJS_READONLY_PROPERTY(P_CURRENT_PAGE, "currentPage")
  WXJS_READONLY_PROPERTY(P_PAGE_COUNT, "pageCount")
  WXJS_READONLY_PROPERTY(P_SELECTED_PAGE, "selectedPage")
  WXJS_READONLY_PROPERTY(P_SELECTED_PROPERTY, "selectedProperty")
  WXJS_READONLY_PROPERTY(P_SELECTION, "selection")
  WXJS_READONLY_PROPERTY(P_TOOLBAR, "toolBar")
  WXJS_READONLY_PROPERTY(P_IS_ANY_MODIFIED, "isAnyModified")
  WXJS_READONLY_PROPERTY(P_IS_FROZEN, "isFrozen")
WXJS_END_PROPERTY_MAP()

// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPropertyGridManager, GridManager)
	switch (id) 
	{
	case P_GRID:
		{
			wxPropertyGrid* pGrid = p->GetGrid();
			if( pGrid == NULL ) {
				vp.setNull();
			} else {
				vp.set( Grid::CreateObject(cx, pGrid, NULL) );
			}
		}
		break;
	case P_CURRENT_PAGE:
		{
			wxPropertyGridPage * pPage = p->GetCurrentPage();
			if( pPage == NULL ) {
				vp.setNull();
			} else {
				vp.set( GridPage::CreateObject(cx, pPage, NULL) );
			}
		}
		break;
	case P_PAGE_COUNT:
		vp.setInt32( p->GetPageCount() );
		break;
	case P_SELECTED_PAGE:
		vp.setInt32( p->GetSelectedPage () );
		break;
	case P_SELECTED_PROPERTY:
		{
			wxPGProperty* pProp = p->GetSelectedProperty();
			if( pProp == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pProp, NULL) );
			}
		}
		break;
	case P_SELECTION:
		{
			wxPGProperty* pProp = p->GetSelection();
			if( pProp == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pProp, NULL) );
			}
		}
		break;
	case P_TOOLBAR:
		{
			wxToolBar * pToolBar = p->GetToolBar();
			if( pToolBar == NULL ) {
				vp.setNull();
			} else {
				vp.set( ToolBar::CreateObject(cx, pToolBar, NULL) );
			}
		}
		break;
	case P_IS_ANY_MODIFIED:
		vp.setBoolean( p->IsAnyModified() );
		break;
	case P_IS_FROZEN:
		vp.setBoolean( p->IsFrozen() );
		break;
	}
	return true;
WXJS_END_GET_PROP

// プロパティー set の実装
WXJS_BEGIN_SET_PROP(wxPropertyGridManager, GridManager)

	return true;
WXJS_END_SET_PROP

	
WXJS_BEGIN_ADD_PROP(wxPropertyGridManager, GridManager)
{

    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    GridManagerEventHandler::ConnectEvent(p, prop, true);
    return true;
}
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxPropertyGridManager, GridManager)
{
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  GridManagerEventHandler::ConnectEvent(p, prop, false);
  return true;
}
WXJS_END_DEL_PROP



// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPropertyGridManager, GridManager)
{
	wxPropertyGridManager *p = new wxPropertyGridManager();

    SetPrivate(cx, obj, p);

    if ( argc > 0 )
    {
        jsval rval;
        if ( ! _innerCreate(cx, obj, argc, vp, &rval) )
        {
          return NULL;
        }
    }

	return p;
}
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxPropertyGridManager, GridManager)
{

}
WXJS_END_DESTRUCTOR
	

JSBool GridManager::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxPropertyGridManager *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	wxWindow *parent = NULL;
	wxWindowID id=wxID_ANY;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = wxPGMAN_DEFAULT_STYLE;
	wxString name=wxPropertyGridManagerNameStr;


	
	ZZZJS_CHECK_ARG_COUNT(1, 6);
	
	argIndex = argc -1;
	switch(argc)
	{
	case 6:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex--;
	case 5:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 3:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	case 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex--;
	default:
		wxWindow *parent = NULL;
		int id;

		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;

		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JavaScriptClientData *clntParent =
				dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), style, name) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

    return JS_TRUE;
}

// メソッドの定義
WXJS_BEGIN_METHOD_MAP(GridManager)
	WXJS_METHOD("create", create, 1)
	WXJS_METHOD("addPage", addPage, 0)
	WXJS_METHOD("clear", clear, 0)
	WXJS_METHOD("clearPage", clearPage, 1)
	WXJS_METHOD("commitChangesFromEditor", commitChangesFromEditor, 0)
	WXJS_METHOD("enableCategories", enableCategories, 1)
	WXJS_METHOD("ensureVisible", ensureVisible, 1)
	WXJS_METHOD("getColumnCount", getColumnCount, 0)
	WXJS_METHOD("getDescBoxHeight", getDescBoxHeight, 0)
	WXJS_METHOD("getPage", getPage, 1)
	WXJS_METHOD("getPageByName", getPageByName, 1)
	WXJS_METHOD("getPageName", getPageName, 1)
	WXJS_METHOD("getPageRoot", getPageRoot, 1)
	WXJS_METHOD("insertPage", insertPage, 2)
	WXJS_METHOD("isPageModified", isPageModified, 1)
	WXJS_METHOD("isPropertySelected", isPropertySelected, 1)
	WXJS_METHOD("removePage", removePage, 1)
	WXJS_METHOD("selectPage", selectPage, 1)
	WXJS_METHOD("selectProperty", selectProperty, 1)
	WXJS_METHOD("setColumnCount", setColumnCount, 1)
	WXJS_METHOD("setColumnTitle", setColumnTitle, 2)
	WXJS_METHOD("setDescription", setDescription, 2)
	WXJS_METHOD("setDescBoxHeight", setDescBoxHeight, 1)
	WXJS_METHOD("setSplitterLeft", setSplitterLeft, 0)
	WXJS_METHOD("setPageSplitterLeft", setPageSplitterLeft, 1)
	WXJS_METHOD("setPageSplitterPosition", setPageSplitterPosition, 2)
	WXJS_METHOD("setSplitterPosition", setSplitterPosition, 1)
	WXJS_METHOD("showHeader", showHeader, 0)
	

	//-----------------------------------------------
	//	wxPropertyGridInterface
	//-----------------------------------------------
	WXJS_METHOD("append", append, 1 )
	WXJS_METHOD("appendIn", appendIn, 2 )
	WXJS_METHOD("beginAddChildren", beginAddChildren, 1 )
	//WXJS_METHOD("clear", clear, 0 ) ... same function defined avobe.
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
	//WXJS_METHOD("isPropertySelected", isPropertySelected, 1 ) ... same function defined avobe.
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

JSBool GridManager::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}

JSBool GridManager::addPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	wxString label=wxEmptyString;
	wxBitmap bmp=wxPG_NULL_BITMAP;
	wxPropertyGridPage *pageObj=NULL;

	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 3:
		{
			pageObj = GridPage::GetPrivate(cx, argv[argIndex], false);
			if( pageObj == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.GridPage");
				return JS_FALSE;
			}
		}
		argIndex--;
	case 2:
		{
			zzzJsPtr<wxBitmap> apBitmap;
			if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Bitmap::getClassName());
				return JS_FALSE;
			}
			bmp = *(apBitmap.get());
		}
		argIndex--;
	case 1:
		if( FromJS(cx, argv[argIndex], label) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と戻り値の設定
	wxPropertyGridPage *pRet = p->AddPage(label, bmp, pageObj);
	if( pRet == NULL ) {
		vp->setNull();
	} else {
		*vp = GridPage::CreateObject(cx, pRet, NULL);
	}

	return JS_TRUE;
}

JSBool GridManager::clear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	// APIの実行
	p->Clear();

	return JS_TRUE;
}

JSBool GridManager::clearPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int page = 0;
	if( FromJS(cx, argv[argIndex], page) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->ClearPage(page);


	return JS_TRUE;
}

JSBool GridManager::commitChangesFromEditor(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	wxUint32 flags=0;

	if( argc > 1 ) {
		argc = 1;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 1:
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と戻り値の設定
	vp->setBoolean( p->CommitChangesFromEditor(flags) );

	return JS_TRUE;
}

JSBool GridManager::enableCategories(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	bool enable=false;


	if( FromJS(cx, argv[argIndex], enable) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	vp->setBoolean( p->EnableCategories(enable) );

	return JS_TRUE;
}

JSBool GridManager::ensureVisible(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	GridInterface_ArgID	argId;

	
	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	vp->setBoolean( p->EnsureVisible(argId.get()) );

	return JS_TRUE;
}

JSBool GridManager::getColumnCount(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// 引数の取得
	int argIndex = 0;
	int page=-1;

	if( argc > 1 ) {
		argc = 1;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 1:
		if( FromJS(cx, argv[argIndex], page) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}

	// APIの実行と戻り値の設定
	vp->setInt32( p->GetColumnCount(page) );

	return JS_TRUE;
}

JSBool GridManager::getDescBoxHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	

	// APIの実行と戻り値の設定
	vp->setInt32( p->GetDescBoxHeight() );

	return JS_TRUE;
}

JSBool GridManager::getPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// 引数の取得
	int argIndex = 0;
	unsigned int ind=0;
	wxString strName(_T(""));

	if( argv[argIndex].isString() ) {
		if( FromJS(cx, argv[argIndex], strName) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	} else {
		if( FromJS(cx, argv[argIndex], ind) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}


	// APIの実行と戻り値の設定
	wxPropertyGridPage *pPage = NULL;
	if( strName.Length() != 0 ) {
		pPage = p->GetPage( strName );
	} else {
		pPage = p->GetPage( ind );
	}
	if( pPage == NULL ) {
		vp->setNull();
	} else {
		*vp = GridPage::CreateObject(cx, pPage, NULL);
	}
	return JS_TRUE;
}

JSBool GridManager::getPageByName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// 引数の取得
	int argIndex = 0;
	wxString name;

	if( FromJS(cx, argv[argIndex], name) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	int  iRet = p->GetPageByName(name);
	*vp = ToJS(cx, iRet);
	return JS_TRUE;
}

JSBool GridManager::getPageName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// 引数の取得
	int argIndex = 0;
	int index = 0;

	if( FromJS(cx, argv[argIndex], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	wxString str = p->GetPageName(index);
	*vp = ToJS(cx, str);
	return JS_TRUE;
}

JSBool GridManager::getPageRoot(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	
	// 引数の取得
	int argIndex = 0;
	int index = 0;

	if( FromJS(cx, argv[argIndex], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	wxPGProperty *pProp = p->GetPageRoot(index);
	if( pProp == NULL ) {
		vp->setNull();
	} else {
		*vp = Property::CreateObject(cx, pProp, NULL);
	}
	return JS_TRUE;
}

JSBool GridManager::insertPage(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int index = 0;
	wxString label=wxEmptyString;
	wxBitmap bmp=wxPG_NULL_BITMAP;
	wxPropertyGridPage *pageObj=NULL;

	if( argc > 4 ) {
		argc = 4;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 4:
		{
			pageObj = GridPage::GetPrivate(cx, argv[argIndex], false);
			if( pageObj == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.GridPage");
				return JS_FALSE;
			}
		}
		argIndex--;
	case 3:
		{
			zzzJsPtr<wxBitmap> apBitmap;
			if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
				return JS_FALSE;
			}
			bmp = *(apBitmap.get());
		}
		argIndex--;
	}
	argIndex = 0;
	if( FromJS(cx, argv[argIndex], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	if( FromJS(cx, argv[argIndex], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex--;

	// APIの実行と戻り値の設定
	wxPropertyGridPage *pRet = p->InsertPage(index, label, bmp, pageObj);
	if( pRet == NULL ) {
		vp->setNull();
	} else {
		*vp = GridPage::CreateObject(cx, pRet, NULL);
	}

	return JS_TRUE;
}

JSBool GridManager::isPageModified(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int index = 0;
	if( FromJS(cx, argv[argIndex], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	vp->setBoolean( p->IsPageModified(index) );

	return JS_TRUE;
}

JSBool GridManager::isPropertySelected(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	GridInterface_ArgID	argId;

	
	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	vp->setBoolean( p->IsPropertySelected(argId.get()) );

	return JS_TRUE;
}

JSBool GridManager::removePage(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int page = 0;
	if( FromJS(cx, argv[argIndex], page) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	vp->setBoolean( p->RemovePage(page) );

	return JS_TRUE;
}

JSBool GridManager::selectPage(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int page = 0;
	if( FromJS(cx, argv[argIndex], page) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	p->SelectPage(page);

	return JS_TRUE;
}

JSBool GridManager::selectProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	GridInterface_ArgID	argId;
	 bool focus=false;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], focus) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	vp->setBoolean( p->SelectProperty(argId.get(), focus) );

	return JS_TRUE;
}

JSBool GridManager::setColumnCount(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int colCount = 0;
	int page=-1;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], page) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], page) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と戻り値の設定
	p->SetColumnCount(colCount, page);

	return JS_TRUE;
}

JSBool GridManager::setColumnTitle(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int idx = 0;
	wxString title;
	
	// 1
	if( FromJS(cx, argv[argIndex], idx) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( FromJS(cx, argv[argIndex], title) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;


	// APIの実行と戻り値の設定
	p->SetColumnTitle(idx, title);

	return JS_TRUE;
}

JSBool GridManager::setDescription(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	wxString label;
	wxString content;
	
	// 1
	if( FromJS(cx, argv[argIndex], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( FromJS(cx, argv[argIndex], content) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;


	// APIの実行と戻り値の設定
	p->SetDescription(label, content);

	return JS_TRUE;
}

JSBool GridManager::setDescBoxHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int ht = 0;
	bool refresh=true;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], refresh) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], ht) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;


	// APIの実行と戻り値の設定
	p->SetDescBoxHeight(ht, refresh);

	return JS_TRUE;
}

JSBool GridManager::setSplitterLeft(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	bool subProps=false;
	bool allPages=true;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], allPages) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	case 1:
		if( FromJS(cx, argv[argIndex], allPages) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と戻り値の設定
	p->SetSplitterLeft(subProps, allPages);

	return JS_TRUE;
}

JSBool GridManager::setPageSplitterLeft(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int page = 0;
	bool subProps=false;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], subProps) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], page) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetPageSplitterLeft(page, subProps);

	return JS_TRUE;
}

JSBool GridManager::setPageSplitterPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int page = 0;
	int pos = 0;
	int column=0;
	
	if( argc > 3 ) {
		argc = 3;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 3:
		if( FromJS(cx, argv[argIndex], column) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 2:
		if( FromJS(cx, argv[argIndex], pos) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], page) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetPageSplitterPosition(page,pos, column);

	return JS_TRUE;
}

JSBool GridManager::setSplitterPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	int pos = 0;
	int column=0;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		if( FromJS(cx, argv[argIndex], column) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], pos) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と戻り値の設定
	p->SetSplitterPosition(pos, column);

	return JS_TRUE;
}

JSBool GridManager::showHeader(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGridManager *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// 引数の取得
	int argIndex = 0;
	bool show=true;
	
	if( argc > 1 ) {
		argc = 1;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 1:
		if( FromJS(cx, argv[argIndex], show) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と戻り値の設定
	p->ShowHeader(show);

	return JS_TRUE;
}



//-----------------------------------------------
//	wxPropertyGridInterface
//-----------------------------------------------
#define MY_IMPLE_GRID_IF(X) JSBool GridManager::## X ## (JSContext *cx, unsigned argc, JS::Value *vp) \
{\
	JSObject *obj = JS_THIS_OBJECT(cx, vp);\
	JS::CallArgs argv = CallArgsFromVp(argc, vp);\
    wxPropertyGridManager *p = GetPrivate(cx, obj);\
    if ( p == NULL )\
        return JS_FALSE;\
	return GridInterface::impl_## X ##(cx, argc, vp, p);\
}
MY_IMPLE_GRID_IF(append)
MY_IMPLE_GRID_IF(appendIn)
MY_IMPLE_GRID_IF(beginAddChildren)
//MY_IMPLE_GRID_IF(clear) ... same function defined avobe.
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
//MY_IMPLE_GRID_IF(isPropertySelected) ... same function defined avobe.
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





//------------------------------------------------------------------
//	GridManagerEventHandler
//------------------------------------------------------------------

WXJS_INIT_EVENT_MAP(wxPropertyGridManager)
const wxString ZZZJS_PG_GRID_ON_SELECTED = wxT("onSelected");
const wxString ZZZJS_PG_GRID_ON_CHANGED = wxT("onChanged");
const wxString ZZZJS_PG_GRID_ON_CHANGING = wxT("onChanging");
const wxString ZZZJS_PG_GRID_ON_HIGH_LIGHTED = wxT("onHighLighted");
const wxString ZZZJS_PG_GRID_ON_RIGHT_CLICK = wxT("onRightClick");
const wxString ZZZJS_PG_GRID_ON_DOUBLE_CLICK = wxT("onDoubleClick");
const wxString ZZZJS_PG_GRID_ON_ITEM_COLLSPSED = wxT("onItemCollapsed");
const wxString ZZZJS_PG_GRID_ON_ITEM_EXOANDED = wxT("onItemExpanded");
const wxString ZZZJS_PG_GRID_ON_LABEL_EDIT_BEGIN = wxT("onLabelEditBegin");
const wxString ZZZJS_PG_GRID_ON_LABEL_EDIT_ENDING = wxT("onLabelEditEnding");
const wxString ZZZJS_PG_GRID_ON_COL_BEGIN_DRAG = wxT("onColBeginDrag");
const wxString ZZZJS_PG_GRID_ON_COL_DRAGGING = wxT("onColDragging");
const wxString ZZZJS_PG_GRID_ON_COL_END_DRAG = wxT("onColEndDrag");



#define IMPLE_EVT(NAME, STRNAMNE, EVT) void GridManagerEventHandler::On ## NAME(wxPropertyGridEvent &event) \
{ \
	PrivGridEvent::Fire<GridEvent>(event, STRNAMNE);\
}\
void GridManagerEventHandler::Connect ## NAME(wxPropertyGridManager *p, bool connect) \
{\
	if ( connect )\
	{\
		p->Connect(EVT, \
		wxPropertyGridEventHandler(GridManagerEventHandler::On ## NAME )); \
	}\
	else\
	{\
		p->Disconnect(EVT, \
			wxPropertyGridEventHandler(GridManagerEventHandler::On ## NAME ));\
	}\
}
#include "js/gui/pg/pg_evt_grid.h"
IMPLE_EVT(Selected, ZZZJS_PG_GRID_ON_SELECTED, wxEVT_PG_SELECTED)
IMPLE_EVT(Changed, ZZZJS_PG_GRID_ON_CHANGED, wxEVT_PG_CHANGED)
IMPLE_EVT(Changing, ZZZJS_PG_GRID_ON_CHANGING,  wxEVT_PG_CHANGING )
IMPLE_EVT(HighLighted, ZZZJS_PG_GRID_ON_HIGH_LIGHTED, wxEVT_PG_HIGHLIGHTED)
IMPLE_EVT(RightClick, ZZZJS_PG_GRID_ON_RIGHT_CLICK, wxEVT_PG_RIGHT_CLICK)
IMPLE_EVT(DoubleClick, ZZZJS_PG_GRID_ON_DOUBLE_CLICK, wxEVT_PG_DOUBLE_CLICK)
IMPLE_EVT(ItemCollapsed, ZZZJS_PG_GRID_ON_ITEM_COLLSPSED,  wxEVT_PG_ITEM_COLLAPSED)
IMPLE_EVT(ItemExpanded, ZZZJS_PG_GRID_ON_ITEM_EXOANDED,  wxEVT_PG_ITEM_EXPANDED)
IMPLE_EVT(LabelEditBegin, ZZZJS_PG_GRID_ON_LABEL_EDIT_BEGIN,  wxEVT_PG_LABEL_EDIT_BEGIN)
IMPLE_EVT(LabelEditEnding, ZZZJS_PG_GRID_ON_LABEL_EDIT_ENDING,  wxEVT_PG_LABEL_EDIT_ENDING)
IMPLE_EVT(ColBeginDrag, ZZZJS_PG_GRID_ON_COL_BEGIN_DRAG,  wxEVT_PG_COL_BEGIN_DRAG)
IMPLE_EVT(ColDragging, ZZZJS_PG_GRID_ON_COL_DRAGGING,  wxEVT_PG_COL_DRAGGING)
IMPLE_EVT(ColEndDrag, ZZZJS_PG_GRID_ON_COL_END_DRAG,  wxEVT_PG_COL_END_DRAG)

#undef IMPLE_EVT


void GridManagerEventHandler::InitConnectEventMap()
{
  AddConnector(ZZZJS_PG_GRID_ON_SELECTED, ConnectSelected);
  AddConnector(ZZZJS_PG_GRID_ON_CHANGED, ConnectChanged);
  AddConnector(ZZZJS_PG_GRID_ON_CHANGING, ConnectChanging);
  AddConnector(ZZZJS_PG_GRID_ON_HIGH_LIGHTED, ConnectHighLighted);
  AddConnector(ZZZJS_PG_GRID_ON_RIGHT_CLICK, ConnectRightClick);
  AddConnector(ZZZJS_PG_GRID_ON_DOUBLE_CLICK, ConnectDoubleClick);
  AddConnector(ZZZJS_PG_GRID_ON_ITEM_COLLSPSED, ConnectItemCollapsed);
  AddConnector(ZZZJS_PG_GRID_ON_ITEM_EXOANDED, ConnectItemExpanded);
  AddConnector(ZZZJS_PG_GRID_ON_LABEL_EDIT_BEGIN, ConnectLabelEditBegin);
  AddConnector(ZZZJS_PG_GRID_ON_LABEL_EDIT_ENDING, ConnectLabelEditEnding);
  AddConnector(ZZZJS_PG_GRID_ON_COL_BEGIN_DRAG, ConnectColBeginDrag);
  AddConnector(ZZZJS_PG_GRID_ON_COL_DRAGGING, ConnectColDragging);
  AddConnector(ZZZJS_PG_GRID_ON_COL_END_DRAG, ConnectColEndDrag);

}