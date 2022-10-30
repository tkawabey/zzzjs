/*
 * wxJavaScript - tostream.cpp
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
 * $Id: tostream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/stream.h"
#include "js/io/ostream.h"
#include "js/io/tostream.h"



using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>tostream</file>
 * <module>io</module>
 * <class name="wxTextOutputStream" version="0.8.2">
 *  This class provides functions that write text datas using an output stream.
 *  So, you can write text, floats and integers.
 *
 *  An example:
 *  <pre><code class="whjs">
 *   textout.writeString("The value of x:");
 *   textout.write32(x);
 *  </code></pre>
 *  This example can also be written as follows:
 *  <code class="whjs">
 *   textout.writeString("The value of x:" + x);</code>
 * </class>
 */
ZZZJS_INIT_CLASS(TextOutputStream, "TextOutputStream", 1)

/***
 * <constants>
 *  <type name="wxEol">
 *   <constant name="NATIVE" />
 *   <constant name="UNIX" />
 *   <constant name="MAC" />
 *   <constant name="DOS" />
 *  </type>
 *  <desc>
 *   wxEol is ported as a separate JavaScript object.
 *  </desc>
 * </constants>
 */
void TextOutputStream::InitClass(JSContext *cx, JSObject *obj, JSObject *proto)
{
    JSConstDoubleSpec wxEolMap[] = 
    {
        ZZZJS_CONSTANT(wxEOL_, NATIVE)
        ZZZJS_CONSTANT(wxEOL_, UNIX)
        ZZZJS_CONSTANT(wxEOL_, MAC)
        ZZZJS_CONSTANT(wxEOL_, DOS)
	    { 0 }
    };

    JSObject *constObj = JS_DefineObject(cx, obj, "wxEol", 
										 NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxEolMap);
}

/***
 * <ctor>
 *  <function>
 *   <arg name="Output" type="@wxOutputStream">An output stream</arg>
 *   <arg name="Mode" type="@wxTextOutputStream#wxEol" default="wxEol.NATIVE">The end-of-line mode</arg>
 *   <arg name="Encoding" type=ZZZJS_TYPE_STRING default="UTF-8">The encoding to use</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxTextOutputStream object.
 *  </desc>
 * </ctor>
 */
//wxTextOutputStream* TextOutputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxTextOutputStream, TextOutputStream)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc > 3 )
        argc = 3;

    wxString encoding(WXJS_EXTERNAL_ENCODING);
    int mode = wxEOL_NATIVE;
    switch(argc)
    {
    case 3:
        FromJS(cx, argv[2], encoding);
        // Fall through
    case 2:
        if ( ! FromJS(cx, argv[1], mode) )
            return NULL;
        // Fall through
    default:
        Stream *out = OutputStream::GetPrivate(cx, argv[0]);
        if ( out == NULL )
            return NULL;

	    // This is needed, because otherwise the stream can be garbage collected.
	    // Another method could be to root the stream, but how are we going to unroot it?
	    JS_DefineProperty(cx, obj, "__stream__", argv[0], NULL, NULL, JSPROP_READONLY);
        wxCSConv conv(encoding);
	    return new wxTextOutputStream(*(wxOutputStream *) out->GetStream(), (wxEOL) mode, conv);
    }
}
ZZZJS_END_CONSTRUCTOR

/***
 * <properties>
 *  <property name="mode" type=ZZZJS_TYPE_NUMBER>
 *   Gets/Sets the end-of-line mode. See @wxTextOutputStream#wxEol.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(TextOutputStream)
    ZZZJS_PROPERTY(P_MODE, "mode")
ZZZJS_END_PROPERTY_MAP()

//bool TextOutputStream::GetProperty(wxTextOutputStream *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxTextOutputStream, TextOutputStream)
{
    if ( id == P_MODE )
    {
        ToJSVal(cx, vp, (int) p->GetMode());
    }
    return true;
}
ZZZJS_END_GET_PROP

//bool TextOutputStream::SetProperty(wxTextOutputStream *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxTextOutputStream, TextOutputStream)
{
    if ( id == P_MODE )
    {
        int mode;
        if ( FromJS(cx, vp, mode) )
        {
            p->SetMode((wxEOL) mode);
        }
    }
    return true;
}
ZZZJS_END_SET_PROP

ZZZJS_BEGIN_METHOD_MAP(TextOutputStream)
    ZZZJS_METHOD("write32", write32, 1)
    ZZZJS_METHOD("write16", write16, 1)
    ZZZJS_METHOD("write8", write8, 1)
    ZZZJS_METHOD("writeString", writeString, 1)
    ZZZJS_METHOD("writeDouble", writeDouble, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="write32">
 *  <function>
 *   <arg name="Value" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Writes a 32 bit integer to the stream.
 *  </desc>
 * </method>
 */
JSBool TextOutputStream::write32(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

// Check for other platforms !!!
#ifdef __WXMSW__
    int value;
    if ( FromJS(cx, argv[0], value) )
    {
        p->Write32(value);
        return JS_TRUE;
    }
#endif

    return JS_FALSE;
}

/***
 * <method name="write16">
 *  <function>
 *   <arg name="Value" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Writes a 16 bit integer to the stream.
 *  </desc>
 * </method>
 */
JSBool TextOutputStream::write16(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

// TODO: Check for other platforms !!!
#ifdef __WXMSW__
    int value;
    if ( FromJS(cx, argv[0], value) )
    {
        p->Write16(value);
        return JS_TRUE;
    }
#endif
    return JS_FALSE;
}

/***
 * <method name="write8">
 *  <function>
 *   <arg name="Value" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Writes a 8 bit integer to the stream.
 *  </desc>
 * </method>
 */
JSBool TextOutputStream::write8(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

// TODO: Check for other platforms !!!
#ifdef __WXMSW__
    int value;
    if ( FromJS(cx, argv[0], value) )
    {
        p->Write8(value);
        return JS_TRUE;
    }
#endif
    return JS_FALSE;
}

/***
 * <method name="writeDouble">
 *  <function>
 *   <arg name="Value" type=ZZZJS_TYPE_DOUBLE />
 *  </function>
 *  <desc>
 *   Writes a double (IEEE encoded) to a stream.
 *  </desc>
 * </method>
 */
JSBool TextOutputStream::writeDouble(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    double value;
    if ( FromJS(cx, argv[0], value) )
    {
        p->WriteDouble(value);
        return JS_TRUE;
    }
    return JS_FALSE;
}

/***
 * <method name="writeString">
 *  <function>
 *   <arg name="Value" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Writes string as a line. Depending on the end-of-line mode the end of line 
 *   ('\n') characters in the string are converted to the correct line 
 *   ending terminator.
 *  </desc>
 * </method>
 */
JSBool TextOutputStream::writeString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString value;
    FromJS(cx, argv[0], value);
    p->WriteString(value);
    return JS_TRUE;
}
