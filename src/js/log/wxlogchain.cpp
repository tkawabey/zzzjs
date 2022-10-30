/*
 * wxJavaScript - dir.cpp
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
 * $Id: dir.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// wxJSDir.cpp
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
#include "js/log/wxlogchain.h"
#include "js/log/wxlog.h"
#include "js/gui/errors.h"
#include "js/common/jsutil.h"


using namespace zzzJs;
using namespace zzzJs::log;

WXJS_INIT_CLASS(LogChain, "LogChain", 1)
	
WXJS_BEGIN_PROPERTY_MAP(LogChain)
  WXJS_READONLY_PROPERTY(P_OLD_LOG, "oldLog")
  WXJS_READONLY_PROPERTY(p_IS_PASSING_MSG, "isPassingMessages")
WXJS_END_PROPERTY_MAP()



WXJS_BEGIN_GET_PROP(wxLogChain, LogChain)
	switch (id) 
	{
	case P_OLD_LOG:
		{
			wxLog* pOldLog = p->GetOldLog();
			if( pOldLog != NULL ) {
				vp.set( Log::CreateObject( cx, pOldLog) );
			} else {
				vp.setNull();
			}
		}
		break;
	case p_IS_PASSING_MSG:
		ToJSVal(cx, vp, p->IsPassingMessages());
		break;
	}
    return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxLogChain, LogChain)

    return true;
WXJS_END_SET_PROP	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxLogChain, LogChain)
	Log::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
	
WXJS_BEGIN_ADD_PROP(wxLogChain, LogChain)
    //if ( WindowEventHandler::ConnectEvent(p, prop, true) )
    //    return true;
    //
    //ChoiceEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP

WXJS_BEGIN_DEL_PROP(wxLogChain, LogChain)
  //if ( WindowEventHandler::ConnectEvent(p, prop, false) )
  //  return true;
  //
  //ChoiceEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP






// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxLogChain, LogChain)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	wxLog* pLog = Log::GetPrivate(cx, argv[0]);
	if( pLog == NULL ) {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Log");
        return NULL;
	}

    return new wxLogChain(pLog);
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxLogChain, LogChain)

WXJS_END_DESTRUCTOR



//
//	メソッド
//
WXJS_BEGIN_METHOD_MAP(LogChain)
    WXJS_METHOD("detachOldLog", detachOldLog, 0)
    WXJS_METHOD("passMessages", passMessages, 1)
    WXJS_METHOD("setLog", setLog, 1)
WXJS_END_METHOD_MAP()

JSBool LogChain::detachOldLog(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxLogChain *p = GetPrivate(cx, obj);
	p->DetachOldLog();

    return JS_TRUE;
}


JSBool LogChain::passMessages(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxLogChain *p = GetPrivate(cx, obj);
	bool bPassMessages = false;
	
	
	if ( ! FromJS(cx, argv[0], bPassMessages) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}
	p->PassMessages( bPassMessages );

    return JS_TRUE;
}


JSBool LogChain::setLog(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxLogChain *p = GetPrivate(cx, obj);
	wxLog* pLog = NULL;
	
	pLog = Log::GetPrivate(cx, argv[0]);
	if( pLog == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Log");
		return JS_FALSE;
	}

	p->SetLog(pLog);

    return JS_TRUE;
}