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
 * $Id: init.cpp 625 2007-03-16 20:42:02Z fbraem $
 */
#include "precompile.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <jsapi.h>

#include "js/sqlite/zzzjs_sqlite_init.h"
#include "js/sqlite/db.h"
#include "js/sqlite/stmt.h"

using namespace zzzJs::sqlite;

bool zzzJs::sqlite::InitClass(JSContext *cx, JSObject *global)
{
    JSObject *namespaceObj = JS_DefineObject(cx, global, "sqlite", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	Database::define_Class(cx, namespaceObj);
    Statement::define_Class(cx, namespaceObj);
    return true;
}

bool zzzJs::sqlite::InitObject(JSContext* WXUNUSED(cx), JSObject* WXUNUSED(global))
{
    return true;
}

void zzzJs::sqlite::Destroy()
{
}
