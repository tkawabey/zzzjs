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
#include "js/common/jsutil.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/misc/size.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewvirtuallistmodel.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;


//--------------------------------------------------------
//	MyDataViewVirtualListModel
//--------------------------------------------------------
MyDataViewVirtualListModel::MyDataViewVirtualListModel(JSContext *cx, JSObject* pObj, unsigned int initial_size /*= 0 */)
	:	wxDataViewVirtualListModel(initial_size)
	,	m_pCx(cx)
	,	m_pObj( pObj )
{

}
unsigned int MyDataViewVirtualListModel::GetColumnCount() const
{
	jsval fval;
	if ( zzzJs::GetFunctionProperty(m_pCx, m_pObj, "onGetColumnCount", &fval) == JS_TRUE )
	{
		if( fval.isObject() == true ) 
		{
			jsval rval;
			if ( JS_CallFunctionValue(m_pCx, m_pObj, fval, 0, NULL, &rval) == JS_TRUE )
			{
				if( rval.isNumber() ) {
					return rval.toInt32();
				}
			}
		}
	}
	return 0;
}

// return type as reported by wxVariant
wxString MyDataViewVirtualListModel::GetColumnType( unsigned int col ) const
{
	jsval fval;
	if ( zzzJs::GetFunctionProperty(m_pCx, m_pObj, "onGetColumnType", &fval) == JS_TRUE )
	{
		if( fval.isObject() == true ) 
		{
			jsval rval;
			jsval argv[1];
			argv[0].setInt32(col);
			if ( JS_CallFunctionValue(m_pCx, m_pObj, fval, 1, argv, &rval) == JS_TRUE )
			{
				if( rval.isString() ) {
					wxString strRet;
					FromJS(m_pCx, rval, strRet);
					return strRet;

				}
			}
		}
	}
	return _T("");
}

void MyDataViewVirtualListModel::GetValueByRow( wxVariant &variant,
							unsigned int row, unsigned int col ) const
{
	jsval fval;
	if ( zzzJs::GetFunctionProperty(m_pCx, m_pObj, "onGetValueByRow", &fval) == JS_TRUE )
	{
		if( fval.isObject() == true ) 
		{
			jsval rval;
			jsval argv[2];
			argv[0].setInt32(row);
			argv[1].setInt32(col);
			if ( JS_CallFunctionValue(m_pCx, m_pObj, fval, 2, argv, &rval) == JS_TRUE )
			{
				ConvertJs2WxVariant(m_pCx, rval, variant);
			}
		}
	}
}

bool MyDataViewVirtualListModel::GetAttrByRow( unsigned int row, unsigned int col,
							wxDataViewItemAttr &attr ) const
{
	jsval fval;
	if ( zzzJs::GetFunctionProperty(m_pCx, m_pObj, "onGetAttrByRow", &fval) == JS_TRUE )
	{
		if( fval.isObject() == true ) 
		{
			jsval rval;
			jsval argv[2];
			argv[0].setInt32(row);
			argv[1].setInt32(col);
			if ( JS_CallFunctionValue(m_pCx, m_pObj, fval, 2, argv, &rval) == JS_TRUE )
			{
				do {

					if( rval.isObjectOrNull() != true ) {
						break;
					}	
					wxDataViewItemAttr* pAttr = DataViewItemAttr::GetPrivate(m_pCx, rval.toObjectOrNull() );
					if( pAttr == NULL ) {
						break;
					}
					attr.SetBold( pAttr->GetBold() );
					attr.SetItalic( pAttr->GetItalic() );
					if( attr.HasBackgroundColour() ) {
						attr.SetBackgroundColour( pAttr->GetBackgroundColour() );
					}
					if( attr.HasColour() ) {
						attr.SetColour( pAttr->GetColour() );
					}
				} while( 0 );


				return true;
			}
		}
	}
	return false;
}

bool MyDataViewVirtualListModel::SetValueByRow( const wxVariant &variant,
							unsigned int row, unsigned int col )
{
	jsval fval;
	if ( zzzJs::GetFunctionProperty(m_pCx, m_pObj, "onSetValueByRow", &fval) == JS_TRUE )
	{
		if( fval.isObject() == true ) 
		{
			jsval rval;
			jsval argv[3];
			argv[0].setInt32(row);
			argv[1].setInt32(col);
			ConvertWxVariant2Js(m_pCx, variant, argv[2]);
			if ( JS_CallFunctionValue(m_pCx, m_pObj, fval, 3, argv, &rval) == JS_TRUE )
			{
				return true;
			}
		}
	}
	return false;
}

//--------------------------------------------------------
//	DataViewVirtualListModel
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewVirtualListModel, "DataViewVirtualListModel", 1)

void DataViewVirtualListModel::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{

}
	
//WXJS_BEGIN_CONSTANT_MAP(DataViewVirtualListModel)
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
WXJS_BEGIN_PROPERTY_MAP(DataViewVirtualListModel)
  WXJS_PROPERTY(P_ColumnCount, "columnCount")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(MyDataViewVirtualListModel, DataViewVirtualListModel)
	switch (id) 
	{
	case P_ColumnCount:
		ToJSVal(cx, vp, p->GetColumnCount ());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(MyDataViewVirtualListModel, DataViewVirtualListModel)
	switch (id) 
	{
	case P_FLAG:
		{
			int value = 0;
			if ( FromJS(cx, vp, value) )
			{

			}
		}
		break;
	}
	return true;
WXJS_END_SET_PROP

WXJS_BEGIN_ADD_PROP(MyDataViewVirtualListModel, DataViewVirtualListModel)
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(MyDataViewVirtualListModel, DataViewVirtualListModel)
  return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Bitmap" type="@wxBitmap">The bitmap to display</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTO_DRAW">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Constructs a new MyDataViewVirtualListModel object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(MyDataViewVirtualListModel, DataViewVirtualListModel)

	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	unsigned int initial_size=0;
	if( argc > 1 ) {
		if ( ! FromJS(cx, argv[0], initial_size) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	MyDataViewVirtualListModel *p = new MyDataViewVirtualListModel(cx, obj, initial_size);
	return p;
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(MyDataViewVirtualListModel, DataViewVirtualListModel)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewVirtualListModel)
    WXJS_METHOD("getItem", getItem, 1)
	WXJS_METHOD("reset", reset, 1)
	WXJS_METHOD("rowAppended", rowAppended, 0)
	WXJS_METHOD("rowChanged", rowChanged, 1)
	WXJS_METHOD("rowDeleted", rowDeleted, 1)
	WXJS_METHOD("rowInserted", rowInserted, 1)
	WXJS_METHOD("rowPrepended", rowPrepended, 0)
	WXJS_METHOD("rowValueChanged", rowValueChanged, 2)
WXJS_END_METHOD_MAP()

JSBool DataViewVirtualListModel::getItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int row = 0;


	// 1.
    if ( ! FromJS(cx, argv[0], row) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	wxDataViewItem  item = p->GetItem( row );
	wxDataViewItem* pItem = new wxDataViewItem( item );

	// 戻り値
	*vp = DataViewItem::CreateObject( cx, pItem);
	
	return JS_TRUE;
}


JSBool DataViewVirtualListModel::reset(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int new_size = 0;


	// 1.
    if ( ! FromJS(cx, argv[0], new_size) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	p->Reset( new_size );
	// 戻り値
	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowAppended(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	p->RowAppended();
	// 戻り値

	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowChanged(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int row = 0;


	// 1.
    if ( ! FromJS(cx, argv[0], row) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	p->RowChanged( row );
	// 戻り値
	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowDeleted(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int row = 0;


	// 1.
    if ( ! FromJS(cx, argv[0], row) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	p->RowDeleted( row );
	// 戻り値
	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowInserted(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int row = 0;


	// 1.
    if ( ! FromJS(cx, argv[0], row) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	p->RowInserted( row );
	// 戻り値
	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowPrepended(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	//unsigned int row = 0;


	//// 1.
 //   if ( ! FromJS(cx, argv[0], row) )
 //   {
 //       JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
 //       return JS_FALSE;
 //   }

	p->RowPrepended( );
	// 戻り値
	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowValueChanged(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	unsigned int row = 0;
	unsigned int col = 0;


	// 1.
    if ( ! FromJS(cx, argv[0], row) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	// 2.
    if ( ! FromJS(cx, argv[1], col) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }

	p->RowValueChanged( row, col );
	// 戻り値
	return JS_TRUE;
}

JSBool DataViewVirtualListModel::rowsDeleted(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	
    wxDataViewVirtualListModel *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxArrayInt arryI;
	JSObject *objItems = JSVAL_TO_OBJECT( argv[0] );
	if (    objItems != (JSObject *) NULL
		    && JS_IsArrayObject(cx, objItems ) )
	{
		
		uint32_t length = 0;
		JS_GetArrayLength(cx, objItems, &length);
		for(uint32_t i =0; i < length; i++)
		{
			JS::Value element;
			JS_GetElement(cx, objItems, i, &element);
			if( element.isNumber() ) {
				arryI.Add( element.toInt32() );
			}
		}
	}
	p->RowsDeleted( arryI );
	// 戻り値
	return JS_TRUE;
}





