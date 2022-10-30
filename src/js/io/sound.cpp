/*
 * wxJavaScript - sound.cpp
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
 * $Id: sound.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/sound.h"



using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>sound</file>
 * <module>io</module>
 * <class name="wxSound">
 *  This class represents a short sound (loaded from Windows WAV file), that can be stored in memory and played.
 * </class>
 */
ZZZJS_INIT_CLASS(Sound, "Sound", 0)

/***
 * <constants>
 *  <type name="Flags">
 *   <constant name="ASYNC" />
 *   <constant name="LOOP" />
 *   <constant name="SYNC" />
 *  </type>
 * </constants>
 */
ZZZJS_BEGIN_CONSTANT_MAP(Sound)
    ZZZJS_CONSTANT(wxSOUND_, SYNC)
    ZZZJS_CONSTANT(wxSOUND_, ASYNC)
    ZZZJS_CONSTANT(wxSOUND_, LOOP)
ZZZJS_END_CONSTANT_MAP()

ZZZJS_BEGIN_STATIC_METHOD_MAP(Sound)
    ZZZJS_METHOD("stop", stop, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <class_method name="stop">
 *  <function />
 *  <desc>
 *   Stops the sound
 *  </desc>
 * </class_method>
 */
JSBool Sound::stop(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxSound::Stop();
    return JS_TRUE;
}

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Filename" type=ZZZJS_TYPE_STRING>The name of the soundfile.</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxSound object. When no argument is specified, use @wxSound#create
 *   afterwards.
 *  </desc>
 * </ctor>
 */
//wxSound* Sound::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxSound, Sound)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    if ( argc == 0 )
        return new wxSound();

    if ( argc == 1 )
    {
        wxString f;
        FromJS(cx, argv[0], f);
        return new wxSound(f);
    }

    return NULL;
ZZZJS_END_CONSTRUCTOR

/***
 * <properties>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true when the soundfile is successfully loaded.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Sound)
    ZZZJS_READONLY_PROPERTY(P_OK, "ok")
ZZZJS_END_PROPERTY_MAP()

//bool Sound::GetProperty(wxSound *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxSound, Sound)
    if ( id == P_OK )
        ToJSVal(cx, vp, p->IsOk());
    return true;
ZZZJS_END_GET_PROP

ZZZJS_BEGIN_METHOD_MAP(Sound)
    ZZZJS_METHOD("play", play, 0)
    ZZZJS_METHOD("create", create, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="FileName" type=ZZZJS_TYPE_STRING>The name of the soundfile</arg>
 *  </function>
 *  <desc>
 *   Constructs a sound object.
 *  </desc>
 * </method>
 */
JSBool Sound::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSound *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString file;
	FromJS(cx, argv[0], file);
	*vp = ToJS(cx, p->Create(file));

    return JS_TRUE;
}

/***
 * <method name="play">
 *  <function returns="Boolean">
 *   <arg name="Flags" default="wxSound.ASYNC" />
 *  </function>
 *  <desc>
 *   Plays the sound.
 *  </desc>
 * </method>
 */
JSBool Sound::play(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSound *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int flag = wxSOUND_ASYNC;
	if ( argc > 0 )
	{
		if ( ! FromJS(cx, argv[0], flag) )
			return JS_FALSE;
	}
	*vp = ToJS(cx, p->Play((unsigned int) flag));

    return JS_TRUE;
}
