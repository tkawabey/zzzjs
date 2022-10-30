/*
 * wxJavaScript - size.cpp
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
 * $Id: size.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// size.cpp
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
#include "js/common/jsutil.h"
#include "js/gui/misc/size.h"


using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_HEIGHT			"height"
#define PROP_NM_WIDTH			"width"
#define PROP_NM_X				"x"
#define PROP_NM_Y				"y"



/***
 * <file>misc/size</file>
 * <module>gui</module>
 * <class name="wxSize">
 *  A wxSize is a useful data structure for graphics operations. 
 *  It simply contains integer width and height members.
 * </class>
 */
ZZZJS_INIT_CLASS(Size, "Size", 0)

/***
 * <properties>
 *  <property name="height" type=WXJS_TYPE_NUMBER>
 *   The height property.
 *  </property>
 *  <property name="width" type=WXJS_TYPE_NUMBER>
 *   The width property.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Size)
  ZZZJS_PROPERTY(P_WIDTH, PROP_NM_WIDTH)
  ZZZJS_PROPERTY(P_HEIGHT, PROP_NM_HEIGHT)
ZZZJS_END_PROPERTY_MAP()

//bool Size::GetProperty(wxSize *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxSize, Size)
{
    switch (id) 
	{
	case P_WIDTH:
		ToJSVal(cx, vp, p->GetHeight());
		break;
	case P_HEIGHT:
		ToJSVal(cx, vp, p->GetWidth());
		break;
    }
	return true;
}
ZZZJS_END_GET_PROP

//bool Size::SetProperty(wxSize *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxSize, Size)
{
    switch (id) 
	{
	case P_WIDTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetWidth(value);
			break;
		}
	case P_HEIGHT:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetHeight(value);
			break;
		}
	}
    return true;
}
ZZZJS_END_SET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER default="-1">
 *    The width
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER default="-1">
 *     The height. When not specified and Width is specified the value will be 0.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a new wxSize. When no arguments are given then wxSize gets the same value
 *   as wxDefaultSize.
 *  </desc>
 * </ctor>
 */
//wxSize* Size::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
ZZZJS_BEGIN_CONSTRUCTOR(wxSize, Size)
{
	int x = -1;
	int y = -1;
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	if (      argc > 0
		 && ! FromJS(cx, argv[0], x) )
		return NULL;

	if (      argc > 1
		 && ! FromJS(cx, argv[1], y) )
		return NULL;

	return new wxSize(x, y);
}
ZZZJS_END_CONSTRUCTOR

	
ZZZJS_BEGIN_O2I(wxSize, Size)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	/*
 		wxSize ()
 		Initializes this size object with zero width and height. More...
 
 		wxSize (int width, int height)
 		Initializes this size object with the given width and height.
	*/

	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_WIDTH), &v) == JS_TRUE )  
	{
		int width = 0,  height = 0;

		// width
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER);

		bAllocation = true;
		return new wxSize(width, height);
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_X), &v) == JS_TRUE )  
	{
		int width = 0,  height = 0;

		// x
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_X, WXJS_TYPE_NUMBER);
		// y
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_Y, WXJS_TYPE_NUMBER);

		bAllocation = true;
		return new wxSize(width, height);
	}
	
	return NULL;
}
ZZZJS_END_O2I