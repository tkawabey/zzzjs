/*
 * wxJavaScript - fontdata.cpp
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
 * $Id: fontdata.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// fontdata.cpp
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

#include "js/gui/control/fontdata.h"

#include "js/gui/misc/font.h"
#include "js/gui/misc/colour.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/fontdata</file>
 * <module>gui</module>
 * <class name="wxFontData">
 *  This class holds a variety of information related to font dialogs.
 *  See @wxFontDialog
 * </class>
 */
WXJS_INIT_CLASS(FontData, "FontData", 0)

/***
 * <properties>
 *  <property name="allowSymbols" type="Boolean">
 *   Under MS Windows, get/set a flag determining whether symbol fonts can be selected. 
 *   Has no effect on other platforms
 *  </property>
 *  <property name="enableEffects" type="Boolean">
 *   Get/Set whether 'effects' are enabled under Windows. This refers to the controls for 
 *   manipulating colour, strikeout and underline properties.
 *  </property>
 *  <property name="chosenFont" type="@wxFont">
 *   Get the selected font
 *  </property>
 *  <property name="colour" type="@wxColour" />
 *  <property name="initialFont" type="@wxFont">
 *   Get/Set the font that will be initially used by the font dialog
 *  </property>
 *  <property name="showHelp" type="boolean">
 *   Show the help button? Windows only.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(FontData)
  WXJS_PROPERTY(P_ALLOW_SYMBOLS, "allowSymbols")
  WXJS_PROPERTY(P_ENABLE_EFFECTS, "enableEffects")
  WXJS_PROPERTY(P_CHOSEN_FONT, "chosenFont")
  WXJS_PROPERTY(P_COLOUR, "colour")
  WXJS_PROPERTY(P_INITIAL_FONT, "initialFont")
  WXJS_PROPERTY(P_SHOW_HELP, "showHelp")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxFontData, FontData)
	switch (id) 
	{
	case P_ALLOW_SYMBOLS:
		ToJSVal(cx, vp, p->GetAllowSymbols());
		break;
	case P_ENABLE_EFFECTS:
		ToJSVal(cx, vp, p->GetEnableEffects());
		break;
	case P_CHOSEN_FONT:
        vp.set( Font::CreateObject(cx, new wxFont(p->GetChosenFont()), obj) );
		break;
	case P_COLOUR:
		vp.set( Colour::CreateObject(cx, new wxColour(p->GetColour())) );
		break;
	case P_INITIAL_FONT:
        vp.set( Font::CreateObject(cx, new wxFont(p->GetInitialFont()), obj) );
		break;
	case P_SHOW_HELP:
		ToJSVal(cx, vp, p->GetShowHelp());
		break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxFontData, FontData)
	switch (id) 
	{
	case P_ALLOW_SYMBOLS:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
				p->SetAllowSymbols(value);
			break;
		}
	case P_ENABLE_EFFECTS:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
				p->EnableEffects(value);
			break;
		}
	case P_CHOSEN_FONT:
		{
			zzzJsPtr<wxFont> apFont;
			if ( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true )
				p->SetChosenFont(*(apFont.get()));
			break;
		}
	case P_COLOUR:
		{
			wxColour *colour = Colour::GetPrivate(cx, vp);
			if ( colour != NULL )
				p->SetColour(*colour);
			break;
		}
	case P_INITIAL_FONT:
		{
			zzzJsPtr<wxFont> apFont;
			if ( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true )
				p->SetInitialFont(*(apFont.get()));
			break;
		}
	case P_SHOW_HELP:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
				p->SetShowHelp(value);
			break;
		}
	}
    return true;
WXJS_END_SET_PROP

/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Constructs a new wxFontData object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxFontData, FontData)
    return new wxFontData();
WXJS_END_CONSTRUCTOR
