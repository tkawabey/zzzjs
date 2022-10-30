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
#include "js/gui/dataview/dataviewlistctrl.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"
#include "js/gui/dataview/dataviewcolmn.h"
#include "js/gui/dataview/dataviewmodel.h"
#include "js/gui/dataview/dataviewevent.h"
#include "js/gui/dataview/dataviewctrl.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewListCtrl
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewListCtrl, "DataViewListCtrl", 1)

void DataViewListCtrl::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{
}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewListCtrl)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewListCtrl)
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

WXJS_BEGIN_GET_PROP(wxDataViewListCtrl, DataViewListCtrl)
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

WXJS_BEGIN_SET_PROP(wxDataViewListCtrl, DataViewListCtrl)
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

WXJS_BEGIN_ADD_PROP(wxDataViewListCtrl, DataViewListCtrl)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;

	
	DataViewEventHandler::ConnectEvent(p, prop, true);
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewListCtrl, DataViewListCtrl)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
	
	DataViewEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP


WXJS_BEGIN_DESTRUCTOR(wxDataViewListCtrl, DataViewListCtrl)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewListCtrl)
	WXJS_METHOD("create", create, 3)
	WXJS_METHOD("itemToRow", itemToRow, 1)
	WXJS_METHOD("rowToItem", rowToItem, 1)


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

WXJS_BEGIN_CONSTRUCTOR(wxDataViewListCtrl, DataViewListCtrl)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxDataViewListCtrl *p = new wxDataViewListCtrl();
	
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
	
	
JSBool DataViewListCtrl::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool DataViewListCtrl::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxDataViewListCtrl *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	const wxValidator *val = &wxDefaultValidator;
	

	ZZZJS_CHECK_ARG_COUNT(2, 6);

	switch(argc)
	{
	case 6:
		val = Validator::GetPrivate(cx, argv[5]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 6, "Validator");
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

		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	return JS_TRUE;
}

JSBool DataViewListCtrl::itemToRow(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewListCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	
	// –ß‚è’l
	vp->setInt32(
		p->ItemToRow (*pItem )	
	);
	
	return JS_TRUE;
}
JSBool DataViewListCtrl::rowToItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewListCtrl *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int row = 0;

	
    if ( ! FromJS(cx, argv[0], row) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	wxDataViewItem item = p->RowToItem( row );

	
	// –ß‚è’l
	*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(item));
	
	return JS_TRUE;
}
