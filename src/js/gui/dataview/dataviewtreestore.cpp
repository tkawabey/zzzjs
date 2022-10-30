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
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/icon.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewtreestore.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewTreeStore
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewTreeStore, "DataViewTreeStore", 1)

void DataViewTreeStore::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{

}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewTreeStore)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewTreeStore)
  WXJS_PROPERTY(P_ColumnCount, "columnCount")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewTreeStore, DataViewTreeStore)
	switch (id) 
	{
	case P_ColumnCount:
		ToJSVal(cx, vp, p->GetColumnCount ());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDataViewTreeStore, DataViewTreeStore)
	//switch (id) 
	//{
	//case P_FLAG:
	//	{
	//		int value = 0;
	//		if ( FromJS(cx, vp, value) )
	//		{

	//		}
	//	}
	//	break;
	//}
	return true;
WXJS_END_SET_PROP

WXJS_BEGIN_ADD_PROP(wxDataViewTreeStore, DataViewTreeStore)
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewTreeStore, DataViewTreeStore)
  return true;
WXJS_END_DEL_PROP


WXJS_BEGIN_DESTRUCTOR(wxDataViewTreeStore, DataViewTreeStore)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewTreeStore)
	WXJS_METHOD("appendContainer", appendContainer, 2)
    WXJS_METHOD("appendItem", appendItem, 2)
    WXJS_METHOD("deleteAllItems", deleteAllItems, 0)
    WXJS_METHOD("deleteChildren", deleteChildren, 1)
    WXJS_METHOD("deleteItem", deleteItem, 1)
    WXJS_METHOD("getChildCount", getChildCount, 1)
    WXJS_METHOD("getItemData", getItemData, 1)
	WXJS_METHOD("getItemExpandedIcon", getItemExpandedIcon, 1)
	WXJS_METHOD("getItemIcon", getItemIcon, 1)
	WXJS_METHOD("getNthChild", getNthChild, 2)
	WXJS_METHOD("insertContainer", insertContainer, 3)
	WXJS_METHOD("insertItem", insertItem, 3)
	WXJS_METHOD("prependContainer", prependContainer, 2)
	WXJS_METHOD("prependItem", prependItem, 2)
	WXJS_METHOD("setItemData", setItemData, 2)
	WXJS_METHOD("setItemExpandedIcon", setItemExpandedIcon, 2)
	WXJS_METHOD("setItemIcon", setItemIcon, 2)	

WXJS_END_METHOD_MAP()

JSBool DataViewTreeStore::appendContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;
	wxIcon expanded = wxNullIcon;
	wxString	text;
	int			col = 0;
	wxClientData *data=NULL;



	if( argc > 5 ) {
		argc = 5;
	}

	switch( argc ) {
	case 5:
		{			
			data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
		}
	case 4:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[3]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			expanded = *pIcon;
		}
	case 3:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[2]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			icon = *pIcon;
		}
	default:
		// 2.
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// 1. 
		wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			return JS_FALSE;
		}
		wxDataViewItem 	newItem = p->AppendContainer(*pItem, text, icon, expanded
			, data
		);

		
		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	

	
	
	return JS_TRUE;
}


JSBool DataViewTreeStore::appendItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;
	wxString	text;
	int			col = 0;
	wxClientData *data=NULL;
	

	if( argc > 4 ) {
		argc = 4;
	}

	switch( argc ) {
	case 4:
		{			
			data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
		}
	case 3:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[2]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			icon = *pIcon;
		}
	default:
		// 2.
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		// 1. 
		wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			return JS_FALSE;
		}
		wxDataViewItem 	newItem = p->AppendItem(*pItem, text, icon
			, data
		);
		
		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}
	

	
	
	return JS_TRUE;
}



JSBool DataViewTreeStore::deleteAllItems(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	p->DeleteAllItems();

	
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::deleteChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	p->DeleteChildren( *pItem );
	
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::deleteItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	p->DeleteItem( *pItem );
	
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::getChildCount(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	vp->setInt32( 
		p->GetChildCount( *pItem )
	);
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::getItemData(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	wxClientData *pItemData = p->GetItemData( *pItem );
	if( pItemData == NULL ) {
		*vp = JSVAL_VOID;
	} else {
		JavaScriptClientData* pItemDJs = (JavaScriptClientData*)pItem;
		JSObject* pObj = ((JavaScriptClientData*)pItem)->GetObject();
		vp->setObjectOrNull( pObj );
	}
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::getItemExpandedIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	wxIcon icon = p->GetItemExpandedIcon( *pItem );
	if( icon.IsOk() ) {
		*vp = Icon::CreateObject(cx, &icon);
	} else {
		*vp = JSVAL_VOID;
	}
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::getItemIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	wxIcon icon = p->GetItemIcon( *pItem );
	if( icon.IsOk() ) {
		*vp = Icon::CreateObject(cx, &icon);
	} else {
		*vp = JSVAL_VOID;
	}
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::getItemText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	*vp = ToJS(cx, p->GetItemText( *pItem ) );

	return JS_TRUE;
}




JSBool DataViewTreeStore::getNthChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int pos = 0;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
	if( FromJS(cx, argv[1], pos) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// 戻り値
	wxDataViewItem item = p->GetNthChild(*pItem, pos);
	if( item.IsOk() ) {
		*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(item) );
	} else {
		*vp = JSVAL_VOID;
	}

	return JS_TRUE;
}




JSBool DataViewTreeStore::insertContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;
	wxIcon expanded = wxNullIcon;
	wxString	text;
	int			col = 0;
	wxClientData *data=NULL;



	if( argc > 6 ) {
		argc = 6;
	}

	switch( argc ) {
	case 6:
		{			
			data = new JavaScriptClientData(cx, argv[5].toObjectOrNull(), false, true);
		}
	case 5:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[4]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			expanded = *pIcon;
		}
	case 4:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[3]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			icon = *pIcon;
		}
	default:
		// 3.
		if ( ! FromJS(cx, argv[2], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		// 2. 
		wxDataViewItem* pPrevious = DataViewItem::GetPrivate(cx, argv[1]);
		if( pPrevious == NULL ) {
			return JS_FALSE;
		}
		// 1. 
		wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			return JS_FALSE;
		}
		wxDataViewItem 	newItem = p->InsertContainer(
			  *pItem
			, *pPrevious
			, text
			, icon
			, expanded
			, data
		);

		
		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}	
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::insertItem(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;
	wxString	text;
	int			col = 0;
	wxClientData *data=NULL;



	if( argc > 5 ) {
		argc = 5;
	}

	switch( argc ) {
	case 5:
		{			
			data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
		}
	case 4:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[3]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			icon = *pIcon;
		}
	default:
		// 3.
		if ( ! FromJS(cx, argv[2], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		// 2. 
		wxDataViewItem* pPrevious = DataViewItem::GetPrivate(cx, argv[1]);
		if( pPrevious == NULL ) {
			return JS_FALSE;
		}
		// 1. 
		wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			return JS_FALSE;
		}
		wxDataViewItem 	newItem = p->InsertItem (
			  *pItem
			, *pPrevious
			, text
			, icon
			, data
		);

		
		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}	
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::prependContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;
	wxIcon expanded = wxNullIcon;
	wxString	text;
	int			col = 0;
	wxClientData *data=NULL;



	if( argc > 5 ) {
		argc = 5;
	}

	switch( argc ) {
	case 5:
		{			
			data = new JavaScriptClientData(cx, argv[4].toObjectOrNull(), false, true);
		}
	case 4:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[3]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			expanded = *pIcon;
		}
	case 3:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[2]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			icon = *pIcon;
		}
	default:
		// 2.
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		// 1. 
		wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			return JS_FALSE;
		}
		wxDataViewItem 	newItem = p->PrependContainer (
			  *pItem
			, text
			, icon
			, expanded
			, data
		);

		
		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}	
	
	return JS_TRUE;
}




JSBool DataViewTreeStore::prependItem(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;
	wxString	text;
	int			col = 0;
	wxClientData *data=NULL;



	if( argc > 4 ) {
		argc = 4;
	}

	switch( argc ) {
	case 4:
		{			
			data = new JavaScriptClientData(cx, argv[3].toObjectOrNull(), false, true);
		}
	case 3:
		{
			wxIcon* pIcon = Icon::GetPrivate(cx, argv[2]);
			if( pIcon == NULL ) {
				return JS_FALSE;
			}
			icon = *pIcon;
		}
	default:
		// 2.
		if ( ! FromJS(cx, argv[1], text) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		// 1. 
		wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
		if( pItem == NULL ) {
			return JS_FALSE;
		}
		wxDataViewItem 	newItem = p->PrependItem (
			  *pItem
			, text
			, icon
			, data
		);

		
		// 戻り値
		if( newItem.IsOk() ) {
			*vp = DataViewItem::CreateObject(cx, new wxDataViewItem(newItem) );
		} else {
			*vp = JSVAL_VOID;
		}
	}	
	
	return JS_TRUE;
}


JSBool DataViewTreeStore::setItemData(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxClientData *data=NULL;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
	data = new JavaScriptClientData(cx, argv[1].toObjectOrNull(), false, true);



	p->SetItemData  (
			*pItem
		, data
	);
	
	return JS_TRUE;
}



JSBool DataViewTreeStore::setItemExpandedIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
	wxIcon* pIcon = Icon::GetPrivate(cx, argv[1]);
	if( pIcon == NULL ) {
		return JS_FALSE;
	}

	p->SetItemExpandedIcon(
			*pItem
		, *pIcon
	);
	
	return JS_TRUE;
}



JSBool DataViewTreeStore::setItemIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{

	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
			
    wxDataViewTreeStore *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	wxIcon icon = wxNullIcon;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
	wxIcon* pIcon = Icon::GetPrivate(cx, argv[1]);
	if( pIcon == NULL ) {
		return JS_FALSE;
	}

	p->SetItemIcon(
		  *pItem
		, *pIcon
	);
	
	return JS_TRUE;
}















