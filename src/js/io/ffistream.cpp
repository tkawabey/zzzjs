/*
 * wxJavaScript - ffistream.cpp
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
 * $Id: ffistream.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/wfstream.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/io/ffile.h"
#include "js/io/stream.h"
#include "js/io/ffistream.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>ffistream</file>
 * <module>io</module>
 * <class name="wxFFileInputStream" prototype="@wxInputStream" version="0.8.2">
 *  This class represents data read in from a file. There are actually two such groups of classes: 
 *  this one is based on @wxFFile whereas @wxFileInputStream is based on the @wxFile class.
 * </class>
 */
ZZZJS_INIT_CLASS(FFileInputStream, "FFileInputStream", 1)

/***
 * <ctor>
 *  <function>
 *   <arg name="FileName" type=WXJS_TYPE_STRING>The name of a file</arg>
 *  </function>
 *  <function>
 *   <arg name="FFile" type="@wxFFile" />
 *  </function>
 *  <function>
 *   <arg name="Fd" type=WXJS_TYPE_NUMBER>A file descriptor</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxFFileInputStream object. A wxFFileInputStream is always opened in read-only mode.
 *  </desc>
 * </ctor>
 */
//Stream* FFileInputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(Stream, FFileInputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( FFile::HasPrototype(cx, argv[0]) )
    {
        wxFFile *file = FFile::GetPrivate(cx, argv[0], false);
		// This is needed, because otherwise the file can be garbage collected.
		// Another method could be to root ffile, but how are we going to unroot it?
		JS_DefineProperty(cx, obj, "__ffile__", argv[0], NULL, NULL, JSPROP_READONLY);

        return new Stream(new wxFFileInputStream(*file));
    }
    else if ( JSVAL_IS_STRING(argv[0]) )
    {
        wxString name;
        FromJS(cx, argv[0], name);
        return new Stream(new wxFFileInputStream(name));
    }
    return NULL;
ZZZJS_END_CONSTRUCTOR
