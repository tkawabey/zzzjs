/*
 * wxJavaScript - sostream.cpp
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
 * $Id: sostream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/sockbase.h"
#include "js/io/sostream.h"
#include "js/io/ostream.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>sostream</file>
 * <module>io</module>
 * <class name="wxSocketOutputStream" prototype="@wxOutputStream" version="0.8.4">
 *  This class implements an output stream which writes data from a connected socket.
 *  Note that this stream is purely sequential and it does not support seeking.
 * </class>
 */
ZZZJS_INIT_CLASS(SocketOutputStream, "SocketOutputStream", 1)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, SocketOutputStream)
	OutputStream::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Socket" type="@wxSocketBase">A socket</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxSocketOutputStream object.
 *  </desc>
 * </ctor>
 */
//Stream* SocketOutputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(Stream, SocketOutputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    if ( SocketBase::HasPrototype(cx, argv[0]) )
    {
        SocketBasePrivate *base = SocketBase::GetPrivate(cx, argv[0], false);
		// This is needed, because otherwise the socket can be garbage collected.
		// Another method could be to root socket, but how are we going to unroot it?
		JS_DefineProperty(cx, obj, "__socket__", argv[0], NULL, NULL, JSPROP_READONLY);

		return new Stream(new wxSocketOutputStream(*base->GetBase()));
    }
    return NULL;
ZZZJS_END_CONSTRUCTOR
