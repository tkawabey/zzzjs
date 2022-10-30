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
#include "js/gui/gdi/buffered_paint_dc.h"
#include "js/gui/gdi/auto_buffered_paint_dc.h"
#include "js/gui/gdi/memory_dc.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/control/window.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::gdi;

WXJS_INIT_CLASS(AutoBufferedPaintDC, "AutoBufferedPaintDC", 1)
	


WXJS_BEGIN_GET_SET_STR_PROP(wxAutoBufferedPaintDC, AutoBufferedPaintDC)
	BufferedPaintDC::SetStringProperty(p, cx,  obj, propertyName, vp);
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
 *   Constructs a new wxAutoBufferedPaintDC object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxAutoBufferedPaintDC, AutoBufferedPaintDC)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	/*
	wxAutoBufferedPaintDC (wxWindow *window)
 		Constructor.
	*/
	int argIndex = 0;
    if ( argc > 3 )
        argc = 3;
	
	// 0
	wxWindow *window = Window::GetPrivate(cx, argv[argIndex], false);
	if( window == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return NULL;
	}
	argIndex++;

	return new wxAutoBufferedPaintDC(window);
}
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxAutoBufferedPaintDC, AutoBufferedPaintDC)

WXJS_END_DESTRUCTOR

