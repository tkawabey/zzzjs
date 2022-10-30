/*
 * wxJavaScript - ostream.cpp
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
 * $Id: ostream.cpp 759 2007-06-12 21:13:52Z fbraem $
 */
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/archive.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/io/stream.h"
#include "js/io/istream.h"
#include "js/io/ostream.h"


#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/jsmembuf.h"

using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>ostream</file>
 * <module>io</module>
 * <class name="wxOutputStream" prototpye="@wxStreamBase" version="0.8.2">
 *  wxOutputStream is a prototype for output streams. You can't construct it directly.
 *  See @wxMemoryOutputStream, @wxFileOutputStream, @wxFFileOutputStream.
 * </class>
 */
ZZZJS_INIT_CLASS(OutputStream, "OutputStream", 0)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, OutputStream)
	StreamBase::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <properties>
 *  <property name="lastWrite" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Gets the last number of bytes written.
 *  </property> 
 *  <property name="tellO" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the current position.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(OutputStream)
    ZZZJS_READONLY_PROPERTY(P_LAST_WRITE, "lastWrite")
    ZZZJS_READONLY_PROPERTY(P_TELL_O, "tellO")
ZZZJS_END_PROPERTY_MAP()

//bool OutputStream::GetProperty(Stream *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(Stream, OutputStream)
    wxOutputStream *stream = (wxOutputStream *) p->GetStream();
    switch (id)
    {
    case P_LAST_WRITE:
        ToJSVal(cx, vp, (long) stream->LastWrite());
        break;
    case P_TELL_O:
        ToJSVal(cx, vp, (long) stream->TellO());
        break;
    }
    return true;
ZZZJS_END_GET_PROP

ZZZJS_BEGIN_METHOD_MAP(OutputStream)
    ZZZJS_METHOD("close", close, 0)
    ZZZJS_METHOD("putC", putC, 1)
    ZZZJS_METHOD("write", write, 1)
    ZZZJS_METHOD("seekO", seekO, 1)
    ZZZJS_METHOD("sync", sync, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="close">
 *  <function returns="Boolean" />
 *  <desc>
 *   Closes the stream
 *  </desc>
 * </method>
 */
JSBool OutputStream::close(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p != NULL )
    {
        wxOutputStream *out = (wxOutputStream *) p->GetStream();
        *vp = ToJS(cx, out->Close());
    }
    return JS_TRUE;
}

/***
 * <method name="putC">
 *  <function>
 *   <arg name="Char" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   The first character of the String is written to the output stream.
 *  </desc>
 * </method>
 */
JSBool OutputStream::putC(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxOutputStream *out = (wxOutputStream *) p->GetStream();

    wxString Buffer;
    FromJS(cx, argv[0], Buffer);
    if ( Buffer.length() > 0 )
    {
        out->PutC(Buffer.at(0));
    }
    return JS_TRUE;
}

/***
 * <method name="write">
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Buffer" type="@wxMemoryBuffer" />
 *   <arg name="Count" type=ZZZJS_TYPE_NUMBER>The number of characters to write. Default is the length of buffer.</arg>
 *  </function>
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Str" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Input" type="@wxInputStream" />
 *  </function>
 *  <desc>
 *  1. Writes the buffer to the outputstream. Unlike wxWindows, the size of the buffer must not
 *  be specified. If ommitted then the full buffer is written.
 *  <br /><br />
 *  2. Reads data from the specified input stream and stores them in the current stream. 
 *  The data is read until an error is raised by one of the two streams.
 *  <br /><br />
 *  Unlike wxWidgets, this method returns the number of bytes written.
 *  </desc>
 * </method>
 */
JSBool OutputStream::write(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxOutputStream *out = (wxOutputStream *) p->GetStream();

    if ( InputStream::HasPrototype(cx, argv[0]) )
    {
        Stream *p_in = InputStream::GetPrivate(cx, argv[0], false);
        wxInputStream *in = (wxInputStream *) p_in->GetStream();
        out->Write(*in);
    }
    else
    {
		if ( argv[0].isObject() )
		{
			wxMemoryBuffer* buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[0]));
			if ( buffer != NULL )
			{
				*vp = ToJS(cx, out->Write(buffer->GetData(), buffer->GetDataLen()).LastWrite());
				return JS_TRUE;
			}
		}

        wxString buffer;
        FromJS(cx, argv[0], buffer);

        int count = buffer.length();
        if ( argc > 1 )
        {
          if ( FromJS(cx, argv[1], count) )
          {
            if ( count > (int) buffer.length() )
                count = buffer.length();
          }
          else
              return JS_FALSE;
        }

		*vp = ToJS(cx, out->Write(buffer, count).LastWrite());
    }
    return JS_TRUE;
}

/***
 * <method name="seekO">
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Offset" type=ZZZJS_TYPE_NUMBER>Offset to seek to</arg>
 *   <arg name="Mode" type="@wxFile#wxSeekMode" default="wxSeekMode.FromStart" />
 *  </function>
 *  <desc>
 *   Seeks the offset. Returns the actual position or -1 on error.
 *  </desc>
 * </method>
 */
JSBool OutputStream::seekO(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxOutputStream *out = (wxOutputStream *) p->GetStream();

    int offset;
	if ( ! FromJS(cx, argv[0], offset) )
		return JS_FALSE;

	int pos;

	if ( argc > 1 )
	{
		int mode;
		if ( FromJS(cx, argv[1], mode) )
		{
			pos = out->SeekO(offset, (wxSeekMode) mode);
		}
		else
			return JS_FALSE;
	}
	else
		pos = out->SeekO(offset);

	*vp = ToJS(cx, pos);
	return JS_TRUE;
}

/***
 * <method name="sync">
 *  <function />
 *  <desc>
 *   Flushes the buffer.
 *  </desc>
 * </method>
 */
JSBool OutputStream::sync(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxOutputStream *out = (wxOutputStream *) p->GetStream();

    out->Sync();
    return JS_TRUE;
}

