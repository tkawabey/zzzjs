/*
 * wxJavaScript - fontdlg.cpp
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
 * $Id: fontdlg.cpp 810 2007-07-13 20:07:05Z fbraem $
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


#include "js/gui/control/fontdlg.h"
#include "js/gui/control/fontdata.h"
#include "js/gui/control/window.h"
#include "js/gui/control/dialog.h"

#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/fontdlg</file>
 * <module>gui</module>
 * <class name="wxFontDialog" prototype="@wxDialog">
 *	The wxFontDialog presents a Font selector to the user.
 * </class>
 */
WXJS_INIT_CLASS(FontDialog, "FontDialog", 1)

/***
 * <properties>
 *	<property name="FontData" type="@wxFontData" readonly="Y">
 *	 Gets the Font data.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(FontDialog)
  WXJS_READONLY_PROPERTY(P_FONT_DATA, "FontData")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxFontDialog, FontDialog)
	if ( id == P_FONT_DATA )
        vp.set( FontData::CreateObject(cx, new wxFontData(p->GetFontData())) );
    return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxFontDialog, FontDialog)
	Dialog::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

/***
 * <ctor>
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of wxFontDialog.
 *   </arg>
 *	 <arg name="FontData" type="@wxFontData">
 *	  The Font data.
 *   </arg>
 *  </function>
 *	<desc>
 *   Constructs a new wxFontDialog object
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxFontDialog, FontDialog)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc > 2 )
      argc = 2;

    wxFontData *data = NULL;
    if ( argc == 2 )
    {
        if ( (data = FontData::GetPrivate(cx, argv[1])) == NULL )
        {
          JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "wxFontData");
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
#if wxCHECK_VERSION(2,7,0)
    wxFontDialog *p = new wxFontDialog(parent, *data);
#else
    wxFontDialog *p = new wxFontDialog(parent, data);
#endif

    if ( p != NULL )
    {
      p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
    }

    return p;
WXJS_END_CONSTRUCTOR

//void FontDialog::Destruct(JSContext* WXUNUSED(cx), wxFontDialog *p)
//void FontDialog::Destruct(wxFontDialog *p)
WXJS_BEGIN_DESTRUCTOR(wxFontDialog, FontDialog)
//	p->Destroy();
WXJS_END_DESTRUCTOR
