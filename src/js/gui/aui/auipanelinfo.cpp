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
#include "js/gui/aui/auipanelinfo.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::aui;

WXJS_INIT_CLASS(AuiPaneInfo, "PaneInfo", 0)
	
/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(AuiPaneInfo)
  WXJS_PROPERTY(P_FLAG, "flags")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxAuiPaneInfo, AuiPaneInfo)
	switch (id) 
	{
	case P_FLAG:
//		ToJSVal(cx, vp, p->GetFlags());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxAuiPaneInfo, AuiPaneInfo)
	switch (id) 
	{
	case P_FLAG:
		//{
		//	int value = 0;
		//	if ( FromJS(cx, vp, value) )
		//		p->SetFlags(value);
		//}
		break;
	}
	return true;
WXJS_END_SET_PROP


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
 *   Constructs a new wxAuiPaneInfo object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxAuiPaneInfo, AuiPaneInfo)
	wxAuiPaneInfo *p = new wxAuiPaneInfo();
	return p;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxAuiPaneInfo, AuiPaneInfo)

WXJS_END_DESTRUCTOR



WXJS_BEGIN_METHOD_MAP(AuiPaneInfo)
    WXJS_METHOD("bottom", bottom, 0)
    WXJS_METHOD("bottomDockable", bottomDockable, 0)
    WXJS_METHOD("caption", caption, 1)
	WXJS_METHOD("captionVisible", captionVisible, 0)
	WXJS_METHOD("closeButton", closeButton, 0)
	WXJS_METHOD("defaultPane", defaultPane, 0)
	WXJS_METHOD("destroyOnClose", destroyOnClose, 0)
	WXJS_METHOD("direction", direction, 1)
	WXJS_METHOD("dock", dock, 0)
	WXJS_METHOD("dockable", dockable, 0)
	WXJS_METHOD("dockable", fixed, 0)
	WXJS_METHOD("float", float_fn, 0)
	WXJS_METHOD("floatable", floatable, 0)
	WXJS_METHOD("gripperTop", gripperTop, 0)
	WXJS_METHOD("hasBorder", hasBorder, 0)
	WXJS_METHOD("hasCaption", hasCaption, 0)
	WXJS_METHOD("hasCloseButton", hasCloseButton, 0)
	WXJS_METHOD("hasFlag", hasFlag, 1)
	WXJS_METHOD("hasGripper", hasGripper, 0)
	WXJS_METHOD("hasGripperTop", hasGripperTop, 0)
	WXJS_METHOD("hasMaximizeButton", hasMaximizeButton, 0)
	WXJS_METHOD("hasMaximizeButton", hasMinimizeButton, 0)
	WXJS_METHOD("hasPinButton", hasPinButton, 0)
	WXJS_METHOD("hide", hide, 0)
	WXJS_METHOD("icon", icon, 1)
	WXJS_METHOD("isBottomDockable", isBottomDockable, 0)
	WXJS_METHOD("isDockable", isDockable, 0)
	WXJS_METHOD("isDocked", isDocked, 0)
	WXJS_METHOD("isFixed", isFixed, 0)
	WXJS_METHOD("isFloatable", isFloatable, 0)
	WXJS_METHOD("isFloating", isFloating, 0)
	WXJS_METHOD("isLeftDockable", isLeftDockable, 0)
	WXJS_METHOD("isLeftDockable", isLeftDockable, 0)
	WXJS_METHOD("isMovable", isMovable, 0)
	WXJS_METHOD("isOk", isOk, 0)
	WXJS_METHOD("isResizable", isResizable, 0)
	WXJS_METHOD("isRightDockable", isRightDockable, 0)
	WXJS_METHOD("isShown", isShown, 0)
	WXJS_METHOD("isToolbar", isToolbar, 0)
	WXJS_METHOD("isTopDockable", isTopDockable, 0)
	WXJS_METHOD("layer", layer, 0)
	WXJS_METHOD("left", left, 0)
	WXJS_METHOD("leftDockable", leftDockable, 0)
	WXJS_METHOD("maximizeButton", maximizeButton, 0)
	WXJS_METHOD("minimizeButton", minimizeButton, 0)
	WXJS_METHOD("maximize", maximize, 0)
	WXJS_METHOD("movable", movable, 0)
	WXJS_METHOD("name", name, 1)
	WXJS_METHOD("paneBorder", paneBorder, 0)
	WXJS_METHOD("pinButton", pinButton, 0)
	WXJS_METHOD("position", position, 1)
	WXJS_METHOD("resizable", resizable, 0)
	WXJS_METHOD("right", right, 0)
	WXJS_METHOD("rightDockable", rightDockable, 0)
	WXJS_METHOD("row", row, 0)
	WXJS_METHOD("setFlag", setFlag, 2)
	WXJS_METHOD("show", show, 0)
	WXJS_METHOD("toolbarPane", toolbarPane, 0)
	WXJS_METHOD("top", top, 0)
	WXJS_METHOD("topDockable", topDockable, 0)
	WXJS_METHOD("window", window, 1)
	WXJS_METHOD("bestSize", bestSize, 2)
	WXJS_METHOD("centre", centre, 0)
	WXJS_METHOD("center", center, 0)
	WXJS_METHOD("centrePane", centrePane, 0)
	WXJS_METHOD("centerPane", centerPane, 0)
	WXJS_METHOD("floatingPosition", floatingPosition, 2)
	WXJS_METHOD("floatingSize", floatingSize, 2)
	WXJS_METHOD("maxSize", maxSize, 2)
	WXJS_METHOD("minSize", minSize, 2)
WXJS_END_METHOD_MAP()

JSBool AuiPaneInfo::bottom(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);


	if( p == NULL ) {
		return JS_FALSE;
	}

	p->Bottom();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::bottomDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->BottomDockable(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::caption(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	wxString strValue;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], strValue) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_STRING);
			return JS_FALSE;
        }
	}
	
	p->Caption(strValue);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::captionVisible(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->CaptionVisible(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::closeButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->CloseButton(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::defaultPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	p->DefaultPane();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::destroyOnClose(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->DestroyOnClose(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::direction(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	int value = 0;
    if ( ! FromJS(cx, argv[0], value) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
	p->Direction(value);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::dock(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	p->Dock();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}
JSBool AuiPaneInfo::dockFixed(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->DockFixed(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::dockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->Dockable(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::fixed(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	p->Fixed();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::float_fn(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	p->Float();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::floatable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->Floatable(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::gripper(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->Gripper(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::gripperTop(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}


	bool bUpdate = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], bUpdate) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}
	
	p->GripperTop(bUpdate);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasBorder(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	vp->setBoolean( 
		p->HasBorder()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasCaption(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasCaption()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasCloseButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasCloseButton()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	int val = 0;
    if ( ! FromJS(cx, argv[0], val) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }	
	
	vp->setBoolean( 
		p->HasFlag (val)
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasGripper(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasGripper()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasGripperTop(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasGripperTop()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasMaximizeButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasMaximizeButton()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasMinimizeButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasMinimizeButton()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hasPinButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->HasPinButton()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::hide(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	//if( argc > 1 ) {
	//	argc = 1;
	//}


	//bool bUpdate = true;
	//switch( argc ) {
	//case 1:
 //       if ( ! FromJS(cx, argv[0], bUpdate) )
 //       {
	//		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
	//		return JS_FALSE;
 //       }
	//}
	
	p->Hide();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::icon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	zzzJsPtr<wxBitmap> apBitmap;
	if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[0], apBitmap.bAllocation)) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bitmap");
		return JS_FALSE;
	}

	p->Icon(*(apBitmap.get()));
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::isBottomDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsBottomDockable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsDocked()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isDocked(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsDocked()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isFixed(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsFixed()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isFloatable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsFloatable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isFloating(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsFloating()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isLeftDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsLeftDockable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isMovable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsMovable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isOk(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsOk()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isResizable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsResizable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isRightDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsRightDockable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isShown(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsShown()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isToolbar(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsToolbar()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::isTopDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	
	
	vp->setBoolean( 
		p->IsTopDockable()
	);
	return JS_TRUE;
}

JSBool AuiPaneInfo::layer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	int val = 0;
    if ( ! FromJS(cx, argv[0], val) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
	
	p->Layer(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::left(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	
	p->Left();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::leftDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->LeftDockable(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::maximizeButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->MaximizeButton(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::minimizeButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->MinimizeButton(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::maximize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	p->Maximize();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::movable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->Movable(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::name(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	wxString val;
	//switch( argc ) {
	//case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_STRING);
			return JS_FALSE;
        }
	//}

	
	p->Name(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::paneBorder(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->PaneBorder(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::pinButton(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->PinButton(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::position(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	int val = 0;
	//switch( argc ) {
	//case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	//}

	
	p->Position(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::resizable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->Resizable(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::right(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
		
	p->Right();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::rightDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->RightDockable(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::row(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	int val = 0;
    if ( ! FromJS(cx, argv[0], val) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	
	p->Row(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::setFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 2 ) {
		argc = 2;
	}
	
	int flag = 0;
	bool opt = 0;
    if ( ! FromJS(cx, argv[0], flag) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], opt) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
		return JS_FALSE;
    }

	
	p->SetFlag(flag, opt);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::show(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->Show(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::toolbarPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	
	p->ToolbarPane();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::top(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}


	
	p->Top();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::topDockable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	if( argc > 1 ) {
		argc = 1;
	}
	
	bool val = true;
	switch( argc ) {
	case 1:
        if ( ! FromJS(cx, argv[0], val) )
        {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Bool");
			return JS_FALSE;
        }
	}

	
	p->TopDockable(val);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::window(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}

	wxWindow *pWindow = Window::GetPrivate(cx, argv[0]);
	if( pWindow == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, "Window");
		return JS_FALSE;
	}

	
	p->Window(pWindow);
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::bestSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int x = 0;
	int y = 0;
    if ( ! FromJS(cx, argv[0], x) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], y) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	
	p->BestSize( x, y );
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::centre(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	p->Centre();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::center(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	p->Center();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::centrePane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	p->CentrePane();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::centerPane(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	p->CenterPane();
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::floatingPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int x = 0;
	int y = 0;
    if ( ! FromJS(cx, argv[0], x) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], y) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	
	p->FloatingPosition( x, y );
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::floatingSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int x = 0;
	int y = 0;
    if ( ! FromJS(cx, argv[0], x) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], y) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	
	p->FloatingSize( x, y );
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::maxSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int x = 0;
	int y = 0;
    if ( ! FromJS(cx, argv[0], x) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], y) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	
	p->MaxSize( x, y );
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}

JSBool AuiPaneInfo::minSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxAuiPaneInfo *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	int x = 0;
	int y = 0;
    if ( ! FromJS(cx, argv[0], x) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }
    if ( ! FromJS(cx, argv[1], y) )
    {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 0, WXJS_TYPE_NUMBER);
		return JS_FALSE;
    }

	
	p->MinSize( x, y );
	vp->setObjectOrNull( obj );
	return JS_TRUE;
}








