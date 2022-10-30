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

#include "js/gui/misc/size.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/validate.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/rect.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/control/control.h"
#include "js/gui/dataview/dataviewctrl.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"
#include "js/gui/dataview/dataviewcolmn.h"
#include "js/gui/dataview/dataviewmodel.h"
#include "js/gui/dataview/dataviewevent.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewCtrl
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewCtrl, "DataViewCtrl", 1)

void DataViewCtrl::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{
	DataViewEventHandler::InitConnectEventMap();
}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewCtrl)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewCtrl)
  WXJS_PROPERTY(P_ColumnCount, "columnCount")
  WXJS_PROPERTY(P_ExpanderColumn, "expanderColumn")
  WXJS_PROPERTY(P_CurrentItem, "currentItem")
  WXJS_PROPERTY(P_CurrentColumn, "currentColumn")
  WXJS_PROPERTY(P_Indent, "indent")
  WXJS_PROPERTY(P_Model, "model")
  WXJS_PROPERTY(P_SelectedItemsCount, "selectedItemsCount")
  WXJS_PROPERTY(P_SortingColumn, "sortingColumn")
  WXJS_PROPERTY(P_SortingColumns, "sortingColumns")
  WXJS_PROPERTY(P_HasSelection, "hasSelection")
  WXJS_PROPERTY(P_IsMultiColumnSortAllowed, "isMultiColumnSortAllowed")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewCtrl, DataViewCtrl)
	switch (id) 
	{
	case P_ColumnCount:
		ToJSVal(cx, vp, p->GetColumnCount ());
		break;
	case P_ExpanderColumn:
		{
			vp.set( DataViewColumn::CreateObject( 
				cx, 
				p->GetExpanderColumn()
				)
			);
		}
		break;
	case P_CurrentItem:
		{
			vp.set( DataViewItem::CreateObject( 
				cx, 
				new wxDataViewItem( p->GetCurrentItem () )
				)
			);
		}
		break;
	case P_CurrentColumn:
		{
			if( p->GetCurrentColumn() == NULL ) {
				vp.set( JSVAL_VOID );
			} else {
				vp.set( DataViewColumn ::CreateObject( 
					cx, 
					p->GetCurrentColumn()
					)
				);
			}
		}
		break;
	case P_Indent:
		ToJSVal(cx, vp, p->GetIndent  ());
		break;
	case P_Model:
		{
			if( p->GetModel() == NULL ) {
				vp.set( JSVAL_VOID );
			} else {
				vp.set( DataViewModel::CreateObject( 
					cx, 
					p->GetModel()
					)
				);
			}
		}
		break;
	case P_SelectedItemsCount:
		ToJSVal(cx, vp, p->GetSelectedItemsCount());
		break;
	case P_Selection:
		{
			wxDataViewItem item = p->GetSelection();
			vp.set( DataViewItem::CreateObject(
				cx,
				new wxDataViewItem(item))
			);
		}
		break;
	case P_Selections:
		{
			wxDataViewItemArray arr;
			p->GetSelections( arr );
			JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
			for(size_t i = 0; i < arr.GetCount(); i++ ) {
				jsval element = DataViewItem::CreateObject(cx, &arr[i]);
				JS_SetElement(cx, objArray, i, &element);
			}
			wxDataViewItem item = p->GetSelection();
			vp.setObjectOrNull( objArray );
		}
		break;
	case P_SortingColumn:
		{
			wxDataViewColumn *item = p->GetSortingColumn ();
			vp.set( DataViewColumn::CreateObject(
				cx,
				item)
			);
		}
		break;
	case P_SortingColumns:
		{
			wxVector<wxDataViewColumn*> arr
				= p->GetSortingColumns( );
			JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
			for(size_t i = 0; i < arr.size(); i++ ) {
				jsval element = DataViewColumn::CreateObject(cx, arr[i]);
				JS_SetElement(cx, objArray, i, &element);
			}
			wxDataViewItem item = p->GetSelection();
			vp.setObjectOrNull( objArray );
		}
		break;
	case P_HasSelection:
		ToJSVal(cx, vp, p->HasSelection());
		break;
	case P_IsMultiColumnSortAllowed:
		ToJSVal(cx, vp, p->IsMultiColumnSortAllowed());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDataViewCtrl, DataViewCtrl)
	switch (id) 
	{
	case P_ExpanderColumn:
		{
			wxDataViewColumn* pItem = 
				DataViewColumn::GetPrivate(cx, vp);
			if ( pItem != NULL )
			{
				p->SetExpanderColumn( pItem );
			}
		}
		break;
	case P_CurrentItem:
		{
			wxDataViewItem* pItem = 
				DataViewItem::GetPrivate(cx, vp);
			if ( pItem != NULL )
			{
				p->SetCurrentItem( *pItem );
			}
		}
		break;
	case P_Indent:
		{
			int val = 0;
			if( FromJS(cx, vp, val) == false ) {
				p->SetIndent( val );
			}
		}
		break;
	case P_Selection:
		{
			wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, vp);
			if( pItem != NULL ) {
				p->Select( *pItem );
			}
		}
		break;
	case P_Selections:
	    JSObject *objItems = JSVAL_TO_OBJECT(vp);
	    if (    objItems != (JSObject *) NULL
		     && JS_IsArrayObject(cx, objItems) )
	    {
			wxDataViewItemArray arr;
			uint32_t length = 0;
		    JS_GetArrayLength(cx, objItems, &length);
		    for(uint32_t i =0; i < length; i++)
		    {
			    JS::Value element;
			    JS_GetElement(cx, objItems, i, &element);

				wxDataViewItem* pItem = 
					DataViewItem::GetPrivate(cx, element.toObjectOrNull());
				arr.Add(*pItem);
		    }
			p->SetSelections( arr );			
	    }
		break;
	}
	return true;
WXJS_END_SET_PROP

WXJS_BEGIN_ADD_PROP(wxDataViewCtrl, DataViewCtrl)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;

	
	DataViewEventHandler::ConnectEvent(p, prop, true);
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewCtrl, DataViewCtrl)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
	
	DataViewEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP


WXJS_BEGIN_DESTRUCTOR(wxDataViewCtrl, DataViewCtrl)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewCtrl)
	WXJS_METHOD("create", create, 3)
	WXJS_METHOD("allowMultiColumnSort", allowMultiColumnSort, 1)
	WXJS_METHOD("appendColumn", appendColumn, 1)
	WXJS_METHOD("prependColumn", prependColumn, 1)
	WXJS_METHOD("insertColumn", insertColumn, 2)
	WXJS_METHOD("associateModel", associateModel, 1)
	WXJS_METHOD("clearColumns", clearColumns, 0)
	WXJS_METHOD("collapse", collapse, 1)
	WXJS_METHOD("deleteColumn", deleteColumn, 1)
	WXJS_METHOD("editItem", editItem, 2)
	WXJS_METHOD("enableDragSource", enableDragSource, 1)
	WXJS_METHOD("enableDropTarget", enableDropTarget, 1)
	WXJS_METHOD("ensureVisible", ensureVisible, 2)
	WXJS_METHOD("expand", expand, 1)
	WXJS_METHOD("expandAncestors", expandAncestors, 1)
	WXJS_METHOD("getColumn", getColumn, 1)
	WXJS_METHOD("getColumnPosition", getColumnPosition, 1)
	WXJS_METHOD("getItemRect", getItemRect, 1)
	WXJS_METHOD("hitTest", hitTest, 1)
	WXJS_METHOD("isExpanded", isExpanded, 1)
	WXJS_METHOD("isSelected", isSelected, 1)
	WXJS_METHOD("select", select, 1)
	WXJS_METHOD("selectAll", selectAll, 0)
	WXJS_METHOD("unselect", unselect, 1)
	WXJS_METHOD("unselectAll", unselectAll, 0)
	WXJS_METHOD("setRowHeight", setRowHeight, 1)
	WXJS_METHOD("toggleSortByColumn", toggleSortByColumn, 1)


	WXJS_METHOD("appendBitmapColumn", appendBitmapColumn, 2)
	WXJS_METHOD("prependBitmapColumn", prependBitmapColumn, 2)
	WXJS_METHOD("appendDateColumn", appendDateColumn, 2)
	WXJS_METHOD("prependDateColumn", prependDateColumn , 2)
	WXJS_METHOD("appendIconTextColumn", appendIconTextColumn, 2)
	WXJS_METHOD("prependIconTextColumn", prependIconTextColumn  , 2)
	WXJS_METHOD("appendProgressColumn", appendProgressColumn , 2)
	WXJS_METHOD("prependProgressColumn", prependProgressColumn   , 2)
	WXJS_METHOD("appendTextColumn", appendTextColumn, 2)
	WXJS_METHOD("prependTextColumn", prependTextColumn, 2)
	WXJS_METHOD("appendToggleColumn", appendToggleColumn, 2)
	WXJS_METHOD("prependToggleColumn", prependToggleColumn, 2)
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

WXJS_BEGIN_CONSTRUCTOR(wxDataViewCtrl, DataViewCtrl)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxDataViewCtrl *p = new wxDataViewCtrl();
	
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
WXJS_END_CONSTRUCTOR
	
	
JSBool DataViewCtrl::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool DataViewCtrl::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxDataViewCtrl *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	if ( argc > 7 )
		argc = 7;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	const wxValidator *val = &wxDefaultValidator;
	wxString name = wxDataViewCtrlNameStr;
	
	ZZZJS_CHECK_ARG_COUNT(2, 7);

	switch(argc)
	{
	case 7:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		argIndex--;
	case 6:
		val = Validator::GetPrivate(cx, argv[argIndex]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Validator");
			return JS_FALSE;
		}
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

		JavaScriptClientData *clntParent 
			= dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), style, *val, name) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	return JS_TRUE;
}

JSBool DataViewCtrl::allowMultiColumnSort(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	bool allow = false;

	// 1.
    if ( ! FromJS(cx, argv[0], allow) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
        return JS_FALSE;
    }
	
	// 戻り値
	vp->setBoolean(
		p->AllowMultiColumnSort(allow)	
	);
	
	return JS_TRUE;
}
JSBool DataViewCtrl::appendColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxDataViewColumn *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[0]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}

	
	// 戻り値
	vp->setBoolean(
		p->AppendColumn (pClmn )	
	);
	
	return JS_TRUE;
}
JSBool DataViewCtrl::prependColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxDataViewColumn *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[0]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}

	
	// 戻り値
	vp->setBoolean(
		p->PrependColumn  (pClmn )	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::insertColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int col = 0;
	
	// 1.
    if ( ! FromJS(cx, argv[0], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	wxDataViewColumn *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[1]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}

	
	// 戻り値
	vp->setBoolean(
		p->InsertColumn(col, pClmn )	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::associateModel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxDataViewModel  *pModel = 
		DataViewModel::GetPrivate(cx, argv[0]);
	if( pModel == NULL ) {
		return JS_FALSE;
	}

	
	// 戻り値
	vp->setBoolean(
		p->AssociateModel( pModel )	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::clearColumns(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	vp->setBoolean(
		p->ClearColumns()	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::collapse(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxDataViewItem  *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	
	// 戻り値
	p->Collapse( *pItem );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::deleteColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxDataViewColumn   *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[0]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}

	
	// 戻り値
	vp->setBoolean(
		p->DeleteColumn( pClmn )	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::editItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2
	wxDataViewColumn   *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[1]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}

//	wxDataFormat  a = wxDF_INVALID;
	// 戻り値
	p->EditItem ( *pItem, pClmn );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::enableDragSource(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int format = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], format) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	vp->setBoolean(
		p->EnableDragSource( (wxDataFormatId)format )	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::enableDropTarget(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int format = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], format) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	vp->setBoolean(
		p->EnableDropTarget( (wxDataFormatId)format )	
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::ensureVisible(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2
	wxDataViewColumn   *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[1]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	p->EnsureVisible( *pItem, pClmn );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::expand(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	p->Expand( *pItem );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::expandAncestors(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	p->ExpandAncestors( *pItem );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::getColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int pos = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], pos) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	wxDataViewColumn *pClmn = p->GetColumn( pos );
	if( pClmn == NULL ) {
		*vp = JSVAL_VOID;
	} else {
		*vp = DataViewColumn::CreateObject(cx, pClmn);
	}
	
	return JS_TRUE;
}

JSBool DataViewCtrl::getColumnPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	// 1
	wxDataViewColumn   *pClmn = 
		DataViewColumn::GetPrivate(cx, argv[0]);
	if( pClmn == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	vp->setInt32(
		p->GetColumnPosition( pClmn )
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::getItemRect(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewColumn   *pClmn = NULL;
	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	if( argc >= 2 ) {
		// 2
		pClmn = 
			DataViewColumn::GetPrivate(cx, argv[1]);
		if( pClmn == NULL ) {
			return JS_FALSE;
		}
	}


	// 戻り値
	wxRect  rc = p->GetItemRect(*pItem, pClmn);
	*vp = Rect::CreateObject( cx, new wxRect( rc ) );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::hitTest(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	wxDataViewItem item;
	wxDataViewColumn   *pClmn = NULL;

	// 1.
    ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);


	p->HitTest(*(apPoint.get()), item, pClmn);

	JSObject *newObject = JS_NewObject(cx, NULL, NULL, NULL);

	jsval v = DataViewItem::CreateObject(cx, new wxDataViewItem(item) );

	JS_SetProperty(cx, newObject, "item", &v);
	if( pClmn == NULL ) {
		v = JSVAL_VOID;
	} else {
		v = DataViewColumn::CreateObject(cx, pClmn );
	}
	JS_SetProperty(cx, newObject, "column", &v);

	vp->setObjectOrNull(newObject);

	return JS_TRUE;
}


JSBool DataViewCtrl::isExpanded(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	vp->setBoolean(
		p->IsExpanded( *pItem )
	);
	
	return JS_TRUE;
}


JSBool DataViewCtrl::isSelected(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	vp->setBoolean(
		p->IsSelected( *pItem )
	);
	
	return JS_TRUE;
}


JSBool DataViewCtrl::select(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	p->Select( *pItem );
	
	return JS_TRUE;
}


JSBool DataViewCtrl::selectAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	// 戻り値
	p->SelectAll();
	
	return JS_TRUE;
}

JSBool DataViewCtrl::unselect(JSContext *cx, unsigned argc, JS::Value *vp)
{
//	wxItemAttr oo;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	// 1
	wxDataViewItem    *pItem = 
		DataViewItem ::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	p->Unselect( *pItem );
	
	return JS_TRUE;
}

JSBool DataViewCtrl::unselectAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
//	wxItemAttr oo;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	p->UnselectAll();
	
	return JS_TRUE;
}

JSBool DataViewCtrl::setRowHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int rowHeight = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], rowHeight) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	vp->setBoolean(
		p->SetRowHeight( rowHeight )
	);
	
	return JS_TRUE;
}

JSBool DataViewCtrl::toggleSortByColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int rowHeight = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], rowHeight) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	p->ToggleSortByColumn( rowHeight );
	
	return JS_TRUE;
}


JSBool DataViewCtrl::innerAppendXXXColumn(int method, 
								   JSContext *cx, 
								   unsigned argc, 
								   JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxString label;
	zzzJsPtr<wxBitmap> apBitmap;
	unsigned int model_column = 0;
	int mode = wxDATAVIEW_CELL_INERT;
	int width = -1;
	int align = wxALIGN_CENTER;
	int flags = wxDATAVIEW_COL_RESIZABLE;
	int iOr = 0;

	
	if( argc > 6 ) {
		argc = 6;
	}
	switch( argc ) {
	case 6:
		if ( ! FromJS(cx, argv[5], flags) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 6, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 5:
		if ( ! FromJS(cx, argv[4], align) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 5, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 4:
		if ( ! FromJS(cx, argv[3], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 3:
		if ( ! FromJS(cx, argv[2], mode) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		// 2.
		if ( ! FromJS(cx, argv[1], model_column) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// 1.
		if( argv[0].isString() ) {
			iOr = 0;
			if ( ! FromJS(cx, argv[0], label) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
		} else {
			iOr = 1;
			if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[0], apBitmap.bAllocation)) == false ) {
				return false;
			}
		}
	}

	wxDataViewColumn* pClmn = NULL;
	if( iOr == 0 ) {
		switch (method)
		{
		case 0:
			pClmn = p->AppendBitmapColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 1:
			pClmn = p->PrependBitmapColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 2:
			pClmn = p->AppendDateColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 3:
			pClmn = p->PrependDateColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 4:
			pClmn = p->AppendIconTextColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 5:
			pClmn = p->PrependIconTextColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 6:
			pClmn = p->AppendProgressColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 7:
			pClmn = p->PrependProgressColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 8:
			pClmn = p->AppendTextColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 9:
			pClmn = p->PrependTextColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 10:
			pClmn = p->AppendToggleColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 11:
			pClmn = p->PrependToggleColumn(label, model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		default:
			break;
		}
	} else {
		switch (method)
		{
		case 0:
			pClmn = p->AppendBitmapColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 1:
			pClmn = p->PrependBitmapColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 2:
			pClmn = p->AppendDateColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 3:
			pClmn = p->PrependDateColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 4:
			pClmn = p->AppendIconTextColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 5:
			pClmn = p->PrependIconTextColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 6:
			pClmn = p->AppendProgressColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 7:
			pClmn = p->PrependProgressColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 8:
			pClmn = p->AppendTextColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 9:
			pClmn = p->PrependTextColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 10:
			pClmn = p->AppendToggleColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		case 11:
			pClmn = p->PrependToggleColumn(*(apBitmap.get()), model_column, (wxDataViewCellMode)mode, width, (wxAlignment)align, flags);
			break;
		default:
			break;
		}
	}
	
	// 戻り値
	if( pClmn == NULL ) {
		*vp = JSVAL_VOID;
	} else {
		*vp = DataViewColumn::CreateObject(cx, pClmn);
	}
	
	return JS_TRUE;
}


JSBool DataViewCtrl::appendBitmapColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(0, cx, argc, vp);
}

JSBool DataViewCtrl::prependBitmapColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(1, cx, argc, vp);
}


JSBool DataViewCtrl::appendDateColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(2, cx, argc, vp);
}

JSBool DataViewCtrl::prependDateColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(3, cx, argc, vp);
}


JSBool DataViewCtrl::appendIconTextColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(4, cx, argc, vp);
}

JSBool DataViewCtrl::prependIconTextColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(5, cx, argc, vp);
}



JSBool DataViewCtrl::appendProgressColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(6, cx, argc, vp);
}

JSBool DataViewCtrl::prependProgressColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(7, cx, argc, vp);
}



JSBool DataViewCtrl::appendTextColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(8, cx, argc, vp);
}

JSBool DataViewCtrl::prependTextColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(9, cx, argc, vp);
}



JSBool DataViewCtrl::appendToggleColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(10, cx, argc, vp);
}

JSBool DataViewCtrl::prependToggleColumn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return innerAppendXXXColumn(11, cx, argc, vp);
}




//---------------------------------------------------------------
//
//	DataViewEventHandler
//
//---------------------------------------------------------------
WXJS_INIT_EVENT_MAP(wxDataViewCtrl)
const wxString WXJS_DATAVIEW_SELECT_CHANGE = wxT("onSelectChange");
const wxString WXJS_DATAVIEW_ITEM_ACTIVATED = wxT("onItemActivated");
const wxString WXJS_DATAVIEW_ITEM_START_EDITING = wxT("onItemStartEditing");
const wxString WXJS_DATAVIEW_ITEM_EDITING_STARTED = wxT("onItemEndingStated");
const wxString WXJS_DATAVIEW_ITEM_EDITING_DONE = wxT("onItemEndingDone");
const wxString WXJS_DATAVIEW_ITEM_COLLAPSING = wxT("onItemCollapsing");
const wxString WXJS_DATAVIEW_ITEM_COLLAPSED = wxT("onItemCollapsed");
const wxString WXJS_DATAVIEW_ITEM_EXPANDING= wxT("onItemExpanding");
const wxString WXJS_DATAVIEW_ITEM_EXPANDED = wxT("onItemExpanded");
const wxString WXJS_DATAVIEW_ITEM_VALUE_CHANGED= wxT("onItemValueChanged");
const wxString WXJS_DATAVIEW_ITEM_CONTEXT_MENU = wxT("onItemContextMenu");
const wxString WXJS_DATAVIEW_COLUMN_HEADER_CLICK = wxT("onColumnHeaderClick");
const wxString WXJS_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK = wxT("onColumnHeaderRightClick");
const wxString WXJS_DATAVIEW_COLUMN_SORTED = wxT("onColumnSorted");
const wxString WXJS_DATAVIEW_COLUMN_REORDERED = wxT("onColumnReOrdered");
const wxString WXJS_DATAVIEW_ITEM_BEGIN_DRAG = wxT("onItemBeginDrag");
const wxString WXJS_DATAVIEW_ITEM_DROP_POSSIBLE= wxT("onItemDropPossible");
const wxString WXJS_DATAVIEW_ITEM_DROP = wxT("onItemDrop");



void DataViewEventHandler::OnSelectChange(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_SELECT_CHANGE);
}
void DataViewEventHandler::OnItemActivated(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_ACTIVATED);
}
void DataViewEventHandler::OnItemStartEditing(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_START_EDITING);
}
void DataViewEventHandler::OnItemEndingStated(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_EDITING_STARTED);
}
void DataViewEventHandler::OnItemEndingDone(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_EDITING_DONE);
}
void DataViewEventHandler::OnItemCollapsing(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_COLLAPSING);
}
void DataViewEventHandler::OnItemCollapsed(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_COLLAPSED);
}
void DataViewEventHandler::OnItemExpanding(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_EXPANDING);
}
void DataViewEventHandler::OnItemExpanded(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_EXPANDED);
}
void DataViewEventHandler::OnItemValueChanged(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_VALUE_CHANGED);
}
void DataViewEventHandler::OnItemContextMenu(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_CONTEXT_MENU);
}
void DataViewEventHandler::OnColumnHeaderClick(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_COLUMN_HEADER_CLICK);
}
void DataViewEventHandler::OnColumnHeaderRightClick(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK);
}
void DataViewEventHandler::OnColumnSorted(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_COLUMN_SORTED);
}
void DataViewEventHandler::OnColumnReOrdered(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_COLUMN_REORDERED);
}
void DataViewEventHandler::OnItemBeginDrag(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_BEGIN_DRAG);
}
void DataViewEventHandler::OnItemDropPossible(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_DROP_POSSIBLE);
}
void DataViewEventHandler::OnItemDrop(wxDataViewEvent &event)
{
	PrivDataViewEvent::Fire<DataViewEvent>(event, WXJS_DATAVIEW_ITEM_DROP);
}

void DataViewEventHandler::ConnectSelectChange(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_SELECTION_CHANGED, 
			wxDataViewEventHandler(DataViewEventHandler::OnSelectChange));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_SELECTION_CHANGED, 
			wxDataViewEventHandler(DataViewEventHandler::OnSelectChange));
	}
}
void DataViewEventHandler::ConnectItemActivated(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_ACTIVATED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemActivated));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_ACTIVATED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemActivated));
	}
}
void DataViewEventHandler::ConnectItemStartEditing(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_START_EDITING, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemStartEditing));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_START_EDITING, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemStartEditing));
	}
}
void DataViewEventHandler::ConnectItemEndingStated(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_EDITING_STARTED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemEndingStated));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_EDITING_STARTED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemEndingStated));
	}
}
void DataViewEventHandler::ConnectItemEndingDone(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_EDITING_DONE,
			wxDataViewEventHandler(DataViewEventHandler::OnItemEndingDone));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_EDITING_DONE, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemEndingDone));
	}
}
void DataViewEventHandler::ConnectItemCollapsing(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_COLLAPSING,
			wxDataViewEventHandler(DataViewEventHandler::OnItemCollapsing));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_COLLAPSING, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemCollapsing));
	}
}
void DataViewEventHandler::ConnectItemCollapsed(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_COLLAPSED,
			wxDataViewEventHandler(DataViewEventHandler::OnItemCollapsed));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_COLLAPSED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemCollapsed));
	}
}
void DataViewEventHandler::ConnectItemExpanding(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_EXPANDING,
			wxDataViewEventHandler(DataViewEventHandler::OnItemExpanding));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_EXPANDING, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemExpanding));
	}
}
void DataViewEventHandler::ConnectItemExpanded(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_EXPANDED,
			wxDataViewEventHandler(DataViewEventHandler::OnItemExpanded));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_EXPANDED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemExpanded));
	}
}
void DataViewEventHandler::ConnectItemValueChanged(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED,
			wxDataViewEventHandler(DataViewEventHandler::OnItemValueChanged));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemValueChanged));
	}
}
void DataViewEventHandler::ConnectItemContextMenu(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU,
			wxDataViewEventHandler(DataViewEventHandler::OnItemContextMenu));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemContextMenu));
	}
}
void DataViewEventHandler::ConnectColumnHeaderClick(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK,
			wxDataViewEventHandler(DataViewEventHandler::OnColumnHeaderClick));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, 
			wxDataViewEventHandler(DataViewEventHandler::OnColumnHeaderClick));
	}
}
void DataViewEventHandler::ConnectColumnHeaderRightClick(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK,
			wxDataViewEventHandler(DataViewEventHandler::OnColumnHeaderRightClick));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK, 
			wxDataViewEventHandler(DataViewEventHandler::OnColumnHeaderRightClick));
	}
}
void DataViewEventHandler::ConnectColumnSorted(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_COLUMN_SORTED,
			wxDataViewEventHandler(DataViewEventHandler::OnColumnSorted));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_COLUMN_SORTED, 
			wxDataViewEventHandler(DataViewEventHandler::OnColumnSorted));
	}
}
void DataViewEventHandler::ConnectColumnReOrdered(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_COLUMN_REORDERED,
			wxDataViewEventHandler(DataViewEventHandler::OnColumnReOrdered));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_COLUMN_REORDERED, 
			wxDataViewEventHandler(DataViewEventHandler::OnColumnReOrdered));
	}
}
void DataViewEventHandler::ConnectItemBeginDrag(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG,
			wxDataViewEventHandler(DataViewEventHandler::OnItemBeginDrag));
	}
	else
	{
		p->Disconnect(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG, 
			wxDataViewEventHandler(DataViewEventHandler::OnItemBeginDrag));
	}
}
void DataViewEventHandler::ConnectItemDropPossible(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect( wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE ,
			wxDataViewEventHandler(DataViewEventHandler::OnItemDropPossible));
	}
	else
	{
		p->Disconnect( wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE , 
			wxDataViewEventHandler(DataViewEventHandler::OnItemDropPossible));
	}
}
void DataViewEventHandler::ConnectItemDrop(wxDataViewCtrl *p, bool connect)
{
	if ( connect )
	{
		p->Connect( wxEVT_DATAVIEW_ITEM_DROP ,
			wxDataViewEventHandler(DataViewEventHandler::OnItemDrop));
	}
	else
	{
		p->Disconnect( wxEVT_DATAVIEW_ITEM_DROP , 
			wxDataViewEventHandler(DataViewEventHandler::OnItemDrop));
	}
}

void DataViewEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_DATAVIEW_SELECT_CHANGE, ConnectSelectChange);
    AddConnector(WXJS_DATAVIEW_ITEM_ACTIVATED, ConnectItemActivated);
    AddConnector(WXJS_DATAVIEW_ITEM_START_EDITING, ConnectItemStartEditing);
    AddConnector(WXJS_DATAVIEW_ITEM_EDITING_STARTED, ConnectItemEndingStated);
    AddConnector(WXJS_DATAVIEW_ITEM_EDITING_DONE, ConnectItemEndingDone);
    AddConnector(WXJS_DATAVIEW_ITEM_COLLAPSING, ConnectItemCollapsing);
    AddConnector(WXJS_DATAVIEW_ITEM_COLLAPSED, ConnectItemCollapsed);
    AddConnector(WXJS_DATAVIEW_ITEM_EXPANDING, ConnectItemExpanding);
    AddConnector(WXJS_DATAVIEW_ITEM_EXPANDED, ConnectItemExpanded);
    AddConnector(WXJS_DATAVIEW_ITEM_VALUE_CHANGED, ConnectItemValueChanged);
    AddConnector(WXJS_DATAVIEW_ITEM_CONTEXT_MENU, ConnectItemContextMenu);
    AddConnector(WXJS_DATAVIEW_COLUMN_HEADER_CLICK, ConnectColumnHeaderClick);
    AddConnector(WXJS_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK, ConnectColumnHeaderRightClick);
    AddConnector(WXJS_DATAVIEW_COLUMN_SORTED, ConnectColumnSorted);
    AddConnector(WXJS_DATAVIEW_COLUMN_REORDERED, ConnectColumnReOrdered);
    AddConnector(WXJS_DATAVIEW_ITEM_BEGIN_DRAG, ConnectItemBeginDrag);
    AddConnector(WXJS_DATAVIEW_ITEM_DROP_POSSIBLE, ConnectItemDropPossible);
    AddConnector(WXJS_DATAVIEW_ITEM_DROP, ConnectItemDrop);
}
