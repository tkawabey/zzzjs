/*
 * wxJavaScript - bmpbtn.cpp
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
 * $Id: bmpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/gui/errors.h"
#include "js/gui/pg/pg_arg_id.h"
#include "js/gui/pg/pg_prop.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



bool zzzJs::gui::pg::getGridInterface_ArgID(JSContext *cx, jsval v, int argIndex, GridInterface_ArgID& ret)
{
	if( v.isString() == true ) {
		ret.m_flg = 0;
		if( FromJS(cx, v, ret.str) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex, WXJS_TYPE_STRING);
			return false;
		}
	} else {
		ret.m_flg = 1;
		ret.pProp = Property::GetPrivate(cx, v, false);
		if( ret.pProp == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex, "pg.Property");
			return false;
		}
	}
	return true;
}