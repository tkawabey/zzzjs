/*
 * wxJavaScript - http.cpp
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
 * $Id: http.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include <wx/wfstream.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/io/constant.h"
#include "js/io/jsstream.h"
#include "js/io/sockbase.h"
#include "js/io/http.h"
#include "js/io/httphdr.h"
#include "js/io/sockaddr.h"
#include "js/io/protocol.h"




using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>http</file>
 * <module>io</module>
 * <class name="wxHTTP" prototype="@wxProtocol" version="0.8.4">
 *  Implements the HTTP protocol.
 * </class>
 */
ZZZJS_INIT_CLASS(HTTP, "HTTP", 0)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(SocketBasePrivate, HTTP)
	Protocol::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Creates a new wxHTTP object
 *  </desc>
 * </ctor>
 */
//SocketBasePrivate *HTTP::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
ZZZJS_BEGIN_CONSTRUCTOR(SocketBasePrivate, HTTP)
	return new SocketBasePrivate(new wxHTTP());
ZZZJS_END_CONSTRUCTOR


ZZZJS_BEGIN_DESTRUCTOR(SocketBasePrivate, HTTP)
{
	p->DestroyStreams(/*cx*/);
	delete p;
}
ZZZJS_END_DESTRUCTOR
/***
 * <properties>
 *  <property name="headers" type="Array" readonly="Y">
 *   Contains the headers. Access the elements of the array with String keys.
 *  </property>
 *  <property name="response" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the HTTP response code returned by the server.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(HTTP)
	ZZZJS_READONLY_PROPERTY(P_RESPONSE, "response")
	ZZZJS_READONLY_PROPERTY(P_HEADERS, "headers")
ZZZJS_END_PROPERTY_MAP()

//bool HTTP::GetProperty(SocketBasePrivate *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(SocketBasePrivate, HTTP)
	wxHTTP *http = dynamic_cast<wxHTTP *>(p->GetBase());
	switch(id)
	{
	case P_RESPONSE:
		ToJSVal(cx, vp, http->GetResponse());
		break;
	case P_HEADERS:
		vp.set( HTTPHeader::CreateObject(cx, new HTTPHeader(), obj) );
		break;
	}
	return true;
ZZZJS_END_GET_PROP
