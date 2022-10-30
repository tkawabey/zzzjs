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
#include <wx/notebook.h>
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
#include "js/gui/control/simplebook.h"
#include "js/gui/control/bookctrlbase.h"
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
 * <class name="wxSimplebook" prototype="@wxWindow">
 *  This is the prototype for a control or 'widget'.
 *  A control is generally a small window which processes user input
 *  and/or displays one or more item of data.
 * </class>
 */
ZZZJS_INIT_CLASS(Simplebook, "Simplebook", 0)
void Simplebook::InitClass(JSContext* cx,
								JSObject* obj,
								JSObject* proto)
{
	SimplebookEventHandler::InitConnectEventMap();
}

	
ZZZJS_BEGIN_GET_SET_STR_PROP(wxSimplebook, Simplebook)
{
	BookCtrlBase::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
}
ZZZJS_END_GET_SET_STR_PROP


ZZZJS_BEGIN_METHOD_MAP(Simplebook)
  WXJS_METHOD("create", create, 1)
ZZZJS_END_METHOD_MAP()

ZZZJS_BEGIN_DESTRUCTOR(wxSimplebook, Simplebook)
{

}
ZZZJS_END_DESTRUCTOR

	
// Object 2 Instatance

ZZZJS_BEGIN_O2I(wxSimplebook, Simplebook)
{
	
	pRet = Simplebook::GetPrivate(cx, obj);
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
		, const wxString &name=wxNotebookNameStr
		)
 			Creates a notebook control.
	*/
	wxWindow *parent = NULL;
	int id = -1;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	long style=0;
	wxString name = wxNotebookNameStr;


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



	return new wxSimplebook(parent, id, *(apPoint.get()), *(apSize.get()), style, name);
}
ZZZJS_END_O2I

//
// wxWithImages  imple
//

JSBool Simplebook::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);
	return JS_TRUE;
}
JSBool Simplebook::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
ZZZJS_FUNC_ENT
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxSimplebook *p = GetPrivate(cx, obj);
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
			, const wxString &name=wxNotebookNameStr)
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
		wxString name = wxNotebookNameStr;
		
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
		zzzJsPtr<wxSimplebook> apNotebook;

		if( apNotebook.set( 
			Simplebook::getObject2Instance(cx, argv[argIndex].toObjectOrNull() , apNotebook.bAllocation) ) == true 
		) {
			delete p;
					
			if( apNotebook.bAllocation == true ) {
				p =  apNotebook.release();
			} else {
				p = apNotebook.get();
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



JSBool Simplebook::setEffects(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxSimplebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	void 	SetEffects (wxShowEffect showEffect, wxShowEffect hideEffect)
 		Set the effects to use for showing and hiding the pages. More...
	*/
	int argIndex = 0;
	int showEffect = 0;
	int hideEffect = 0;
	ZZZJS_CHECK_ARG_COUNT(2, 2)


	if( argv[argIndex].isNumber() == true ) 
	{		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(showEffect, WXJS_TYPE_NUMBER)
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(hideEffect, WXJS_TYPE_NUMBER)
		argIndex++;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			/*
			{
				showEffect:Number,
				hideEffect:Number,
			}
			*/
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(showEffect, pObj, "showEffect", WXJS_TYPE_NUMBER)
			ZZZJS_PROP_FROMJS_IF_EXIST(hideEffect, pObj, "hideEffect", WXJS_TYPE_NUMBER)
				
		} while( 0 );
	}
	else 
	{	
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	p->SetEffects((wxShowEffect)showEffect, (wxShowEffect)hideEffect);
	return JS_TRUE;
}

JSBool Simplebook::setEffect(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxSimplebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	void 	SetEffect (wxShowEffect effect)
 		Set the same effect to use for both showing and hiding the pages. More...
	*/
	int argIndex = 0;
	int effect = 0;
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(effect, WXJS_TYPE_NUMBER)
		argIndex++;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			/*
			{
				effect:Number,
			}
			*/
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(effect, pObj, "effect", WXJS_TYPE_NUMBER)
				
		} while( 0 );
	}
	else 
	{	
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	p->SetEffect((wxShowEffect)effect);
	return JS_TRUE;
}

JSBool Simplebook::setEffectsTimeouts(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxSimplebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		void 	SetEffectsTimeouts (unsigned showTimeout, unsigned hideTimeout)
 			Set the effect timeout to use for showing and hiding the pages. More...
	*/
	int argIndex = 0;
	int showTimeout = 0;
	int hideTimeout = 0;
	ZZZJS_CHECK_ARG_COUNT(2, 2)


	if( argv[argIndex].isNumber() == true ) 
	{		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(showTimeout, WXJS_TYPE_NUMBER)
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(hideTimeout, WXJS_TYPE_NUMBER)
		argIndex++;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			/*
			{
				showEffect:Number,
				hideEffec:Number,
			}
			*/
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(showTimeout, pObj, "showTimeout", WXJS_TYPE_NUMBER)
			ZZZJS_PROP_FROMJS_IF_EXIST(hideTimeout, pObj, "hideTimeout", WXJS_TYPE_NUMBER)
				
		} while( 0 );
	}
	else 
	{	
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	p->SetEffectsTimeouts(showTimeout, hideTimeout);
	return JS_TRUE;
}

JSBool Simplebook::setEffectTimeout(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxSimplebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
	void 	SetEffectTimeout (unsigned timeout)
 		Set the same effect timeout to use for both showing and hiding the pages. More...
	*/
	int argIndex = 0;
	int timeout = 0;
	ZZZJS_CHECK_ARG_COUNT(2, 2)


	if( argv[argIndex].isNumber() == true ) 
	{		
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(timeout, WXJS_TYPE_NUMBER)
		argIndex++;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		int page = 0;
	
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			/*
			{
				timeout:Number,
			}
			*/
			if( pObj == NULL ) {
				break;
			}	
			ZZZJS_PROP_FROMJS_IF_EXIST(timeout, pObj, "timeout", WXJS_TYPE_NUMBER)
				
		} while( 0 );
	}
	else 
	{	
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	p->SetEffectTimeout(timeout);
	return JS_TRUE;
}


JSBool Simplebook::showNewPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxSimplebook *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	/*
		bool 	ShowNewPage (wxWindow *page)
 			Add a new page and show it immediately. More...
	*/
	int argIndex = 0;
	wxWindow* page = 0;
	ZZZJS_CHECK_ARG_COUNT(1, 1)


	if( argv[argIndex].isNumber() == true ) 
	{		
		// 0
		page = Window::GetPrivate(cx, argv[argIndex]);
		if( page == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
			return JS_FALSE;
		}
		argIndex++;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		bool bPass = false;
		do {
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			/*
			{
				page:Window
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T("page"), &v) != JS_TRUE )  
			{
				JS_ReportError(cx, "page property not exist.");
				return JS_FALSE;
			}
			page = Window::GetPrivate( cx, v.toObjectOrNull());
			if( page == NULL )
			{
				JS_ReportError(cx, "page property is not Window.");
				return JS_FALSE;
			}
				
		} while( 0 );
	}
	else 
	{	
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}

	p->ShowNewPage(page);
	return JS_TRUE;
}









WXJS_INIT_EVENT_MAP(wxSimplebook)
const wxString WXJS_PAGE_CHANGED_EVENT = wxT("onPageChanged");
const wxString WXJS_PAGE_CHANGING_EVENT = wxT("onPageChanging");



void SimplebookEventHandler::OnPageChanged(wxBookCtrlEvent &event)
{
	PrivBookCtrlEvent::Fire<BookCtrlEvent>(event, WXJS_PAGE_CHANGED_EVENT);
}

void SimplebookEventHandler::OnPageChanging(wxBookCtrlEvent &event)
{
	PrivBookCtrlEvent::Fire<BookCtrlEvent>(event, WXJS_PAGE_CHANGING_EVENT);
}


void SimplebookEventHandler::ConnectNotebookPageChanged(wxSimplebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect( wxEVT_BOOKCTRL_PAGE_CHANGED ,
				wxBookCtrlEventHandler(SimplebookEventHandler::OnPageChanged));
	}
	else
	{
		p->Disconnect( wxEVT_BOOKCTRL_PAGE_CHANGED ,
				wxBookCtrlEventHandler(SimplebookEventHandler::OnPageChanged));
	}
}

void SimplebookEventHandler::ConnectNotebookPageChanging(wxSimplebook *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_BOOKCTRL_PAGE_CHANGING ,
				wxBookCtrlEventHandler(SimplebookEventHandler::OnPageChanging));
	}
	else
	{
		p->Disconnect(wxEVT_BOOKCTRL_PAGE_CHANGING ,
				wxBookCtrlEventHandler(SimplebookEventHandler::OnPageChanging));
	}
}

void SimplebookEventHandler::InitConnectEventMap()
{
	AddConnector(WXJS_PAGE_CHANGED_EVENT, ConnectNotebookPageChanged);
	AddConnector(WXJS_PAGE_CHANGING_EVENT, ConnectNotebookPageChanging);
}






