/*
 * wxJavaScript - distream.cpp
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
 * $Id: distream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/stream.h"
#include "js/io/istream.h"
#include "js/io/distream.h"

using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>distream</file>
 * <module>io</module>
 * <class name="wxDataInputStream" version="0.8.3">
 *  This class provides functions that read binary data types in a portable way. 
 *  Data can be read in either big-endian or little-endian format, little-endian being
 *  the default on all architectures.
 *  <br /><br />
 *  If you want to read data from text files (or streams) use @wxTextInputStream instead.
 *  <br /><br />
 *  <b>Remark :</b>This class is not thoroughly tested. If you find problems let
 *  it know on the <a href="http://sourceforge.net/forum/forum.php?forum_id=168145">project forum</a>.
 * </class>
 */

WXJS_INIT_CLASS(DataInputStream, "DataInputStream", 1)
/***
 * <ctor>
 *  <function>
 *   <arg name="Input" type="@wxInputStream">An input stream</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxDataInputStream object.
 *  </desc>
 * </ctor>
 */
//wxDataInputStream* DataInputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
WXJS_BEGIN_CONSTRUCTOR(wxDataInputStream, DataInputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *in = InputStream::GetPrivate(cx, argv[0]);
    if ( in == NULL )
        return NULL;

	// This is needed, because otherwise the stream can be garbage collected.
	// Another method could be to root the stream, but how are we going to unroot it?
	JS_DefineProperty(cx, obj, "__stream__", argv[0], NULL, NULL, JSPROP_READONLY);

    return new wxDataInputStream(*dynamic_cast<wxInputStream *>(in->GetStream()));
WXJS_END_CONSTRUCTOR

WXJS_BEGIN_METHOD_MAP(DataInputStream)
    WXJS_METHOD("bigEndianOrdered", bigEndianOrdered, 1)
    WXJS_METHOD("read64", read64, 0)
    WXJS_METHOD("read32", read32, 0)
    WXJS_METHOD("read16", read16, 0)
    WXJS_METHOD("read8", read8, 0)
    WXJS_METHOD("readString", readString, 0)
WXJS_END_METHOD_MAP()

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
 JSBool DataInputStream::bigEndianOrdered(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
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
 * <method name="read64">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 64 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool DataInputStream::read64(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint64 value = p->Read64();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (long) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="read32">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 32 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool DataInputStream::read32(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint32 value = p->Read32();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (int) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="read16">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 16 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool DataInputStream::read16(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint16 value = p->Read16();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (int) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="read8">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 8 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool DataInputStream::read8(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint8 value = p->Read8();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (int) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="readDouble">
 *  <function return=WXJS_TYPE_DOUBLE />
 *  <desc>
 *   Reads a double (IEEE encoded) from a stream.
 *  </desc>
 * </method>
 */
JSBool DataInputStream::readDouble(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->ReadDouble());

    return JS_TRUE;
}

/***
 * <method name="readString">
 *  <function returns=WXJS_TYPE_STRING />
 *  <desc>
 *   Reads a string from a stream. Actually, this function first reads a long integer 
 *   specifying the length of the string (without the last null character) and then reads the string.
 *  </desc>
 * </method>
 */
JSBool DataInputStream::readString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxDataInputStream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->ReadString());
    return JS_TRUE;
}
