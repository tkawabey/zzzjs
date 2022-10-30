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
#include "js/common/jsutil.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"

#include "js/gui/misc/size.h"
#include "js/gui/gdi/dc.h"
#include "js/gui/gdi/metafile_dc.h"
#include "js/gui/gdi/memory_dc.h"
#include "js/gui/gdi/metafile.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::gdi;

WXJS_INIT_CLASS(MetafileDC, "MetafileDC", 0)

	


WXJS_BEGIN_GET_SET_STR_PROP(wxMetafileDC, MetafileDC)
	DC::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">The parent window</arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>A windows identifier. Use -1 when you don't need it.</arg>
 *   <arg name="Bitmap" type="@wxBitmap">The bitmap to display</arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">The position of the control on the given parent</arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">The size of the control</arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxButton.AUTO_DRAW">The style of the control</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxMetafileDC object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxMetafileDC, MetafileDC)
{

	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxString filename = wxEmptyString;

	if( argc >= 1 ) {

		if( FromJS(cx, argv[0], filename) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return NULL;
		}
	}
	return new wxMetafileDC(filename);
}
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxMetafileDC, MetafileDC)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(MetafileDC)
	WXJS_METHOD("close", close, 0)
WXJS_END_METHOD_MAP()



JSBool MetafileDC::close(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxMetafileDC *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxMetafile * pMetaFile = p->Close();
	if( pMetaFile == NULL ) {
		vp->setNull();
	} else {
		*vp = Metafile::CreateObject(cx, new wxMetaFile( *pMetaFile ), NULL);
	}
	return JS_TRUE;
}

