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
#include <wx/treebook.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/ext/point.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/imagelst.h"
#include "js/gui/control/control.h"
#include "js/gui/control/window.h"
#include "js/gui/control/treebook.h"
#include "js/gui/control/bookctrlbase.h"
#include "js/gui/control/treectrl.h"
#include "js/gui/event/bookctrlevt.h"



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
 * <class name="wxNotebook" prototype="@wxWindow">
 *  This is the prototype for a control or 'widget'.
 *  A control is generally a small window which processes user input
 *  and/or displays one or more item of data.
 * </class>
 */
ZZZJS_INIT_CLASS(Treebook, "Treebook", 0)
void Treebook::InitClass(JSContext* cx,
								JSObject* obj,
								JSObject* proto)
{
	TreeBookEventHandler::InitConnectEventMap();
}

	
ZZZJS_BEGIN_GET_SET_STR_PROP(wxTreebook, Treebook)
{
	BookCtrlBase::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
}
ZZZJS_END_GET_SET_STR_PROP


ZZZJS_BEGIN_METHOD_MAP(Treebook)
  WXJS_METHOD("create", create, 1)
ZZZJS_END_METHOD_MAP()

ZZZJS_BEGIN_DESTRUCTOR(wxTreebook, Treebook)
{

}
ZZZJS_END_DESTRUCTOR

	
// Object 2 Instatance

ZZZJS_BEGIN_O2I(wxTreebook, Treebook)
{
	
	pRet = Treebook::GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}
	/*
		bool 	Create (
		wxWindow *parent
		, wxWindowID id
		, const wxPoint &pos=wxDefaultPosition
		, const wxSize &size=wxDefaultSize
		, long style=0
		, const wxString &name=wxTreeBookNameStr
		)
 			Creates a Treebook control.
	*/
	wxWindow *parent = NULL;
	int id = -1;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	long style=0;
	wxString name = wxEmptyString;


	/*
	{
			parent:Window
		,	id:Number
		,	pos:Point [Option = DefaultPosition]
		,	size:Size [Option = DefaultSize]
		,	style:Number [Option = 0]
		,	name:String [Option = ...]
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
	ZZZJS_PROP_FROMJS_CHK_AND_ERROR(id, obj, "id", WXJS_TYPE_NUMBER)	
	// pos:Point [Option = DefaultPosition]
	ZZZJS_PROP_AP_IF_EXIST(apPoint, zzzJs::ext::Point, "pos");
	// size:Size [Option = DefaultSize]
	ZZZJS_PROP_AP_IF_EXIST(apSize, Size, "size");
	// style
	ZZZJS_PROP_FROMJS_IF_EXIST(style, obj, "style", WXJS_TYPE_NUMBER);
	// name
	ZZZJS_PROP_FROMJS_IF_EXIST(name, obj, "name", WXJS_TYPE_STRING);



	return new wxTreebook(parent, id, *(apPoint.get()), *(apSize.get()), style, name);
}
ZZZJS_END_O2I

//
// wxWithImages  imple
//
JSBool Treebook::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);
	return JS_TRUE;
}
JSBool Treebook::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
ZZZJS_FUNC_ENT
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;


	if( argc == 0 ) 
	{
		return JS_TRUE;
	}
	/*
		bool 	Create (
			wxWindow *parent
			, wxWindowID id
			, const wxPoint &pos=wxDefaultPosition
			, const wxSize &size=wxDefaultSize
			, long style=0
			, const wxString &name=wxTreeBookNameStr)
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
		int id = -1;
		zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		long style=0;
		wxString name = wxEmptyString;
		
		ZZZJS_CHECK_ARG_COUNT(2, 6);

		argIndex++;
		// id
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);


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
		}


		bool bRet = p->Create( parent, id, *apPoint.get(), *apSize.get(), style, name);
		
		rval->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	{
		zzzJsPtr<wxTreebook> apTreeBook;

		if( apTreeBook.set( 
			Treebook::getObject2Instance(cx, argv[argIndex].toObjectOrNull() , apTreeBook.bAllocation) ) == true 
		) {
			delete p;
					
			if( apTreeBook.bAllocation == true ) {
				p =  apTreeBook.release();
			} else {
				p = apTreeBook.get();
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


JSBool Treebook::insertSubPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	// Inserts a new sub-page to the end of children of the page at given pos.
	virtual bool InsertSubPage(size_t pos,
								wxWindow *page,
								const wxString& text,
								bool bSelect = false,
							int imageId = wxWithImages::NO_IMAGE(<--  -1 )) wxOVERRIDE;
	*/
	if ( argc == 0 )
	{    
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;    
	}
	int argIndex = 0;


	if( argv[argIndex].isNumber() == true )
	{
		// 　パラメータが引数で与えられた場合

		ZZZJS_CHECK_ARG_COUNT(3, 5)

		int pos = -1;
		wxWindow* pWnd = NULL;
		wxString strText(_T(""));
		bool bSelect = false;
		int imageID = wxWithImages::NO_IMAGE;

		
		argIndex = argc - 1;
		switch( argc ) 
		{
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(imageID, WXJS_TYPE_NUMBER);
			argIndex--;
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(bSelect, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}
		argIndex = 0;	
		// 1: 	
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(pos, WXJS_TYPE_NUMBER);
		argIndex++;
		// 2:
		pWnd = Window::GetPrivate(cx, argv[argIndex]);
		if( pWnd == NULL ) 
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
			return JS_FALSE;
		}
		argIndex++;
		// 3:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(strText, WXJS_TYPE_NUMBER);
		argIndex++;


		bool bRet = p->InsertSubPage( pos, pWnd, strText, bSelect, imageID);
		vp->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isNullOrUndefined() == true )
	{
		// 　パラメータがオブジェクトで与えられた場合
		bool bPass = false;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Object");
			return JS_FALSE;
		}
		/*
		{
			pos:Number,
			page:Window,
			text:String
			select:Boolean [Option, Default=false],
			imageId:Number  [Option, Default=wxWithImages::NO_IMAGE(<--  -1 )]
		}
		*/

		do {
			jsval v;

			int pos = -1;
			wxWindow* pWnd = NULL;
			wxString strText(_T(""));
			bool bSelect = false;
			int imageID = wxWithImages::NO_IMAGE;


			// pos
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pos, pObj, "pos", WXJS_TYPE_NUMBER);
			// page
			if( GetPropertyWhenPresent( cx, pObj, _T("page"), &v) != JS_TRUE )  
			{
				JS_ReportError(cx, "page propety not exist.");
				return JS_FALSE;
			}
			pWnd = Window::GetPrivate( cx, v.toObjectOrNull());
			if( pWnd == NULL )
			{
				JS_ReportError(cx, "page propety is not Window.");
				return JS_FALSE;	break;
			}
			// text
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(strText, pObj, "text", WXJS_TYPE_NUMBER);
			// imageId
			ZZZJS_PROP_FROMJS_IF_EXIST(imageID, pObj, "imageId", WXJS_TYPE_NUMBER);
			// select
			ZZZJS_PROP_FROMJS_IF_EXIST(bSelect, pObj, "select", WXJS_TYPE_BOOLEAN);


			bool bRet = p->InsertSubPage( pos, pWnd, strText, bSelect, imageID);
			vp->setBoolean( bRet );
			return JS_TRUE;
		}while ( false );
	}


	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;		
}

JSBool Treebook::addSubPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		// Adds a new child-page to the last top-level page inserted.
		// Useful when constructing 1 level tree structure.
		virtual bool AddSubPage(wxWindow *page,
								const wxString& text,
								bool bSelect = false,
								int imageId = wxWithImages::NO_IMAGE(<--  -1 )) wxOVERRIDE;
	*/
	if ( argc == 0 )
	{    
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;    
	}
	int argIndex = 0;


	if( argv[argIndex].isNumber() == true )
	{
		// 　パラメータが引数で与えられた場合

		ZZZJS_CHECK_ARG_COUNT(3, 4)

		wxWindow* pWnd = NULL;
		wxString strText(_T(""));
		bool bSelect = false;
		int imageID = wxWithImages::NO_IMAGE;

		
		argIndex = argc - 1;
		switch( argc ) 
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(imageID, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(bSelect, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}
		argIndex = 0;	
		// 1:
		pWnd = Window::GetPrivate(cx, argv[argIndex]);
		if( pWnd == NULL ) 
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
			return JS_FALSE;
		}
		argIndex++;
		// 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(strText, WXJS_TYPE_NUMBER);
		argIndex++;


		bool bRet = p->AddSubPage( pWnd, strText, bSelect, imageID);
		vp->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isNullOrUndefined() == true )
	{
		// 　パラメータがオブジェクトで与えられた場合
		bool bPass = false;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Object");
			return JS_FALSE;
		}
		/*
		{
			page:Window,
			text:String
			select:Boolean [Option, Default=false],
			imageId:Number  [Option, Default=wxWithImages::NO_IMAGE(<--  -1 )]
		}
		*/

		do {
			jsval v;

			wxWindow* pWnd = NULL;
			wxString strText(_T(""));
			bool bSelect = false;
			int imageID = wxWithImages::NO_IMAGE;


			// page
			if( GetPropertyWhenPresent( cx, pObj, _T("page"), &v) != JS_TRUE )  
			{
				JS_ReportError(cx, "page propety not exist.");
				return JS_FALSE;
			}
			pWnd = Window::GetPrivate( cx, v.toObjectOrNull());
			if( pWnd == NULL )
			{
				JS_ReportError(cx, "page propety is not Window.");
				return JS_FALSE;	break;
			}
			// text
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(strText, pObj, "text", WXJS_TYPE_STRING);
			// imageId
			ZZZJS_PROP_FROMJS_IF_EXIST(imageID, pObj, "imageId", WXJS_TYPE_NUMBER);
			// select
			ZZZJS_PROP_FROMJS_IF_EXIST(bSelect, pObj, "select", WXJS_TYPE_BOOLEAN);


			bool bRet = p->AddSubPage( pWnd, strText, bSelect, imageID);
			vp->setBoolean( bRet );
			return JS_TRUE;
		}while ( false );
	}


	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;		
}

JSBool Treebook::isNodeExpanded(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		// Gets the page node state -- node is expanded or collapsed
		virtual bool IsNodeExpanded(size_t pos) const;
	*/
	if ( argc == 0 )
	{    
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;    
	}
	int argIndex = 0;


	if( argv[argIndex].isNumber() == true )
	{
		// 　パラメータが引数で与えられた場合
		int pos = 0;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(pos, WXJS_TYPE_NUMBER);
		argIndex++;


		bool bRet = p->IsNodeExpanded( pos );
		vp->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isNullOrUndefined() == true )
	{
		// 　パラメータがオブジェクトで与えられた場合
		bool bPass = false;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Object");
			return JS_FALSE;
		}
		/*
		{
			pos:Number
		}
		*/

		do {
			jsval v;
			
			int pos = 0;
			
			// pos
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pos, pObj, "pos", WXJS_TYPE_NUMBER);
			

			bool bRet = p->IsNodeExpanded( pos );
			vp->setBoolean( bRet );
			return JS_TRUE;
		}while ( false );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;		
}

JSBool Treebook::expandNode(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	// Expands or collapses the page node. Returns the previous state.
	// May generate page changing events (if selected page
	// is under the collapsed branch, then parent is autoselected).
	virtual bool ExpandNode(size_t pos, bool expand = true);
	*/
	if ( argc == 0 )
	{    
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;    
	}
	int argIndex = 0;


	if( argv[argIndex].isNumber() == true )
	{
		// 　パラメータが引数で与えられた場合

		ZZZJS_CHECK_ARG_COUNT(1, 2)

		int pos = -1;
		bool expand = true;
		
		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(expand, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}
		argIndex = 0;	
		// 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(pos, WXJS_TYPE_NUMBER);
		argIndex++;


		bool bRet = p->ExpandNode( pos, expand);
		vp->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isNullOrUndefined() == true )
	{
		// 　パラメータがオブジェクトで与えられた場合
		bool bPass = false;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Object");
			return JS_FALSE;
		}
		/*
		{
			pos:Number,
			select:Boolean [Option, Default=true],
		}
		*/
		do {
			jsval v;
			
			int pos = -1;
			bool expand = true;


			// text
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pos, pObj, "pos", WXJS_TYPE_NUMBER);
			// select
			ZZZJS_PROP_FROMJS_IF_EXIST(expand, pObj, "expand", WXJS_TYPE_BOOLEAN);
			
			bool bRet = p->ExpandNode( pos, expand);
			vp->setBoolean( bRet );
			return JS_TRUE;
		}while ( false );
	}
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;		
}


JSBool Treebook::collapseNode(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		// shortcut for ExpandNode(pos, false)
		bool CollapseNode(size_t pos) { return ExpandNode(pos, false); }
	*/
	if ( argc == 0 )
	{    
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;    
	}
	int argIndex = 0;


	if( argv[argIndex].isNumber() == true )
	{
		// 　パラメータが引数で与えられた場合
		int pos = 0;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(pos, WXJS_TYPE_NUMBER);
		argIndex++;


		bool bRet = p->CollapseNode( pos );
		vp->setBoolean( bRet );
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isNullOrUndefined() == true )
	{
		// 　パラメータがオブジェクトで与えられた場合
		bool bPass = false;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Object");
			return JS_FALSE;
		}
		/*
		{
			pos:Number
		}
		*/

		do {
			jsval v;
			
			int pos = 0;
			
			// pos
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pos, pObj, "pos", WXJS_TYPE_NUMBER);
			

			bool bRet = p->CollapseNode( pos );
			vp->setBoolean( bRet );
			return JS_TRUE;
		}while ( false );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;		
}

JSBool Treebook::getPageParent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		// get the parent page or wxNOT_FOUND if this is a top level page
		int GetPageParent(size_t pos) const;
	*/
	if ( argc == 0 )
	{    
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;    
	}
	int argIndex = 0;


	if( argv[argIndex].isNumber() == true )
	{
		// 　パラメータが引数で与えられた場合
		int pos = 0;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(pos, WXJS_TYPE_NUMBER);
		argIndex++;


		int iRet = p->GetPageParent( pos );
		if( iRet == wxNOT_FOUND )
		{
			vp->setUndefined();
		}
		else 
		{
			vp->setInt32( iRet );
		}
		return JS_TRUE;
	}
	else
	if( argv[argIndex].isNullOrUndefined() == true )
	{
		// 　パラメータがオブジェクトで与えられた場合
		bool bPass = false;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		if( pObj == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Object");
			return JS_FALSE;
		}
		/*
		{
			pos:Number
		}
		*/

		do {
			jsval v;
			
			int pos = 0;
			
			// pos
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(pos, pObj, "pos", WXJS_TYPE_NUMBER);

			int iRet = p->GetPageParent( pos );
			if( iRet == wxNOT_FOUND )
			{
				vp->setUndefined();
			}
			else 
			{
				vp->setInt32( iRet );
			}
			return JS_TRUE;
		}while ( false );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;		
}
JSBool Treebook::getTreeCtrl(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxTreebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	// the tree control we use for showing the pages index tree
	wxTreeCtrl* GetTreeCtrl() const { return (wxTreeCtrl*)m_bookctrl; }
	*/
	wxTreeCtrl* pTreeCtrl = p->GetTreeCtrl();
	if( pTreeCtrl == NULL )
	{
		vp->setUndefined();
		return JS_TRUE;
	}


	jsval v = TreeCtrl::CreateObject(cx, pTreeCtrl);
	*vp = v;

	return JS_TRUE;
}




WXJS_INIT_EVENT_MAP(wxTreebook)
const wxString WXJS_PAGE_CHANGED_EVENT   = wxT("onPageChanged");
const wxString WXJS_PAGE_CHANGING_EVENT  = wxT("onPageChanging");
const wxString WXJS_NODE_COLLAPSED_EVENT = wxT("onNodeCollapsed");
const wxString WXJS_NODE_EXPANDED_EVENT  = wxT("onNodeExpanded");



void TreeBookEventHandler::OnPageChanged(wxBookCtrlEvent &event)
{
	PrivBookCtrlEvent::Fire<BookCtrlEvent>(event, WXJS_PAGE_CHANGED_EVENT);
}

void TreeBookEventHandler::OnPageChanging(wxBookCtrlEvent &event)
{
	PrivBookCtrlEvent::Fire<BookCtrlEvent>(event, WXJS_PAGE_CHANGING_EVENT);
}

void TreeBookEventHandler::OnNodeCollapsed(wxBookCtrlEvent &event)
{
	PrivBookCtrlEvent::Fire<BookCtrlEvent>(event, WXJS_NODE_COLLAPSED_EVENT);
}

void TreeBookEventHandler::OnNodeExpanded(wxBookCtrlEvent &event)
{
	PrivBookCtrlEvent::Fire<BookCtrlEvent>(event, WXJS_NODE_EXPANDED_EVENT);
}


void TreeBookEventHandler::ConnectPageChanged(wxTreebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_TREEBOOK_PAGE_CHANGED,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnPageChanged));
	}
	else
	{
		p->Disconnect(wxEVT_TREEBOOK_PAGE_CHANGED,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnPageChanged));
	}
}

void TreeBookEventHandler::ConnectPageChanging(wxTreebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect( wxEVT_TREEBOOK_PAGE_CHANGING,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnPageChanging));
	}
	else
	{
		p->Disconnect( wxEVT_TREEBOOK_PAGE_CHANGING,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnPageChanging));
	}
}

void TreeBookEventHandler::ConnectNodeCollapsed(wxTreebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect( wxEVT_TREEBOOK_NODE_COLLAPSED,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnNodeCollapsed));
	}
	else
	{
		p->Disconnect( wxEVT_TREEBOOK_NODE_COLLAPSED,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnNodeCollapsed));
	}
}

void TreeBookEventHandler::ConnectNodeExpanded(wxTreebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect( wxEVT_TREEBOOK_NODE_EXPANDED,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnNodeExpanded));
	}
	else
	{
		p->Disconnect( wxEVT_TREEBOOK_NODE_EXPANDED,
				wxBookCtrlEventHandler(TreeBookEventHandler::OnNodeExpanded));
	}
}

void TreeBookEventHandler::InitConnectEventMap()
{
	AddConnector(WXJS_PAGE_CHANGED_EVENT, ConnectPageChanged);
	AddConnector(WXJS_PAGE_CHANGING_EVENT, ConnectPageChanging);
	AddConnector(WXJS_NODE_COLLAPSED_EVENT, ConnectNodeCollapsed);
	AddConnector(WXJS_NODE_EXPANDED_EVENT, ConnectNodeExpanded);
}






