// jsmembuf.cpp
#include "precompile.h"


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/ext/jsmembuf.h"
#include "js/common/conf.h"
#include "js/common/defs.h"
#include <wx/string.h>

using namespace zzzJs;
using namespace ext;

/***
 * <file>memorybuffer</file>
 * <module>ext</module>
 * <class name="wxMemoryBuffer">
 *  A wxMemoryBuffer is a useful data structure for storing arbitrary sized blocks of memory.
 *  <br />
 *  <br />
 *  You can access the data of the buffer as a JavaScript array.
 *  For example:<br />
 *  <pre><code class="whjs">
 *   var buffer = new wxMemoryBuffer(10);
 *   buffer[0] = 10;
 *   buffer[1] = 'a';
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(MemoryBuffer, "MemoryBuffer", 0)

/***
 * <properties>
 *  <property name="isNull" type="Boolean" readonly="Y">
 *   Is the buffer null? (dataLen and bufSize are 0).
 *  </property>
 *  <property name="dataLen" type=WXJS_TYPE_NUMBER>
 *   Get/Set the length of the data in the buffer. The length of the data
 *   can be less then the length of the buffer.
 *  </property>
 *  <property name="bufSize" type=WXJS_TYPE_NUMBER>
 *   Get/Set the size of the buffer.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(MemoryBuffer)
	WXJS_PROPERTY(P_DATA_LENGTH, "dataLen")
	WXJS_PROPERTY(P_LENGTH, "bufSize")
	WXJS_READONLY_PROPERTY(P_IS_NULL, "isNull")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxMemoryBuffer, MemoryBuffer)
	if ( id > -1 )
	{
		if ( (unsigned int) id < p->GetDataLen() ) 
		{
			unsigned int *data = (unsigned int*) p->GetData();
			ToJSVal(cx, vp, (int) data[id]);
		}
	}
	else
	{
		switch(id)
		{
		case P_DATA_LENGTH:
			ToJSVal(cx, vp, p->GetDataLen());
			break;
		case P_LENGTH:
			ToJSVal(cx, vp, p->GetBufSize());
			break;
		case P_IS_NULL:
			ToJSVal(cx, vp, p->GetDataLen() == 0 && p->GetBufSize() == 0);
			break;
		}
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxMemoryBuffer, MemoryBuffer)
	if ( id > -1 )
	{
		if ( (unsigned int) id < p->GetDataLen() )
		{
			if ( vp.isString() )
			{
				wxString str;
				FromJS(cx, vp, str);
				if ( str.Length() > 0 )
				{
					char *bufdata = (char *) p->GetData();
					bufdata[id] = str[0];
				}
			}
			else
			{
				int data;
				if ( FromJS(cx, vp, data) )
				{
					char *bufdata = (char *) p->GetData();
					bufdata[id] = data;
				}
			}
		}
	}
	else
	{
		switch(id)
		{
		case P_DATA_LENGTH:
			{
				int length = 0;
				if ( FromJS(cx, vp, length) )
					p->SetDataLen(length);
				break;
			}
		case P_LENGTH:
			{
				int dlength = 0;
				if ( FromJS(cx, vp, dlength) )
					p->SetBufSize(dlength);
				break;
			}
		}
	}
	return true;
WXJS_END_SET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Size" type=WXJS_TYPE_NUMBER default="0">The size of the buffer</arg>
 *  </function>
 *  <function>
 *   <arg name="Str" type=WXJS_TYPE_STRING>A string to fill the buffer</arg>
 *   <arg name="Encoding" type=WXJS_TYPE_STRING default="UTF-16">The encoding to use to put this string in the buffer</arg>
 *  </function>
 *  <desc>
 *   Creates a new wxMemoryBuffer object with the given size or with
 *   string as content.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxMemoryBuffer, MemoryBuffer)
	JS::CallArgs args = CallArgsFromVp(argc, vp);
    if ( args.length() == 0 )
        return new wxMemoryBuffer();

	if (    argc == 1 
         && JSVAL_IS_INT(args[0]) )
	{
		int size = 0;
		if (    FromJS(cx, args[0], size)
		     && size > 0 )
		{
			return new wxMemoryBuffer(size);
		}
	}

    wxString encoding(WXJS_INTERNAL_ENCODING);
    if ( argc > 1 )
    {
        FromJS(cx, args[1], encoding);
    }
    wxString data;
	FromJS(cx, args[0], data);

    wxCharBuffer content;
    if ( encoding.CmpNoCase(WXJS_INTERNAL_ENCODING) == 0 )
    {
        content = data.mb_str();
    }
    else
    {
        wxCSConv conv(encoding);
        content = data.mb_str(conv);
    }

    wxMemoryBuffer *buffer = new wxMemoryBuffer();
    buffer->AppendData(content, data.length());

    return buffer;
WXJS_END_CONSTRUCTOR

WXJS_BEGIN_METHOD_MAP(MemoryBuffer)
	WXJS_METHOD("append", append, 1) 
	WXJS_METHOD("toString", toString, 0) 
WXJS_END_METHOD_MAP()

/***
 * <method name="append">
 *  <function>
 *   <arg name="Byte" type="integer">The byte to add</arg>
 *  </function>
 *  <function>
 *   <arg name="Buffer" type="wxMemoryBuffer">The buffer to add</arg>
 *   <arg name="Size" type=WXJS_TYPE_NUMBER default="Buffer.size">The size of the buffer to add. When not set, the full buffer is added.</arg>
 *  </function>
 *  <desc>
 *   Concatenate a byte or buffer to this buffer.
 *  </desc>
 * </method>
 */
JSBool MemoryBuffer::append(JSContext *cx, unsigned argc, JS::Value *vp)
{

    JS::CallArgs args = CallArgsFromVp(argc, vp);
	// プライベートデータの取得
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    if (!obj) {
        return JS_FALSE;
	}	


	wxMemoryBuffer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	if ( JSVAL_IS_INT(args[0]) )
	{
		int byte;
		FromJS(cx, args[0], byte);
		p->AppendByte((char) byte);
		return JS_TRUE;
	}

	if( args[0].isObject() ) 
//	if ( JSVAL_IS_OBJECT(args[0]) )
	{
		wxMemoryBuffer *buffer = GetPrivate(cx, args[0], false);
		if ( buffer != NULL )
		{
			if ( argc > 1 )
			{
				int size;
				if ( FromJS(cx, args[1], size) )
				{
					if ( size > (int) buffer->GetDataLen() )
						size = buffer->GetDataLen();
					p->AppendData(buffer->GetData(), size);
				}
				else
				{
					return JS_FALSE;
				}
			}
			else
			{
				p->AppendData(buffer->GetData(), buffer->GetDataLen());
				return JS_TRUE;
			}
		}
	}

    wxString encoding(WXJS_INTERNAL_ENCODING);
    if ( argc > 1 )
    {
        FromJS(cx, args[1], encoding);
    }

    wxString data;
	FromJS(cx, args[0], data);

    wxCharBuffer content;
    if ( encoding.CmpNoCase(WXJS_INTERNAL_ENCODING) == 0 )
    {
        content = data.mb_str();
    }
    else
    {
        wxCSConv conv(encoding);
        content = data.mb_str(conv);
    }

    p->AppendData(content, data.length());
	
    return JS_TRUE;
}

/***
 * <method name="toString">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Encoding" type=WXJS_TYPE_STRING default="UTF-16">
 *    The encoding of the string in this buffer.
 *   </arg>
 *  </function>
 *  <desc>
 *   Converts the content in the buffer to a String. 
 *   The default encoding is UTF-16 because in JavaScript all strings
 *   are stored in UTF-16. A conversion is done to UTF-16,
 *   when another encoding is specified.
 *  </desc>
 * </method>
 */
JSBool MemoryBuffer::toString(JSContext *cx, unsigned argc, JS::Value *vp)
{
    JS::CallArgs args = CallArgsFromVp(argc, vp);
	// プライベートデータの取得
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    if (!obj) {
        return JS_FALSE;
	}	


	wxMemoryBuffer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

    wxString encoding(WXJS_INTERNAL_ENCODING);
    if ( argc > 0 )
        FromJS(cx, args[0], encoding);
    
    wxCSConv conv(encoding);
    wxString content((const char*) p->GetData(), conv, p->GetDataLen());

	*vp = ToJS(cx, content);

	return JS_TRUE;
}
