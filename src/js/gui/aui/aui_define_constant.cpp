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
#include <wx/aui/auibook.h>

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
#include "js/gui/aui/constant.h"



using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::aui;



JSConstDoubleSpec wxAuiManagerDockMap[] =
{
	WXJS_CONSTANT(wxAUI_DOCK_, NONE)
	WXJS_CONSTANT(wxAUI_DOCK_, TOP)
	WXJS_CONSTANT(wxAUI_DOCK_, RIGHT)
	WXJS_CONSTANT(wxAUI_DOCK_, BOTTOM)
	WXJS_CONSTANT(wxAUI_DOCK_, LEFT)
	WXJS_CONSTANT(wxAUI_DOCK_, CENTER)
	{ 0 }
};

JSConstDoubleSpec wxAuiManagerOptionMap[] =
{
	WXJS_CONSTANT(wxAUI_MGR_, ALLOW_FLOATING)
	WXJS_CONSTANT(wxAUI_MGR_, ALLOW_ACTIVE_PANE)
	WXJS_CONSTANT(wxAUI_MGR_, TRANSPARENT_DRAG)
	WXJS_CONSTANT(wxAUI_MGR_, TRANSPARENT_HINT)
	WXJS_CONSTANT(wxAUI_MGR_, VENETIAN_BLINDS_HINT)
	WXJS_CONSTANT(wxAUI_MGR_, RECTANGLE_HINT)
	WXJS_CONSTANT(wxAUI_MGR_, HINT_FADE)
	WXJS_CONSTANT(wxAUI_MGR_, NO_VENETIAN_BLINDS_FADE)
	WXJS_CONSTANT(wxAUI_MGR_, LIVE_RESIZE)
	WXJS_CONSTANT(wxAUI_MGR_, DEFAULT)
	{ 0 }
};

JSConstDoubleSpec wxAuiPaneDockArtSettingMap[] =
{
    WXJS_CONSTANT(wxAUI_DOCKART_, SASH_SIZE)
    WXJS_CONSTANT(wxAUI_DOCKART_, CAPTION_SIZE)
    WXJS_CONSTANT(wxAUI_DOCKART_, GRIPPER_SIZE)
    WXJS_CONSTANT(wxAUI_DOCKART_, PANE_BORDER_SIZE)
    WXJS_CONSTANT(wxAUI_DOCKART_, PANE_BUTTON_SIZE)
    WXJS_CONSTANT(wxAUI_DOCKART_, BACKGROUND_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, SASH_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, ACTIVE_CAPTION_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, ACTIVE_CAPTION_GRADIENT_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, INACTIVE_CAPTION_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, INACTIVE_CAPTION_GRADIENT_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, ACTIVE_CAPTION_TEXT_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, INACTIVE_CAPTION_TEXT_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, BORDER_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, GRIPPER_COLOUR)
    WXJS_CONSTANT(wxAUI_DOCKART_, CAPTION_FONT)
    WXJS_CONSTANT(wxAUI_DOCKART_, GRADIENT_TYPE)
	{ 0 }
};

JSConstDoubleSpec wxAuiPaneDockArtGradientsMap[] =
{
    WXJS_CONSTANT(wxAUI_GRADIENT_, NONE)
	WXJS_CONSTANT(wxAUI_GRADIENT_, VERTICAL)
	WXJS_CONSTANT(wxAUI_GRADIENT_, HORIZONTAL)
	{ 0 }
};

JSConstDoubleSpec wxAuiPaneButtonStateMap[] =
{
    WXJS_CONSTANT(wxAUI_BUTTON_STATE_, NORMAL)
	WXJS_CONSTANT(wxAUI_BUTTON_STATE_, HOVER)
	WXJS_CONSTANT(wxAUI_BUTTON_STATE_, PRESSED)
	WXJS_CONSTANT(wxAUI_BUTTON_STATE_, DISABLED)
	WXJS_CONSTANT(wxAUI_BUTTON_STATE_, HIDDEN)
	WXJS_CONSTANT(wxAUI_BUTTON_STATE_, CHECKED)
	{ 0 }
};

JSConstDoubleSpec wxAuiButtonIdMap[] =
{
    WXJS_CONSTANT(wxAUI_BUTTON_, CLOSE)
    WXJS_CONSTANT(wxAUI_BUTTON_, MAXIMIZE_RESTORE)
    WXJS_CONSTANT(wxAUI_BUTTON_, MINIMIZE)
    WXJS_CONSTANT(wxAUI_BUTTON_, PIN)
    WXJS_CONSTANT(wxAUI_BUTTON_, OPTIONS)
    WXJS_CONSTANT(wxAUI_BUTTON_, WINDOWLIST)
    WXJS_CONSTANT(wxAUI_BUTTON_, LEFT)
    WXJS_CONSTANT(wxAUI_BUTTON_, RIGHT)
    WXJS_CONSTANT(wxAUI_BUTTON_, UP)
    WXJS_CONSTANT(wxAUI_BUTTON_, DOWN)
    WXJS_CONSTANT(wxAUI_BUTTON_, CUSTOM1)
    WXJS_CONSTANT(wxAUI_BUTTON_, CUSTOM2)
    WXJS_CONSTANT(wxAUI_BUTTON_, CUSTOM3)
	{ 0 }
};



JSConstDoubleSpec wxAuiPaneInsertLevelMap[] =
{
    WXJS_CONSTANT(wxAUI_INSERT_, PANE)
	WXJS_CONSTANT(wxAUI_INSERT_, ROW)
	WXJS_CONSTANT(wxAUI_INSERT_, DOCK)
	{ 0 }
};

JSConstDoubleSpec wxAuiNotebookOptionMap[] =
{
    WXJS_CONSTANT(wxAUI_NB_, TOP)
    WXJS_CONSTANT(wxAUI_NB_, LEFT)
    WXJS_CONSTANT(wxAUI_NB_, RIGHT)
    WXJS_CONSTANT(wxAUI_NB_, BOTTOM)
    WXJS_CONSTANT(wxAUI_NB_, TAB_SPLIT)
    WXJS_CONSTANT(wxAUI_NB_, TAB_MOVE)
    WXJS_CONSTANT(wxAUI_NB_, TAB_EXTERNAL_MOVE)
    WXJS_CONSTANT(wxAUI_NB_, TAB_FIXED_WIDTH)
    WXJS_CONSTANT(wxAUI_NB_, SCROLL_BUTTONS)
    WXJS_CONSTANT(wxAUI_NB_, WINDOWLIST_BUTTON)
    WXJS_CONSTANT(wxAUI_NB_, CLOSE_BUTTON)
    WXJS_CONSTANT(wxAUI_NB_, CLOSE_ON_ACTIVE_TAB)
    WXJS_CONSTANT(wxAUI_NB_, CLOSE_ON_ALL_TABS)
    WXJS_CONSTANT(wxAUI_NB_, MIDDLE_CLICK_CLOSE)
    WXJS_CONSTANT(wxAUI_NB_, DEFAULT_STYLE)

	{ 0 }
};

void zzzJs::gui::aui::InitAuiConstants(JSContext *cx, JSObject *obj)
{
	
	JSObject *constObj = JS_DefineObject(cx, obj, "ManagerDock", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiManagerDockMap);



	constObj = JS_DefineObject(cx, obj, "ManagerOption", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiManagerOptionMap);



	constObj = JS_DefineObject(cx, obj, "PaneDockArtSetting", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiPaneDockArtSettingMap);



	constObj = JS_DefineObject(cx, obj, "PaneDockArtGradients", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiPaneDockArtGradientsMap);



	constObj = JS_DefineObject(cx, obj, "PaneButtonState", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiPaneButtonStateMap);



	constObj = JS_DefineObject(cx, obj, "ButtonId", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiButtonIdMap);



	constObj = JS_DefineObject(cx, obj, "PaneInsertLevel", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiPaneInsertLevelMap);



	constObj = JS_DefineObject(cx, obj, "NotebookOption", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxAuiNotebookOptionMap);







}


