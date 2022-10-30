/*
 * wxJavaScript - listitattr.cpp
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
 * $Id: listitattr.cpp 784 2007-06-25 18:34:22Z fbraem $
 */
// listitem.cpp
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/listctrl.h>


#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"


#include "js/gui/misc/font.h"
#include "js/gui/misc/colour.h"

#include "js/gui/control/listitattr.h"
#include "js/gui/control/listctrl.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/listitattr</file>
 * <module>gui</module>
 * <class name="wxListItemAttr">
 *  wxListItemAttr is used in virtual list controls.
 *  See @wxListCtrl#onGetItemAttr property
 * </class>
 */
WXJS_INIT_CLASS(ListItemAttr, "ListItemAttr", 0)

/***
 * <properties>
 *  <property name="textColour" type="@wxColour">
 *   The colour used for displaying text.
 *  </property>
 *  <property name="backgroundColour" type="@wxColour">
 *   The colour used as background.
 *  </property>
 *  <property name="font" type="@wxFont">
 *   The font used for displaying text.
 *  </property>
 *  <property name="hasTextColour" type="Boolean" readonly="Y">
 *   Indicates that this attribute defines the text colour.
 *  </property>
 *  <property name="hasBackgroundColour" type="Boolean" readonly="Y">
 *   Indicates that this attribute defines the background colour.
 *  </property>
 *  <property name="hasFont" type="Boolean" readonly="Y">
 *   Indicates that this attributes defines a font.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ListItemAttr)
    WXJS_PROPERTY(P_TEXT_COLOUR, "textColour")
    WXJS_PROPERTY(P_BG_COLOUR, "backgroundColour")
    WXJS_PROPERTY(P_FONT, "font")
    WXJS_READONLY_PROPERTY(P_HAS_TEXT_COLOUR, "hasTextColour")
    WXJS_READONLY_PROPERTY(P_HAS_BG_COLOUR, "hasBackgroundColour")
    WXJS_READONLY_PROPERTY(P_HAS_FONT, "hasFont")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxListItemAttr, ListItemAttr)
    switch (id)
    {
    case P_TEXT_COLOUR:
        {
            wxColour colour = p->GetTextColour();
            vp.set( ( colour == wxNullColour ) ? JSVAL_VOID
                                             : Colour::CreateObject(cx, new wxColour(colour))
											 );
            break;
        }
    case P_BG_COLOUR:
        {
            wxColour colour = p->GetBackgroundColour();
            vp.set(  ( colour == wxNullColour ) ? JSVAL_VOID
                                             : Colour::CreateObject(cx, new wxColour(colour))
											 );
            break;
        }
    case P_FONT:
        {
            wxFont font = p->GetFont();
            vp.set(  ( font == wxNullFont ) ? JSVAL_VOID
                                         : Font::CreateObject(cx, new wxFont(font))
										 );
            break;
        }
    case P_HAS_TEXT_COLOUR:
        ToJSVal(cx, vp, p->HasTextColour());
        break;
    case P_HAS_BG_COLOUR:
        ToJSVal(cx, vp, p->HasBackgroundColour());
        break;
    case P_HAS_FONT:
        ToJSVal(cx, vp, p->HasFont());
        break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxListItemAttr, ListItemAttr)
    switch (id)
    {
    case P_TEXT_COLOUR:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
                p->SetTextColour(*colour);
            break;
        }
    case P_BG_COLOUR:
        {
            wxColour *colour = Colour::GetPrivate(cx, vp);
            if ( colour != NULL )
                p->SetBackgroundColour(*colour);
            break;
        }
    case P_FONT:
        {
			zzzJsPtr<wxFont> apFont;
            if ( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true )
                p->SetFont(*(apFont.get()));
            break;
        }
    }
    return true;
WXJS_END_SET_PROP

/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Creates a new wxListItem object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxListItemAttr, ListItemAttr)
    return new wxListItemAttr();
WXJS_END_CONSTRUCTOR
