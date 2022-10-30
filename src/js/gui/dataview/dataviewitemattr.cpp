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

#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewitemattr.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;


//--------------------------------------------------------
//	DataViewItemAttr
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewItemAttr, "DataViewItemAttr", 0)


/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(DataViewItemAttr)
  WXJS_PROPERTY(P_BOLD, "bold")
  WXJS_PROPERTY(P_BackgroundColour, "backgroundColour")
  WXJS_READONLY_PROPERTY(P_HasBackgroundColour, "hasBackgroundColour")
  WXJS_PROPERTY(P_Italic, "italic")
  WXJS_PROPERTY(P_Colour, "colour")
  WXJS_READONLY_PROPERTY(P_HasColour, "hasColour")
  WXJS_READONLY_PROPERTY(P_HasFont, "hasFont")
  WXJS_READONLY_PROPERTY(P_HasEffectiveFont, "hasEffectiveFont")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewItemAttr, DataViewItemAttr)
	switch (id) 
	{
	case P_BOLD:
		ToJSVal(cx, vp, p->GetBold());
		break;
	case P_BackgroundColour:
		{
			wxColor* value = new wxColor( p->GetColour() );
			vp.set( Colour::CreateObject(cx, value) );
		}
		break;
	case P_HasBackgroundColour:
		ToJSVal(cx, vp, p->HasBackgroundColour());
		break;
	case P_Italic:
		ToJSVal(cx, vp, p->GetItalic());
		break;
	case P_Colour:
		{
			wxColor* value = new wxColor( p->GetColour() );
			vp.set( Colour::CreateObject(cx, value) );
		}
		break;
	case P_HasColour:
		ToJSVal(cx, vp, p->HasColour());
		break;
	case P_HasFont:
		ToJSVal(cx, vp, p->HasFont());
		break;
	case P_HasEffectiveFont:
		ToJSVal(cx, vp, p->HasBackgroundColour());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDataViewItemAttr, DataViewItemAttr)
	switch (id) 
	{
	case P_BOLD:
		{
			bool value = false;
			if ( FromJS(cx, vp, value) )
			{
				p->SetBold( value );
			}
		}
		break;
	case P_BackgroundColour:
		{
			wxColor* pColor = Colour::GetPrivate(cx, vp);
			if( pColor != NULL ) {
				p->SetBackgroundColour( *pColor );
			}
			
		}
		break;
	case P_Italic:
		{
			bool value = false;
			if ( FromJS(cx, vp, value) )
			{
				p->SetItalic( value );
			}
		}
		break;
	case P_Colour:
		{
			wxColor* pColor = Colour::GetPrivate(cx, vp);
			if( pColor != NULL ) {
				p->SetColour( *pColor );
			}
			
		}
		break;
	}
	return true;
WXJS_END_SET_PROP


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
 *   Constructs a new wxDataViewItemAttr object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxDataViewItemAttr, DataViewItemAttr)

	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxDataViewItemAttr *p = new wxDataViewItemAttr();
	return p;
WXJS_END_CONSTRUCTOR


WXJS_BEGIN_DESTRUCTOR(wxDataViewItemAttr, DataViewItemAttr)

WXJS_END_DESTRUCTOR

WXJS_BEGIN_METHOD_MAP(DataViewItemAttr)
    WXJS_METHOD("getEffectiveFont", getEffectiveFont, 1)
WXJS_END_METHOD_MAP()

JSBool DataViewItemAttr::getEffectiveFont(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFont workFont;
		
    wxDataViewItemAttr *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	zzzJsPtr<wxFont> apFont;
	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
	wxFont font = p->GetEffectiveFont( *(apFont.get()) );
	*vp = Font::CreateObject(cx, new wxFont(font) );
	return JS_TRUE;
}
