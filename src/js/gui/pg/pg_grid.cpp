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
#include "js/gui/pg/pg_grid.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_arg_id.h"
#include "js/gui/pg/pg_grid_page.h"
#include "js/gui/pg/pg_cell.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/rect.h"
#include "js/gui/control/window.h"
#include "js/gui/control/panel.h"
#include "js/gui/control/textctrl.h"
#include "js/ext/point.h"
#include "js/gui/pg/pg_evt_grid.h"
#include "js/gui/pg/pg_grid_if.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	Grid
//--------------------------------------------------------
WXJS_INIT_CLASS(Grid, "Grid", 0)
	
void Grid::InitClass(JSContext* WXUNUSED(cx), JSObject* WXUNUSED(obj), JSObject* WXUNUSED(proto))
{
    GridEventHandler::InitConnectEventMap();
}


// プロパティー
WXJS_BEGIN_PROPERTY_MAP(Grid)
	WXJS_READONLY_PROPERTY(P_FIT_COLUMNS, "fitColumns")
	WXJS_READONLY_PROPERTY(P_LABEL_EDITOR, "labelEditor")
	WXJS_READONLY_PROPERTY(P_PANEL, "panel")
	WXJS_PROPERTY(P_CAPTION_BACKGROUND_COLOR, "captionBackgroundColour")
	WXJS_READONLY_PROPERTY(P_CAPTION_FONT, "captionFont")
	WXJS_READONLY_PROPERTY(P_CAPTION_FOREGROUND_COLOR, "captionForegroundColour")
	WXJS_PROPERTY(P_CELL_BACKGROUND_COLOR, "cellBackgroundColour")
	WXJS_PROPERTY(P_CELL_DISABLED_TEXT_COLOR, "cellDisabledTextColour")
	WXJS_PROPERTY(P_CELL_TEXT_COLOR, "cellTextColour")
	WXJS_PROPERTY(P_COLUMN_COUNT, "columnCount")
	WXJS_PROPERTY(P_EMPTY_SPACE_COLOR, "emptySpaceColour")
	WXJS_READONLY_PROPERTY(P_FONT_HIGHT, "fontHeight")
	WXJS_READONLY_PROPERTY(P_GRID, "grid")
	WXJS_PROPERTY(P_LINE_COLOR, "lineColour")
	WXJS_PROPERTY(P_MARGIN_COLOR, "marginColour")
	WXJS_READONLY_PROPERTY(P_ROOT, "root")
	WXJS_READONLY_PROPERTY(P_ROW_HEIGHT, "rowHeight")
	WXJS_READONLY_PROPERTY(P_SELECTED_PROPERTY, "selectedProperty")
	WXJS_PROPERTY(P_SELECTION, "selection")
	WXJS_PROPERTY(P_SELECTION_FOREGROUND_COLOR, "selectionBackgroundColour")
	WXJS_READONLY_PROPERTY(P_SELECTION_BACKGROUND_COLOR, "selectionForegroundColour")
	WXJS_READONLY_PROPERTY(P_SORT_FUNC, "sortFunction")
	WXJS_READONLY_PROPERTY(P_EDIT_TEXT_CTRL, "editorTextCtrl")
	WXJS_PROPERTY(P_UNSPECIFIED_VALUE_APPEARANCE, "unspecifiedValueAppearance")
	WXJS_PROPERTY(P_VERTICAL_SPACING, "verticalSpacing")
	WXJS_READONLY_PROPERTY(P_IS_ANY_MODIFIED, "isAnyModified ")
	WXJS_READONLY_PROPERTY(P_IS_EDITOR_FOCUSED, "isAnyModified ")
	WXJS_READONLY_PROPERTY(P_IS_FROZEN, "isAnyModified ")
	WXJS_PROPERTY(P_CAPTION_TEXT_COLOR, "captionTextColour")
	WXJS_PROPERTY(P_SELECTION_TEXT_COLOR, "selectionTextColour")
WXJS_END_PROPERTY_MAP()

// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPropertyGrid, Grid)
{
	switch (id) 
	{
	case P_FIT_COLUMNS:
		{
			wxSize sz = p->FitColumns();
			vp.set( Size::CreateObject(cx, new wxSize(sz), NULL) );

		}
		break;
	case P_LABEL_EDITOR:
		{
			wxTextCtrl* pSet = p->GetLabelEditor();
			vp.set( TextCtrl::CreateObject(cx, pSet, NULL) );
		}
		break;
	case P_PANEL:
		{
			wxWindow * pSet = p->GetPanel();
			vp.set( Window::CreateObject(cx, pSet, NULL) );
		}
		break;
	case P_CAPTION_BACKGROUND_COLOR:
		{
			wxColour 	pSet = p->GetCaptionBackgroundColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_CAPTION_FONT:
		{
			wxFont 	pSet = p->GetCaptionFont();
			vp.set( Font::CreateObject(cx, new wxFont(pSet), NULL) );
		}
		break;
	case P_CAPTION_FOREGROUND_COLOR:
		{
			wxColour 	pSet = p->GetCaptionForegroundColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_CELL_BACKGROUND_COLOR:
		{
			wxColour 	pSet = p->GetCellBackgroundColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_CELL_DISABLED_TEXT_COLOR:
		{
			wxColour 	pSet = p->GetCellDisabledTextColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_CELL_TEXT_COLOR:
		{
			wxColour 	pSet = p->GetCellTextColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_COLUMN_COUNT:
		ToJSVal(cx, vp, p->GetColumnCount());
		break;
	case P_EMPTY_SPACE_COLOR:
		{
			wxColour 	pSet = p->GetEmptySpaceColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_FONT_HIGHT:
		ToJSVal(cx, vp, p->GetFontHeight());
		break;
	case P_GRID:
		{
			wxPropertyGrid *  	pSet = p->GetGrid();
			if( pSet == NULL ) {
				vp.setNull();
			} else {
				vp.set( Grid::CreateObject(cx, pSet, NULL) );
			}			
		}
		break;
	case P_LINE_COLOR:
		{
			wxColour 	pSet = p->GetLineColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_MARGIN_COLOR:
		{
			wxColour 	pSet = p->GetMarginColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_ROOT:
		{
			wxPGProperty*  	pSet = p->GetRoot();
			if( pSet == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pSet, NULL) );
			}			
		}
		break;
	case P_ROW_HEIGHT:
		ToJSVal(cx, vp, p->GetRowHeight());
		break;
	case P_SELECTED_PROPERTY:
		{
			wxPGProperty*  	pSet = p->GetSelectedProperty();
			if( pSet == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pSet, NULL) );
			}			
		}
		break;
	case P_SELECTION:
		{
			wxPGProperty*  	pSet = p->GetSelection();
			if( pSet == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pSet, NULL) );
			}			
		}
		break;
	case P_SELECTION_BACKGROUND_COLOR:
		{
			wxColour 	pSet = p->GetSelectionBackgroundColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_SELECTION_FOREGROUND_COLOR:
		{
			wxColour 	pSet = p->GetSelectionForegroundColour();
			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_SORT_FUNC:
		{
			wxPGSortCallback  	pSet = p->GetSortFunction();
//			vp.set( Colour::CreateObject(cx, new wxColour(pSet), NULL) );
		}
		break;
	case P_EDIT_TEXT_CTRL:
		{
			wxTextCtrl*  	pSet = p->GetEditorTextCtrl ();
			if( pSet == NULL ) {
				vp.setNull();
			} else {
				vp.set( TextCtrl::CreateObject(cx, pSet, NULL) );
			}			
		}
		break;
	case P_UNSPECIFIED_VALUE_APPEARANCE:
		{
			const wxPGCell& 	pSet = p->GetUnspecifiedValueAppearance ();
			vp.set( Cell::CreateObject(cx, (wxPGCell*)&pSet, NULL) );
		}
		break;
	case P_VERTICAL_SPACING:
		ToJSVal(cx, vp, p->GetVerticalSpacing());
		break;
	case P_IS_ANY_MODIFIED:
		ToJSVal(cx, vp, p->IsAnyModified());
		break;
	case P_IS_EDITOR_FOCUSED:
		ToJSVal(cx, vp, p->IsEditorFocused ());
		break;
	case P_IS_FROZEN:
		ToJSVal(cx, vp, p->IsFrozen());
		break;
	}
	return true;
}
WXJS_END_GET_PROP

// プロパティー set の実装
WXJS_BEGIN_SET_PROP(wxPropertyGrid, Grid)
{
	switch (id) 
	{
	case P_CAPTION_BACKGROUND_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetCaptionBackgroundColour( *(apColour.get()) );
			}
		}
		break;
	case P_CELL_BACKGROUND_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetCellBackgroundColour( *(apColour.get()) );
			}
		}
		break;
	case P_CELL_DISABLED_TEXT_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetCellDisabledTextColour( *(apColour.get()) );
			}
		}
		break;
	case P_CELL_TEXT_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetCellTextColour( *(apColour.get()) );
			}
		}
		break;
	case P_COLUMN_COUNT:
		{
			unsigned int 	val = 0;
			if( FromJS(cx, vp, val) == true ) {
				p->SetColumnCount(val);
			}

		}
		break;
	case P_EMPTY_SPACE_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetEmptySpaceColour( *(apColour.get()) );
			}
		}
		break;
	case P_LINE_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetLineColour( *(apColour.get()) );
			}
		}
		break;
	case P_MARGIN_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetMarginColour( *(apColour.get()) );
			}
		}
		break;
	case P_SELECTION:
		do{

			wxArrayPGProperty arr;

			if( JS_IsArrayObject( cx, vp.toObjectOrNull() ) == JS_FALSE) {
				break;
			}
			
		   JSObject *objItems = JSVAL_TO_OBJECT(vp);
			uint32_t length = 0;
		    JS_GetArrayLength(cx, objItems , &length);
		    for(uint32_t i =0; i < length; i++)
		    {
			    JS::Value element;
			    JS_GetElement(cx, objItems, i, &element);

				wxPGProperty* pProp = Property::GetPrivate(cx, element, false);
				if( pProp != NULL ) {
					arr.Add( pProp );
				}
		    }

			p->SetSelection( arr );

		} while( 0 );
		break;
	case P_SELECTION_BACKGROUND_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetSelectionBackgroundColour( *(apColour.get()) );
			}
		}
		break;
	case P_UNSPECIFIED_VALUE_APPEARANCE:
		{
			wxPGCell* pSet = Cell::GetPrivate(cx, vp, false);
			if( pSet != NULL ) {
				p->SetUnspecifiedValueAppearance( *pSet );
			}
		}
		break;
	case P_VERTICAL_SPACING:
		{
			int 	val = 0;
			if( FromJS(cx, vp, val) == true ) {
				p->SetVerticalSpacing(val);
			}
		}
		break;
	case P_CAPTION_TEXT_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetCaptionTextColour( *(apColour.get()) );
			}
		}
		break;
	case P_SELECTION_TEXT_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetSelectionTextColour( *(apColour.get()) );
			}
		}
		break;
	}


	return true;
}
WXJS_END_SET_PROP

// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPropertyGrid, Grid)
{
	wxPropertyGrid *p = new wxPropertyGrid();

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
WXJS_BEGIN_DESTRUCTOR(wxPropertyGrid, Grid)
{

}
WXJS_END_DESTRUCTOR
	

JSBool Grid::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxPropertyGrid *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	wxWindow *parent = NULL;
	wxWindowID id=wxID_ANY;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = wxPGMAN_DEFAULT_STYLE;
	wxString name=wxPropertyGridManagerNameStr;


	if ( argc > 6 ) {
		argc = 6;
	}
	

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

		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
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
WXJS_BEGIN_METHOD_MAP(Grid)
	WXJS_METHOD("create", create, 1)
	WXJS_METHOD("addActionTrigger", addActionTrigger, 2)
	WXJS_METHOD("addToSelection", addToSelection, 1)
	WXJS_METHOD("beginLabelEdit", beginLabelEdit, 0)
	WXJS_METHOD("changePropertyValue", changePropertyValue, 2)
	WXJS_METHOD("centerSplitter", centerSplitter, 0)
	WXJS_METHOD("clear", clear, 0)
	WXJS_METHOD("clearActionTriggers", clearActionTriggers, 1)
	WXJS_METHOD("dedicateKey", dedicateKey, 1)
	WXJS_METHOD("enableCategories", enableCategories, 1)
	WXJS_METHOD("endLabelEdit", endLabelEdit, 0)
	WXJS_METHOD("ensureVisible", ensureVisible, 1)
	WXJS_METHOD("getImageRect", getImageRect, 2)
	WXJS_METHOD("getImageSize", getImageSize, 0)
	WXJS_METHOD("getLastItem", getLastItem, 0)
	WXJS_METHOD("getSplitterPosition", getSplitterPosition, 0)
	WXJS_METHOD("getUnspecifiedValueText", getUnspecifiedValueText, 0)
	WXJS_METHOD("hitTest", hitTest, 1)
	WXJS_METHOD("makeColumnEditable", makeColumnEditable, 1)
	WXJS_METHOD("onTLPChanging", onTLPChanging, 1)
	WXJS_METHOD("refreshEditor", refreshEditor, 0)
	WXJS_METHOD("refreshProperty", refreshProperty, 1)
	WXJS_METHOD("resetColours", resetColours, 0)
	WXJS_METHOD("resetColumnSizes", resetColumnSizes, 0)
	WXJS_METHOD("removeFromSelection", removeFromSelection, 1)
	WXJS_METHOD("selectProperty", selectProperty, 1)
	WXJS_METHOD("setSplitterPosition", setSplitterPosition, 1)
	WXJS_METHOD("setSplitterLeft", setSplitterLeft, 0)

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
	//WXJS_METHOD("changePropertyValue", changePropertyValue, 2 ) ... same function defined avobe.
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
	//WXJS_METHOD("refreshProperty", refreshProperty, 1) ... same function defined avobe.

WXJS_END_METHOD_MAP()

JSBool Grid::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}


JSBool Grid::addActionTrigger(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int action = 0;
	int keycode = 0;
	int modifiers=0;

	if( argc >= 3  ) {
		if( FromJS(cx, argv[2], modifiers) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	// 1
	if( FromJS(cx, argv[0], action) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	// 2
	if( FromJS(cx, argv[1], keycode) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	p->AddActionTrigger(action, keycode, modifiers);

	return JS_TRUE;
}


JSBool Grid::addToSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	GridInterface_ArgID	argId;


	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}

	vp->setBoolean( p->AddToSelection(argId.get()) );

	return JS_TRUE;
}


JSBool Grid::beginLabelEdit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	unsigned int colIndex=0;


	if( argc >= 1 ) {
		if( FromJS(cx, argv[0], colIndex) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	p->BeginLabelEdit((unsigned long)colIndex);

	return JS_TRUE;
}


JSBool Grid::changePropertyValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	wxVariant newValue;
	
	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	argIndex++;
	// 2
	if( FromJS(cx, argv[argIndex], newValue) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Variant");
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	vp->setBoolean( p->ChangePropertyValue(argId.get(), newValue) );

	return JS_TRUE;
}


JSBool Grid::centerSplitter(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	bool enableAutoResizing=false;
	
	if( argc >= 1 ) {
		// 1
		if( FromJS(cx, argv[argIndex], enableAutoResizing) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
	}

	// APIの実行と、戻り値の設定
	p->CenterSplitter(enableAutoResizing);

	return JS_TRUE;
}


JSBool Grid::clear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	


	// APIの実行と、戻り値の設定
	p->Clear();

	return JS_TRUE;
}


JSBool Grid::clearActionTriggers(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	int action=0;
	
	// 1
	if( FromJS(cx, argv[argIndex], action) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と、戻り値の設定
	p->ClearActionTriggers (action);

	return JS_TRUE;
}


JSBool Grid::dedicateKey(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	int keycode=0;
	
	// 1
	if( FromJS(cx, argv[argIndex], keycode) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と、戻り値の設定
	p->DedicateKey(keycode);

	return JS_TRUE;
}


JSBool Grid::enableCategories(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	bool enable=false;
	
	// 1
	if( FromJS(cx, argv[argIndex], enable) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
		return JS_FALSE;
	}


	// APIの実行と、戻り値の設定
	p->EnableCategories(enable);

	return JS_TRUE;
}


JSBool Grid::endLabelEdit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	bool commit=true;
	
	if( argc >= 1 ) {
		// 1
		if( FromJS(cx, argv[argIndex], commit) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
	}


	// APIの実行と、戻り値の設定
	p->EndLabelEdit(commit);

	return JS_TRUE;
}


JSBool Grid::ensureVisible(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}


	// APIの実行と、戻り値の設定
	vp->setBoolean( p->EnsureVisible(argId.get()) );

	return JS_TRUE;
}


JSBool Grid::getImageRect(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	wxPGProperty *property = NULL;
	int item = 0;
	
	// 1
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
			return JS_FALSE;
	}
	argIndex++;
	// 2
	if( FromJS(cx, argv[argIndex], item) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;


	// APIの実行と、戻り値の設定
	wxRect rc = p->GetImageRect(property, item );
	*vp = Rect::CreateObject(cx, new wxRect( rc ), NULL);
	return JS_TRUE;
}


JSBool Grid::getImageSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	wxPGProperty *property = NULL;
	int item = -1;
	
	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		// 2
		if( FromJS(cx, argv[argIndex], item) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 1:
		// 1
		property = Property::GetPrivate(cx, argv[argIndex], false);
		if( property == NULL ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
				return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と、戻り値の設定
	wxSize rc = p->GetImageSize(property, item );
	*vp = Size::CreateObject(cx, new wxSize( rc ), NULL);
	return JS_TRUE;
}


JSBool Grid::getLastItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	int flags=wxPG_ITERATE_DEFAULT;


	if( argc > 1 ) {
		argc = 1;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 1:
		// 1
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と、戻り値の設定
	wxPGProperty *pProp = p->GetLastItem( flags );
	*vp = Property::CreateObject(cx, pProp, NULL);
	return JS_TRUE;
}


JSBool Grid::getSplitterPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	unsigned int splitterIndex=0;


	if( argc > 1 ) {
		argc = 1;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 1:
		// 1
		if( FromJS(cx, argv[argIndex], splitterIndex) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と、戻り値の設定
	vp->setInt32( p->GetSplitterPosition ( splitterIndex ) );
	return JS_TRUE;
}


JSBool Grid::getUnspecifiedValueText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	int argFlags=0;


	if( argc > 1 ) {
		argc = 1;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 1:
		// 1
		if( FromJS(cx, argv[argIndex], argFlags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}


	// APIの実行と、戻り値の設定
	wxString str = p->GetUnspecifiedValueText( argFlags );
	*vp = ToJS(cx, str);

	return JS_TRUE;
}


JSBool Grid::hitTest(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	wxPoint pt;


	// APIの実行と、戻り値の設定
	wxPropertyGridHitTestResult  ret = p->HitTest( pt );
	JSObject *objAttr = JS_NewObject(cx, NULL, NULL, NULL);

	{
		wxString attr(_T("property"));
		wxPGProperty* pProp = ret.GetProperty();

		jsval attrValue;
		if( pProp == NULL ) {
			attrValue.setNull();
		} else {
			attrValue = Property::CreateObject( cx, pProp, NULL);
		}

		JS_SetUCProperty(cx, objAttr, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	}
	{
		wxString attr(_T("column"));

		jsval attrValue = ToJS(cx, ret.GetColumn());

		JS_SetUCProperty(cx, objAttr, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	}
	{
		wxString attr(_T("splitter"));
		jsval attrValue = ToJS(cx, ret.GetSplitter());
		JS_SetUCProperty(cx, objAttr, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	}
	{
		wxString attr(_T("splitterHitOffset"));
		jsval attrValue = ToJS(cx, ret.GetSplitterHitOffset());

		JS_SetUCProperty(cx, objAttr, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	}
	vp->setObjectOrNull(objAttr);

	return JS_TRUE;
}


JSBool Grid::makeColumnEditable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	unsigned int column;
	bool editable=true;


	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		// 2
		if( FromJS(cx, argv[argIndex], editable) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], column) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	// APIの実行と、戻り値の設定
	p->MakeColumnEditable( column, editable );

	return JS_TRUE;
}


JSBool Grid::onTLPChanging(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	wxWindow *newTLP = NULL;

	newTLP = Window::GetPrivate(cx, argv[argIndex], false );
	if( newTLP == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}



	// APIの実行と、戻り値の設定
	p->OnTLPChanging( newTLP);

	return JS_TRUE;
}


JSBool Grid::refreshEditor(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// APIの実行と、戻り値の設定
	p->RefreshEditor( );

	return JS_TRUE;
}


JSBool Grid::refreshProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	wxPGProperty *pProp = NULL;

	pProp = Property::GetPrivate(cx, argv[argIndex], false );
	if( pProp == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}



	// APIの実行と、戻り値の設定
	p->RefreshProperty( pProp);

	return JS_TRUE;
}


JSBool Grid::resetColours(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	

	// APIの実行と、戻り値の設定
	p->ResetColours( );

	return JS_TRUE;
}


JSBool Grid::resetColumnSizes(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	bool enableAutoResizing=false;
	
	if( argc >= 1 ) {
		if( FromJS(cx, argv[argIndex], enableAutoResizing) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
	}
	// APIの実行と、戻り値の設定
	p->ResetColumnSizes( enableAutoResizing );

	return JS_TRUE;
}


JSBool Grid::removeFromSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	
	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	
	
	// APIの実行と、戻り値の設定
	vp->setBoolean( p->RemoveFromSelection( argId.get() ) );

	return JS_TRUE;
}


JSBool Grid::selectProperty(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	GridInterface_ArgID	argId;
	bool focus=false;


	if( argc >= 2 ) {
		if( FromJS(cx, argv[1], focus) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Boolean");
			return JS_FALSE;
		}

	}

	// 1
	if( getGridInterface_ArgID(cx, argv[argIndex], argIndex+1, argId) == false ) {
		return JS_FALSE;
	}
	
	
	// APIの実行と、戻り値の設定
	vp->setBoolean( p->SelectProperty( argId.get(), focus ) );

	return JS_TRUE;
}


JSBool Grid::setSplitterPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	int newxpos = 0;
	int col=0;


	if( argc >= 2 ) {
		if( FromJS(cx, argv[1], col) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}

	}

	// 1
	if( FromJS(cx, argv[0], newxpos) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	
	
	// APIの実行と、戻り値の設定
	p->SetSplitterPosition( newxpos, col );

	return JS_TRUE;
}


JSBool Grid::setSplitterLeft(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPropertyGrid *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
	bool privateChildrenToo=false;


	if( argc >= 1 ) {
		if( FromJS(cx, argv[0], privateChildrenToo) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
			return JS_FALSE;
		}

	}

	
	
	// APIの実行と、戻り値の設定
	p->SetSplitterLeft ( privateChildrenToo );

	return JS_TRUE;
}



//-----------------------------------------------
//	wxPropertyGridInterface
//-----------------------------------------------
#define MY_IMPLE_GRID_IF(X) JSBool Grid::## X ## (JSContext *cx, unsigned argc, JS::Value *vp) \
{\
	JSObject *obj = JS_THIS_OBJECT(cx, vp);\
	JS::CallArgs argv = CallArgsFromVp(argc, vp);\
    wxPropertyGrid *p = GetPrivate(cx, obj);\
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
//MY_IMPLE_GRID_IF(changePropertyValue) ... same function defined avobe.
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
//MY_IMPLE_GRID_IF(refreshProperty) ... same function defined avobe.
#undef MY_IMPLE_GRID_IF


//------------------------------------------------------------------
//	GridEventHandler
//------------------------------------------------------------------

WXJS_INIT_EVENT_MAP(wxPropertyGrid)
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



#define IMPLE_EVT(NAME, STRNAMNE, EVT) void GridEventHandler::On ## NAME(wxPropertyGridEvent &event) \
{ \
	PrivGridEvent::Fire<GridEvent>(event, STRNAMNE);\
}\
void GridEventHandler::Connect ## NAME(wxPropertyGrid *p, bool connect) \
{\
	if ( connect )\
	{\
		p->Connect(EVT, \
		wxPropertyGridEventHandler(GridEventHandler::On ## NAME )); \
	}\
	else\
	{\
		p->Disconnect(EVT, \
			wxPropertyGridEventHandler(GridEventHandler::On ## NAME ));\
	}\
}

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


void GridEventHandler::InitConnectEventMap()
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
/*
void GridEventHandler::OnSelected(wxPropertyGridEvent &event)
{
	PrivGridEvent::Fire<GridEvent>(event, ZZZJS_PG_GRID_ON_SELECTED);
}
void GridEventHandler::ConnectSelected(wxPropertyGrid *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_PG_SELECTED, 
			wxPropertyGridEventHandler(GridEventHandler::OnSelected));
	}
	else
	{
		p->Disconnect(wxEVT_PG_SELECTED, 
			wxPropertyGridEventHandler(GridEventHandler::OnSelected));
	}
}
*/



