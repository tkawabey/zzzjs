/*
 * wxJavaScript - control.cpp
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
 * $Id: control.cpp 672 2007-04-12 20:29:39Z fbraem $
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
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/imagelst.h"
#include "js/gui/control/control.h"
#include "js/gui/control/window.h"
#include "js/gui/control/bookctrlbase.h"



using namespace zzzJs;
using namespace zzzJs::gui;


#define PROP_PAGE_COUNT				"pageCount"
#define PROP_CURRENT_PAGE			"currentPage"
#define PROP_SELECTION				"selection"
#define PROP_CONTROLLER_SIZE		"controllerSize"
#define PROP_CONTROL_SIZER			"controlSizer"
#define PROP_INTERNAL_BORDER		"internalBorder"
#define PROP_CONTOL_MARGIN			"controlMargin"
#define PROP_IS_VETICAL				"isVertical"
#define PROP_FIT_TO_CURRENT_PAGE	"fitToCurrentPage"
#define PROP_PAGE					"page"
#define PROP_IMAGE					"image"
#define PROP_TEXT					"text"
/***
 * <file>control/control</file>
 * <module>gui</module>
 * <class name="wxBookCtrlBase" prototype="@wxWindow">
 *  This is the prototype for a control or 'widget'.
 *  A control is generally a small window which processes user input
 *  and/or displays one or more item of data.
 * </class>
 */
ZZZJS_INIT_CLASS(BookCtrlBase, "BookCtrlBase", 0)

/***
 * <properties>
 *  <property name="label" type=WXJS_TYPE_STRING>
 *   Get/Set the label
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(BookCtrlBase)
    ZZZJS_READONLY_PROPERTY(P_PAGE_COUNT, PROP_PAGE_COUNT)
    ZZZJS_READONLY_PROPERTY(P_CURRENT_PAGE, PROP_CURRENT_PAGE)
    ZZZJS_READONLY_PROPERTY(P_SELECTION, PROP_SELECTION)
    ZZZJS_READONLY_PROPERTY(CONTROLLER_SIZE, PROP_CONTROLLER_SIZE)
    ZZZJS_READONLY_PROPERTY(CONTROL_SIZER, PROP_CONTROL_SIZER)
    ZZZJS_PROPERTY(INTERNAL_BORDER, PROP_INTERNAL_BORDER)
    ZZZJS_PROPERTY(CONTOL_MARGIN, PROP_CONTOL_MARGIN)
    ZZZJS_READONLY_PROPERTY(IS_VETICAL, PROP_IS_VETICAL)
    ZZZJS_PROPERTY(FIT_TO_CURRENT_PAGE, PROP_FIT_TO_CURRENT_PAGE)
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_GET_PROP(wxBookCtrlBase, BookCtrlBase)
{
	switch( id )
	{
	case P_PAGE_COUNT:
		ToJSVal(cx, vp, p->GetPageCount());
		break;
	case P_CURRENT_PAGE:
		{
			wxWindow* pItem = p->GetCurrentPage();
			vp.set( Window::CreateObject( cx, pItem, NULL) );
		}
		break;
	case P_SELECTION:
		ToJSVal(cx, vp, p->GetSelection());
		break;
	case CONTROLLER_SIZE:
		{
			wxSize sz = p->GetControllerSize();
			vp.set( Size::CreateObject( cx, new wxSize(sz), NULL) );
		}
		break;
	case CONTROL_SIZER:
		{
			wxSizer* pItem = p->GetControlSizer();
			vp.set( Sizer::CreateObject( cx, pItem, NULL) );
		}
		break;
	case INTERNAL_BORDER:
		ToJSVal(cx, vp, p->GetInternalBorder());
		break;
	case CONTOL_MARGIN:
		ToJSVal(cx, vp, p->GetControlMargin());
		break;
	case IS_VETICAL:
		ToJSVal(cx, vp, p->IsVertical());
		break;
	case FIT_TO_CURRENT_PAGE:
		ToJSVal(cx, vp, p->GetFitToCurrentPage());
		break;
	}
    return true;
}
ZZZJS_END_GET_PROP

ZZZJS_BEGIN_SET_PROP(wxBookCtrlBase, BookCtrlBase)
{
	switch( id )
	{
	case P_SELECTION:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetSelection(iVal);
			}
		}
		break;
	case INTERNAL_BORDER:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetInternalBorder(iVal);
			}
		}
		break;
	case CONTOL_MARGIN:
		{
			int iVal = 0;
			if( FromJS(cx, vp, iVal ) == true ) {
				p->SetControlMargin(iVal);
			}
		}
		break;
	case FIT_TO_CURRENT_PAGE:
		{
			bool bVal = false;
			if( FromJS(cx, vp, bVal ) == true ) {
				p->SetFitToCurrentPage(bVal);
			}
		}
		break;
	}
    return true;
}
ZZZJS_END_SET_PROP
	
ZZZJS_BEGIN_GET_SET_STR_PROP(wxBookCtrlBase, BookCtrlBase)
{
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
}
ZZZJS_END_GET_SET_STR_PROP


ZZZJS_BEGIN_METHOD_MAP(BookCtrlBase)
  WXJS_METHOD("assignImageList", assignImageList, 1)
  WXJS_METHOD("setImageList", setImageList, 1)
  WXJS_METHOD("getImageList", getImageList, 0)
  WXJS_METHOD("getPageImage", getPageImage, 1)
  WXJS_METHOD("setPageImage", setPageImage, 1)
  WXJS_METHOD("getPageText", getPageText, 1)
  WXJS_METHOD("setPageText", setPageText, 1)
  WXJS_METHOD("advanceSelection", advanceSelection, 0)
  WXJS_METHOD("changeSelection", changeSelection, 1)
  WXJS_METHOD("findPage", findPage, 1)
  WXJS_METHOD("getPage", getPage, 1)
  WXJS_METHOD("addPage", addPage, 1)
  WXJS_METHOD("deleteAllPages", deleteAllPages, 0)
  WXJS_METHOD("deletePage", deletePage, 1)
  WXJS_METHOD("insertPage", insertPage, 1)
  WXJS_METHOD("removePage", removePage, 1)
ZZZJS_END_METHOD_MAP()

ZZZJS_BEGIN_DESTRUCTOR(wxBookCtrlBase, BookCtrlBase)
ZZZJS_END_DESTRUCTOR

	
// Object 2 Instatance

ZZZJS_BEGIN_O2I(wxBookCtrlBase, BookCtrlBase)
{
	
	pRet = BookCtrlBase::GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}



	return NULL;
}
ZZZJS_END_O2I

//
// wxWithImages  imple
//

JSBool BookCtrlBase::assignImageList(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	void 	AssignImageList (wxImageList *imageList)
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)

	zzzJsPtr<ImageList> apImgLst;
	if ( apImgLst.set(ImageList::getObject2Instance(cx, argv[argIndex], apImgLst.bAllocation)) == false )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, ImageList::getClassName());
		return JS_FALSE;
	}

	p->AssignImageList((apImgLst.get()));
	return JS_TRUE;	
}




//TODO: An event can't be created yet, so this function is not used.
JSBool BookCtrlBase::setImageList(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual void 	SetImageList (wxImageList *imageList)
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)

	zzzJsPtr<ImageList> apImgLst;
	if ( apImgLst.set(ImageList::getObject2Instance(cx, argv[argIndex], apImgLst.bAllocation)) == false )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, ImageList::getClassName());
		return JS_FALSE;
	}

	p->SetImageList((apImgLst.get()));
	return JS_TRUE;	
}




//TODO: Returns the associated image list, may be NULL. More...
JSBool BookCtrlBase::getImageList(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	wxImageList * 	GetImageList () const
	*/

	ImageList* pImageLst = (ImageList*)p->GetImageList();
	if( pImageLst == NULL) 
	{
		vp->setNull();
	}
	else
	{
		*vp = ( ImageList::CreateObject(cx, pImageLst, NULL) );
	}

	return JS_TRUE;	
}


//
// Image list functions
//

//TODO: An event can't be created yet, so this function is not used.
JSBool BookCtrlBase::getPageImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual int 	GetPageImage (size_t nPage) const =0
	*/
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		

		int ret = p->GetPageImage(page);
		vp->setInt32( ret );
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
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_NUMBER)
	
				
			int ret = p->GetPageImage(page);
			vp->setInt32( ret );
			return JS_TRUE;	
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}


//TODO: Sets the image index for the given page. More...
JSBool BookCtrlBase::setPageImage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual bool 	SetPageImage (size_t page, int image)=0
 		Sets the image index for the given page. More...
	*/
	if ( argc > 2 )
        argc = 2;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 2)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		int image = 0;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(image, WXJS_TYPE_NUMBER)
		argIndex++;
		

		bool ret = p->SetPageImage(page, image);
		vp->setBoolean( ret );
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
		int image = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_NUMBER)
			ZZZJS_PROP_FROMJS_IF_EXIST(image, pObj, PROP_IMAGE, WXJS_TYPE_NUMBER)
	
				
			bool ret = p->SetPageImage(page, image);
			vp->setBoolean( ret );
			return JS_TRUE;	
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}


//
//Page text functions
//

//TODO: Returns the string for the given page. More...
JSBool BookCtrlBase::getPageText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual wxString 	GetPageText (size_t nPage) const =0
 		Returns the string for the given page. More...
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		

		*vp = ToJS(cx, p->GetPageText(page) );
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
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_NUMBER)
					
			*vp = ToJS(cx, p->GetPageText(page) );
			return JS_TRUE;	
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

//TODO: Sets the text for the given page. More...
JSBool BookCtrlBase::setPageText(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual bool 	SetPageText (size_t page, const wxString &text)=0
 		Sets the text for the given page. More...
	*/
	if ( argc > 2 )
        argc = 2;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 2)


	if( argv[argIndex].isNumber() == true ) 
	{
		int page = 0;
		wxString text;
		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_NUMBER)
		argIndex++;
		// 2
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(text, WXJS_TYPE_STRING)
		argIndex++;
		

		*vp = ToJS(cx, p->SetPageText(page, text) );
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
		wxString text;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_NUMBER)
			ZZZJS_PROP_FROMJS_IF_EXIST(text, pObj, PROP_TEXT, WXJS_TYPE_STRING)
					
			*vp = ToJS(cx, p->SetPageText(page, text) );
			return JS_TRUE;	
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}

//
// Selection functions
//



JSBool BookCtrlBase::advanceSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	void 	AdvanceSelection (bool forward=true)
	Cycles through the tabs.

	The call to this function generates the page changing events.
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(0, 1)

	bool forward = true;


	if( argc != 0 ) {
		if( argv[argIndex].isBoolean() == true ) 
		{
			// 0
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(forward, WXJS_TYPE_BOOLEAN)
			argIndex++;
		}
		else 
		if( argv[argIndex].isObjectOrNull() == true ) 
		{
			do {
				jsval v;
				JSObject* pObj = argv[argIndex].toObjectOrNull();
			
				if( pObj == NULL ) {
					break;
				}	
				ZZZJS_PROP_FROMJS_IF_EXIST(forward, pObj, "forward", WXJS_TYPE_BOOLEAN)
					
			} while( 0 );
		}
	}

	p->AdvanceSelection( forward );
	
	return JS_TRUE;	
}


JSBool BookCtrlBase::changeSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual int 	ChangeSelection (size_t page)=0

	Changes the selection to the given page, returning the previous selection.

	This function behaves as SetSelection() but does not generate the page changing events.

	See User Generated Events vs Programmatically Generated Events for more information.
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)

	int page = 0;
	bool bPass = false;


	if( argv[argIndex].isNumber() == true ) 
	{
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_BOOLEAN)
		argIndex++;

		bPass = true;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_BOOLEAN)
					
			bPass = true;
		} while( 0 );
	}
	if( bPass == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	
	vp->setInt32( p->ChangeSelection( page ) );
	return JS_TRUE;	
}


JSBool BookCtrlBase::findPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	int 	FindPage (const wxWindow *page) const
		Returns the index of the specified tab window or wxNOT_FOUND if not found
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)

	int page = 0;
	bool bPass = false;
	

	wxWindow* pWnd = Window::GetPrivate(cx, argv[argIndex]);
	if( pWnd == NULL )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	
	vp->setInt32( p->FindPage( pWnd ) );
	return JS_TRUE;	
}


JSBool BookCtrlBase::getPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	wxWindow * 	GetPage (size_t page) const
 		Returns the window at the given page position. More...
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	int page = 0;
	bool bPass = false;


	if( argv[argIndex].isNumber() == true ) 
	{
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_BOOLEAN)
		argIndex++;

		bPass = true;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_BOOLEAN)
					
			bPass = true;
		} while( 0 );
	}
	if( bPass == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	wxWindow* pWnd = p->GetPage( page );
	if( pWnd != NULL )
	{
		*vp = Window::CreateObject(cx,  pWnd );
	}
	else
	{
		vp->setNull();
	}
	return JS_TRUE;	
}




JSBool BookCtrlBase::addPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual bool 	AddPage (
			wxWindow *page, 
			const wxString &text, 
			bool select=false, 
			int imageId=NO_IMAGE
	)
 		Adds a new page. More...
	*/
	int argIndex = 0;	
//	ZZZJS_CHECK_ARG_COUNT(1, 1)
	if( argc == 0 )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	wxWindow* pWnd = NULL;
	wxString text;
	bool select=false;
	int imageId= wxWithImages::NO_IMAGE;
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
		*/
		ZZZJS_CHECK_ARG_COUNT(2, 4)


		argIndex = argc -1;
		switch( argc )
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(imageId, WXJS_TYPE_NUMBER);
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


		bool bRet = p->AddPage(pWnd, text, select, imageId);

		// 戻り値を設定
		vp->setBoolean( bRet );

		return JS_TRUE;
	}

	do {
		jsval v;

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
		// text
		ZZZJS_PROP_FROMJS_IF_EXIST(select, pObj, "select", WXJS_TYPE_BOOLEAN);
					
		bPass = true;
	} while( 0 );
	if( bPass == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	bool bRet = p->AddPage(pWnd, text, select, imageId);

	// 戻り値を設定
	vp->setBoolean( bRet );

	return JS_TRUE;	
}




JSBool BookCtrlBase::deleteAllPages(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;


	bool bRet = p->DeleteAllPages();

	// 戻り値を設定
	vp->setBoolean( bRet );

	return JS_TRUE;	
}


JSBool BookCtrlBase::deletePage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		virtual bool 	DeletePage (size_t page)
 			Deletes the specified page, and the associated window.
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	int page = 0;
	bool bPass = false;


	if( argv[argIndex].isNumber() == true ) 
	{
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_BOOLEAN)
		argIndex++;

		bPass = true;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_BOOLEAN)
					
			bPass = true;
		} while( 0 );
	}
	if( bPass == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	bool bRet = p->DeletePage( page );
	vp->setBoolean( bRet );
	return JS_TRUE;	
}






JSBool BookCtrlBase::insertPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual bool 	InsertPage (
		size_t index
		, wxWindow *page
		, const wxString &text
		, bool select=false
		, int imageId=NO_IMAGE
	)
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
	wxString text;
	bool select=false;
	int imageId= wxWithImages::NO_IMAGE;
	bool bPass = false;
	JSObject* pObj = NULL;


	if( argv[argIndex].isNumber() == true ) 
	{
		
		ZZZJS_CHECK_ARG_COUNT(3, 5);

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(imageId, WXJS_TYPE_NUMBER);
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
			ZZZJS_PROP_FROMJS_IF_EXIST(select, pObj, "select", WXJS_TYPE_BOOLEAN);
					
			bPass = true;
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

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;	
}




JSBool BookCtrlBase::removePage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxBookCtrlBase *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	virtual bool 	RemovePage (size_t page)
 		Deletes the specified page, without deleting the associated window. More...
	*/
	if ( argc > 1 )
        argc = 1;
	int argIndex = 0;
	
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	int page = 0;
	bool bPass = false;


	if( argv[argIndex].isNumber() == true ) 
	{
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(page, WXJS_TYPE_BOOLEAN)
		argIndex++;

		bPass = true;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(page, pObj, PROP_PAGE, WXJS_TYPE_BOOLEAN)
					
			bPass = true;
		} while( 0 );
	}
	if( bPass == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	bool bRet = p->RemovePage( page );
	vp->setBoolean( bRet );
	return JS_TRUE;	
}

