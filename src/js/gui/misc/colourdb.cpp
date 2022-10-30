/*
 * wxJavaScript - colourdb.cpp
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
 * $Id: colourdb.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// colourdb.cpp
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
#include "js/gui/misc/colourdb.h"
#include "js/gui/misc/colour.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>file/colourdb</file>
 * <module>gui</module>
 * <class name="wxColourDatabase">
 *  wxWindows maintains a database of standard RGB colours for a predefined set 
 *  of named colours (such as "BLACK", "LIGHT GREY"). wxColourDatabase is a singleton
 *  and is instantiated when the application starts: wxTheColourDatabase.
 *  An example:
 *  <code class="whjs">
 *   var colour = wxTheColourDatabase.findColour("RED");</code>
 * </class>
 */
ZZZJS_INIT_CLASS(ColourDatabase, "ColourDatabase", 0)
	
ZZZJS_BEGIN_DESTRUCTOR(wxColourDatabase, ColourDatabase)
{

}
ZZZJS_END_DESTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(ColourDatabase)
    ZZZJS_METHOD("find", find, 1)
    ZZZJS_METHOD("findName", findName, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="find">
 *  <function returns="wxColour">
 *   <arg name="Name" type=WXJS_TYPE_STRING>The name of a colour.</arg>
 *  </function>
 *  <desc>
 *   Returns the colour with the given name. <I>undefined</I> is returned 
 *   when the colour does not exist.
 *  </desc>
 * </method>
 */
//JSBool ColourDatabase::find(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(ColourDatabase, find )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxColourDatabase *p = GetPrivate(cx, obj);
    ZZZJS_CHECK_PRIM_NULL( p );
	
	int argIndex = 0;
    wxString name;


	ZZZJS_ARG_FROMJS_CHK_AND_ERROR(name, WXJS_TYPE_STRING);

    // Create a copy of the colour, because the colour pointer is owned by wxWindows.
	wxColour color = p->Find(name);
	if( color.IsOk() ) {
		vp->setNull();
	} else {
		*vp = Colour::CreateObject(cx, new wxColour(color));
	}
    
    return JS_TRUE;
}
ZZZJS_END_METHOD	

/***
 * <method name="findName">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Colour" type="@wxColour" />
 *  </function>
 *  <desc>
 *   Returns the name of the colour. <I>undefined</I> is returned when the colour has no name.
 *  </desc>
 * </method>
 */
//JSBool ColourDatabase::findName(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(ColourDatabase, findName )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxColourDatabase *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL( p );
	
	int argIndex = 0;
	zzzJsPtr<wxColour> apColour;

	ZZZJS_ARG_AP_CHK_AND_ERROR(apColour, Colour);


    wxString name = p->FindName(*(apColour.get()));
	if( name.Length() == 0  ) {
		vp->setNull();
	} else {
		*vp = ToJS(cx, name);
	}

    return JS_TRUE;
}
ZZZJS_END_METHOD
