/*
 * wxJavaScript - stream.cpp
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
 * $Id: stream.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// stream.cpp
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



using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>streambase</file>
 * <module>io</module>
 * <class name="wxStreamBase" version="0.8.2" >
 *  wxStreamBase is a prototype class. It's the prototype of the Stream classes.
 *  See @wxInputStream, @wxOutputStream.
 * </class>
 */
ZZZJS_INIT_CLASS(StreamBase, "StreamBase", 0)

/***
 * <properties>
 *  <property name="lastError" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the last error. 
 *  </property>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true if no error occurred.
 *  </property>
 *  <property name="size" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the size of the stream. For example, for a file it is the size of the file.
 *   There are streams which do not have size by definition, such as socket streams. 
 *   In these cases, size returns 0.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(StreamBase)
    ZZZJS_READONLY_PROPERTY(P_OK, "ok")
    ZZZJS_READONLY_PROPERTY(P_SIZE, "size")
    ZZZJS_READONLY_PROPERTY(P_LAST_ERROR, "lastError")
ZZZJS_END_PROPERTY_MAP()

//bool StreamBase::GetProperty(Stream *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(Stream, StreamBase)
    wxStreamBase *stream = p->GetStream();
    switch (id)
    {
    case P_OK:
        ToJSVal(cx, vp, stream->IsOk());
        break;
    case P_SIZE:
        ToJSVal(cx, vp, (long) stream->GetSize());
        break;
    case P_LAST_ERROR:
        ToJSVal(cx, vp, (int) stream->GetLastError());
        break;
    }
    return true;
ZZZJS_END_GET_PROP
