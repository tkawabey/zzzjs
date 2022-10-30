/*
 * wxJavaScript - httphdr.cpp
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
 * $Id: httphdr.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
#include "precompile.h"



#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 



#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/protocol/http.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/io/sockbase.h"
#include "js/io/httphdr.h"
#include "js/io/http.h"


using namespace zzzJs;
using namespace zzzJs::io;

ZZZJS_INIT_CLASS(HTTPHeader, "HTTPHeader", 0)

//bool HTTPHeader::AddProperty(HTTPHeader *p, JSContext *cx, JSObject *obj, 
//						         const wxString &prop,  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_ADD_PROP(HTTPHeader, HTTPHeader)
{
	JSObject *objParent = JS_GetParent(obj);//JS_GetParent(cx, obj);
	SocketBasePrivate *base = HTTP::GetPrivate(cx, objParent);
	wxHTTP *http = dynamic_cast<wxHTTP *>(base->GetBase());
	if ( http )
	{
		wxString value;
		FromJS(cx, vp, value);
		http->SetHeader(prop, value);
	}
	return true;
}
ZZZJS_END_ADD_PROP

bool HTTPHeader::GetStringProperty(HTTPHeader *p, JSContext *cx, JSObject *obj, 
									   const wxString &propertyName,  JS::MutableHandle<JS::Value>& vp)
{
	JSObject *objParent = JS_GetParent(obj);//JS_GetParent(cx, obj);
	SocketBasePrivate *base = HTTP::GetPrivate(cx, objParent);
	wxHTTP *http = dynamic_cast<wxHTTP *>(base->GetBase());

	if ( http )
	{
		wxString value = http->GetHeader(propertyName);
		ToJSVal(cx, vp, value); 
	}
	return true;
}
