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
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewmodel.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewModel
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewModel, "DataViewModel", 1)

void DataViewModel::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{

}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewModel)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewModel)
  WXJS_PROPERTY(P_ColumnCount, "columnCount")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewModel, DataViewModel)
	switch (id) 
	{
	case P_ColumnCount:
		ToJSVal(cx, vp, p->GetColumnCount ());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDataViewModel, DataViewModel)
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

WXJS_BEGIN_ADD_PROP(wxDataViewModel, DataViewModel)
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewModel, DataViewModel)
  return true;
WXJS_END_DEL_PROP


WXJS_BEGIN_DESTRUCTOR(wxDataViewModel, DataViewModel)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewModel)
    WXJS_METHOD("changeValue", changeValue, 3)
	WXJS_METHOD("cleared", cleared, 0)
	WXJS_METHOD("compare", compare, 4)
	WXJS_METHOD("getAttr", getAttr, 2)
	WXJS_METHOD("isEnabled", isEnabled, 2)
	WXJS_METHOD("getChildren", getChildren, 1)
	WXJS_METHOD("getColumnType", getColumnType, 1)
	WXJS_METHOD("getParent", getParent, 1)
	WXJS_METHOD("getValue", getValue, 2)
	WXJS_METHOD("hasContainerColumns", hasContainerColumns, 1)
	WXJS_METHOD("hasValue", hasValue, 2)
	WXJS_METHOD("isContainer", isContainer, 1)
	WXJS_METHOD("itemAdded", itemAdded, 2)
	WXJS_METHOD("itemChanged", itemChanged, 1)
	WXJS_METHOD("itemDeleted", itemDeleted, 2)
	WXJS_METHOD("itemsAdded", itemsAdded, 2)
	WXJS_METHOD("itemsChanged", itemsChanged, 1)
	WXJS_METHOD("itemsDeleted", itemsDeleted, 2)
	WXJS_METHOD("resort", resort, 0)
	WXJS_METHOD("setValue", setValue, 3)
	WXJS_METHOD("valueChanged", valueChanged, 2)
	WXJS_METHOD("isListModel", isListModel, 0)
	WXJS_METHOD("isVirtualListModel", isVirtualListModel, 0)
WXJS_END_METHOD_MAP()

JSBool DataViewModel::changeValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxVariant	variant;
	int			col = 0;

	// 1. 
	if( ConvertJs2WxVariant(cx, argv[0], variant) == false ) {
		return JS_FALSE;
	}
	// 2. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[1]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 3.
    if ( ! FromJS(cx, argv[2], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	vp->setBoolean( 
		p->ChangeValue(variant, *pItem, col)
	);
	
	return JS_TRUE;
}


JSBool DataViewModel::cleared(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
//	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean( 
		p->Cleared()
	);
	return JS_TRUE;
}

JSBool DataViewModel::compare(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	

	int colomn = 0;
	bool ascending = false;

	// 1. 
	wxDataViewItem* pItem1 = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem1 == NULL ) {
		return JS_FALSE;
	}
	// 2. 
	wxDataViewItem* pItem2 = DataViewItem::GetPrivate(cx, argv[1]);
	if( pItem2 == NULL ) {
		return JS_FALSE;
	}
	// 3.
    if ( ! FromJS(cx, argv[2], colomn) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	// 4.
    if ( ! FromJS(cx, argv[3], ascending) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, "Boolen");
        return JS_FALSE;
    }

	// 戻り値
	vp->setInt32( 
		p->Compare(*pItem1, *pItem2, colomn, ascending)
	);

	return JS_TRUE;
}

JSBool DataViewModel::getAttr(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	

	unsigned int col = 0;
	wxDataViewItemAttr attr;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
    if ( ! FromJS(cx, argv[1], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	// 戻り値
	if( p->GetAttr(*pItem, col, attr) == false ) {
		*vp = JSVAL_VOID;
	} else {
		
		wxDataViewItemAttr* pNewAttr = new wxDataViewItemAttr();
		pNewAttr->SetBold( attr.GetBold() );
		pNewAttr->SetItalic( attr.GetItalic() );
		if( attr.HasColour() ) {
			pNewAttr->SetColour ( attr.GetColour () );
		}
		if( attr.HasBackgroundColour() ) {
			pNewAttr->SetBackgroundColour( attr.GetBackgroundColour () );
		}
		*vp = DataViewItemAttr::CreateObject(cx, pNewAttr);
	}

	return JS_TRUE;
}

JSBool DataViewModel::isEnabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	

	unsigned int col = 0;
	wxDataViewItemAttr attr;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
    if ( ! FromJS(cx, argv[1], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	// 戻り値
	vp->setBoolean(
		p->IsEnabled(*pItem, col)
	);
	return JS_TRUE;
}

JSBool DataViewModel::getChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItemArray children;
	wxDataViewItemAttr attr;

	// 1. 
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	
	JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
	p->GetChildren(*pItem, children);
	for(size_t i = 0; i < children.GetCount(); i++ ) {
		wxDataViewItem& item = children[i];
		wxDataViewItem* pItem = new wxDataViewItem(item);

		jsval element = DataViewItem::CreateObject(cx, pItem);
		JS_SetElement(cx, objArray, i, &element);

	}
	*vp = OBJECT_TO_JSVAL(objArray);

	return JS_TRUE;
}



JSBool DataViewModel::getColumnType(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	

	unsigned int col = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	// 戻り値
	*vp = ToJS(cx, p->GetColumnType(col));

	return JS_TRUE;
}



JSBool DataViewModel::getParent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	wxDataViewItem item = p->GetParent( *pItem );

	// 戻り値
	*vp = DataViewItem::CreateObject(cx, new wxDataViewItem( item ) );

	return JS_TRUE;
}



JSBool DataViewModel::getValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int col = 0;
	wxVariant retVal;
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
    if ( ! FromJS(cx, argv[1], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	p->GetValue(retVal, *pItem, col);

	// 戻り値
	*vp = ToJS(cx, retVal);

	return JS_TRUE;
}



JSBool DataViewModel::hasContainerColumns(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int col = 0;
	wxVariant retVal;
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->HasContainerColumns( *pItem )
	);

	return JS_TRUE;
}

JSBool DataViewModel::hasValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int col = 0;
	wxVariant retVal;
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 2.
    if ( ! FromJS(cx, argv[1], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	// 戻り値
	vp->setBoolean(
		p->HasValue( *pItem, col )
	);

	return JS_TRUE;
}

JSBool DataViewModel::isContainer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxVariant retVal;
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->IsContainer( *pItem )
	);

	return JS_TRUE;
}

JSBool DataViewModel::itemAdded(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxDataViewItem* pParent = DataViewItem::GetPrivate(cx, argv[0]);
	if( pParent == NULL ) {
		return JS_FALSE;
	}
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[1]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->ItemAdded(*pParent, *pItem )
	);

	return JS_TRUE;
}

JSBool DataViewModel::itemChanged(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->ItemChanged(*pItem )
	);

	return JS_TRUE;
}

JSBool DataViewModel::itemDeleted(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxDataViewItem* pParent = DataViewItem::GetPrivate(cx, argv[0]);
	if( pParent == NULL ) {
		return JS_FALSE;
	}
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[1]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->ItemDeleted(*pParent, *pItem )
	);

	return JS_TRUE;
}

JSBool DataViewModel::itemsAdded(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	wxDataViewItem* pParent = DataViewItem::GetPrivate(cx, argv[0]);
	if( pParent == NULL ) {
		return JS_FALSE;
	}


	// 2
	wxDataViewItemArray arry;
    JSObject *objItems = JSVAL_TO_OBJECT(argv[1]);
    if (    objItems != NULL
            && JS_IsArrayObject(cx, objItems) )
    {
		uint32_t length = 0;
		JS_GetArrayLength(cx, objItems, &length);
		for(uint32_t i =0; i < length; i++)
		{
			JS::Value element;
			JS_GetElement(cx, objItems, i, &element);
			wxDataViewItem* p = DataViewItem::GetPrivate(cx, element);
			if( p != NULL ) {
				arry.Add(*p);
			}
		}
        return true;
    }

	// 戻り値
	vp->setBoolean(
		p->ItemsAdded(*pParent, arry )
	);

	return JS_TRUE;
}

JSBool DataViewModel::itemsChanged(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
/*
	wxDataViewItem* pParent = DataViewItem::GetPrivate(cx, argv[0]);
	if( pParent == NULL ) {
		return JS_FALSE;
	}
*/

	// 2
	wxDataViewItemArray arry;
    JSObject *objItems = JSVAL_TO_OBJECT(argv[0]);
    if (    objItems != NULL
            && JS_IsArrayObject(cx, objItems) )
    {
		uint32_t length = 0;
		JS_GetArrayLength(cx, objItems, &length);
		for(uint32_t i =0; i < length; i++)
		{
			JS::Value element;
			JS_GetElement(cx, objItems, i, &element);
			wxDataViewItem* p = DataViewItem::GetPrivate(cx, element);
			if( p != NULL ) {
				arry.Add(*p);
			}
		}
        return true;
    }

	// 戻り値
	vp->setBoolean(
		p->ItemsChanged( arry )
	);

	return JS_TRUE;
}

JSBool DataViewModel::itemsDeleted(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 1
	wxDataViewItem* pParent = DataViewItem::GetPrivate(cx, argv[0]);
	if( pParent == NULL ) {
		return JS_FALSE;
	}


	// 2
	wxDataViewItemArray arry;
    JSObject *objItems = JSVAL_TO_OBJECT(argv[1]);
    if (    objItems != NULL
            && JS_IsArrayObject(cx, objItems) )
    {
		uint32_t length = 0;
		JS_GetArrayLength(cx, objItems, &length);
		for(uint32_t i =0; i < length; i++)
		{
			JS::Value element;
			JS_GetElement(cx, objItems, i, &element);
			wxDataViewItem* p = DataViewItem::GetPrivate(cx, element);
			if( p != NULL ) {
				arry.Add(*p);
			}
		}
        return true;
    }

	// 戻り値
	vp->setBoolean(
		p->ItemsDeleted(*pParent, arry )
	);

	return JS_TRUE;
}

JSBool DataViewModel::resort(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	// 戻り値
	p->Resort();

	return JS_TRUE;
}

JSBool DataViewModel::setValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	

    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxVariant vval;
	unsigned int col = 0;
	// 1
    if ( ! FromJS(cx, argv[0], vval) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Variant");
        return JS_FALSE;
    }
	// 2
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[1]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 3
    if ( ! FromJS(cx, argv[2], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	// 戻り値
	vp->setBoolean(
		p->SetValue(vval, *pItem, col )
	);

	return JS_TRUE;
}

JSBool DataViewModel::valueChanged(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	

    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	unsigned int col = 0;

	// 2
	wxDataViewItem* pItem = DataViewItem::GetPrivate(cx, argv[0]);
	if( pItem == NULL ) {
		return JS_FALSE;
	}
	// 3
    if ( ! FromJS(cx, argv[1], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	// 戻り値
	vp->setBoolean(
		p->ValueChanged(*pItem, col )
	);

	return JS_TRUE;
}

JSBool DataViewModel::isListModel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	

    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->IsListModel()
	);

	return JS_TRUE;
}

JSBool DataViewModel::isVirtualListModel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	

    wxDataViewModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	// 戻り値
	vp->setBoolean(
		p->IsVirtualListModel()
	);

	return JS_TRUE;
}


