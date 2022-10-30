/*
 * wxJavaScript - init.cpp
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
 * $Id: init.cpp 644 2007-03-27 20:31:33Z fbraem $
 */
#include "precompile.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"

#include <jsapi.h>

#include "js/expat/zzzjs_expat_init.h"
#include "js/expat/parser.h"
#include "js/expat/attr.h"

using namespace zzzJs::xml;

bool zzzJs::xml::InitClass(JSContext *cx, JSObject *global)
{
    JSObject *namespaceObj = JS_DefineObject(cx, global, "expat", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	Parser::define_Class(cx, namespaceObj);
    Attr::define_Class(cx, namespaceObj);
    return true;
}

bool zzzJs::xml::InitObject(JSContext *cx, JSObject *global)
{
	Parser::define_Class(cx, global);
    Attr::define_Class(cx, global);
    return true;
}

void zzzJs::xml::Destroy()
{
}
