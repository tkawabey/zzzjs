/*
 * wxJavaScript - url.cpp
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
 * $Id: url.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/common/index.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/jsmembuf.h"
#include "js/io/url.h"
#include "js/io/jsstream.h"
#include "js/io/istream.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>url</file>
 * <module>io</module>
 * <class name="wxURL" prototype="@wxURI" version="0.8.4">
 *  Parses URLs.
 * </class>
 */
ZZZJS_INIT_CLASS(URL, "URL", 1)

/***
 * <constants>
 *  <type name="wxURLError">
 *   <constant name="NOERR">No error.</constant>
 *   <constant name="SNTXERR">Syntax error in the URL string.</constant>
 *   <constant name="NOPROTO">Found no protocol which can get this URL.</constant>
 *   <constant name="NOHOST">An host name is required for this protocol.</constant>
 *   <constant name="NOPATH">A path is required for this protocol.</constant>
 *   <constant name="CONNERR">Connection error.</constant>
 *   <constant name="PROTOERR">An error occurred during negotiation.</constant>
 *   <desc>
 *    wxURLError is ported to JavaScript as a separate class. Note that this
 *    class doesn't exist in wxWidgets.
 *   </desc>
 *  </type>
 * </constants>
 */
void URL::InitClass(JSContext *cx, JSObject *obj, JSObject *proto)
{
    JSConstDoubleSpec wxURLErrorMap[] = 
    {
		ZZZJS_CONSTANT(wxURL_, NOERR)
		ZZZJS_CONSTANT(wxURL_, SNTXERR)
		ZZZJS_CONSTANT(wxURL_, NOPROTO)
		ZZZJS_CONSTANT(wxURL_, NOHOST)
		ZZZJS_CONSTANT(wxURL_, NOPATH)
		ZZZJS_CONSTANT(wxURL_, CONNERR)
		ZZZJS_CONSTANT(wxURL_, PROTOERR)
		{ 0 }
    };

    JSObject *constObj = JS_DefineObject(cx, obj, "wxURLError", 
									 	 NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxURLErrorMap);
}

/***
 * <ctor>
 *  <function>
 *   <arg name="Url" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Constructs a URL object from the string. The URL must be valid according to RFC 1738.
 *   In particular, file URLs must be of the format 'file://hostname/path/to/file'. It is valid 
 *   to leave out the hostname but slashes must remain in place-- i.e. a file URL without a
 *   hostname must contain three consecutive slashes.
 *  </desc>
 * </ctor>
 */
//wxURL *URL::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxURL, URL)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString url;
	FromJS(cx, argv[0], url);
	return new wxURL(url);
ZZZJS_END_CONSTRUCTOR

/***
 * <properties>
 *  <property name="error" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the last occurred error. See @wxURL#wxURLError.
 *  </property>
 *  <property name="inputStream" type="@wxInputStream" readonly="Y">
 *   Creates a new input stream on the specified URL. You can use all but 
 *   seek functionality of a stream. Seek isn't available on all streams.
 *   For example, http or ftp streams doesn't deal with it.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(URL)
	ZZZJS_READONLY_PROPERTY(P_ERROR, "error")
	ZZZJS_READONLY_PROPERTY(P_INPUT_STREAM, "inputStream")
ZZZJS_END_PROPERTY_MAP()

//bool URL::GetProperty(wxURL *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxURL, URL)
	switch(id)
	{
	case P_ERROR:
		ToJSVal<int>(cx, vp, p->GetError());
		break;
	case P_INPUT_STREAM:
		{
			wxInputStream *stream = p->GetInputStream();
			vp.set( InputStream::CreateObject(cx, new Stream(stream), NULL) );
			break;
		}
	}
	return true;
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_METHOD_MAP(URL)
	ZZZJS_METHOD("setProxy", setProxy, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="setProxy">
 *  <function>
 *   <arg name="proxy" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Sets the proxy to use for this URL.
 *  </desc>
 * </method>
 */
JSBool URL::setProxy(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxURL *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	wxString proxy;
	FromJS(cx, argv[0], proxy);
	p->SetProxy(proxy);
	return JS_TRUE;
}

ZZZJS_BEGIN_STATIC_METHOD_MAP(URL)
	ZZZJS_METHOD("setDefaultProxy", setDefaultProxy, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <class_method name="setDefaultProxy">
 *  <function>
 *   <arg name="proxy" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Sets the default proxy server to use to get the URL. 
 *   The string specifies the proxy like this: &lt;hostname&gt;:&lt;port number&gt;.
 *  </desc>
 * </class_method>
 */
JSBool URL::setDefaultProxy(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString proxy;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], proxy);
	wxURL::SetDefaultProxy(proxy);
	return JS_TRUE;
}
