/*
 * wxJavaScript - mostream.cpp
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
 * $Id: mostream.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/io/mostream.h"
#include "js/io/ostream.h"


using namespace zzzJs;
using namespace zzzJs::io;

MemoryOutputStream::MemoryOutputStream(char *data
									 , size_t len) : wxMemoryOutputStream(data, len)
                                                   , m_data(data)
{
    if ( m_data == NULL )
        GetOutputStreamBuffer()->SetBufferIO(1024);
}

MemoryOutputStream::~MemoryOutputStream()
{
    delete[] m_data;
}

/***
 * <file>mostream</file>
 * <module>io</module>
 * <class name="wxMemoryOutputStream" prototype="@wxOutputStream" version="0.8.2">
 *  wxMemoryOutputStream collects its output in a buffer which can be converted to a String.
 *  See also @wxMemoryInputStream.
 *  An example:
 *  <pre><code class="whjs">
 *   var mos = new wxMemoryOutputStream();
 *   mos.write("This is a test");
 *  </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(MemoryOutputStream, "MemoryOutputStream", 0)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, MemoryOutputStream)
	OutputStream::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Length" type=ZZZJS_TYPE_NUMBER default="1024">
 *    The length of the buffer used in memory.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxMemoryOutputStream object. When no length is specified, a buffer is 
 *   created with size 1024. If necessary it will grow.
 *  </desc>
 * </ctor>
 */
//Stream* MemoryOutputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(Stream, MemoryOutputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc == 0 )
    {	
      MemoryOutputStream *mos = new MemoryOutputStream(NULL, 0);
      mos->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
      return new Stream(mos);
    }

    int length;
    if ( FromJS(cx, argv[0], length) )
    {
      char *dataPtr = new char[length];
      MemoryOutputStream *mos = new MemoryOutputStream(dataPtr, length);
      mos->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
      return new Stream(mos);
    }

    return NULL;
ZZZJS_END_CONSTRUCTOR

/***
 * <properties>
 *  <property name="data" type="@wxMemoryBuffer" readonly="Y">
 *   Gets the buffer.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(MemoryOutputStream)
    ZZZJS_READONLY_PROPERTY(P_DATA, "data")
ZZZJS_END_PROPERTY_MAP()

//bool MemoryOutputStream::GetProperty(Stream *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(Stream, MemoryOutputStream)
    MemoryOutputStream *mstream = (MemoryOutputStream *) p->GetStream();

    switch(id)
    {
    case P_DATA:
        {
            int size = mstream->GetOutputStreamBuffer()->GetIntPosition();
            char* buffer = new char[size];
            mstream->CopyTo(buffer, size);

			vp.set( zzzJs::ext::CreateMemoryBuffer(cx, buffer, size) );
			delete[] buffer;
            break;
        }
    }
    return true;
ZZZJS_END_GET_PROP
