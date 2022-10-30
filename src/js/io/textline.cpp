/*
 * wxJavaScript - textline.cpp
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
 * $Id: textline.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/textline.h"
#include "js/io/textfile.h"



using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>textline</file>
 * <module>io</module>
 * <class name="wxTextLine" version="0.8.3">
 *  wxTextLine is a helper class. It doesn't exist in wxWidgets,
 *  but wxJS needs it, so you can access lines in @wxTextFile as
 *  an array:
 *  <pre><code class="whjs">
 *   var i;
 *   for(i = 0; i &lt; file.lineCount; i++)
 *   {
 *     file.lines[i].content = ...
 *   }
 *   </code></pre>
 *  or as:
 *  <pre><code class="whjs">
 *   for each(line in textfile.lines)
 *   {
 *      line.content = ...
 *   }</code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(TextLine, "TextLine", 0)

bool TextLine::Resolve(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id)
{
    if (    JSID_IS_INT(id) 
		 && JSID_TO_INT(id) >= 0 )
	{
        return JS_DefineElement(cx, obj, id, INT_TO_JSVAL(0), NULL, NULL, 0) == JS_TRUE;
	}
    return true;
}

/***
 * <properties>
 *  <property name="content" type=ZZZJS_TYPE_STRING>
 *   Get/Set the content of the line.<br /><br />
 *   <b>Remark: </b>When you access this object as an array of @wxTextFile
 *   you don't need this property. You can write:
 *   <code class="whjs">
 *    textfile.lines[1] = 'Text';</code>
 *  </property>
 *  <property name="lineType" type="@wxTextFile#wxTextFileType" readonly="Y">
 *   Get the type of the line
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(TextLine)
	ZZZJS_READONLY_PROPERTY(P_LINE_TYPE, "lineType")
	ZZZJS_PROPERTY(P_CONTENT, "content")
ZZZJS_END_PROPERTY_MAP()

//bool TextLine::GetProperty(Index *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(Index, TextLine)
    JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
    wxASSERT_MSG(parent != NULL, wxT("No parent found for TextLine"));

    wxTextFile *file = TextFile::GetPrivate(cx, parent);
    if ( file == NULL )
        return false;

    if ( id >= 0 && id < (int)file->GetLineCount() )
    {
        p->SetIndex(id);
		vp.set( OBJECT_TO_JSVAL(obj) ); //ToJS(cx, file->GetLine(id));
    }
	else
	{
		switch(id)
		{
		case P_LINE_TYPE:
			ToJSVal(cx, vp, (int) file->GetLineType(p->GetIndex()));
			break;
		case P_CONTENT:
			ToJSVal(cx, vp, file->GetLine(p->GetIndex()));
			break;
		default:
			vp.set(JSVAL_VOID);
//			*vp = JSVAL_VOID;
		}
	}

    return true;
ZZZJS_END_GET_PROP

//bool TextLine::SetProperty(Index *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(Index, TextLine)
    JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
    wxASSERT_MSG(parent != NULL, wxT("No parent found for TextLine"));

    wxTextFile *file = TextFile::GetPrivate(cx, parent);
    if ( file == NULL )
        return false;

    if ( id >= 0 && id < (int)file->GetLineCount() )
    {
        p->SetIndex(id);
		wxString content;
		FromJS(cx, vp, content);
		file->GetLine(id) = content;
    }
	else
	{
		if ( id == P_CONTENT )
		{
			wxString content;
			FromJS(cx, vp, content);
			file->GetLine(p->GetIndex()) = content;
		}
	}
    return true;
ZZZJS_END_SET_PROP

bool TextLine::Enumerate(Index *p, JSContext *cx, JSObject *obj, JSIterateOp enum_op, jsval *statep, jsid *idp)
{
	JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
	if ( parent == NULL )
	{
		*statep = JSVAL_NULL;
        if (idp)
            *idp = INT_TO_JSID(0);
		return true;
	}

	wxTextFile *file = TextFile::GetPrivate(cx, parent);
	if ( file == NULL )
	{
		*statep = JSVAL_NULL;
        if (idp)
            *idp = INT_TO_JSID(0);
		return true;
	}

	bool ok = true;

	switch(enum_op)
	{
	case JSENUMERATE_INIT:
		*statep = ToJS(cx, 0);
		if ( idp )
			*idp = INT_TO_JSID(file->GetLineCount());
		break;
	case JSENUMERATE_NEXT:
		{
			int pos;
			FromJS(cx, *statep, pos);
			if ( pos < (int)file->GetLineCount() )
			{
				JS_ValueToId(cx, ToJS(cx, pos), idp);
				*statep = ToJS(cx, ++pos);
				break;
			}
			// Fall through
		}
	case JSENUMERATE_DESTROY:
		*statep = JSVAL_NULL;
		break;
	default:
		ok = false;
	}
	return ok;
}

ZZZJS_BEGIN_METHOD_MAP(TextLine)
	ZZZJS_METHOD("insert", insertLine, 1)
	ZZZJS_METHOD("remove", removeLine, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="insert">
 *  <function>
 *   <arg name="Line" type=ZZZJS_TYPE_STRING>The line to insert (without the end-of-line character(s)).</arg>
 *   <arg name="Type" type="@wxTextFile#wxTextFileType" default="typeDefault" />
 *  </function>
 *  <desc>
 *   Insert a line before this line.
 *  </desc>
 * </method>
 */
JSBool TextLine::insertLine(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	Index *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxTextLine"));

	JSObject *objParent = JS_GetParent(obj);//JS_GetParent(cx, obj);
	if ( objParent == NULL )
		return JS_FALSE;

	wxTextFile *file = TextFile::GetPrivate(cx, objParent);

	wxString line;
	FromJS(cx, argv[0], line);

	if ( argc > 1 )
	{
		int type;
		if ( ! FromJS(cx, argv[1], type) )
			return JS_FALSE;
		file->InsertLine(line, p->GetIndex(), (wxTextFileType) type);
	}
	else
	{
		file->InsertLine(line, p->GetIndex());
	}
	return JS_TRUE;
}

/***
 * <method name="remove">
 *  <function />
 *  <desc>
 *   Removes this line from the file
 *  </desc>
 * </method>
 */
JSBool TextLine::removeLine(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	Index *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxTextLine"));

	JSObject *objParent = JS_GetParent(obj);//JS_GetParent(cx, obj);
	if ( objParent == NULL )
		return JS_FALSE;

	wxTextFile *file = TextFile::GetPrivate(cx, objParent);

	file->RemoveLine(p->GetIndex());
	return JS_TRUE;
}
