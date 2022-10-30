/*
 * wxJavaScript - init.cpp
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
 * $Id: init.cpp 644 2007-03-27 20:31:33Z fbraem $
 */
#include "precompile.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"

#include <jsapi.h>

#include "js/log/wxlog_init.h"
#include "js/log/wxlog.h"
#include "js/log/wxlogchain.h"
#include "js/log/wxlogtext.h"

using namespace zzzJs::log;




JSConstDoubleSpec wxLogLevelValuesMap[] = 
{
    WXJS_CONSTANT(wxLOG_, FatalError)
	WXJS_CONSTANT(wxLOG_, Error)
	WXJS_CONSTANT(wxLOG_, Warning)
	WXJS_CONSTANT(wxLOG_, Message)
	WXJS_CONSTANT(wxLOG_, Status)
	WXJS_CONSTANT(wxLOG_, Info)
	WXJS_CONSTANT(wxLOG_, Debug)
	WXJS_CONSTANT(wxLOG_, Trace)
	WXJS_CONSTANT(wxLOG_, Progress)
	WXJS_CONSTANT(wxLOG_, User)
	{ 0 }
};






bool zzzJs::log::InitClass(JSContext *cx, JSObject *global)
{
    JSObject *namespaceObj = JS_DefineObject(cx, global, "LogLevel", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	
	// Constant‚Ì’è‹`
	JS_DefineConstDoubles(cx, namespaceObj, wxLogLevelValuesMap);

	JSObject* obj = NULL;
	
	obj =Log::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Log prototype creation failed"));
	if (! obj )
		return false;
	
    obj =LogChain::define_Class(cx, global, Log::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Log prototype creation failed"));
	if (! obj )
		return false;

	obj =LogText::define_Class(cx, global, Log::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Log prototype creation failed"));
	if (! obj )
		return false;


    return true;
}

bool zzzJs::log::InitObject(JSContext *cx, JSObject *global)
{
    return true;
}

void zzzJs::log::Destroy()
{
}
