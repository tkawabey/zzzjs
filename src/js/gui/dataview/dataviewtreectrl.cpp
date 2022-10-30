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
#include "js/gui/misc/icon.h"
#include "js/gui/misc/imagelst.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/control/control.h"
#include "js/gui/dataview/dataviewtreectrl.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"
#include "js/gui/dataview/dataviewcolmn.h"
#include "js/gui/dataview/dataviewmodel.h"
#include "js/gui/dataview/dataviewevent.h"
#include "js/gui/dataview/dataviewctrl.h"
#include "js/gui/dataview/dataviewtreestore.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewTreeCtrl
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewTreeCtrl, "DataViewTreeCtrl", 1)

void DataViewTreeCtrl::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{
}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewTreeCtrl)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewTreeCtrl)
  WXJS_PROPERTY(P_IMAGE_LIST, "imageList")
  WXJS_PROPERTY(P_STORE, "store")
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

WXJS_BEGIN_GET_PROP(wxDataViewTreeCtrl, DataViewTreeCtrl)
	switch (id) 
	{
	case P_IMAGE_LIST:
        {
            wxImageList *imgList = p->GetImageList();
            if ( imgList != NULL )
            {
              JavaScriptClientData *data
                = dynamic_cast<JavaScriptClientData*>(imgList);
              if ( data != NULL )
              {
                vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
              }
            }
            break;
        }
		break;
	case P_STORE:
		{
			vp.set( DataViewTreeStore::CreateObject( 
				cx, 
				p->GetStore()
				)
			);
		}
		break;
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

WXJS_BEGIN_SET_PROP(wxDataViewTreeCtrl, DataViewTreeCtrl)
	switch (id) 
	{
    case P_IMAGE_LIST:
        {
          ImageList *imgList = ImageList::GetPrivate(cx, vp);
		  if ( imgList != NULL )
          {
            p->AssignImageList(imgList);
            JavaScriptClientData *data
              = dynamic_cast<JavaScriptClientData*>(imgList->GetClientObject());
            if ( data != NULL )
            {
              data->Protect(true);
              data->SetOwner(false);
            }
          }
		  break;
        }
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

WXJS_BEGIN_ADD_PROP(wxDataViewTreeCtrl, DataViewTreeCtrl)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;

	
	DataViewEventHandler::ConnectEvent(p, prop, true);
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewTreeCtrl, DataViewTreeCtrl)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
	
	DataViewEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP


WXJS_BEGIN_DESTRUCTOR(wxDataViewTreeCtrl, DataViewTreeCtrl)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewTreeCtrl)
	WXJS_METHOD("create", create, 3)
	WXJS_METHOD("appendContainer", appendContainer, 2)
	WXJS_METHOD("appendItem", appendItem, 2)
	WXJS_METHOD("deleteAllItems", deleteAllItems, 0)
	WXJS_METHOD("deleteChildren", deleteChildren, 1)
	WXJS_METHOD("deleteItem", deleteItem, 1)
	WXJS_METHOD("getChildCount", getChildCount, 1)
	WXJS_METHOD("getItemData", getItemData, 1)
	WXJS_METHOD("getItemExpandedIcon", getItemExpandedIcon, 1)
	WXJS_METHOD("getItemIcon", getItemIcon, 1)
	WXJS_METHOD("getItemText", getItemText, 1)
	WXJS_METHOD("getNthChild", getNthChild, 2)
	WXJS_METHOD("insertContainer", insertContainer, 3)
	WXJS_METHOD("insertItem", insertItem, 3)
	WXJS_METHOD("isContainer", isContainer, 1)
	WXJS_METHOD("prependContainer", prependContainer, 2)
	WXJS_METHOD("prependItem", prependItem, 2)
	WXJS_METHOD("setItemData", setItemData, 2)
	WXJS_METHOD("setItemExpandedIcon", setItemExpandedIcon, 2)
	WXJS_METHOD("setItemIcon", setItemIcon, 2)
	WXJS_METHOD("setItemText", setItemText, 2)


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

WXJS_BEGIN_CONSTRUCTOR(wxDataViewTreeCtrl, DataViewTreeCtrl)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxDataViewTreeCtrl *p = new wxDataViewTreeCtrl();
	
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
	
	
JSBool DataViewTreeCtrl::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool DataViewTreeCtrl::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxDataViewTreeCtrl *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
		
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(2, 6);
	
	argIndex = argc -1;
	switch(argc)
	{
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

		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::appendContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int				icon	=	-1;
	int				expanded =  -1;
	wxString		text(_T(""));
	wxClientData *	data=NULL;
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	if( argc > 5 ) {
		argc = 5;
	}
	
	switch(argc)
	{
	case 5:
		data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
	case 4:
		if ( ! FromJS(cx, argv[3], expanded) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 3:
		if ( ! FromJS(cx, argv[2], icon) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}

		wxDataViewItem *pItem = 
			DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem newItem = p->AppendContainer(*pItem, text, icon, expanded, data);

		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::appendItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int				icon	=	-1;
	wxString		text(_T(""));
	wxClientData *	data=NULL;
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	if( argc > 4 ) {
		argc = 4;
	}
	
	switch(argc)
	{
	case 4:
		data = new JavaScriptClientData(cx, argv[3].toObjectOrNull(), false, true);
	case 3:
		if ( ! FromJS(cx, argv[2], icon) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}

		wxDataViewItem *pItem = 
			DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem newItem = p->AppendItem(*pItem, text, icon, data);

		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::deleteAllItems(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	p->DeleteAllItems();
	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::deleteChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	p->DeleteChildren( *pItem );

	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::deleteItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	p->DeleteItem( *pItem );

	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::getChildCount(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	int ret = p->GetChildCount( *pItem );
	vp->setInt32( ret );
	
	return JS_TRUE;
}


JSBool DataViewTreeCtrl::getItemData(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	int ret = p->GetChildCount( *pItem );
	vp->setInt32( ret );
	
	return JS_TRUE;
}


JSBool DataViewTreeCtrl::getItemExpandedIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	const wxIcon& icon 	= p->GetItemExpandedIcon( *pItem );
	
	if( icon.IsOk() ) {
		*vp = Icon::CreateObject( 
			cx, 
			(wxIcon*)&icon
		);
	} else {
		*vp = JSVAL_VOID;
	}
	
	return JS_TRUE;
}


JSBool DataViewTreeCtrl::getItemIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	const wxIcon& icon 	= p->GetItemIcon( *pItem );
	
	if( icon.IsOk() ) {
		*vp = Icon::CreateObject( 
			cx, 
			(wxIcon*)&icon
		);
	} else {
		*vp = JSVAL_VOID;
	}
	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::getItemText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	wxString text 	= p->GetItemText( *pItem );
	*vp = ToJS(cx, text);
	
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::getNthChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int pos = 0;
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	
	if ( ! FromJS(cx, argv[1], pos) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}


	wxDataViewItem newItem = p->GetNthChild(*pItem, pos);


	// 戻り値
	if( newItem.IsOk() ) {
		*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
	} else {
		*vp = JSVAL_VOID;
	}
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::insertContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int				icon	=	-1;
	int				expanded =  -1;
	wxString		text(_T(""));
	wxClientData *	data=NULL;
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	if( argc > 6 ) {
		argc = 6;
	}
	
	switch(argc)
	{
	case 6:
		data = new JavaScriptClientData(cx, argv[5].toObjectOrNull(), false, true);
	case 5:
		if ( ! FromJS(cx, argv[4], expanded) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 5, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 4:
		if ( ! FromJS(cx, argv[3], icon) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[2], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		
		wxDataViewItem *pPrev = 
			DataViewItem::GetPrivate(cx, argv[1]);
		if( pPrev == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem *pParent = 
			DataViewItem::GetPrivate(cx, argv[0]);
		if( pParent == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem newItem = p->InsertContainer(*pParent, *pPrev, text, icon, expanded, data);

		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	return JS_TRUE;
}


JSBool DataViewTreeCtrl::insertItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int				icon	=	-1;
	int				expanded =  -1;
	wxString		text(_T(""));
	wxClientData *	data=NULL;
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	if( argc > 5 ) {
		argc = 5;
	}
	
	switch(argc)
	{
	case 5:
		data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
	case 4:
		if ( ! FromJS(cx, argv[3], icon) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[2], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		
		wxDataViewItem *pPrev = 
			DataViewItem::GetPrivate(cx, argv[1]);
		if( pPrev == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem *pParent = 
			DataViewItem::GetPrivate(cx, argv[0]);
		if( pParent == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem newItem = p->InsertContainer(*pParent, *pPrev, text, icon, expanded, data);

		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	return JS_TRUE;
}

JSBool DataViewTreeCtrl::isContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}



	// 戻り値
	vp->setBoolean( p->IsContainer(*pItem) );
	return JS_TRUE;
}


JSBool DataViewTreeCtrl::prependContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int				icon	=	-1;
	int				expanded =  -1;
	wxString		text(_T(""));
	wxClientData *	data=NULL;
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	if( argc > 5 ) {
		argc = 5;
	}
	
	switch(argc)
	{
	case 5:
		data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
	case 4:
		if ( ! FromJS(cx, argv[3], expanded) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 3:
		if ( ! FromJS(cx, argv[2], icon) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}

		wxDataViewItem *pParent = 
			DataViewItem::GetPrivate(cx, argv[0]);
		if( pParent == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem newItem = p->PrependContainer(*pParent, text, icon, expanded, data);

		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	return JS_TRUE;
}



JSBool DataViewTreeCtrl::prependItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int				icon	=	-1;
	int				expanded =  -1;
	wxString		text(_T(""));
	wxClientData *	data=NULL;
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	if( argc > 4 ) {
		argc = 4;
	}
	
	switch(argc)
	{
	case 4:
		data = new JavaScriptClientData(cx, argv[3].toObjectOrNull(), false, true);
	case 3:
		if ( ! FromJS(cx, argv[2], icon) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}


		wxDataViewItem *pParent = 
			DataViewItem::GetPrivate(cx, argv[0]);
		if( pParent == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
			return JS_FALSE;
		}


		wxDataViewItem newItem = p->PrependItem(*pParent, text, icon, data);

		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	return JS_TRUE;
}


JSBool DataViewTreeCtrl::setItemData(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	wxClientData *	data=NULL;
	data = new JavaScriptClientData(cx, argv[1].toObjectOrNull(), false, true);

	p->SetItemData( *pItem, data );

	// 戻り値
	 // 無し

	return JS_TRUE;
}


JSBool DataViewTreeCtrl::setItemExpandedIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}

	wxIcon* pIcon = Icon::GetPrivate(cx, argv[1]);
	if( pIcon == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Icon");
		return JS_FALSE;
	}

	p->SetItemExpandedIcon( *pItem, *pIcon );

	// 戻り値
	 // 無し

	return JS_TRUE;
}


JSBool DataViewTreeCtrl::setItemIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}

	wxIcon* pIcon = Icon::GetPrivate(cx, argv[1]);
	if( pIcon == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Icon");
		return JS_FALSE;
	}

	p->SetItemIcon( *pItem, *pIcon );

	// 戻り値
	 // 無し

	return JS_TRUE;
}


JSBool DataViewTreeCtrl::setItemText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxDataViewTreeCtrl *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem *pItem = 
		DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxDataViewItem");
		return JS_FALSE;
	}
	
	wxString text;
	if ( ! FromJS(cx, argv[1], text) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	p->SetItemText( *pItem, text );


	// 戻り値
	 // 無し

	return JS_TRUE;
}
