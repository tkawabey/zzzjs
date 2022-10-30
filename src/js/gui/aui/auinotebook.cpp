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
#include "js/gui/misc/font.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/aui/auinotebook.h"
#include "js/gui/aui/auinotebookevent.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::aui;

ZZZJS_INIT_CLASS(AuiNotebook, "AuiNotebook", 1)
	

void AuiNotebook::InitClass(JSContext* cx, 
				JSObject* obj, 
				JSObject* proto)
{
//    AuiNotebookEventHandler::InitConnectEventMap();
}

ZZZJS_BEGIN_CONSTANT_MAP(AuiNotebook)
  ZZZJS_CONSTANT(wxAUI_, NB_TOP )
  ZZZJS_CONSTANT(wxAUI_, NB_LEFT)
  ZZZJS_CONSTANT(wxAUI_, NB_RIGHT  )
  ZZZJS_CONSTANT(wxAUI_, NB_BOTTOM  )
  ZZZJS_CONSTANT(wxAUI_, NB_TAB_SPLIT  )
  ZZZJS_CONSTANT(wxAUI_, NB_TAB_MOVE )
  ZZZJS_CONSTANT(wxAUI_, NB_TAB_EXTERNAL_MOVE )
  ZZZJS_CONSTANT(wxAUI_, NB_TAB_FIXED_WIDTH )
  ZZZJS_CONSTANT(wxAUI_, NB_SCROLL_BUTTONS )
  ZZZJS_CONSTANT(wxAUI_, NB_WINDOWLIST_BUTTON  )
  ZZZJS_CONSTANT(wxAUI_, NB_CLOSE_BUTTON )
  ZZZJS_CONSTANT(wxAUI_, NB_CLOSE_ON_ACTIVE_TAB )
  ZZZJS_CONSTANT(wxAUI_, NB_CLOSE_ON_ALL_TABS )
  ZZZJS_CONSTANT(wxAUI_, NB_MIDDLE_CLICK_CLOSE )
  ZZZJS_CONSTANT(wxAUI_, NB_DEFAULT_STYLE )
ZZZJS_END_CONSTANT_MAP()
/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(AuiNotebook)
  ZZZJS_READONLY_PROPERTY(P_GetPageCount, "pageCount")
  ZZZJS_READONLY_PROPERTY(P_Selection, "selection")
  ZZZJS_READONLY_PROPERTY(P_TabCtrlHeight, "tabCtrlHeight")
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_GET_PROP(wxAuiNotebook, AuiNotebook)
{
//int fasd = wxAUI_NB_DEFAULT_STYLE;
	switch (id) 
	{
	case P_GetPageCount:
		ToJSVal(cx, vp, p->GetPageCount());
		break;
	case P_Selection:
		ToJSVal(cx, vp, p->GetSelection());
		break;
	case P_TabCtrlHeight:
		ToJSVal(cx, vp, p->GetTabCtrlHeight());
		break;
	}
	return true;
}
ZZZJS_END_GET_PROP

ZZZJS_BEGIN_SET_PROP(wxAuiNotebook, AuiNotebook)
{
	//switch (id) 
	//{
	//case P_FLAG:
	//	{
	//		int value = 0;
	//		if ( FromJS(cx, vp, value) )
	//			p->SetFlags(value);
	//	}
	//	break;
	//}
	return true;
}
ZZZJS_END_SET_PROP

ZZZJS_BEGIN_ADD_PROP(wxAuiNotebook, AuiNotebook)
{
//    AuiNotebookEventHandler::ConnectEvent(p, prop, true);
    return true;
}
ZZZJS_END_ADD_PROP
	
ZZZJS_BEGIN_DEL_PROP(wxAuiNotebook, AuiNotebook)
{
//  AuiNotebookEventHandler::ConnectEvent(p, prop, false);
  return true;
}
ZZZJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=ZZZJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Bitmap" type="@wxBitmap">The bitmap to display</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=ZZZJS_TYPE_NUMBER default="wxButton.AUTO_DRAW">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxAuiNotebook object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxAuiNotebook, AuiNotebook)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxAuiNotebook *p = new wxAuiNotebook();
	
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
ZZZJS_END_CONSTRUCTOR


ZZZJS_BEGIN_DESTRUCTOR(wxAuiNotebook, AuiNotebook)
{

}
ZZZJS_END_DESTRUCTOR


ZZZJS_BEGIN_METHOD_MAP(AuiNotebook)
    ZZZJS_METHOD("addPage", addPage, 1)
    ZZZJS_METHOD("insertPage", insertPage, 1)
	ZZZJS_METHOD("getHeightForPageHeight", getHeightForPageHeight, 1)
	ZZZJS_METHOD("getPageBitmap", getPageBitmap, 1)
	ZZZJS_METHOD("getPageIndex", getPageIndex, 1)
	ZZZJS_METHOD("getPageToolTip", getPageToolTip, 1)
	ZZZJS_METHOD("setFont", setFont, 1)
	ZZZJS_METHOD("setMeasuringFont", setMeasuringFont, 1)
	ZZZJS_METHOD("setNormalFont", setNormalFont, 1)
	ZZZJS_METHOD("setPageBitmap", setPageBitmap, 2)
	ZZZJS_METHOD("setPageToolTip", setPageToolTip, 2)
	ZZZJS_METHOD("setSelectedFont", setSelectedFont, 1)
	ZZZJS_METHOD("setTabCtrlHeight", setTabCtrlHeight, 1)
	ZZZJS_METHOD("setUniformBitmapSize", setUniformBitmapSize, 2)
	ZZZJS_METHOD("split", split, 2)
	ZZZJS_METHOD("showWindowMenu", showWindowMenu, 0)
ZZZJS_END_METHOD_MAP()

// Object 2 Instatance

ZZZJS_BEGIN_O2I(wxAuiNotebook, AuiNotebook)
{
	
	pRet = AuiNotebook::GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}
	/*
		bool wxAuiNotebook::Create	(
			wxWindow * 	parent,
			wxWindowID 	id = wxID_ANY,
			const wxPoint & 	pos = wxDefaultPosition,
			const wxSize & 	size = wxDefaultSize,
			long 	style = 0 
		)	
	*/
	wxWindow *parent = NULL;
	int id = wxID_ANY;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	long style=0;


	/*
	{
			parent:Window
		,	id:Number [Option = wx.ID_ANY]
		,	pos:Point [Option = DefaultPosition]
		,	size:Size [Option = DefaultSize]
		,	style:Number [Option = 0]
	}
	*/
	// parent:Window
	if( GetPropertyWhenPresent( cx, obj, "parent", &v) == JS_FALSE ) 
	{
		return NULL;
	}
	parent = Window::GetPrivate(cx, v);
	if( parent == NULL )
	{
		ReportError_PropTypeError(cx, "parent", "Window");
		return JS_FALSE;
	}
	// id
	ZZZJS_PROP_FROMJS_IF_EXIST(id, obj, "id", WXJS_TYPE_NUMBER)	
	// pos:Point [Option = DefaultPosition]
	ZZZJS_PROP_AP_IF_EXIST(apPoint, zzzJs::ext::Point, "pos");
	// size:Size [Option = DefaultSize]
	ZZZJS_PROP_AP_IF_EXIST(apSize, Size, "size");
	// style
	ZZZJS_PROP_FROMJS_IF_EXIST(style, obj, "style", WXJS_TYPE_NUMBER);

	return new wxAuiNotebook(parent, id, *(apPoint.get()), *(apSize.get()), style);
}
ZZZJS_END_O2I

JSBool AuiNotebook::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}

JSBool AuiNotebook::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
ZZZJS_FUNC_ENT
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxAuiNotebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;


	if( argc == 0 ) 
	{
		return JS_TRUE;
	}
	/*
		bool wxAuiNotebook::Create	(
			wxWindow * 	parent,
			wxWindowID 	id = wxID_ANY,
			const wxPoint & 	pos = wxDefaultPosition,
			const wxSize & 	size = wxDefaultSize,
			long 	style = 0 
		)	
	*/
	int argIndex = 0;
	rval->setBoolean( JS_FALSE );
	

	wxWindow *parent = NULL;


	if( argc == 0 ) 
	{
		return JS_TRUE;
	}	
	if( argv[argIndex].isObjectOrNull() == false ) 
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	parent = Window::GetPrivate(cx, argv[argIndex].toObjectOrNull() );
	if( parent != NULL ) 
	{
		int id = wxID_ANY;
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		long style=0;
		wxString name = wxEmptyString;
		
		ZZZJS_CHECK_ARG_COUNT(1, 5);

		argIndex++;

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 6:
			// name
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);
		case 5:
			// style
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		case 4:
			// size
			ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		case 3:
			// pos
			ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		case 2:
			// id
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		}


		bool bRet = p->Create( parent, id, *apPoint.get(), *apSize.get(), style);
		
		rval->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	{
		zzzJsPtr<wxAuiNotebook> apAuiNotebook;

		if( apAuiNotebook.set( 
			AuiNotebook::getObject2Instance(cx, argv[argIndex].toObjectOrNull() , apAuiNotebook.bAllocation) ) == true 
		) {
			delete p;
					
			if( apAuiNotebook.bAllocation == true ) {
				p =  apAuiNotebook.release();
			} else {
				p = apAuiNotebook.get();
			}
			SetPrivate(cx, obj, p);
			rval->setBoolean( JS_TRUE );
			return JS_TRUE;
		}
	}
	
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

JSBool AuiNotebook::addPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
ZZZJS_FUNC_ENT
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	/*	
	bool 	AddPage (
		wxWindow *page
		, const wxString &caption
		, bool select=false
		, const wxBitmap &bitmap=wxNullBitmap)

 		Adds a page. More...
 
	virtual bool 	AddPage (
		wxWindow *page
		, const wxString &text
		, bool select
		, int imageId)

 		Adds a new page.
	*/
	int argIndex = 0;	

	if( argc == 0 )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	wxWindow* pWnd = NULL;
	wxString text;
	bool select=false;
	int imageId= wxWithImages::NO_IMAGE;
	zzzJsPtr<wxBitmap> apBitmap;
	bool bPass = false;
	JSObject* pObj = NULL;


	// 最初は必ずObjectです！！
	if( argv[argIndex].isObjectOrNull() == false ) 
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	if( (pObj = argv[argIndex].toObjectOrNull()) == NULL ) 
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	pWnd = Window::GetPrivate( cx, pObj);
	if( pWnd != NULL )
	{
		/*
		第一引数が、wxWindowsの場合は、以下の引数をとります。
		virtual bool 	AddPage (
			wxWindow *page, 
			const wxString &text, 
			bool select=false, 
			int imageId=NO_IMAGE

		bool 	AddPage (
			wxWindow *page
			, const wxString &caption
			, bool select=false
			, const wxBitmap &bitmap=wxNullBitmap)

		*/
		bool bHasBitmap = false;
		ZZZJS_CHECK_ARG_COUNT(2, 4)


		argIndex = argc -1;
		switch( argc )
		{
		case 4:
			if( argv[argIndex].isNumber() == true )
			{
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(imageId, WXJS_TYPE_NUMBER);
			}
			else
			if( argv[argIndex].isObjectOrNull() == true )
			{
				if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[argIndex], apBitmap.bAllocation)) == false ) 
				{
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
					return JS_FALSE;
				}
				bHasBitmap = true;
			}
			else
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap or Integer");
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(select, WXJS_TYPE_BOOLEAN);
			argIndex--;
		default:
			// wxWindow *page　は、pWndで取得済み
			argIndex = 0;
			// const wxString &text, 
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(text, WXJS_TYPE_STRING);
		}
		
		// APIの実行
		bool bRet = false;
		if( bHasBitmap == true )
		{
			bRet = p->AddPage(pWnd, text, select, apBitmap.get() != NULL ? *(apBitmap.get()): wxNullBitmap );
		}
		else
		{
			bRet = p->AddPage(pWnd, text, select, imageId );
		}
		vp->setBoolean( bRet );
		return JS_TRUE;
	}

	do {
		jsval v;
		bool bHasBitmap = false;

		// pageとtextのプロパティは必須
		if( GetPropertyWhenPresent( cx, pObj, _T("page"), &v) != JS_TRUE )  
		{
			break;
		}
		pWnd = Window::GetPrivate( cx, v.toObjectOrNull());
		if( pWnd == NULL )
		{
			break;
		}
		// text
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(text, pObj, "text", WXJS_TYPE_STRING);
		// text
		ZZZJS_PROP_FROMJS_IF_EXIST(imageId, pObj, "imageId", WXJS_TYPE_NUMBER);
		// select
		if( GetPropertyWhenPresent( cx, pObj, _T("select"), &v) == JS_TRUE )  {
			if( FromJS(cx, v, select ) == false ) {
				ReportError_PropTypeError(cx, "select", WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
		}
		// image
		if( GetPropertyWhenPresent( cx, pObj, _T("image"), &v) == JS_TRUE )  {
			if( apBitmap.set(Bitmap::getObject2Instance(cx, v, apBitmap.bAllocation)) == false ) 
			{
				ReportError_PropTypeError(cx, "image", "Bitmap");
				return JS_FALSE;
			}
			bHasBitmap = true;
		}


		bool bRet = false;
		if( bHasBitmap == true )
		{
			bRet = p->AddPage(pWnd, text, select, apBitmap.get() != NULL ? *(apBitmap.get()): wxNullBitmap );
		}
		else
		{
			bRet = p->AddPage(pWnd, text, select, imageId );
		}
		vp->setBoolean( bRet );
		return JS_TRUE;
	} while( 0 );
	
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

JSBool AuiNotebook::insertPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
ZZZJS_FUNC_ENT
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	/*
	bool 	InsertPage (
		  size_t page_idx
		, wxWindow *page
		, const wxString &caption
		, bool select=false
		, const wxBitmap &bitmap=wxNullBitmap)

 		InsertPage() is similar to AddPage, but allows the ability to specify the insert location. More...
 
	bool 	InsertPage (
		  size_t index
		, wxWindow *page
		, const wxString &text
		, bool select
		, int imageId)

 		Inserts a new page at the specified position. 
	*/
	int argIndex = 0;	
//	ZZZJS_CHECK_ARG_COUNT(1, 1)
	if( argc == 0 )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	wxWindow* pWnd = NULL;
	int index = 0;
	zzzJsPtr<wxBitmap> apBitmap;
	wxString text;
	bool select=false;
	int imageId= wxWithImages::NO_IMAGE;
	bool bPass = false;
	JSObject* pObj = NULL;


	if( argv[argIndex].isNumber() == true ) 
	{		
		bool bHasBitmap = false;
		ZZZJS_CHECK_ARG_COUNT(3, 5);

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 5:
			if( argv[argIndex].isNumber() == true )
			{
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(imageId, WXJS_TYPE_NUMBER);
			}
			else
			if( argv[argIndex].isObjectOrNull() == true )
			{
				if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[argIndex], apBitmap.bAllocation)) == false ) 
				{
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
					return JS_FALSE;
				}
				bHasBitmap = true;
			}
			else
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap or Integer");
				return JS_FALSE;
			}
			argIndex--;
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(select, WXJS_TYPE_BOOLEAN);
			argIndex--;
		default:
			// index
			argIndex = 0;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
			// wxWindow *page
			argIndex++;
			pWnd = Window::GetPrivate(cx, argv[argIndex]);
			if( pWnd == NULL )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
				return JS_FALSE;
			}
			// const wxString &text, 
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(text, WXJS_TYPE_STRING);
		}

		bool bRet = p->InsertPage(index, pWnd, text, select, imageId);

		// 戻り値を設定
		vp->setBoolean( bRet );

		return JS_TRUE;

	}
	else
	if( (pObj = argv[argIndex].toObjectOrNull()) != NULL ) 
	{

		do {
			jsval v;
			bool bHasBitmap = false;
			
			// index
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, pObj, "index", WXJS_TYPE_NUMBER);

			// index, pageとtextのプロパティは必須
			if( GetPropertyWhenPresent( cx, pObj, _T("page"), &v) != JS_TRUE )  
			{
				break;
			}
			pWnd = Window::GetPrivate( cx, v.toObjectOrNull());
			if( pWnd == NULL )
			{
				break;
			}
			// text
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(text, pObj, "text", WXJS_TYPE_STRING);
			// imageId
			ZZZJS_PROP_FROMJS_IF_EXIST(imageId, pObj, "imageId", WXJS_TYPE_NUMBER);
			// select
			if( GetPropertyWhenPresent( cx, pObj, _T("select"), &v) == JS_TRUE )  {
				if( FromJS(cx, v, select ) == false ) {
					ReportError_PropTypeError(cx, "select", WXJS_TYPE_NUMBER);
					return JS_FALSE;
				}
			}
			// image
			if( GetPropertyWhenPresent( cx, pObj, _T("image"), &v) == JS_TRUE )  {
				if( apBitmap.set(Bitmap::getObject2Instance(cx, v, apBitmap.bAllocation)) == false ) 
				{
					ReportError_PropTypeError(cx, "image", "Bitmap");
					return JS_FALSE;
				}
				bHasBitmap = true;
			}
					
			bool bRet = false;
			if( bHasBitmap == true )
			{
				bRet = p->InsertPage(index, pWnd, text, select,apBitmap.get() != NULL ? *(apBitmap.get()): wxNullBitmap );
			}
			else
			{
				bRet = p->InsertPage(index, pWnd, text, select, imageId);
			}
			vp->setBoolean( bRet );
			return JS_TRUE;
		} while( 0 );
		if( bPass == false )
		{
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}
		
		bool bRet = p->InsertPage(index, pWnd, text, select, imageId);

		// 戻り値を設定
		vp->setBoolean( bRet );

		return JS_TRUE;
	}
	
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}


JSBool AuiNotebook::getHeightForPageHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
ZZZJS_FUNC_ENT
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		
		
		vp->setInt32(
			p->GetHeightForPageHeight (page)	
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, "pageHeight", WXJS_TYPE_NUMBER)
	
				
			vp->setInt32(
				p->GetHeightForPageHeight (page)	
			);
			return JS_TRUE;	
		} while( 0 );
	}
	
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}



JSBool AuiNotebook::getPageBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
ZZZJS_FUNC_ENT
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		
		wxBitmap bmp = p->GetPageBitmap( page );
		if( bmp.IsOk() )
		{

			*vp = Bitmap::CreateObject(cx, &bmp, obj);
		}
		else 
		{
			vp->setNull();
		}
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, "page", WXJS_TYPE_NUMBER)
			
			wxBitmap bmp = p->GetPageBitmap( page );
			if( bmp.IsOk() )
			{

				*vp = Bitmap::CreateObject(cx, &bmp, obj);
			}
			else 
			{
				vp->setNull();
			}
			return JS_TRUE;	
		} while( 0 );
	}

	
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}


JSBool AuiNotebook::getPageIndex(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	//if( argc > 1 ) {
	//	argc = 1;
	//}
	
	int ret = -1;
	wxWindow* pWindow = Window::GetPrivate(cx, argv[0]);
	if( pWindow != NULL ) {
		ret = p->GetPageIndex( pWindow );
	}
	vp->setInt32( ret );

	return JS_TRUE;
}

JSBool AuiNotebook::getPageToolTip(JSContext *cx, unsigned argc, JS::Value *vp)
{
ZZZJS_FUNC_ENT
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		
		*vp = ToJS(cx, p->GetPageToolTip(page) );
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, "pageIdx", WXJS_TYPE_NUMBER)
			
			
			*vp = ToJS(cx, p->GetPageToolTip(page) );
			return JS_TRUE;	
		} while( 0 );
	}
	
ZZZJS_FUNC_EXIT
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

JSBool AuiNotebook::setFont(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int argIndex = 0;
	zzzJsPtr<wxFont> apFont;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
	*vp = ToJS(cx, p->SetFont( *(apFont.get()) ) );
	return JS_TRUE;
}

JSBool AuiNotebook::setMeasuringFont(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int argIndex = 0;
	zzzJsPtr<wxFont> apFont;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
	p->SetMeasuringFont( *(apFont.get()) );
	return JS_TRUE;
}

JSBool AuiNotebook::setNormalFont(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int argIndex = 0;
	zzzJsPtr<wxFont> apFont;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
	p->SetNormalFont( *(apFont.get()) );
	return JS_TRUE;
}

JSBool AuiNotebook::setPageBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;

	if( argc == 0 )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		
		ZZZJS_CHECK_ARG_COUNT(2, 2)

		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		// bitmap
		if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[argIndex], apBitmap.bAllocation)) == false ) 
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap");
			return JS_FALSE;
		}

		return JS_TRUE;
	}




	if( p == NULL ) {
		return JS_FALSE;
	}
	int page = 0;
    if ( ! FromJS(cx, argv[0], page) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
	
	if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[1], apBitmap.bAllocation)) == false ) {
		return JS_FALSE;
	}

	*vp = ToJS(cx, p->SetPageBitmap(page, *(apBitmap.get())));
	return JS_TRUE;
}

JSBool AuiNotebook::setPageToolTip(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int page = 0;
	wxString text;
    if ( ! FromJS(cx, argv[0], page) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], text) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
    }


	*vp = ToJS(cx, p->SetPageToolTip(page, text));
	return JS_TRUE;
}



JSBool AuiNotebook::setSelectedFont(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	zzzJsPtr<wxFont> apFont;


	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
	p->SetSelectedFont(*(apFont.get()));
	return JS_TRUE;
}






JSBool AuiNotebook::setTabCtrlHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int page = 0;
    if ( ! FromJS(cx, argv[0], page) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	p->SetTabCtrlHeight(page);
	return JS_TRUE;
}




JSBool AuiNotebook::setUniformBitmapSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int x = 0, y = 0;
    if ( ! FromJS(cx, argv[0], x) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], y) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	p->SetUniformBitmapSize(wxSize(x, y));
	return JS_TRUE;
}




JSBool AuiNotebook::split(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int page = 0, direction = 0;
    if ( ! FromJS(cx, argv[0], page) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], direction) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	p->Split(page, direction);
	return JS_TRUE;
}




JSBool AuiNotebook::showWindowMenu(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiNotebook *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	*vp = ToJS(cx, p->ShowWindowMenu());
	return JS_TRUE;
}





/***
 * <events>
 *  <event name="onClicked">
 *   Called when the button is clicked. The type of the argument that your
*    handler receives is @wxCommandEvent.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxAuiNotebook)
const wxString ZZZJS_EVT_AUINOTEBOOK_PAGE_CLOSE = wxT("onPageClose");

void AuiNotebookEventHandler::OnPageClose(wxAuiNotebookEvent &event)
{
	PrivAuiNotebookEvent::Fire<AuiNotebookEvent>(event, ZZZJS_EVT_AUINOTEBOOK_PAGE_CLOSE);
}



void AuiNotebookEventHandler::ConnectPageClose(wxAuiNotebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUINOTEBOOK_PAGE_CLOSE, 
			wxAuiNotebookEventHandler(AuiNotebookEventHandler::OnPageClose));
	}
	else
	{
		p->Disconnect(wxEVT_AUINOTEBOOK_PAGE_CLOSE, 
			wxAuiNotebookEventHandler(AuiNotebookEventHandler::OnPageClose));
	}
}

void AuiNotebookEventHandler::InitConnectEventMap()
{
	AddConnector(ZZZJS_EVT_AUINOTEBOOK_PAGE_CLOSE, ConnectPageClose);
}


