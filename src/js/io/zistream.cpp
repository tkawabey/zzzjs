/*
 * wxJavaScript - zistream.cpp
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
 * $Id: zistream.cpp 759 2007-06-12 21:13:52Z fbraem $
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
#include "js/io/istream.h"
#include "js/io/zistream.h"
#include "js/io/zipentry.h"
#include "js/io/aistream.h"


using namespace zzzJs;
using namespace zzzJs::io;

ZipInputStream::ZipInputStream(wxInputStream &str) : wxZipInputStream(str)
{
}

/***
 * <file>zistream</file>
 * <module>io</module>
 * <class name="wxZipInputStream" protoype="@wxArchiveInputStream" version="0.8.3">
 *  Input stream for reading zip files.
 * </class>
 */
ZZZJS_INIT_CLASS(ZipInputStream, "ZipInputStream", 1)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, ZipInputStream)
	ArchiveInputStream::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Stream" type="@wxInputStream">An input stream</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxZipInputStream object.
 *  </desc>
 * </ctor>
 */
//Stream* ZipInputStream::Construct(JSContext *cx,  
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(Stream, ZipInputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( InputStream::HasPrototype(cx, argv[0]) )
    {
        Stream *in = InputStream::GetPrivate(cx, argv[0], false);

		// This is needed, because otherwise the stream can be garbage collected.
		// Another method could be to root the stream, but how are we going to unroot it?
		JS_DefineProperty(cx, obj, "__stream__", argv[0], NULL, NULL, JSPROP_READONLY);
		
		ZipInputStream *stream = new ZipInputStream(*(wxInputStream*) in->GetStream());
	    stream->m_refStream = *in;
		return new Stream(stream);
    }
    return NULL;
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_DESTRUCTOR(Stream, ZipInputStream)
    if ( p != NULL )
    {
		ZipInputStream *stream = (ZipInputStream*) p->GetStream();

        // Keep stream alive for a moment, so that the base class
        // doesn't crash when it flushes the stream.
        Stream tempRefStream(stream->m_refStream);

        delete p;
        p = NULL;
    }
ZZZJS_END_DESTRUCTOR

/***
 * <properties>
 *  <property name="comment" type=ZZZJS_TYPE_STRING readonly="Y">
 *    The comment of the zip file
 *  </property>
 *  <property name="nextEntry" type="@wxZipEntry" readonly="Y">
 *   Closes the current entry if one is open, then reads the meta-data for the next 
 *   entry and returns it in a @wxZipEntry object. The stream is then open and can be read.
 *  </property>
 *  <property name="totalEntries" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *    The number of entries in the zip file
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(ZipInputStream)
	ZZZJS_READONLY_PROPERTY(P_COMMENT, "comment")
	ZZZJS_READONLY_PROPERTY(P_TOTAL_ENTRIES, "totalEntries")
	ZZZJS_READONLY_PROPERTY(P_NEXT_ENTRY, "nextEntry")
ZZZJS_END_PROPERTY_MAP()

//bool ZipInputStream::GetProperty(Stream *p,   
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(Stream, ZipInputStream)
	wxZipInputStream *in = (wxZipInputStream*) p->GetStream();
	switch(id)
	{
	case P_COMMENT:
		ToJSVal(cx, vp, in->GetComment());
		break;
	case P_TOTAL_ENTRIES:
		ToJSVal(cx, vp, in->GetTotalEntries());
		break;
	case P_NEXT_ENTRY:
		{
			wxZipEntry *entry = in->GetNextEntry();
			if ( entry == NULL )
			{
				vp.set( JSVAL_VOID );
			}
			else
			{
				vp.set( ZipEntry::CreateObject(cx, entry) );
			}
		}
		break;
	}
	return true;
ZZZJS_END_GET_PROP
