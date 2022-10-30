/*
 * wxJavaScript - init.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
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
 * $Id$
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
// main.cpp
#include <wx/setup.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/intl.h>

#if defined(__WXMSW__)
	#include <wx/msw/private.h>
#endif
#include <wx/calctrl.h>

#if defined(__WXMSW__)
    #include <wx/msw/ole/automtn.h>
#endif

#include <jsapi.h>
#include "js/common/jsutil.h"
#include "js/common/index.h"
 
// All wxJS objects
#include "js/gui/event/jsevent.h"
#include "js/gui/event/event.h"
#include "js/gui/event/notify.h"

// DataView
#include "js/gui/dataview/dataviewevent.h"

#include "js/gui/dataview/zzzjs_gui_dataview_init.h"

using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;

bool zzzJs::gui::dataview::InitClass(JSContext *cx, JSObject *global)
{
    //InitGuiConstants(cx, global);

    JSObject *obj = NULL;


	// DataViewEvent - parent is NotifyEvent
	obj = DataViewEvent::define_Class(cx, global, NotifyEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewEvent prototype creation failed"));
	if (! obj )
		return false;





    // Initialize wxJS JavaScript objects

 //   // Define the global functions
	//InitFunctions(cx, global);

	//DefineGlobals(cx, global);

	return true;
}


bool zzzJs::gui::dataview::InitObject(JSContext *cx, JSObject *obj)
{
  return true;
}

void zzzJs::gui::dataview::Destroy()
{
}
