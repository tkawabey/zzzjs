/*
 * wxJavaScript - control.cpp
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
 * $Id: control.cpp 672 2007-04-12 20:29:39Z fbraem $
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 





#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/control/control.h"
#include "js/gui/control/window.h"



using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/control</file>
 * <module>gui</module>
 * <class name="wxControl" prototype="@wxWindow">
 *  This is the prototype for a control or 'widget'.
 *  A control is generally a small window which processes user input
 *  and/or displays one or more item of data.
 * </class>
 */
WXJS_INIT_CLASS(Control, "Control", 0)

/***
 * <properties>
 *  <property name="label" type=WXJS_TYPE_STRING>
 *   Get/Set the label
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Control)
    WXJS_PROPERTY(P_LABEL, "label")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxControl, Control)
    if ( id == P_LABEL )
        ToJSVal(cx, vp, p->GetLabel());
    return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxControl, Control)
    if ( id == P_LABEL )
    {
        wxString label;
        FromJS(cx, vp, label);
        p->SetLabel(label);
    }
    return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxControl, Control)
	Window::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP


WXJS_BEGIN_METHOD_MAP(Control)
WXJS_END_METHOD_MAP()

WXJS_BEGIN_DESTRUCTOR(wxControl, Control)
WXJS_END_DESTRUCTOR


//TODO: An event can't be created yet, so this function is not used.
JSBool Control::command(JSContext *cx, unsigned argc, JS::Value *vp)
{
    	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

wxControl *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
    return JS_TRUE;
}
