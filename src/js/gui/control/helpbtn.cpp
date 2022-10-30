/*
 * wxJavaScript - helpbtn.cpp
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
 * $Id: helpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
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


#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"

#include "js/gui/control/helpbtn.h"
#include "js/gui/control/button.h"
#include "js/gui/control/window.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/helpbtn</file>
 * <module>gui</module>
 * <class name="wxContextHelpButton" prototype="@wxBitmapButton">
 *  Instances of this class may be used to add a question mark button that
 *  when pressed, puts the application into context-help mode. It does this by 
 *  creating a @wxContextHelp object which itself generates a @wxHelpEvent event
 * when the user clicks on a window.
 * </class>
 */
WXJS_INIT_CLASS(ContextHelpButton, "ContextHelpButton", 1)


WXJS_BEGIN_ADD_PROP(wxContextHelpButton, ContextHelpButton)
  return ButtonEventHandler::ConnectEvent(p, prop, true);
WXJS_END_ADD_PROP


WXJS_BEGIN_DEL_PROP(wxContextHelpButton, ContextHelpButton)
  return ButtonEventHandler::ConnectEvent(p, prop, false);
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxContextHelpButton.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxContextHelpButton object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxContextHelpButton, ContextHelpButton)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  if ( argc > 0 )
  {
    wxWindow *parent = Window::GetPrivate(cx, argv[0]);
    if ( parent == NULL )
    {
        JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
        return NULL;
    }
    JavaScriptClientData *clntParent =
          dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
    if ( clntParent == NULL )
    {
        JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
        return JS_FALSE;
    }
    JS_SetParent(cx, obj, clntParent->GetObject());

    wxContextHelpButton *p = new wxContextHelpButton(parent);
    p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
    return p;
  }
  return NULL;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_GET_SET_STR_PROP(wxContextHelpButton, ContextHelpButton)
	BitmapButton::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
	
WXJS_BEGIN_DESTRUCTOR(wxContextHelpButton, ContextHelpButton)
WXJS_END_CONSTRUCTOR
