/*
 * wxJavaScript - istream.cpp
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
 * $Id: istream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/stream.h"
#include "js/io/ostream.h"
#include "js/io/istream.h"
#include "js/ext/zzzjs_ext_init.h"

using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>istream</file>
 * <module>io</module>
 * <class name="wxInputStream" prototype="@wxStreamBase" version="0.8.2">
 *  wxInputStream is a prototype for input streams. You can't construct it directly.
 *  See @wxMemoryInputStream, @wxFileInputStream and @wxFFileInputStream.
 * </class>
 */
ZZZJS_INIT_CLASS(InputStream, "InputStream", 0)

/***
 * <properties>
 *  <property name="c" type=ZZZJS_TYPE_STRING>
 *   Returns the first character in the input queue and removes it.
 *   When set it puts back the character or full String in the input queue.
 *  </property>
 *  <property name="eof" type="Boolean" readonly="Y">
 *   Returns true when end-of-file occurred.
 *  </property>
 *  <property name="lastRead" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the last number of bytes read.
 *  </property>
 *  <property name="peek" type=ZZZJS_TYPE_STRING readonly="Y">
 *   Returns the first character in the input queue without removing it.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(InputStream)
    ZZZJS_PROPERTY(P_C, "c")
    ZZZJS_READONLY_PROPERTY(P_EOF, "eof")
    ZZZJS_READONLY_PROPERTY(P_LAST_READ, "lastRead")
    ZZZJS_READONLY_PROPERTY(P_PEEK, "peek")
    ZZZJS_READONLY_PROPERTY(P_TELL_I, "tellI")
ZZZJS_END_PROPERTY_MAP()

//bool InputStream::GetProperty(Stream *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(Stream, InputStream)
    wxInputStream *stream = (wxInputStream*) p->GetStream();
    switch (id)
    {
    case P_C:
        ToJSVal(cx, vp, wxString::FromAscii(stream->GetC()));
        break;
    case P_EOF:
        ToJSVal(cx, vp, stream->Eof());
        break;
    case P_LAST_READ:
        ToJSVal(cx, vp, (int) stream->LastRead());
        break;
    case P_PEEK:
		ToJSVal(cx, vp, wxString::FromAscii(stream->Peek()));
        break;
    }
    return true;
ZZZJS_END_GET_PROP

//bool InputStream::SetProperty(Stream *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(Stream, InputStream)
    if ( id == P_C )
    {
        wxInputStream *stream = (wxInputStream*) p->GetStream();
        wxString s;
        FromJS(cx, vp, s);
        if ( s.length() > 0 )
        {
            stream->Ungetch(s, s.length());
        }
    }
    return true;
ZZZJS_END_SET_PROP
	
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, InputStream)
	StreamBase::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


ZZZJS_BEGIN_METHOD_MAP(InputStream)
    ZZZJS_METHOD("getC", getC, 0)
    ZZZJS_METHOD("peek", peek, 0)
    ZZZJS_METHOD("read", read, 1)
    ZZZJS_METHOD("seekI", seekI, 1)
    ZZZJS_METHOD("ungetch", ungetch, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="getC">
 *  <function returns=ZZZJS_TYPE_STRING />
 *  <desc>  
 *   Returns the next character from the input queue and removes it.
 *  </desc>
 * </method>
 */
JSBool InputStream::getC(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxInputStream *in = (wxInputStream *) p->GetStream();
	*vp = ToJS(cx, wxString::FromAscii(in->GetC()));
    return JS_TRUE;
}

/***
 * <method name="peek">
 *  <function returns=ZZZJS_TYPE_STRING />
 *  <desc>
 *   Returns the next character from the input queue without removing it.
 *  </desc>
 * </method>
 */
JSBool InputStream::peek(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxInputStream *in = (wxInputStream *) p->GetStream();

	*vp = ToJS(cx, wxString::FromAscii(in->Peek()));
    return JS_TRUE;
}

/***
 * <method name="read">
 *  <function returns="wxInputStream">
 *   <arg name="Buffer" type="@wxMemoryBuffer" />
 *  </function>
 *  <function returns="wxInputStream">
 *   <arg name="Output" type="@wxOutputStream">
 *    The outputstream that gets the data from the input queue.
 *   </arg>
 *  </function>
 *  <desc>
 *   Reads the specified number of bytes (the size of the buffer) and stores them in the buffer.
 *   <br /><br />
 *   Reads data from the input queue and stores it in the specified output stream. 
 *   The data is read until an error is raised by one of the two streams.
 *  </desc>
 * </method>
 */
JSBool InputStream::read(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxInputStream *in = (wxInputStream *) p->GetStream();

    if ( OutputStream::HasPrototype(cx, argv[0]) )
    {
        Stream *p_out = OutputStream::GetPrivate(cx, argv[0], false);
        wxOutputStream *out = (wxOutputStream *) p_out->GetStream();
        in->Read(*out);
		*vp = OBJECT_TO_JSVAL(obj);
        return JS_TRUE;
    }
    else
    {
        wxMemoryBuffer *buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[0]));
		
		if ( buffer != NULL )
		{
			in->Read(buffer->GetData(), buffer->GetBufSize());
            buffer->SetDataLen(in->LastRead());
			*vp = OBJECT_TO_JSVAL(obj);
			return JS_TRUE;
		}
	}
    return JS_FALSE;
}

/***
 * <method name="seekI">
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Offset" type=ZZZJS_TYPE_NUMBER>
 *    Offset to seek to
 *   </arg>
 *   <arg name="Mode" type="@wxFile#wxSeekMode" default="wxSeekMode.FromStart" />
 *  </function>
 *  <desc>
 *   Seeks the offset. Returns the actual position or -1 on error.
 *  </desc>
 * </method>
 */
JSBool InputStream::seekI(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxInputStream *in = (wxInputStream *) p->GetStream();

    int offset;
	if ( ! FromJS(cx, argv[0], offset) )
		return JS_FALSE;

	int pos;

	if ( argc > 1 )
	{
		int mode;
		if ( FromJS(cx, argv[1], mode) )
		{
			pos = in->SeekI(offset, (wxSeekMode) mode);
		}
		else
			return JS_FALSE;
	}
	else
		pos = in->SeekI(offset);

	*vp = ToJS(cx, pos);
	return JS_TRUE;
}

/***
 * <method name="ungetch">
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Buffer" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Buffer" type="@wxMemoryBuffer" />
 *  </function>
 *  <desc>
 *   This function is only useful in read mode. It is the manager of the "Write-Back" buffer. 
 *   This buffer acts like a temporary buffer where datas which has to be read during the next 
 *   read IO call are put. This is useful when you get a big block of data which you didn't want 
 *   to read: you can replace them at the top of the input queue by this way.
 *   <br /><br />
 *   Be very careful about this call in connection with calling @wxInputStream#seekI on the 
 *   same stream. Any call to @wxInputStream#seekI will invalidate any previous call to this 
 *   method (otherwise you could @wxInputStream#seekI to one position, "unread" a few bytes
 *   there, @wxInputStream#seekI to another position and data would be either lost or corrupted).
 *  </desc>
 * </method>
 */
JSBool InputStream::ungetch(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    Stream *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxInputStream *in = (wxInputStream *) p->GetStream();

	if ( argv[0].isObject() )
	{
		wxMemoryBuffer* buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[0]));
		if ( buffer != NULL )
		{
			*vp = ToJS(cx, (int) in->Ungetch(buffer->GetData(), buffer->GetDataLen()));
			return JS_TRUE;
		}
	}
    
	wxString s;
    FromJS(cx, argv[0], s);
    if ( s.length() > 0 )
    {
        *vp = ToJS(cx, (int) in->Ungetch(s, s.length()));
    }
    else
        *vp = ToJS(cx, 0);

    return JS_TRUE;
}
