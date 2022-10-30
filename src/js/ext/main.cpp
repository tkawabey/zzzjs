/*
 * wxJavaScript - main.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
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
 * $Id: main.cpp 810 2007-07-13 20:07:05Z fbraem $
 */


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#include <wx/wx.h>

#ifdef __WXMSW__
	#include <windows.h>
#endif

#include "js/ext/jsmembuf.h"
#include "js/ext/point.h"
#include "js/ext/wxjs_ext.h"

using namespace zzzJs;
using namespace zzzJs::ext;

#ifdef __WXMSW__
	//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
	//{
	//	BOOL result = TRUE;
	//
	//	switch(fdwReason)
	//	{
	//	case DLL_PROCESS_ATTACH:
	//		DisableThreadLibraryCalls(hinstDLL);
	//		break;
	//	case DLL_PROCESS_DETACH:
	//		break;
	//	}    
	//
	//	return result;
	//}
#endif

WXJSAPI bool zzzJs::ext::InitClass(JSContext *cx, JSObject *global)
{
	MemoryBuffer::define_Class(cx, global);
    Point::define_Class(cx, global);

    return true;
}

/***
 * <file>globfun</file>
 * <module>ext</module>
 * <class name="Global Functions">
 *  On this page you can find all the functions/properties that are defined on the global object.
 * </class>
 * <properties>
 *  <property name="wxDefaultPosition" type="@wxPoint">
 *   The default position
 *  </property>
 * </properties>
 */
WXJSAPI bool zzzJs::ext::InitObject(JSContext *cx, JSObject *obj)
{
    Point::DefineObject(cx, obj, "wxDefaultPosition", new wxPoint(wxDefaultPosition));
    return true;
}

WXJSAPI void zzzJs::ext::Destroy()
{
}

WXJSAPI jsval zzzJs::ext::CreateMemoryBuffer(JSContext *cx, void *buffer, int size)
{
  wxMemoryBuffer *membuf = new wxMemoryBuffer(size);
  membuf->AppendData(buffer, size);
  JSObject *obj = JS_NewObject(cx, MemoryBuffer::GetClass(), NULL, NULL);
  if ( obj == NULL )
    return JSVAL_NULL;

  JS_SetPrivate(obj, membuf);
  return OBJECT_TO_JSVAL(obj);
}

WXJSAPI wxMemoryBuffer* zzzJs::ext::GetMemoryBuffer(JSContext *cx, JSObject *obj)
{
	return MemoryBuffer::GetPrivate(cx, obj);
}

WXJSAPI wxMemoryBuffer* zzzJs::ext::GetMemoryBuffer(JSContext *cx, jsval v)
{
  if ( v.isObject() /*JSVAL_IS_OBJECT(v)*/ )
  {
    return GetMemoryBuffer(cx, JSVAL_TO_OBJECT(v));
  }
  return NULL;
}

WXJSAPI wxMemoryBuffer* zzzJs::ext::NewMemoryBuffer(void *buffer, int size)
{
	wxMemoryBuffer *membuf = new wxMemoryBuffer(size);
	membuf->AppendData(buffer, size);
	return membuf;
}

WXJSAPI wxPoint* zzzJs::ext::GetPoint(JSContext *cx, JSObject *obj)
{
	return Point::GetPrivate(cx, obj);
}

WXJSAPI wxPoint* zzzJs::ext::GetPoint(JSContext *cx, jsval v)
{
  if ( v.isObject() /*JSVAL_IS_OBJECT(v)*/ )
  {
    return GetPoint(cx, JSVAL_TO_OBJECT(v));
  }
  return NULL;
}

WXJSAPI jsval zzzJs::ext::CreatePoint(JSContext *cx, const wxPoint &p)
{
  return Point::CreateObject(cx, new wxPoint(p));
}
