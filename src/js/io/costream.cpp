/*
 * wxJavaScript - costream.cpp
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
 * $Id: costream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/stream.h"
#include "js/io/costream.h"
#include "js/io/ostream.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>costream</file>
 * <module>io</module>
 * <class name="wxCountingOutputStream" prototype="@wxOutputStream" version="0.8.2">
 *  wxCountingOutputStream is a specialized output stream which does not write any data anyway,
 *  instead it counts how many bytes would get written if this were a normal stream. 
 *  This can sometimes be useful or required if some data gets serialized to a stream or 
 *  compressed by using stream compression and thus the final size of the stream cannot be 
 *  known other than pretending to write the stream. One case where the resulting size would 
 *  have to be known is if the data has to be written to a piece of memory and the memory has 
 *  to be allocated before writing to it (which is probably always the case when writing to a 
 *  memory stream).
 * </class>
 */

ZZZJS_INIT_CLASS(CountingOutputStream, "CountingOutputStream", 0)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(Stream, CountingOutputStream)
	OutputStream::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Creates a new wxCountingOutputStream object.
 *  </desc>
 * </ctor>
 */
//Stream* CountingOutputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
ZZZJS_BEGIN_CONSTRUCTOR(Stream, CountingOutputStream)
    return new Stream(new wxCountingOutputStream());
ZZZJS_END_CONSTRUCTOR
