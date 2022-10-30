/*
 * wxJavaScript - coldata.cpp
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
 * $Id: coldata.cpp 672 2007-04-12 20:29:39Z fbraem $
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
#include "js/common/index.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/misc/colour.h"

#include "js/gui/control/coldata.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/colourdata</file>
 * <module>gui</module>
 * <class name="wxColourData">
 *  This class holds a variety of information related to colour dialogs.
 *  See @wxColourDialog.
 * </class>
 */
WXJS_INIT_CLASS(ColourData, "ColourData", 0)

/***
 * <properties>
 *  <property name="chooseFull" type="Boolean">
 *   Under Windows, determines whether the Windows colour dialog will
 *   display the full dialog with custom colour selection controls. 
 *   Has no meaning under other platforms.
 *  </property>
 *  <property name="colour" type="@wxColour">
 *   Get/Set the current colour associated with the colour dialog.
 *  </property>
 *  <property name="customColour" type="Array">
 *   Get/Set the ith custom colour associated with the colour dialog. 
 *   The index must be between 0 and 15. The element is a @wxColour.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ColourData)
  WXJS_PROPERTY(P_CUSTOM_COLOUR, "customColour")
  WXJS_PROPERTY(P_CHOOSE_FULL, "chooseFull")
  WXJS_PROPERTY(P_COLOUR, "colour")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxColourData, ColourData)
    switch(id) 
	{
	case P_CHOOSE_FULL:
		ToJSVal(cx, vp, p->GetChooseFull());
		break;
	case P_COLOUR:
		vp.set( Colour::CreateObject(cx, new wxColour(p->GetColour())) );
		break;
	case P_CUSTOM_COLOUR:
        vp.set( CustomColour::CreateObject(cx, new Index(0), obj) );
		break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxColourData, ColourData)
   switch (id) 
	{
	case P_CHOOSE_FULL:
		{
			bool full;
			if ( FromJS(cx, vp, full) )
				p->SetChooseFull(full);
			break;
		}
	case P_COLOUR:
		{
			wxColour *colour = Colour::GetPrivate(cx, vp);
			if ( colour != NULL )
				p->SetColour(*colour);
			break;
		}
	}
    return true;
WXJS_END_SET_PROP

/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Constructs a new wxColourData object.
 *   The selected colour is black. And @wxColourData#chooseFull is true.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxColourData, ColourData)
	return new wxColourData();
WXJS_END_CONSTRUCTOR

WXJS_INIT_CLASS(CustomColour, "CustomColour", 0)



WXJS_BEGIN_GET_PROP(Index, CustomColour)
  if ( id >= 0 )
  {
    p->SetIndex(id);

    JSObject *objColourData = JS_GetParent(obj);//JS_GetParent(cx, obj);
    wxASSERT_MSG(objColourData != NULL, wxT("wxCustomColour has no parent !"));

    wxColourData *colourData = ColourData::GetPrivate(cx, objColourData);
    if ( colourData == NULL )
      return false;
	
    vp.set( Colour::CreateObject(cx, 
                               new wxColour(colourData->GetCustomColour(id))) );
  }	
  return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(Index, CustomColour)
	if ( id >= 0 )
	{
        JSObject *objColourData = JS_GetParent(obj);//JS_GetParent(cx, obj);
        wxASSERT_MSG(objColourData != NULL, 
                     wxT("wxCustomColour has no parent !"));

        wxColourData *colourData = ColourData::GetPrivate(cx, objColourData);
		if ( colourData == NULL )
			return false;

        wxColour *colour = Colour::GetPrivate(cx, vp);
        if ( colour != NULL )
			colourData->SetCustomColour(id, *colour);
	}
	return true;
WXJS_END_SET_PROP

