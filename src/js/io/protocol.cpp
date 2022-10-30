/*
 * wxJavaScript - protocol.cpp
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
 * $Id: protocol.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 



#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/archive.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/jsmembuf.h"
#include "js/io/jsstream.h"
#include "js/io/sistream.h"
#include "js/io/sockbase.h"
#include "js/io/protocol.h"
#include "js/io/sockclient.h"

using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>protocol</file>
 * <module>io</module>
 * <class name="wxProtocol" prototype="@wxSocketClient" version="0.8.4">
 *  Prototype for all protocol classes.
 * </class>
 */
ZZZJS_INIT_CLASS(Protocol, "Protocol", 0)

/***
 * <constants>
 *  <type name="wxProtocolError">
 *   <constant name="NOERR">No error</constant>
 *   <constant name="NETERR">A generic network error occurred.</constant>
 *   <constant name="PROTERR">An error occurred during negotiation.</constant>
 *   <constant name="CONNERR">The client failed to connect the server.</constant>
 *   <constant name="INVVAL">Invalid value.</constant>
 *   <constant name="NOHNDLR" />
 *   <constant name="NOFILE">The remote file doesn't exist.</constant>
 *   <constant name="ABRT">Last action aborted.</constant>
 *   <constant name="RCNCT">An error occurred during reconnection.</constant>
 *   <constant name="STREAMING">Someone tried to send a command during a transfer.</constant>
 *   <desc>
 *    wxProtocolError is ported to JavaScript as a separate class. Note that this
 *    class doesn't exist in wxWidgets.
 *   </desc>
 *  </type>
 * </constants>
 */
void Protocol::InitClass(JSContext *cx, JSObject *obj, JSObject *proto)
{
    JSConstDoubleSpec wxProtocolErrorMap[] = 
    {
		ZZZJS_CONSTANT(wxPROTO_, NOERR)
		ZZZJS_CONSTANT(wxPROTO_, NETERR)
		ZZZJS_CONSTANT(wxPROTO_, PROTERR)
		ZZZJS_CONSTANT(wxPROTO_, CONNERR)
		ZZZJS_CONSTANT(wxPROTO_, INVVAL)
		ZZZJS_CONSTANT(wxPROTO_, NOHNDLR)
		ZZZJS_CONSTANT(wxPROTO_, NOFILE)
		ZZZJS_CONSTANT(wxPROTO_, ABRT)
		ZZZJS_CONSTANT(wxPROTO_, RCNCT)
		ZZZJS_CONSTANT(wxPROTO_, STREAMING)
	    { 0 }
    };

    JSObject *constObj = JS_DefineObject(cx, obj, "wxProtocolError", 
									 	 NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxProtocolErrorMap);
}

ZZZJS_BEGIN_GET_SET_STR_PROP(SocketBasePrivate, Protocol)
	SocketClient::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <properties>
 *  <property name="contentType" type=ZZZJS_TYPE_STRING readonly="Y">
 *   Returns the type of the content of the last opened stream. It is a mime-type
 *  </property>
 *  <property name="error" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the last occurred error. See @wxProtocol#wxProtocolError.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Protocol)
	ZZZJS_READONLY_PROPERTY(P_CONTENT_TYPE, "contentType")
	ZZZJS_READONLY_PROPERTY(P_ERROR, "error")
ZZZJS_END_PROPERTY_MAP()

//bool Protocol::GetProperty(SocketBasePrivate *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(SocketBasePrivate, Protocol)
	wxProtocol *protocol = dynamic_cast<wxProtocol *>(p->GetBase());

	switch(id)
	{
	case P_CONTENT_TYPE:
		ToJSVal(cx, vp, protocol->GetContentType());
		break;
	case P_ERROR:
		ToJSVal<int>(cx, vp, protocol->GetError());
		break;
	}
	return true;
ZZZJS_END_GET_PROP

ZZZJS_BEGIN_METHOD_MAP(Protocol)
	ZZZJS_METHOD("abort", abort, 0)
	ZZZJS_METHOD("getInputStream", getInputStream, 1)
	ZZZJS_METHOD("reconnect", reconnect, 0)
	ZZZJS_METHOD("setPassword", setPassword, 1)
	ZZZJS_METHOD("setUser", setUser, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="abort">
 *  <function returns="Boolean" />
 *  <desc>
 *   Abort the current stream.
 *  </desc>
 * </method>
 */
JSBool Protocol::abort(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	SocketBasePrivate *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxProtocol *protocol = dynamic_cast<wxProtocol *>(p->GetBase());
	*vp = ToJS(cx, protocol->Abort());
	return JS_TRUE;
}

/***
 * <method name="getInputStream">
 *  <function returns="@wxInputStream">
 *   <arg name="Path" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Creates a new input stream on the specified path. 
 *   You can use all but seek functionality of wxStream. 
 *   @wxInputStream#seekI isn't available on all stream. For example, http or 
 *   ftp streams doesn't deal with it. Other functions like 
 *   @wxStreamBase#size aren't available for the moment for 
 *   this sort of stream. You will be notified when the EOF 
 *   is reached by an error.
 *  </desc>
 * </method>
 */
JSBool Protocol::getInputStream(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	SocketBasePrivate *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxProtocol *protocol = dynamic_cast<wxProtocol *>(p->GetBase());

	wxString path;
	FromJS(cx, argv[0], path);

	wxInputStream *stream = protocol->GetInputStream(path);
	if ( stream != NULL )
	{
		Stream *js_stream = new Stream(stream, false);
		p->AddStream(js_stream);
		*vp = SocketInputStream::CreateObject(cx, js_stream, NULL);
		js_stream->SetObject(JSVAL_TO_OBJECT(*vp));	
	}
	return JS_TRUE;
}

/***
 * <method name="reconnect">
 *  <function returns="Boolean" />
 *  <desc>
 *   Tries to reestablish a previous opened connection (close and renegotiate connection).
 *  </desc>
 * </method>
 */
JSBool Protocol::reconnect(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	SocketBasePrivate *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxProtocol *protocol = dynamic_cast<wxProtocol *>(p->GetBase());

	*vp = ToJS(cx, protocol->Reconnect());
	return JS_TRUE;
}

/***
 * <method name="setPassword">
 *  <function>
 *   <arg name="pwd" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Sets the authentication password. It is mainly useful when FTP is used.
 *  </desc>
 * </method>
 */
JSBool Protocol::setPassword(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	SocketBasePrivate *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxProtocol *protocol = dynamic_cast<wxProtocol *>(p->GetBase());

	wxString pwd;
	FromJS(cx, argv[0], pwd);
	protocol->SetPassword(pwd);
	return JS_TRUE;
}

/***
 * <method name="setUser">
 *  <function>
 *   <arg name="user" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Sets the authentication user. It is mainly useful when FTP is used.
 *  </desc>
 * </method>
 */
JSBool Protocol::setUser(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	SocketBasePrivate *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxProtocol *protocol = dynamic_cast<wxProtocol *>(p->GetBase());

	wxString user;
	FromJS(cx, argv[0], user);
	protocol->SetUser(user);
	return JS_TRUE;
}
