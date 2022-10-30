/*
 * wxJavaScript - bistream.cpp
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
 * $Id: bistream.cpp 715 2007-05-18 20:38:04Z fbraem $
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
#include "js/io/istream.h"
#include "js/io/bistream.h"

using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>bistream</file>
 * <module>io</module>
 * <class name="wxBufferedInputStream" prototype="@wxInputStream" version="0.8.2">
 *  An inputstream that caches the input.
 * </class>
 */
BufferedInputStream::BufferedInputStream(wxInputStream &s
                                         , wxStreamBuffer *buffer)
                            : wxBufferedInputStream(s, buffer) 
{
}

ZZZJS_INIT_CLASS(BufferedInputStream, "BufferedInputStream", 1)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, BufferedInputStream)
	InputStream::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Input" type="@wxInputStream" />
 *  </function>
 *  <desc>
 *   Creates a new wxBufferedInputStream object.
 *  </desc>
 * </ctor>
 */
//Stream* BufferedInputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(Stream, BufferedInputStream)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if (    argc == 0 
         || argc  > 2 )
        return NULL;

    Stream *in = InputStream::GetPrivate(cx, argv[0]);
    if ( in == NULL )
        return NULL;

	// This is needed, because otherwise the stream can be garbage collected.
	// Another method could be to root the stream, but how are we going to unroot it?
	JS_DefineProperty(cx, obj, "__stream__", argv[0], NULL, NULL, JSPROP_READONLY);

    wxStreamBuffer *buffer = NULL;

    BufferedInputStream *stream = new BufferedInputStream(*((wxInputStream*) in->GetStream()), buffer);
    stream->SetClientObject(new JavaScriptClientData(cx, obj, false, true));

    stream->m_refStream = *in;

    return new Stream(stream);
}
ZZZJS_END_CONSTRUCTOR

//void BufferedInputStream::Destruct(JSContext *cx, Stream *p)
ZZZJS_BEGIN_DESTRUCTOR(Stream, BufferedInputStream)
{
    if ( p != NULL )
    {
        BufferedInputStream *stream = (BufferedInputStream*) p->GetStream();

        // Keep stream alive for a moment, so that the base class wxBufferedOutputStream 
        // doesn't crash when it flushes the stream.
        Stream tempRefStream(stream->m_refStream);

        delete p;
        p = NULL;
    }
}
ZZZJS_END_DESTRUCTOR
