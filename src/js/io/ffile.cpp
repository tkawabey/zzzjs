/*
 * wxJavaScript - ffile.cpp
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
 * $Id: ffile.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// file.cpp
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/archive.h>
#include <wx/strconv.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/jsmembuf.h"
#include "js/io/ffile.h"




using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>ffile</file>
 * <module>io</module>
 * <class name="wxFFile">
 *	 A wxFFile performs raw file I/O. 
 *   This is a very small class designed to minimize the overhead of using it - 
 *   in fact, there is hardly any overhead at all, but using it brings you 
 *   automatic error checking and hides differences between platforms.
 *   It wraps inside it a FILE * handle used by standard C IO library (also known as stdio).
 *   <br /><br /><b>Remark :</b> 
 *   A FILE* structure can't be used directly in JavaScript. That's why some methods are not
 *   ported.
 * </class>
 */
ZZZJS_INIT_CLASS(FFile, "FFile", 0)

/***
 * <constants>
 *  <type name="wxFileKind">
 *   <constant name="KIND_UNKNOWN" />
 *   <constant name="KIND_DISK" />
 *   <constant name="KIND_TERMINAL" />
 *   <constant name="KIND_PIPE" />
 *  </type>
 *  <type name="wxSeekMode">
 *   <constant name="FromCurrent" />
 *   <constant name="FromStart" />
 *   <constant name="FromEnd" />
 *  </type>
 * </constants>
 */
ZZZJS_BEGIN_CONSTANT_MAP(FFile)
    ZZZJS_CONSTANT(wxFILE_, KIND_UNKNOWN)
    ZZZJS_CONSTANT(wxFILE_, KIND_DISK)
    ZZZJS_CONSTANT(wxFILE_, KIND_TERMINAL)
    ZZZJS_CONSTANT(wxFILE_, KIND_PIPE)
	ZZZJS_CONSTANT(wx, FromCurrent)
	ZZZJS_CONSTANT(wx, FromStart)
	ZZZJS_CONSTANT(wx, FromEnd)
ZZZJS_END_CONSTANT_MAP()

/***
 * <properties>
 *	<property name="eof" type="Boolean" readonly="Y">
 *	 True when end of file is reached. When the file is not open, undefined is returned.
 *  </property>
 *  <property name="kind" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns the type of the file
 *  </property>
 *	<property name="opened" type="Boolean" readonly="Y">
 *	 True when the file is open.
 *  </property>
 *	<property name="length" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the length of the file. When the file is not open, undefined is returned.
 *  </property>
 *	<property name="tell" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the current position or -1 (invalid offset).
 *   When the file is not open, undefined is returned.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(FFile)
	ZZZJS_READONLY_PROPERTY(P_EOF, "eof")
	ZZZJS_READONLY_PROPERTY(P_KIND, "kind")
	ZZZJS_READONLY_PROPERTY(P_OPENED, "opened")
	ZZZJS_READONLY_PROPERTY(P_LENGTH, "length")
	ZZZJS_READONLY_PROPERTY(P_TELL, "tell")
ZZZJS_END_PROPERTY_MAP()

//bool FFile::GetProperty(wxFFile *p, 
//                        JSContext *cx, 
//                        JSObject *obj, 
//                        int id, 
//                        JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxFFile, FFile)
	switch(id)
	{
	case P_EOF:
		if ( p->IsOpened() )
			ToJSVal(cx, vp, p->Eof());
		else
			vp.setNull();
			//vp = JSVAL_VOID;
		break;
	case P_KIND:
		ToJSVal(cx, vp, (int) p->GetKind());
		break;
	case P_OPENED:
		ToJSVal(cx, vp, p->IsOpened());
		break;
	case P_LENGTH:
		if ( p->IsOpened() )
			ToJSVal(cx, vp, (int) p->Length());
		else
			vp.setNull();
			//vp = JSVAL_VOID;
		break;
	case P_TELL:
		if ( p->IsOpened() )
			ToJSVal(cx, vp, (int) p->Tell());
		else
			vp.setNull();
			//vp = JSVAL_VOID;
		break;
	}
	return true;
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="name" type=ZZZJS_TYPE_STRING>Filename</arg>
 *   <arg name="mode" type=ZZZJS_TYPE_STRING default="r">
 *    The mode in which to open the file
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a new wxFFile object
 *  </desc>
 * </ctor>
 */
//wxFFile *FFile::Construct(JSContext *cx, 
//						unsigned int argc, 
//						JS::Value *vp, 
//						bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxFFile, FFile)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc > 2 )
	    argc = 2;

    if ( argc == 0 )
        return new wxFFile();

	wxString fileName;
    wxString mode = wxT("r"); 
    if ( argc == 2 )
        FromJS(cx, argv[1], mode);

	FromJS(cx, argv[0], fileName);

    return new wxFFile(fileName, mode);
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(FFile)
	ZZZJS_METHOD("close", close, 0)
	ZZZJS_METHOD("flush", flush, 0)
	ZZZJS_METHOD("open", open, 2)
	ZZZJS_METHOD("read", read, 1)
	ZZZJS_METHOD("readAll", readAll, 0)
	ZZZJS_METHOD("seek", seek, 2)
	ZZZJS_METHOD("seekEnd", seekEnd, 1)
	ZZZJS_METHOD("write", write, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="close">
 *  <function returns="Boolean" />
 *  <desc>
 *   Closes the file.
 *  </desc>
 * </method>
 */
JSBool FFile::close(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxFFile"));

	if ( p->IsOpened() )
		*vp = ToJS(cx, p->Close());
	else
		*vp = JSVAL_FALSE;

	return JS_TRUE;
}

/***
 * <method name="flush">
 *  <function returns="Boolean" />
 *  <desc>
 *   Flushes the file.
 *  </desc>
 * </method>
 */
JSBool FFile::flush(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxFFile"));

	if ( p->IsOpened() )
		*vp = ToJS(cx, p->Flush());
	else
		*vp = JSVAL_FALSE;

	return JS_TRUE;
}

/***
 * <method name="open">
 *  <function returns="Boolean">
 *   <arg name="Filename" type=ZZZJS_TYPE_STRING>Name of the file</arg>
 *   <arg name="Mode" type=ZZZJS_TYPE_STRING default="r">The mode in which to open the file</arg>
 *  </function>
 *  <desc>
 *   Opens a file.
 *  </desc>
 * </method>
 */
JSBool FFile::open(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxString fileName;
    wxString mode = wxT("r"); 
    if ( argc == 2 )
        FromJS(cx, argv[1], mode);

    FromJS(cx, argv[0], fileName);

    *vp = ToJS(cx, p->Open(fileName, mode));
	return JS_TRUE;
}

/***
 * <method name="read">
 *  <function returns="@wxMemoryBuffer">
 *   <arg name="Count" type=ZZZJS_TYPE_NUMBER>The number of bytes to read.</arg>
 *  </function>
 *  <desc>
 *   Reads the specified number of bytes.
 *  </desc>
 * </method>
 */
JSBool FFile::read(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxFFile"));

	if ( ! p->IsOpened() )
	{
		return JS_FALSE;
	}
	int count;
	if (    FromJS(cx, argv[0], count) 
		 && count > 0 )
	{
		unsigned char *buffer = new unsigned char[count];
		int readCount = p->Read(buffer, count);
		if ( readCount == wxInvalidOffset )
		{
			*vp = JSVAL_VOID;
		}
		else
		{
            *vp = zzzJs::ext::CreateMemoryBuffer(cx, buffer, count);
		}
		delete[] buffer;


		return JS_TRUE;
	}

    return JS_FALSE;
}

/***
 * <method name="readAll">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="encoding" type=ZZZJS_TYPE_STRING default="UTF-8">
 *    The encoding of the file.
 *   </arg>
 *  </function>
 *  <desc>
 *   Reads all the data and return it in a String. Internally JavaScript
 *   stores the Strings as UTF-16. But because most files are stored
 *   in UTF-8 or ASCII, the default of the encoding is UTF-8. 
 *  </desc>
 * </method>
 */
JSBool FFile::readAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    if ( ! p->IsOpened() )
	{
		return JS_FALSE;
	}

    wxString encoding(WXJS_EXTERNAL_ENCODING);
    if ( argc > 0 )
    {
        FromJS(cx, argv[0], encoding);
    }
    wxCSConv conv(encoding);

    wxString data;
    if ( p->ReadAll(&data, conv) )
    {
        *vp = ToJS(cx, data);
        return JS_TRUE;
    }

    return JS_FALSE;
}

/***
 * <method name="seek">
 *  <function returns="Boolean">
 *   <arg name="Offset" type=WXJS_TYPE_NUMBER>Offset to seek to</arg>
 *   <arg name="Mode" type="@wxFFile#wxSeekMode" default="wxFFile.FromStart" />
 *  </function>
 *  <desc>
 *   Seeks the offset. Returns the actual position or -1 on error.
 *  </desc>
 * </method>
 */
JSBool FFile::seek(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxFFile"));

	if ( ! p->IsOpened() )
	{
		return JS_FALSE;
	}
    
    int offset;
	if ( ! FromJS(cx, argv[0], offset) )
	{
		return JS_FALSE;
	}

	int pos;

	if ( argc > 1 )
	{
		int mode;
		if ( FromJS(cx, argv[1], mode) )
		{
			pos = p->Seek((wxFileOffset) offset, (wxSeekMode) mode);
		}
		else
		{
			return JS_FALSE;
		}
	}
	else
	{
		pos = p->Seek((wxFileOffset) offset);
	}
	*vp = ToJS(cx, pos);
	return JS_TRUE;
}

/***
 * <method name="seekEnd">
 *  <function returns="Boolean">
 *   <arg name="Offset" type=WXJS_TYPE_NUMBER>Offset to seek to.</arg>
 *  </function>
 *  <desc>
 *   Moves the file pointer to the specified number of bytes before the end of the file.
 *   Returns true on success.
 *  </desc>
 * </method>
 */
JSBool FFile::seekEnd(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxFFile"));

	if ( ! p->IsOpened() )
	{
		return JS_FALSE;
	}

    int offset;
	if ( FromJS(cx, argv[0], offset) )
	{
		*vp = ToJS(cx, p->SeekEnd((wxFileOffset) offset));
		return JS_TRUE;
	}

	return JS_FALSE;
}

/***
 * <method name="write">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Buffer" type="@wxMemoryBuffer" />
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Str" type=WXJS_TYPE_STRING />
 *   <arg name="Encoding" type=WXJS_TYPE_STRING default="UTF-8" />
 *  </function>
 *  <desc>
 *   Writes the string or buffer to the file. When you write
 *   a String you can specify an encoding. Because most files
 *   are still written as UTF-8 or ASCII, UTF-8 is the default
 *   (wxJS uses UTF-16 internally).
 *   Returns the actual number of bytes written to the file when
 *   a buffer is used. Otherwise a boolean indicating
 *   success or failure is returned.
 *  </desc>
 * </method>
 */
JSBool FFile::write(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFFile *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxFFile"));

	if ( ! p->IsOpened() )
	{
		return JS_FALSE;
	}

	if ( argv[0].isObject() )
	{
        wxMemoryBuffer* buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[0]));
		if ( buffer != NULL )
		{
			*vp = ToJS(cx, p->Write(buffer->GetData(), buffer->GetDataLen()));
		}
	}
	else
	{
        wxString encoding(WXJS_EXTERNAL_ENCODING);
        if ( argc > 1 )
        {
            FromJS(cx, argv[1], encoding);
        }
        wxCSConv conv(encoding);
		wxString content;
		FromJS(cx, argv[0], content);
		*vp = ToJS(cx, (int) p->Write(content, conv));
	}
	return JS_TRUE;
}
