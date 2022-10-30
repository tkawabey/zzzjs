/*
 * wxJavaScript - listitem.cpp
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
 * $Id: listitem.cpp 784 2007-06-25 18:34:22Z fbraem $
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

#include "js/gui/control/listitem.h"
#include "js/gui/control/listctrl.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/listitem</file>
 * <module>gui</module>
 * <class name="wxListItem">
 *  This class stores information about a @wxListCtrl item or column.
 * </class>
 */
WXJS_INIT_CLASS(ListItem, "ListItem", 0)

/***
 * <properties>
 *  <property name="align" type=WXJS_TYPE_NUMBER>
 *   The column alignment. See @wxListCtrl#wxListColumnFormat.
 *  </property>
 *  <property name="backgroundColour" type="@wxColour">
 *   Get/Set the background colour of the item.
 *  </property>
 *  <property name="column" type=WXJS_TYPE_NUMBER>
 *   Get/Set the column.
 *  </property>
 *  <property name="data" type=WXJS_TYPE_NUMBER>
 *  Get/Set the associated data.
 *  </property>
 *  <property name="font" type="@wxFont">
 *  Get/Set the font of the item.
 *  </property>
 *  <property name="hasAttributes" type="Boolean" readonly="Y">
 *  Returns true when the item has attributes.
 *  </property>
 *  <property name="id" type=WXJS_TYPE_NUMBER>
 *  Get/Set index of the item.
 *  </property>
 *  <property name="image" type=WXJS_TYPE_NUMBER>
 *  Get/Set the index of the image in the associated imagelist of the list control.
 *  </property>
 *  <property name="mask" type=WXJS_TYPE_NUMBER>
 *  Get/Set the mask. The mask indicates which fields of wxListItem are valid. 
 *  See @wxListMask
 *  </property>
 *  <property name="state" type=WXJS_TYPE_NUMBER>
 *  Get/Set the state. See @wxListState
 *  </property>
 *  <property name="stateMask" type=WXJS_TYPE_NUMBER>
 *  Get/Set the state mask. This indicates which state is valid. See @wxListState
 *  </property>
 *  <property name="text" type=WXJS_TYPE_STRING>
 *  Get/Set the text of the item.
 *  </property>
 *  <property name="textColour" type="@wxColour">
 *  Get/Set the text colour.
 *  </property>
 *  <property name="width" type=WXJS_TYPE_NUMBER>
 *  Get/Set the width.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ListItem)
    WXJS_PROPERTY(P_ALIGN, "align")
    WXJS_PROPERTY(P_BG_COLOUR, "backgroundColour")
    WXJS_PROPERTY(P_COLUMN, "column")
    WXJS_PROPERTY(P_DATA, "data")
    WXJS_PROPERTY(P_FONT, "font")
    WXJS_READONLY_PROPERTY(P_HAS_ATTR, "hasAttributes")
    WXJS_PROPERTY(P_ID, "id")
    WXJS_PROPERTY(P_IMAGE, "image")
    WXJS_PROPERTY(P_MASK, "mask")
    WXJS_PROPERTY(P_STATE, "state")
    WXJS_PROPERTY(P_STATE_MASK, "stateMask")
    WXJS_PROPERTY(P_TEXT, "text")
    WXJS_PROPERTY(P_TEXT_COLOUR, "textColour")
    WXJS_PROPERTY(P_WIDTH, "width")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxListItem, ListItem)
    switch (id)
    {
    case P_MASK:
        ToJSVal(cx, vp, p->GetMask());
        break;
    case P_ID:
        ToJSVal(cx, vp, p->GetId());
        break;
    case P_COLUMN:
        ToJSVal(cx, vp, p->GetColumn());
        break;
    case P_STATE:
        ToJSVal(cx, vp, p->GetState());
        break;
    case P_TEXT:
        ToJSVal(cx, vp, p->GetText());
        break;
    case P_IMAGE:
        ToJSVal(cx, vp, p->GetImage());
        break;
    case P_DATA:
        {
            ListObjectData *data = (ListObjectData*) p->GetData();
            vp.set( ( data == NULL ) ? JSVAL_VOID : data->GetJSVal() );
            break;
        }
    case P_WIDTH:
        ToJSVal(cx, vp, p->GetWidth());
        break;
    case P_ALIGN:
        ToJSVal(cx, vp, (int) p->GetAlign());
        break;
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
            vp.set( ( colour == wxNullColour ) ? JSVAL_VOID
                                             : Colour::CreateObject(cx, new wxColour(colour))
											 );
            break;
        }
    case P_FONT:
        {
            wxFont font = p->GetFont();
            vp.set( ( font == wxNullFont ) ? JSVAL_VOID
                                         : Font::CreateObject(cx, new wxFont(font))
										 );
            break;
        }
    case P_HAS_ATTR:
        ToJSVal(cx, vp, p->HasAttributes());
        break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxListItem, ListItem)
    switch (id)
    {
    case P_MASK:
        {
            long mask;
            if ( FromJS(cx, vp, mask) )
                p->SetMask(mask);
            break;
        }
    case P_ID:
        {
            long id;
            if ( FromJS(cx, vp, id) )
                p->SetId(id);
            break;
        }
    case P_COLUMN:
        {
            int column;
            if ( FromJS(cx, vp, column) )
                p->SetColumn(column);
            break;
        }
    case P_STATE:
        {
            long state;
            if ( FromJS(cx, vp, state) )
                p->SetState(state);
            break;
        }
    case P_STATE_MASK:
        {
            long stateMask;
            if ( FromJS(cx, vp, stateMask) )
                p->SetStateMask(stateMask);
            break;
        }
    case P_TEXT:
        {
            wxString text;
            FromJS(cx, vp, text);
            p->SetText(text);
            break;
        }
    case P_IMAGE:
        {
            int img;
            if ( FromJS(cx, vp, img) )
                p->SetImage(img);
            break;
        }
    case P_DATA:
        {
            ListObjectData *data = (ListObjectData*) p->GetData();
            if ( data != NULL )
            {
                delete data;
                data = NULL;
            }

            data = new ListObjectData(cx, vp);
            p->SetData((long) data);
            break;
        }
    case P_WIDTH:
        {
            int width;
            if ( FromJS(cx, vp, width) )
                p->SetWidth(width);
            break;
        }
    case P_ALIGN:
        {
            int align;
            if ( FromJS(cx, vp, align) )
                p->SetAlign((wxListColumnFormat) align);
            break;
        }
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
 *  <function>
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *    The index of the item
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a new wxListItem object.
 *   See @wxListCtrl#getItem and @wxListCtrl#setItem
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxListItem, ListItem)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc == 0 )
        return new wxListItem();
    else if ( argc == 1 )
    {
        int id;
        if ( FromJS(cx, argv[0], id) )
        {
            wxListItem *p = new wxListItem();
            p->SetId(id);
            return p;
        }
    }
    return NULL;
WXJS_END_CONSTRUCTOR

