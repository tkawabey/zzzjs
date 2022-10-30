/*
 * wxJavaScript - pwdlg.cpp
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
 * $Id: pwdlg.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/ext/point.h"


#include "js/gui/event/jsevent.h"

#include "js/gui/errors.h"
#include "js/gui/control/pwdlg.h"
#include "js/gui/control/dialog.h"
#include "js/gui/control/window.h"
#include "js/gui/control/txtdlg.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/pwdlg</file>
 * <module>gui</module>
 * <class name="wxPasswordEntryDialog" prototype="@wxTextEntryDialog">
 *	This class represents a dialog that requests a password from the user. 
 * </class>
 */
WXJS_INIT_CLASS(PasswordEntryDialog, "PasswordEntryDialog", 2)


WXJS_BEGIN_ADD_PROP(wxPasswordEntryDialog, PasswordEntryDialog)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    DialogEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxPasswordEntryDialog, PasswordEntryDialog)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  DialogEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxPasswordEntryDialog, PasswordEntryDialog)
	TextEntryDialog::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

/***
 * <ctor>
 *  <function />
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *    The parent of the dialog. null is Allowed.
 *   </arg>
 *	 <arg name="Message" type=WXJS_TYPE_STRING>Message to show on the dialog.</arg>
 *   <arg name="Title" type=WXJS_TYPE_STRING>The title of the dialog.</arg>
 *   <arg name="DefaultValue" type=WXJS_TYPE_STRING>
 *    The default value of the text control.
 *   </arg>
 *	 <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the dialog.
 *   </arg>
 *	 <arg name="Style" type=WXJS_TYPE_NUMBER default="wxId.OK + wxId.CANCEL">
 *    A dialog style, the buttons wxId.OK and wxId.CANCEL can be used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxPasswordEntryDialog object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxPasswordEntryDialog, PasswordEntryDialog)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc > 6 )
	argc = 6;
	
	int argIndex = 0;
	int style = wxOK | wxCANCEL | wxCENTRE;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	wxString defaultValue = wxEmptyString;
	wxString caption = wxEmptyString;
	
	ZZZJS_CHECK_ARG_COUNT(3, 6);


	argIndex = argc -1;
	switch(argc)
	{
	case 6:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	case 5:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 4:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(defaultValue, WXJS_TYPE_STRING);
		argIndex--;
	case 3:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(caption, WXJS_TYPE_STRING);
		argIndex--;
	default:
		wxString message;
		wxWindow *parent = NULL;
		
		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(message, WXJS_TYPE_STRING);
		argIndex++;

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

		wxPasswordEntryDialog *p = new wxPasswordEntryDialog(parent, message, 
				caption, defaultValue, 
				style, *(apPoint.get()));
		p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		return p;
	}
}
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxPasswordEntryDialog, PasswordEntryDialog)
WXJS_END_DESTRUCTOR
