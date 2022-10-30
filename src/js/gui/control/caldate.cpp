/*
 * wxJavaScript - caldate.cpp
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
 * $Id: caldate.cpp 667 2007-04-06 20:34:24Z fbraem $
 */
// caldate.cpp
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
#include "js/common/index.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"

#include "js/gui/control/calendar.h"
#include "js/gui/control/caldate.h"

using namespace zzzJs;
using namespace zzzJs::gui;

WXJS_INIT_CLASS(CalendarDateAttr, "CalendarDateAttr", 0)

/***
 * <properties>
 *  <property name="backgroundColour" type="@wxColour">
 *   The background colour
 *  </property>
 *  <property name="border" type=WXJS_TYPE_NUMBER>Type of the border. 
 *   See @wxCalendarDateBorder.
 *  </property>
 *  <property name="borderColour" type="#wxColour">
 *   The colour of the border
 *  </property>
 *  <property name="font" type="@wxFont">The font of the text</property>
 *  <property name="holiday" type="boolean">Is the day a holiday?</property>
 *  <property name="textColour" type="@wxColour">
 *   The colour of the text
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(CalendarDateAttr)
  WXJS_PROPERTY(P_TEXT_COLOUR, "textColour")
  WXJS_PROPERTY(P_BG_COLOUR, "backgroundColour")
  WXJS_PROPERTY(P_BORDER_COLOUR, "borderColour")
  WXJS_PROPERTY(P_FONT, "font")
  WXJS_PROPERTY(P_BORDER, "border")
  WXJS_PROPERTY(P_HOLIDAY, "holiday")
WXJS_END_PROPERTY_MAP()

//bool CalendarDateAttr::GetProperty(wxCalendarDateAttr *p,
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
WXJS_BEGIN_GET_PROP(wxCalendarDateAttr, CalendarDateAttr)
    if ( id > 0 && id < 32 ) // Check the day property
    {
      JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
      wxASSERT_MSG(parent != NULL, wxT("No parent found for CalendarDateAttr"));

      wxCalendarCtrl *calendar = CalendarCtrl::GetPrivate(cx, parent);
      if ( calendar == NULL )
        return false;

      wxCalendarDateAttr *attr = calendar->GetAttr(id);
      SetPrivate(cx, obj, (attr == NULL) ? new wxCalendarDateAttr()
                                         : CalendarDateAttr::Clone(attr));
    }
  else
  {
    switch (id) 
    {
    case P_TEXT_COLOUR:
      if ( p->HasTextColour() )
      {
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetTextColour())) );
      }
      break;
    case P_BG_COLOUR:
      if ( p->HasBackgroundColour() )
      {
        vp.set( Colour::CreateObject(cx, new wxColour(p->GetBackgroundColour())) );
      }
      break;
    case P_BORDER_COLOUR:
        if ( p->HasBorderColour() )
        {
            vp.set( Colour::CreateObject(cx, new wxColour(p->GetBorderColour())) );
        }
        break;
    case P_FONT:
        if ( p->HasFont() )
        {
            vp.set( Font::CreateObject(cx, new wxFont(p->GetFont()), obj) );
        }
        break;
    case P_BORDER:
        if ( p->HasBorder() )
        {
            ToJSVal(cx, vp, static_cast<int>(p->GetBorder()));
        }
        break;
    case P_HOLIDAY:
        ToJSVal(cx, vp, p->IsHoliday());
        break;
    }
  }
    return true;
WXJS_END_GET_PROP



WXJS_BEGIN_SET_PROP(wxCalendarDateAttr, CalendarDateAttr)
  if ( id > 0 && id < 32 )
  {
    JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
    wxASSERT_MSG(parent != NULL, wxT("No parent found for CalendarAttrItem"));

    wxCalendarCtrl *calendar = CalendarCtrl::GetPrivate(cx, parent);
    if ( calendar == NULL )
        return false;

    wxCalendarDateAttr *attr = GetPrivate(cx, vp);
    // Clone the attribute because it is owned and destroyed by wxWindows
    // which can give problems. For example: when the calendar object is
    // garbage collected and the attr object is not, the attr object
    // would have an invalid pointer.
    calendar->SetAttr(id, CalendarDateAttr::Clone(attr));
  }
  else
  {
    switch (id) 
    {
    case P_TEXT_COLOUR:
        {
          wxColour *colour = Colour::GetPrivate(cx, vp);
          if ( colour != NULL )
              p->SetTextColour(*colour);
        }
        break;
    case P_BG_COLOUR:
        {
          wxColour *colour = Colour::GetPrivate(cx, vp);
          if ( colour != NULL )
              p->SetBackgroundColour(*colour);
        }
        break;
    case P_BORDER_COLOUR:
        {
          wxColour *colour = Colour::GetPrivate(cx, vp);
          if ( colour != NULL )
              p->SetBorderColour(*colour);
        }
        break;
    case P_FONT:
        {
		  zzzJsPtr<wxFont> apFont;
          if ( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true )
              p->SetFont(*(apFont.get()));
        }
        break;
    case P_BORDER:
        {
          int border;
          if ( FromJS<int>(cx, vp, border) )
              p->SetBorder((wxCalendarDateBorder)border);
          break;
        }
    case P_HOLIDAY:
        {
          bool holiday;
          if ( FromJS(cx, vp, holiday) )
              p->SetHoliday(holiday);
          break;
        }
    }
  }
  return true;
WXJS_END_SET_PROP


/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="TextColour" type="@wxColour">Colour of the text</arg>
 *   <arg name="BackgroundColour" type="@wxColour" default="null">
 *    Backgroundcolour
 *   </arg>
 *   <arg name="BorderColour" type="@wxColour" default="null">BorderColour</arg>
 *   <arg name="Font" type="@wxFont" default="null">The font</arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">The border type</arg>
 *  </function>
 *  <function>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER>The border type</arg>
 *   <arg name="BorderColour" type="@wxColour">BorderColour</arg>
 *  </function>  
 *  <desc>
 *   Constructs a new wxCalendarDateAttr object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxCalendarDateAttr, CalendarDateAttr)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


  int argIndex = 0;
   if ( argc == 0 )
        return new wxCalendarDateAttr();

    if ( Colour::HasPrototype(cx, argv[0]) )
    {
      if ( argc > 5 )
        return NULL;

      int border = wxCAL_BORDER_NONE;
      const wxColour *textColour = &wxNullColour;
      const wxColour *bgColour = &wxNullColour;
      const wxColour *borderColour = &wxNullColour;
	  zzzJsPtr<wxFont> apFont(NULL, &wxNullFont);

	  argIndex = argc - 1;
      switch(argc)
      {
      case 5:
          if ( ! FromJS(cx, argv[argIndex], border) )
              break;
		  argIndex--;
          // Fall through
      case 4:
         ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);
		  argIndex--;
          // Fall through
      case 3:
          borderColour = Colour::GetPrivate(cx, argv[2]);
          if ( borderColour == NULL )
              break;
		  argIndex--;
          // Fall through
      case 2:
          bgColour = Colour::GetPrivate(cx, argv[1]);
          if ( bgColour == NULL )
              break;
		  argIndex--;
          // Fall through
      default:
          textColour = Colour::GetPrivate(cx, argv[0]);
          if ( textColour == NULL )
              break;
		  argIndex--;
          
        return new wxCalendarDateAttr(*textColour, *bgColour,
                                      *borderColour, *(apFont.get()),
                                      (wxCalendarDateBorder) border);
      }

        return NULL;
    }
    else
    {
        int border;
        if ( ! FromJS(cx, argv[0], border) )
            return NULL;

        const wxColour *colour = &wxNullColour;
        if (    argc > 1 
             && (colour = Colour::GetPrivate(cx, argv[1])) == NULL )
            return NULL;

        return new wxCalendarDateAttr((wxCalendarDateBorder) border, *colour);
    }
WXJS_END_CONSTRUCTOR



WXJS_BEGIN_DESTRUCTOR(wxCalendarDateAttr, CalendarDateAttr)
WXJS_END_DESTRUCTOR
