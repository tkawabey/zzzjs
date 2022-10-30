/*
 * wxJavaScript - mistream.cpp
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
 * $Id: mistream.cpp 759 2007-06-12 21:13:52Z fbraem $
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
#include "js/io/stream.h"
#include "js/io/mistream.h"
#include "js/io/istream.h"





using namespace zzzJs;
using namespace zzzJs::io;

MemoryInputStream::MemoryInputStream(char *data
									 , size_t len) : wxMemoryInputStream(data, len)
                                                   , m_data(data)
{
}

MemoryInputStream::~MemoryInputStream()
{
    delete[] m_data;
}

/***
 * <file>mistream</file>
 * <module>io</module>
 * <class name="wxMemoryInputStream" version="0.8.3" prototype="@wxInputStream">
 *  wxMemoryInputStream allows an application to create an input stream
 *  in which the bytes read are supplied by a memory buffer or a string.
 *  See also @wxMemoryOutputStream.
 * </class>
 */
ZZZJS_INIT_CLASS(MemoryInputStream, "MemoryInputStream", 1)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, MemoryInputStream)
	InputStream::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Data" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <function>
 *   <arg name="Buffer" type="@wxMemoryBuffer" />
 *  </function>
 *  <desc>
 *   Constructs a new wxMemoryInputStream object. A copy is created
 *   of the data and passed to the stream.
 *   <br /><br />
 *   When a String is used, the string is stored as UTF-16!
 *  </desc>
 * </ctor>
 */
//Stream* MemoryInputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(Stream, MemoryInputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argv[0].isObject() )
	{
		wxMemoryBuffer* buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[0]));
		if ( buffer != NULL )
		{
			char *dataPtr = new char[buffer->GetDataLen()];
			memcpy(dataPtr, buffer->GetData(), buffer->GetDataLen());
            MemoryInputStream *mis = new MemoryInputStream(dataPtr, (size_t) buffer->GetDataLen());
            mis->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
			return new Stream(mis);
		}		
	}

	wxString data;
	FromJS(cx, argv[0], data);

    wxMBConvUTF16 utf16;
    int length = utf16.WC2MB(NULL, data, 0);
    if ( length > 0 )
    {
        char *buffer = new char[length + utf16.GetMBNulLen()];
        length = utf16.WC2MB(buffer, data, length + utf16.GetMBNulLen());
        MemoryInputStream *mis = new MemoryInputStream(buffer, length);
        mis->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
    	return new Stream(mis);
    }
    return NULL;
ZZZJS_END_CONSTRUCTOR
