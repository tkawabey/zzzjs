/*
 * wxJavaScript - dostream.cpp
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
 * $Id: dostream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/io/constant.h"
#include "js/io/stream.h"
#include "js/io/ostream.h"
#include "js/io/dostream.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>dostream</file>
 * <module>io</module>
 * <class name="wxDataOutputStream" version="0.8.3">
 *  This class provides functions that write binary data types in a portable way. 
 *  Data can be written in either big-endian or little-endian format, little-endian
 *  being the default on all architectures.
 *  If you want to write data to text files (or streams) use @wxTextOutputStream instead.
 *  <br /><br />
 *  <b>Remark :</b>This class is not thoroughly tested. If you find problems let
 *  it know on the <a href="http://sourceforge.net/forum/forum.php?forum_id=168145">project forum</a>.
 * </class>
 */
ZZZJS_INIT_CLASS(DataOutputStream, "DataOutputStream", 1)

/***
 * <ctor>
 *  <function>
 *   <arg name="Output" type="@wxOutputStream">An output stream</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxDataOutputStream object.
 *  </desc>
 * </ctor>
 */
//wxDataOutputStream* DataOutputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxDataOutputStream, DataOutputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *out = OutputStream::GetPrivate(cx, argv[0]);
    if ( out == NULL )
        return NULL;

	// This is needed, because otherwise the stream can be garbage collected.
	// Another method could be to root the stream, but how are we going to unroot it?
	JS_DefineProperty(cx, obj, "__stream__", argv[0], NULL, NULL, JSPROP_READONLY);

    return new wxDataOutputStream(*dynamic_cast<wxOutputStream *>(out->GetStream()));
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(DataOutputStream)
    ZZZJS_METHOD("bigEndianOrdered", bigEndianOrdered, 1)
	ZZZJS_METHOD("write64", write64, 1)
    ZZZJS_METHOD("write32", write32, 1)
    ZZZJS_METHOD("write16", write16, 1)
    ZZZJS_METHOD("write8", write8, 1)
    ZZZJS_METHOD("writeString", writeString, 1)
    ZZZJS_METHOD("writeDouble", writeDouble, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="bigEndianOrdered">
 *  <function>
 *   <arg name="Ordered" type="Boolean" />
 *  </function>
 *  <desc>
 *   If <i>Ordered</i> is true, all data will be read in big-endian order, 
 *   such as written by programs on a big endian architecture (e.g. Sparc)
 *   or written by Java-Streams (which always use big-endian order).
 *  </desc>
 * </method>
 */
 JSBool DataOutputStream::bigEndianOrdered(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	bool ordered;
	if ( FromJS(cx, argv[0], ordered) )
	{
		p->BigEndianOrdered(ordered);
		return JS_TRUE;
	}
	return JS_FALSE;
}

/***
 * <method name="write64">
 *  <function>
 *   <arg name="Value" type="Long" />
 *  </function>
 *  <desc>
 *   Writes a 64 bit integer to the stream.
 *  </desc>
 * </method>
 */
JSBool DataOutputStream::write64(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

// Check for other platforms !!!
#ifdef __WXMSW__
	long value;
    if ( FromJS(cx, argv[0], value) )
    {
        p->Write64((wxUint64) value);
        return JS_TRUE;
    }
#endif

    return JS_FALSE;
}

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
JSBool DataOutputStream::write32(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
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
JSBool DataOutputStream::write16(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
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
JSBool DataOutputStream::write8(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
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
JSBool DataOutputStream::writeDouble(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
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
JSBool DataOutputStream::writeString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataOutputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString value;
    FromJS(cx, argv[0], value);
    p->WriteString(value);
    return JS_TRUE;
}
