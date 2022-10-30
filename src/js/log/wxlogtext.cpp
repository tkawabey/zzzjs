/*
 * wxJavaScript - wxlogtext.cpp
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
#include "js/log/wxlogtext.h"
#include "js/log/wxlog.h"
#include "js/gui/control/textctrl.h"
#include "js/gui/errors.h"
#include "js/common/jsutil.h"


using namespace zzzJs;
using namespace zzzJs::log;

WXJS_INIT_CLASS(LogText, "LogText", 1)
	
WXJS_BEGIN_PROPERTY_MAP(LogText)
WXJS_END_PROPERTY_MAP()



WXJS_BEGIN_GET_PROP(wxLogTextCtrl, LogText)
    return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxLogTextCtrl, LogText)

    return true;
WXJS_END_SET_PROP	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxLogTextCtrl, LogText)
	Log::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
	
WXJS_BEGIN_ADD_PROP(wxLogTextCtrl, LogText)
    //if ( WindowEventHandler::ConnectEvent(p, prop, true) )
    //    return true;
    //
    //ChoiceEventHandler::ConnectEvent(p, prop, true);
    return true;
WXJS_END_ADD_PROP

WXJS_BEGIN_DEL_PROP(wxLogTextCtrl, LogText)
  //if ( WindowEventHandler::ConnectEvent(p, prop, false) )
  //  return true;
  //
  //ChoiceEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxLogTextCtrl, LogText)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		
	wxTextCtrl* pTextCtrl = zzzJs::gui::TextCtrl::GetPrivate(cx, argv[0]);
	if( pTextCtrl == NULL ) {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "TextCtrl");
        return NULL;
	}

    return new wxLogTextCtrl(pTextCtrl);
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxLogTextCtrl, LogText)

WXJS_END_DESTRUCTOR



//
//	メソッド
//
WXJS_BEGIN_METHOD_MAP(LogText)
WXJS_END_METHOD_MAP()
