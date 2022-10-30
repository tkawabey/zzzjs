/*
 * wxJavaScript - tistream.cpp
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
 * $Id: tistream.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/tistream.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>tistream</file>
 * <module>io</module>
 * <class name="wxTextInputStream" version="0.8.2">
 *  This class provides functions that read text datas using an input stream. 
 *  So, you can read text, floats and integers. wxTextInputStream correctly reads
 *  text files (or streams) in DOS, Macintosh and Unix formats and reports a 
 *  single newline char as a line ending.
 *  <br /><br />The following example uses a @wxMemoryInputStream and makes an array which
 *  contains all words of the given string.
 *
 *  <pre><code class="whjs">
 *  var m = new wxMemoryInputStream("This is a test");
 *  var t = new wxTextInputStream(m);
 *  var words = new Array();
 *  for(var i = 0; ! m.eof; i++)
 *  {
 *    words[i] = t.readWord();
 *  }
 *  </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(TextInputStream, "TextInputStream", 1)

TextInputStream::TextInputStream(wxInputStream &stream, 
                                 const wxString &sep, 
                                 wxMBConv& conv) : wxTextInputStream(stream, sep, conv)
{
}

/***
 * <ctor>
 *  <function>
 *   <arg name="Input" type="@wxInputStream">An input stream</arg>
 *   <arg name="Sep" type=ZZZJS_TYPE_STRING>The initial string separator</arg>
 *   <arg name="Encoding" type=ZZZJS_TYPE_STRING default="UTF-8">The encoding used to convert bytes</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxTextInputStream object.
 *  </desc>
 * </ctor>
 */
//TextInputStream* TextInputStream::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(TextInputStream, TextInputStream)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc > 3 )
        argc = 3;

    wxString encoding(WXJS_EXTERNAL_ENCODING);
    wxString sep = wxT("\t");
    switch(argc)
    {
    case 3:
        FromJS(cx, argv[2], encoding);
        // Fall through
    case 2:
        FromJS(cx, argv[1], sep);
        // Fall through
    default:
        {
            wxCSConv conv(encoding);
            Stream *in = InputStream::GetPrivate(cx, argv[0]);
            if ( in == NULL )
                return NULL;

	        JS_DefineProperty(cx, obj, "__stream__", argv[0], NULL, NULL, 0);

	        return new TextInputStream(*(wxInputStream *) in->GetStream(), sep, conv);
        }
    }

    return NULL;
ZZZJS_END_CONSTRUCTOR

/***
 * <properties>
 *  <property name="stringSeparators" type=ZZZJS_TYPE_STRING>
 *   Gets/Sets the characters which are used to define the word boundaries in 
 *   See @wxTextInputStream#readWord. The default separators are the space and TAB characters.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(TextInputStream)
    ZZZJS_PROPERTY(P_STRING_SEPARATORS, "stringSeparators")
ZZZJS_END_PROPERTY_MAP()

//bool TextInputStream::GetProperty(TextInputStream *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(TextInputStream, TextInputStream)
    if ( id == P_STRING_SEPARATORS )
    {
        ToJSVal(cx, vp, p->GetStringSeparators());
    }
    return true;
ZZZJS_END_GET_PROP

//bool TextInputStream::SetProperty(TextInputStream *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(TextInputStream, TextInputStream)
    if ( id == P_STRING_SEPARATORS )
    {
        wxString sep;
        FromJS(cx, vp, sep);
        p->SetStringSeparators(sep);
    }
    return true;
ZZZJS_END_SET_PROP

ZZZJS_BEGIN_METHOD_MAP(TextInputStream)
    ZZZJS_METHOD("read32", read32, 0)
    ZZZJS_METHOD("read16", read16, 0)
    ZZZJS_METHOD("read8", read8, 0)
    ZZZJS_METHOD("readLine", readLine, 0)
    ZZZJS_METHOD("readDouble", readDouble, 0)
    ZZZJS_METHOD("readWord", readWord, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="read32">
 *  <function returns=ZZZJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 32 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool TextInputStream::read32(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextInputStream *p = TextInputStream::GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint32 value = p->Read32();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (int) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="read16">
 *  <function returns=ZZZJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 16 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool TextInputStream::read16(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextInputStream *p = TextInputStream::GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint16 value = p->Read16();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (int) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="read8">
 *  <function returns=ZZZJS_TYPE_NUMBER />
 *  <desc>
 *   Reads a 8 bit integer from the stream.
 *  </desc>
 * </method>
 */
JSBool TextInputStream::read8(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextInputStream *p = TextInputStream::GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxUint8 value = p->Read8();

// Check this for other platforms!
#ifdef __WXMSW__
    *vp = ToJS(cx, (int) value);
#else
    *vp = ToJS(cx, (int) value);
#endif

    return JS_TRUE;
}

/***
 * <method name="readDouble">
 *  <function return=ZZZJS_TYPE_DOUBLE />
 *  <desc>
 *   Reads a double (IEEE encoded) from a stream.
 *  </desc>
 * </method>
 */
JSBool TextInputStream::readDouble(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextInputStream *p = TextInputStream::GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->ReadDouble());

    return JS_TRUE;
}

/***
 * <method name="readLine">
 *  <function returns=ZZZJS_TYPE_STRING />
 *  <desc>
 *   Reads from the input stream until an end-of-line character is read.
 *   The end-of-line character is not returned.
 *  </desc>
 * </method>
 */
JSBool TextInputStream::readLine(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    TextInputStream *p = TextInputStream::GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->ReadLine());
    return JS_TRUE;
}

/***
 * <method name="readWord">
 *  <function returns=ZZZJS_TYPE_STRING />
 *  <desc>
 *   Reads a word (a sequence of characters until the next separator) from the input stream.
 *   See @wxTextInputStream#stringSeparators.
 *  </desc>
 * </method>
 */
JSBool TextInputStream::readWord(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxTextInputStream *p = TextInputStream::GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->ReadWord());
    return JS_TRUE;
}
