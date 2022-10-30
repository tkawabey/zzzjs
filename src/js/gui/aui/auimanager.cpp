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
#include "js/gui/aui/auimanager.h"
#include "js/gui/aui/auipanelinfo.h"
#include "js/gui/aui/auinotebook.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"
#include "js/gui/aui/auimanagerevent.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::aui;

WXJS_INIT_CLASS(AuiManager, "Manager", 1)

void AuiManager::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{
	int das = wxAUI_INSERT_PANE;

    AuiManagerEventHandler::InitConnectEventMap();
}
	
WXJS_BEGIN_CONSTANT_MAP(AuiManager)
  WXJS_CONSTANT(wxAUI_MGR_, ALLOW_FLOATING)
  WXJS_CONSTANT(wxAUI_MGR_, ALLOW_ACTIVE_PANE)
  WXJS_CONSTANT(wxAUI_MGR_, TRANSPARENT_DRAG )
  WXJS_CONSTANT(wxAUI_MGR_, TRANSPARENT_HINT )
  WXJS_CONSTANT(wxAUI_MGR_, VENETIAN_BLINDS_HINT )
  WXJS_CONSTANT(wxAUI_MGR_, RECTANGLE_HINT )
  WXJS_CONSTANT(wxAUI_MGR_, HINT_FADE )
  WXJS_CONSTANT(wxAUI_MGR_, NO_VENETIAN_BLINDS_FADE )
  WXJS_CONSTANT(wxAUI_MGR_, LIVE_RESIZE )
  WXJS_CONSTANT(wxAUI_MGR_, DEFAULT )



  WXJS_CONSTANT(wxAUI_, INSERT_PANE )
  WXJS_CONSTANT(wxAUI_, INSERT_ROW )
  WXJS_CONSTANT(wxAUI_, INSERT_DOCK )
WXJS_END_CONSTANT_MAP()
/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(AuiManager)
  WXJS_PROPERTY(P_FLAG, "flags")
  WXJS_PROPERTY(P_ManagedWindow, "managedWindow")
  WXJS_PROPERTY(P_DockSizeConstraint, "dockSizeConstraint")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxAuiManager, AuiManager)
	switch (id) 
	{
	case P_FLAG:
		ToJSVal(cx, vp, p->GetFlags());
		break;
	case P_ManagedWindow:
		{
			vp.set( Window::CreateObject(cx, p->GetManagedWindow()) );
		}
		break;
	case P_DockSizeConstraint:
		{
			jsval vns;
			double widthpct = 0,heightpct = 0;
			p->GetDockSizeConstraint(&widthpct, &heightpct);
			JSObject *newObject = JS_NewObject(cx, NULL, NULL, NULL);
			vns = DOUBLE_TO_JSVAL(widthpct);
			JS_SetUCProperty(cx, newObject, L"widthpct", 8, &vns);
			vns = DOUBLE_TO_JSVAL(heightpct);
			JS_SetUCProperty(cx, newObject, L"heightpct", 9, &vns);

			vp.setObject( *newObject );
		}
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxAuiManager, AuiManager)
	switch (id) 
	{
	case P_FLAG:
		{
			int value = 0;
			if ( FromJS(cx, vp, value) )
				p->SetFlags(value);
		}
		break;
	case P_ManagedWindow:
		{
			wxWindow *pWnd = Window::GetPrivate(cx, vp);
			if( pWnd != NULL ) {
				p->SetManagedWindow( pWnd );
			}
		}
		break;
	case P_DockSizeConstraint:
		{
			double widthpct = 0,heightpct = 0;
			if( vp.isObject() == false ) {
				return JS_FALSE;
			}
			jsval ret;
			JSObject* pObj = vp.toObjectOrNull();
			if( JS_GetUCProperty(cx, pObj,
							L"widthpct", 8,
							 &ret) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( ret.isDouble() == false ) {
				return JS_FALSE;
			}
			widthpct = ret.toDouble();
			if( JS_GetUCProperty(cx, pObj,
							L"heightpct", 9,
							 &ret) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( ret.isDouble() == false ) {
				return JS_FALSE;
			}
			heightpct = ret.toDouble();

			
			p->SetDockSizeConstraint(widthpct, heightpct);

		}
		break;
	}
	return true;
WXJS_END_SET_PROP

WXJS_BEGIN_ADD_PROP(wxAuiManager, AuiManager)
	AuiManagerEventHandler::ConnectEvent(p, prop, true);
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxAuiManager, AuiManager)
  AuiManagerEventHandler::ConnectEvent(p, prop, false);
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
 *   Constructs a new wxAuiManager object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxAuiManager, AuiManager)

	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxWindow*	pParent = NULL;
	unsigned int flags	=	wxAUI_MGR_DEFAULT;


	if ( argc > 2 )
		argc = 2;

    switch(argc)
    {
    case 2:
        if ( ! FromJS(cx, argv[1], flags) )
        {
          JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
          return JS_FALSE;
        }
        // Walk through
    default:
        pParent = Window::GetPrivate(cx, argv[0]);
        if ( pParent == NULL )
        {
            JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
            return JS_FALSE;
        }
    }


	wxAuiManager *p = new wxAuiManager(pParent, flags);
	return p;
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxAuiManager, AuiManager)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(AuiManager)
    WXJS_METHOD("addPane", addPane, 2)
    WXJS_METHOD("update", update, 0)
	WXJS_METHOD("unInit", unInit, 0)
    WXJS_METHOD("detachPane", detachPane, 1)
    WXJS_METHOD("savePerspective", detachPane, 0)
    WXJS_METHOD("hideHint", hideHint, 0)
    WXJS_METHOD("insertPane", insertPane, 2)
    WXJS_METHOD("savePerspective", savePerspective, 0)
    WXJS_METHOD("savePerspective", savePerspective, 0)
	WXJS_METHOD("setManagedWindow", setManagedWindow, 1)
	WXJS_METHOD("getPane", getPane, 1)
WXJS_END_METHOD_MAP()

JSBool AuiManager::addPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	wxWindow* pWnd = Window::GetPrivate(cx, argv[0]);
	if( pWnd == NULL ) {
		return JS_FALSE;
	}

	wxAuiPaneInfo* pAui = AuiPaneInfo::GetPrivate(cx, argv[1]);
	if( pAui == NULL ) {
		return JS_FALSE;
	}
	*vp = ToJS(cx, p->AddPane(pWnd, *pAui) );

	return JS_TRUE;
}
JSBool AuiManager::update(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	p->Update();
//	*vp = ToJS(cx, p->Update() );

	return JS_TRUE;
}

JSBool AuiManager::unInit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	p->UnInit();
	return JS_TRUE;
}


JSBool AuiManager::detachPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	wxWindow* pWnd = Window::GetPrivate(cx, argv[0]);
	if( pWnd == NULL ) {
		return JS_FALSE;
	}

	*vp = ToJS(cx, p->DetachPane( pWnd ) );

	return JS_TRUE;
}
JSBool AuiManager::hideHint(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	p->HideHint();

	return JS_TRUE;
}
JSBool AuiManager::insertPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	if( argc > 3 ) {
		argc = 3;
	}

	int flag = wxAUI_INSERT_PANE;
	wxWindow* pWnd = Window::GetPrivate(cx, argv[0]);
	if( pWnd == NULL ) {
		return JS_FALSE;
	}
	wxAuiPaneInfo *pPaneInfo = AuiPaneInfo::GetPrivate(cx, argv[1]); 
	if( pPaneInfo == NULL ) {
		return JS_FALSE;
	}
	switch( argc ) {
	case 3:
        if ( ! FromJS(cx, argv[2], flag) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
        }

	}

	*vp = ToJS(cx, p->InsertPane( pWnd, *pPaneInfo, flag ) );

	return JS_TRUE;
}
JSBool AuiManager::savePerspective(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	p->SavePerspective();

	return JS_TRUE;
}
JSBool AuiManager::loadPerspective(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxAuiPaneInfo a;
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 2 ) {
		argc = 2;
	}

	wxString strPerspective(_T(""));
	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[1], strPerspective) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
        }
	default:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	if( p->LoadPerspective(strPerspective, bUpdate) == true ) {
		*vp = JSVAL_TRUE;
	} else {
		*vp = JSVAL_FALSE;
	}
	return JS_TRUE;
}
JSBool AuiManager::setManagedWindow(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxWindow* pWnd = Window::GetPrivate(cx, argv[0]);
	if( pWnd == NULL ) {
		return JS_FALSE;
	}
	p->SetManagedWindow(pWnd);

	return JS_TRUE;
}

JSBool AuiManager::getPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
    wxAuiManager *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argv[0].isString() ) {
		wxString str;		
        if ( ! FromJS(cx, argv[0], str) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
        }

		wxAuiPaneInfo& pneinf = p->GetPane(str);

		jsval r = AuiPaneInfo::CreateObject(cx, &pneinf, NULL);
		*vp = r;
	} 
	else 
	if( argv[0].isObject() ) {
		wxWindow* pWnd = Window::GetPrivate(cx, argv[0]);
		if( pWnd == NULL ) {
			return JS_FALSE;
		}
		wxAuiPaneInfo& pneinf = p->GetPane(pWnd);

		jsval r = AuiPaneInfo::CreateObject(cx, &pneinf, NULL);
		*vp = r;
	} else {
		JS_ReportError(cx, "argv 0 is data type error. String or Window");
		return JS_FALSE;
	}


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
WXJS_INIT_EVENT_MAP(wxAuiManager)
const wxString WXJS_EVT_AUI_PANE_BUTTON = wxT("onPaneClicked");
const wxString WXJS_EVT_AUI_PANE_CLOSE = wxT("onPaneClose");
const wxString WXJS_EVT_AUI_PANE_MAXIMIZE = wxT("onPaneMazimize");
const wxString WXJS_EVT_AUI_PANE_RESTORE = wxT("onPaneRestore");
const wxString WXJS_EVT_AUI_PANE_ACTIVATED = wxT("onPaneActivated");
const wxString WXJS_EVT_AUI_RENDER = wxT("onRender");
const wxString WXJS_EVT_AUI_FIND_MANAGER= wxT("onFindManager");

void AuiManagerEventHandler::OnClicked(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, WXJS_EVT_AUI_PANE_BUTTON);
}
void AuiManagerEventHandler::OnClose(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, 
		WXJS_EVT_AUI_PANE_CLOSE);
}
void AuiManagerEventHandler::OnMaximize(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, 
		WXJS_EVT_AUI_PANE_MAXIMIZE);
}
void AuiManagerEventHandler::OnRestore(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, 
		WXJS_EVT_AUI_PANE_RESTORE);
}
void AuiManagerEventHandler::OnActivated(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, 
		WXJS_EVT_AUI_PANE_ACTIVATED);
}
void AuiManagerEventHandler::OnRender(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, 
		WXJS_EVT_AUI_RENDER);
}
void AuiManagerEventHandler::OnFindManager(wxAuiManagerEvent &event)
{
	PrivAuiManagerEvent::Fire<AuiManagerEvent>(event, 
		WXJS_EVT_AUI_FIND_MANAGER);
}




void AuiManagerEventHandler::ConnectClicked(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_PANE_BUTTON, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnClicked));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_PANE_BUTTON, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnClicked));
	}
}
void AuiManagerEventHandler::ConnectClose(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_PANE_CLOSE, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnClose));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_PANE_CLOSE, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnClose));
	}
}
void AuiManagerEventHandler::ConnectMaximize(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_PANE_MAXIMIZE, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnMaximize));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_PANE_MAXIMIZE, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnMaximize));
	}
}
void AuiManagerEventHandler::ConnectRestore(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_PANE_RESTORE, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnRestore));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_PANE_RESTORE, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnRestore));
	}
}
void AuiManagerEventHandler::ConnectActivate(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_PANE_ACTIVATED, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnActivated));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_PANE_ACTIVATED, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnActivated));
	}
}
void AuiManagerEventHandler::ConnectRender(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_RENDER, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnRender));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_RENDER, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnRender));
	}
}
void AuiManagerEventHandler::ConnectFindManager(wxAuiManager *p, bool connect)
{
	if ( connect )
	{
		p->Connect(wxEVT_AUI_FIND_MANAGER, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnFindManager));
	}
	else
	{
		p->Disconnect(wxEVT_AUI_FIND_MANAGER, 
			wxAuiManagerEventHandler(AuiManagerEventHandler::OnFindManager));
	}
}

void AuiManagerEventHandler::InitConnectEventMap()
{
	AddConnector(WXJS_EVT_AUI_PANE_BUTTON, ConnectClicked);
	AddConnector(WXJS_EVT_AUI_PANE_CLOSE, ConnectClose);
	AddConnector(WXJS_EVT_AUI_PANE_MAXIMIZE, ConnectMaximize);
	AddConnector(WXJS_EVT_AUI_PANE_RESTORE, ConnectRestore);
	AddConnector(WXJS_EVT_AUI_PANE_ACTIVATED, ConnectActivate);
	AddConnector(WXJS_EVT_AUI_RENDER, ConnectRender);
	AddConnector(WXJS_EVT_AUI_FIND_MANAGER, ConnectFindManager);
}


