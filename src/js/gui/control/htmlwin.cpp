/*
 * wxJavaScript - htmlwin.cpp
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
 * $Id: htmlwin.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 




#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/filename.h>

/***
 * <file>control/htmlwin</file>
 * <module>gui</module>
 * <class name="wxHtmlWindow" prototype="@wxScrolledWindow">
 *  The purpose of this class is to display HTML pages (either local file or downloaded via HTTP protocol) 
 *  in a window. The width of the window is constant - given in the constructor - and virtual height is changed 
 *  dynamically depending on page size.
 * </class>
 */

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"

#include "js/gui/event/jsevent.h"
#include "js/gui/event/htmllink.h"

#include "js/gui/misc/size.h"
#include "js/gui/control/htmlwin.h"
#include "js/gui/control/frame.h"
#include "js/gui/control/window.h"
#include "js/gui/control/scrollwnd.h"

#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

WXJS_INIT_CLASS(HtmlWindow, "HtmlWindow", 0)

void HtmlWindow::InitClass(JSContext* WXUNUSED(cx),
                           JSObject* WXUNUSED(obj),
                           JSObject* WXUNUSED(proto))
{
    HtmlLinkEventHandler::InitConnectEventMap();
}

/***
 * <constants>
 *	<type name="styles">
 *   <constant name="SCROLLBAR_NEVER">
 *    Never display scrollbars, not even when the page is larger 
 *    than the window.</constant>
 *   <constant name="SCROLLBAR_AUTO">
 *    Display scrollbars only if page's size exceeds window's size.
 *   </constant>
 *   <constant name="NO_SELECTION">
 *    Don't allow the user to select text.
 *   </constant>
 *   <constant name="DEFAULT_STYLE" />
 *  </type>
 * </constants>
 */

WXJS_BEGIN_CONSTANT_MAP(HtmlWindow)
  WXJS_CONSTANT(wxHW_, SCROLLBAR_NEVER)
  WXJS_CONSTANT(wxHW_, SCROLLBAR_AUTO)
  WXJS_CONSTANT(wxHW_, NO_SELECTION)
  WXJS_CONSTANT(wxHW_, DEFAULT_STYLE)
WXJS_END_CONSTANT_MAP()

/***
 * <properties>
 *  <property name="historyCanBack" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns true if it is possible to go back in the history 
 *   (i.e. @wxHtmlWindow#historyBack won't fail).
 *  </property>
 *  <property name="historyCanForward" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns true if it is possible to go forward in the history 
 *   (i.e. @wxHtmlWindow#historyForward won't fail).
 *  </property>
 *  <property name="openedAnchor" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns anchor within currently opened page (see @wxHtmlWindow#openedPage). 
 *   If no page is opened or if the displayed page wasn't produced by call to 
 *   @wxHtmlWindow#loadPage, empty string is returned.
 *  </property>
 *  <property name="openedPage" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns full location of the opened page. If no page is opened or if the 
 *   displayed page wasn't produced by call to @wxHtmlWindow#loadPage, empty 
 *   string is returned. 
 *  </property>
 *  <property name="openedPageTitle" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns title of the opened page or wxEmptyString if current page does
*    not contain &lt;title&gt; tag.
 *  </property>
 *  <property name="relatedFrame" type="@wxFrame">
 *   Gets/Sets the frame in which page title will be displayed.
 *  </property>
 *  <property name="text" type=WXJS_TYPE_STRING>
 *   Returns content of currently displayed page as plain text.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(HtmlWindow)
    WXJS_READONLY_PROPERTY(P_HISTORY_CAN_BACK, "historyCanBack")
    WXJS_READONLY_PROPERTY(P_HISTORY_CAN_FORWARD, "historyCanForward")
    WXJS_READONLY_PROPERTY(P_OPENED_ANCHOR, "openedAnchor")
    WXJS_READONLY_PROPERTY(P_OPENED_PAGE, "openedPage")
    WXJS_READONLY_PROPERTY(P_OPENED_PAGE_TITLE, "openedPageTitle")
    WXJS_PROPERTY(P_RELATED_FRAME, "relatedFrame")
    WXJS_READONLY_PROPERTY(P_TEXT, "text")
    WXJS_READONLY_PROPERTY(P_SELECTION_TEXT, "selectionText")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxHtmlWindow, HtmlWindow)
    switch (id) 
	{
    case P_HISTORY_CAN_BACK:
        ToJSVal(cx, vp,  p->HistoryCanBack());
        break;
    case P_HISTORY_CAN_FORWARD:
        ToJSVal(cx, vp,  p->HistoryCanForward());
        break;
    case P_OPENED_ANCHOR:
        ToJSVal(cx, vp,  p->GetOpenedAnchor());
        break;
    case P_OPENED_PAGE:
        ToJSVal(cx, vp,  p->GetOpenedPage());
        break;
    case P_OPENED_PAGE_TITLE:
        ToJSVal(cx, vp,  p->GetOpenedPageTitle());
        break;
    case P_RELATED_FRAME:
        vp.set( Frame::CreateObject(cx, (wxFrame*)p->GetRelatedFrame(), NULL) );
        break;
    case P_TEXT:
        ToJSVal(cx, vp,  p->ToText());
        break;
    case P_SELECTION_TEXT:
        ToJSVal(cx, vp,  p->SelectionToText());
        break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxHtmlWindow, HtmlWindow)
    switch (id) 
	{
	case P_RELATED_FRAME:
		{
            wxFrame *frame = Frame::GetPrivate(cx, vp);
			if ( frame != NULL )
				p->SetRelatedFrame(frame, wxT("%s"));
			break;
		}
	}
    return true;
WXJS_END_SET_PROP


WXJS_BEGIN_ADD_PROP(wxHtmlWindow, HtmlWindow)
    if ( ! WindowEventHandler::ConnectEvent(p, prop, true) )
    {
        HtmlLinkEventHandler::ConnectEvent(p, prop, true);
    }
    return true;
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxHtmlWindow, HtmlWindow)
    if ( ! WindowEventHandler::ConnectEvent(p, prop, false) )
    {
        HtmlLinkEventHandler::ConnectEvent(p, prop, false);
    }
    return true;
WXJS_END_DEL_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxHtmlWindow, HtmlWindow)
	ScrolledWindow::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxHtmlWindow.DEFAULT_STYLE">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxHtmlWindow object. See also @wxHtmlWindow#create.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxHtmlWindow, HtmlWindow)

    wxHtmlWindow *p = new wxHtmlWindow();

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
	
WXJS_BEGIN_DESTRUCTOR(wxHtmlWindow, HtmlWindow)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(HtmlWindow)
    WXJS_METHOD("create", create, 1)
    WXJS_METHOD("appendToPage", appendToPage, 1)
    WXJS_METHOD("historyBack", historyBack, 0)
    WXJS_METHOD("historyClear", historyClear, 0)
    WXJS_METHOD("historyBack", historyBack, 0)
    WXJS_METHOD("historyBack", historyBack, 0)
    WXJS_METHOD("loadFile", loadFile, 1)
    WXJS_METHOD("loadPage", loadPage, 1)
    WXJS_METHOD("setPage", setPage, 1)
    WXJS_METHOD("setRelatedFrame", setRelatedFrame, 2)
    WXJS_METHOD("setRelatedStatusBar", setRelatedStatusBar, 0)
    WXJS_METHOD("selectAll", selectAll, 0)
    WXJS_METHOD("selectLine", selectWord, 1)
    WXJS_METHOD("selectWord", selectWord, 1)
    WXJS_METHOD("setBorders", setBorders, 1)
    WXJS_METHOD("setFonts", setFonts, 2)
WXJS_END_METHOD_MAP()

//TODO: AddFilter

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxHtmlWindow.DEFAULT_STYLE">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Creates an HTML window.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool HtmlWindow::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxHtmlWindow *p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = wxHW_DEFAULT_STYLE;
	int id = -1;
	
	ZZZJS_CHECK_ARG_COUNT(1, 5);

	switch(argc)
	{
	case 5:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 4:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 3:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	case 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex--;
	default:
		wxWindow *parent = NULL;
		
		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		argIndex++;
		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}


		JavaScriptClientData *clntParent =
			dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, *(apPoint.get()), *(apSize.get()), style) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}

	return JS_TRUE;
}

/***
 * <method name="appendToPage">
 *  <function returns="Boolean">
 *   <arg name="Source" type=WXJS_TYPE_STRING>HTML fragment</arg>
 *  </function>
 *  <desc>
 *   Appends HTML fragment to currently displayed text and refreshes the window.
 *   False is returned on failure.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::appendToPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxString html;
    FromJS(cx, argv[0], html);
    *vp = ToJS(cx, p->AppendToPage(html));
	return JS_TRUE;
}

/***
 * <method name="historyBack">
 *  <function returns="Boolean" />
 *  <desc>
 *   Moves back to the previous page. (each page displayed using 
 *   @wxHtmlWindow#loadPage is stored in history list.)
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::historyBack(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    *vp = ToJS(cx, p->HistoryBack());
	return JS_TRUE;
}

/***
 * <method name="historyClear">
 *  <function />
 *  <desc>
 *   Clears the history.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::historyClear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    p->HistoryClear();
	return JS_TRUE;
}

/***
 * <method name="historyForward">
 *  <function returns="Boolean" />
 *  <desc>
 *   Moves forward to the next page. (each page displayed using
 *   @wxHtmlWindow#loadPage is stored in history list.)
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::historyForward(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    *vp = ToJS(cx, p->HistoryForward());
	return JS_TRUE;
}

/***
 * <method name="loadFile">
 *  <function returns="Boolean">
 *   <arg name="filename" type="@wxFileName">The file to load</arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="filename" type=WXJS_TYPE_STRING>The file to load</arg>
 *  </function>
 *  <desc>
 *   Loads HTML page from file and displays it. Returns false on failure.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::loadFile(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	if ( argv[0].isObject() )
    {
        JSClass *clazz = zzzJs::GetClass(cx, obj, "wxFileName");
        if ( clazz != NULL )
        {
            wxFileName *filename = (wxFileName *) JS_GetInstancePrivate(cx, JSVAL_TO_OBJECT(argv[0]), clazz, NULL);
            if ( filename != NULL )
            {
                *vp = ToJS(cx, p->LoadFile(*filename));
                return JS_TRUE;
            }
        }
    }

    wxString filename;
    FromJS(cx, argv[0], filename);
    *vp = ToJS(cx, p->LoadFile(filename));

    return JS_TRUE;
}

/***
 * <method name="loadPage">
 *  <function returns="Boolean">
 *   <arg name="Location" type=WXJS_TYPE_STRING>The address of document</arg>
 *  </function>
 *  <desc>
 *   Unlike @wxHtmlWindow#setPage this function first loads HTML page
 *   from location and then displays it.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::loadPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxString location;
    FromJS(cx, argv[0], location);
    *vp = ToJS(cx, p->LoadPage(location));

    return JS_TRUE;
}

//TODO: readCustomization

/***
 * <method name="selectAll">
 *  <function />
 *  <desc>
 *   Selects all text in the window.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::selectAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    p->SelectAll();

    return JS_TRUE;
}

/***
 * <method name="selectLine">
 *  <function>
 *   <arg name="Pos" type="@wxPoint" />
 *  </function>
 *  <desc>
 *   Selects the line of text that pos points at. Note that pos is relative to
 *   the top of displayed page, 
 *   not to window's origin, use @wxScrolledWindow#calcUnscrolledPosition to 
 *   convert physical coordinate. 
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::selectLine(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	
	ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
	argIndex++;


	p->SelectLine(*(apPoint.get()));

	return JS_TRUE;
}

/***
 * <method name="selectWord">
 *  <function>
 *   <arg name="Pos" type="@wxPoint" />
 *  </function>
 *  <desc>
 *   Selects the word at position pos. Note that pos is relative to the 
 *   top of displayed page,
 *   not to window's origin, use @wxScrolledWindow#calcUnscrolledPosition 
 *   to convert physical coordinate.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::selectWord(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	
	ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
	argIndex++;


	p->SelectWord(*(apPoint.get()));

    return JS_TRUE;
}

/***
 * <method name="setBorders">
 *  <function>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   This function sets the space between border of window and HTML contents.
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::setBorders(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    int border;
    if ( FromJS(cx, argv[0], border) )
    {
        p->SetBorders(border);
    }
    return JS_TRUE;
}

/***
 * <method name="setFonts">
 *  <function>
 *   <arg name="NormalFace" type=WXJS_TYPE_STRING>
 *    This is face name for normal (i.e. non-fixed) font. It can be either
 *    empty string (then the default face is chosen) or platform-specific face
 *    name. Examples are "helvetica" under Unix or "Times New Roman" under 
 *    Windows.
 *   </arg>
 *   <arg name="FixedFace" type=WXJS_TYPE_STRING>
 *    The same thing for fixed face
 *   </arg>
 *   <arg name="Sizes" type="Array" default="null">
 *    This is an array of 7 items of Integer type. The values represent size 
 *    of font with HTML size from -2 to +4 ( &lt;FONT SIZE=-2&gt; to 
 *    &lt;FONT SIZE=+4&gt; ). Default sizes are used if sizes is null.
 *   </arg>
 *  </function>
 *  <desc>
 *   This function sets font sizes and faces
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::setFonts(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxString normalFace;
    wxString fixedFace;
    int *sizes = NULL;
    if (    argc > 2 
		&& argv[2].isObject() )
    {
        JSObject *objArr = JSVAL_TO_OBJECT(argv[2]);
        if ( JS_IsArrayObject(cx, objArr) )
        {
			uint32_t length = 0;
		    JS_GetArrayLength(cx, objArr, &length);
		    sizes = new int[length];
		    for(uint32_t i =0; i < length; i++)
		    {
			    jsval element;
			    JS_GetElement(cx, objArr, i, &element);
                FromJS(cx, element, sizes[i]);
		    }
        }
    }
    
    p->SetFonts(normalFace, fixedFace, sizes);
    delete[] sizes;

    return JS_TRUE;
}

/***
 * <method name="setPage">
 *  <function returns="Boolean">
 *   <arg name="Source" type=WXJS_TYPE_STRING>The HTML source</arg>
 *  </function>
 *  <desc>
 *   Sets HTML page and display it. This won't load the page!! 
 *   It will display the source
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::setPage(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxString source;
    FromJS(cx, argv[0], source);
    *vp = ToJS(cx, p->SetPage(source));

    return JS_TRUE;
}

/***
 * <method name="setRelatedFrame">
 *  <function>
 *   <arg name="Frame" type="@wxFrame" />
 *   <arg name="Format" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Sets the frame in which page title will be displayed. 
 *   format is format of frame title, e.g. "HtmlHelp : %s". 
 *   It must contain exactly one %s. This %s is substituted with HTML page title. 
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::setRelatedFrame(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxFrame *frame = Frame::GetPrivate(cx, argv[0]);
    if ( frame == NULL )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "wxFrame");
        return JS_FALSE;
    }

    wxString format;
    FromJS(cx, argv[1], format);
    p->SetRelatedFrame(frame, format);

    return JS_TRUE;
}

/***
 * <method name="setRelatedStatusBar">
 *  <function>
 *   <arg name="Bar" type=WXJS_TYPE_NUMBER default="-1" />
 *  </function>
 *  <desc>
 *   After calling @wxHtmlWindow#setRelatedFrame, this sets statusbar slot 
 *   where messages will be displayed. (Default is -1 = no messages.)
 *  </desc>
 * </method>
 */
JSBool HtmlWindow::setRelatedStatusBar(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxHtmlWindow *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    int bar = -1; 
    if ( argc > 0 )
        FromJS(cx, argv[0], bar);
    p->SetRelatedStatusBar(bar);

    return JS_TRUE;
}

//TODO: WriteCustomization

WXJS_INIT_EVENT_MAP(wxHtmlWindow)
const wxString WXJS_HTMLLINK_EVENT = wxT("onLinkClicked");

/***
 * <events>
 *  <event name="onLinkClicked">
 *   This event is triggered when a hyperlinck is clicked. The function receives
 *   a @wxHtmlLinkEvent as argument.
 *  </event>
 * </events>
 */
void HtmlLinkEventHandler::OnLinkClicked(wxHtmlLinkEvent &event)
{
    // The event object must be set here, because wxHtmlLinkEvent
    // is created when a wxCommandEvent is handled, and it doesn't copy
    // this data yet (this will be solved in 2.8.4)
    event.SetEventObject(this);
    PrivHtmlLinkEvent::Fire<HtmlLinkEvent>(event, WXJS_HTMLLINK_EVENT);
}

void HtmlLinkEventHandler::ConnectLinkClicked(wxHtmlWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_COMMAND_HTML_LINK_CLICKED, 
               wxHtmlLinkEventHandler(HtmlLinkEventHandler::OnLinkClicked));
  }
  else
  {
    p->Disconnect(wxEVT_COMMAND_HTML_LINK_CLICKED, 
                  wxHtmlLinkEventHandler(HtmlLinkEventHandler::OnLinkClicked));
  }
}

void HtmlLinkEventHandler::InitConnectEventMap()
{
    AddConnector(WXJS_HTMLLINK_EVENT, ConnectLinkClicked);
}
