/*
 * wxJavaScript - globfun.cpp
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
 * $Id: globfun.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// globfun.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 





#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/image.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/gui/misc/globfun.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/fontlist.h"
#include "js/gui/misc/colourdb.h"
#include "js/gui/misc/brush.h"
#include "js/gui/misc/pen.h"
#include "js/gui/misc/font.h"

/***
 * <file>misc/globfun</file>
 * <module>gui</module>
 * <class name="Global Functions">
 *  On this page you can find all the functions that are defined on the global object.
 * </class>
 */
static JSFunctionSpec Functions[] =
{
    JS_FS( "MessageBox", zzzJs::gui::MessageBox, 1, 0 ),
    JS_FS( "InitAllImageHandlers", zzzJs::gui::InitAllImageHandlers, 0, 0 ),
	JS_FN( "NewId", zzzJs::gui::NewID, 0, 0),
	JS_FS_END
};

/***
 * <method name="wxMessageBox">
 *  <function>
 *   <arg name="Text" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Shows a modal message box with the given text.
 *  </desc>
 * </method>
 */
JSBool zzzJs::gui::MessageBox(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc == 1 )
	{
        wxString msg;
        FromJS(cx, argv[0], msg);
		wxMessageBox(msg);
		return JS_TRUE;
	}
	return JS_FALSE;
}

/***
 * <method name="wxInitAllImageHandlers">
 *  <function />
 *  <desc>
 *   Initializes all available image handlers. When wxJS is started,
 *   only @wxBMPHandler is instantiated. When you only need one
 *   image handler you can also use @wxImage#addHandler.
 *   <br /><br />
 *   See @wxImage, @wxBMPHandler, @wxGIFHandler, @wxICOHandler, 
 *   @wxJPEGHandler, @wxPCXHandler, @wxPNGHandler, @wxPNMHandler, 
 *   @wxTIFFHandler, @wxXPMHandler
 *  </desc>
 * </method>
 */
JSBool zzzJs::gui::InitAllImageHandlers(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxInitAllImageHandlers();
    return JS_TRUE;
}

JSBool zzzJs::gui::NewID(JSContext *cx, unsigned argc, JS::Value *vp)
{
	vp->setInt32( wxNewId() );
    return JS_TRUE;
}
bool zzzJs::gui::InitFunctions(JSContext *cx, JSObject *global)
{
	JS_DefineFunctions(cx, global, Functions);
	return true;
}
#include "js/ext/point.h"

/***
 * <properties>
 *  <property name="wxDefaultPosition" type="@wxPoint">
 *   The default position
 *  </property>
 *  <property name="wxDefaultSize" type="@wxSize">
 *   The default size
 *  </property>
 *  <property name="wxTheFontList" type="@wxFontList">
 *   The one and only font list object.
 *  </property>
 *  <property name="wxTheColourDatabase" type="@wxColourDatabase">
 *   The one and only colour database.
 *  </property>
 * </properties>
 */
void zzzJs::gui::DefineGlobals(JSContext *cx, JSObject *global)
{
    zzzJs::ext::Point::DefineObject(cx, global, "DefaultPosition", new wxPoint(wxDefaultPosition));
    zzzJs::gui::Size::DefineObject(cx, global, "DefaultSize", new wxSize(wxDefaultSize));
    zzzJs::gui::FontList::DefineObject(cx, global, "TheFontList", wxTheFontList);
    zzzJs::gui::ColourDatabase::DefineObject(cx, global, "TheColourDatabase", wxTheColourDatabase);

    zzzJs::gui::DefineGlobalColours(cx, global);
    zzzJs::gui::DefineGlobalBrushs(cx, global);
	zzzJs::gui::DefineGlobalPens(cx, global);
	zzzJs::gui::DefineGlobalFonts(cx, global);
}
