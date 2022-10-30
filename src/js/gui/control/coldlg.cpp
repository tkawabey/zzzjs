/*
 * wxJavaScript - coldlg.cpp
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
 * $Id: coldlg.cpp 810 2007-07-13 20:07:05Z fbraem $
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

#include "js/gui/control/coldlg.h"
#include "js/gui/control/coldata.h"
#include "js/gui/control/window.h"
#include "js/gui/control/dialog.h"
#include "js/gui/control/toplevel.h"


#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/coldlg</file>
 * <module>gui</module>
 * <class name="wxColourDialog" prototype="@wxDialog">
 *	The wxColourDialog presents a colour selector to the user.
 *  See also @wxColourData. The following sample shows this 
 *  dialog:
 *  <pre><code class="whjs">
 *    wxTheApp.onInit = function()
 *    {
 *      clrData = new wxColourData();
 *      // Set the selected colour
 *      clrData.colour = new wxColour(0, 0, 0);
 *
 *      // Set a custom colour
 *      clrData.customColour[0]  = wxRED;
 *    
 *      dlg = new wxColourDialog(null, clrData);
 *      dlg.title = "Select a colour";
 *      dlg.showModal();
 *      
 *      return false;  
 *    }
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(ColourDialog, "ColourDialog", 1)

/***
 * <properties>
 *	<property name="colourData" type="@wxColourData" readonly="Y">
 *	 Gets the colour data.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ColourDialog)
  WXJS_READONLY_PROPERTY(P_COLOUR_DATA, "colourData")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxColourDialog, ColourDialog)
  if ( id == P_COLOUR_DATA )
  {
    vp.set( ColourData::CreateObject(cx, new wxColourData(p->GetColourData())) );
  }
  return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxColourDialog, ColourDialog)
	Dialog::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of wxColourDialog.
 *   </arg>
 *   <arg name="ColourData" type="@wxColourData">
 *	  The colour data.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxColourDialog object
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxColourDialog, ColourDialog)

	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc > 2 )
        argc = 2;

    wxColourData *data = NULL;
    if ( argc == 2 )
    {
        data = ColourData::GetPrivate(cx, argv[1]);
        if ( data == NULL )
        {
          JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "wxColourData");
          return NULL;
        }
    }

    wxWindow *parent = Window::GetPrivate(cx, argv[0]);
    if ( parent != NULL )
    {
      JavaScriptClientData *clntParent =
            dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
      if ( clntParent == NULL )
      {
          JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
          return JS_FALSE;
      }
      JS_SetParent(cx, obj, clntParent->GetObject());
    }

	return new wxColourDialog(parent, data);
WXJS_END_CONSTRUCTOR

//void ColourDialog::Destruct(JSContext* WXUNUSED(cx), wxColourDialog *p)
WXJS_BEGIN_DESTRUCTOR(wxColourDialog, ColourDialog)


WXJS_END_DESTRUCTOR
