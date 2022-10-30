/*
 * wxJavaScript - dirdlg.cpp
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
 * $Id: dirdlg.cpp 810 2007-07-13 20:07:05Z fbraem $
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


#include "js/gui/control/dirdlg.h"
#include "js/gui/control/window.h"
#include "js/gui/control/dialog.h"

#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/dirdlg</file>
 * <module>gui</module>
 * <class name="wxDirDialog" prototype="wxDialog">
 *	This class represents the directory chooser dialog.
 * </class>
 */
WXJS_INIT_CLASS(DirDialog, "DirDialog", 1)

/***
 * <properties>
 *	<property name="message" type=WXJS_TYPE_STRING>
 *	 Get/Set the message of the dialog
 *  </property>
 *  <property name="path" type=WXJS_TYPE_STRING>
 *	 Get/Set the full path of the selected file
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(DirDialog)
  WXJS_PROPERTY(P_MESSAGE, "message")
  WXJS_PROPERTY(P_PATH, "path")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxDirDialog, DirDialog)
	switch (id) 
	{
	case P_MESSAGE:
		ToJSVal(cx, vp,p->GetMessage());
		break;
	case P_PATH:
		ToJSVal(cx, vp,p->GetPath());
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxDirDialog, DirDialog)
	switch (id) 
	{
	case P_MESSAGE:
		{
			wxString msg;
			FromJS(cx, vp, msg);
			p->SetMessage(msg);
			break;
		}
	case P_PATH:
		{
			wxString path;
			FromJS(cx, vp, path);
			p->SetPath(path);
			break;
		}
	}
	return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxDirDialog, DirDialog)
	Dialog::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *	<function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxDirDialog
 *   </arg>
 *   <arg name="Message" type=WXJS_TYPE_STRING default="'Choose a directory'">
 *    The title of the dialog
 *   </arg>
 *   <arg name="DefaultPath" type=WXJS_TYPE_STRING default="">
 *    The default directory
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *    Unused
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *	  The position of the dialog.
 *   </arg>
 *  </function>
 *	<desc>
 *   Constructs a new wxDirDialog object
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxDirDialog, DirDialog)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	int style = 0;
	wxString defaultPath = wxEmptyString;
	wxString message = wxDirSelectorPromptStr;
	
	ZZZJS_CHECK_ARG_COUNT(3, 6);
	
	argIndex = argc -1;
	switch(argc)
	{
	case 5:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	case 4:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 3:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(defaultPath, WXJS_TYPE_NUMBER);
		argIndex--;
	case 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(message, WXJS_TYPE_NUMBER);
		argIndex--;
	default:
		wxWindow *parent = NULL;

		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
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
		return new wxDirDialog(parent, message, defaultPath, style, *(apPoint.get()));
	}

	return NULL;
}
WXJS_END_CONSTRUCTOR

//void DirDialog::Destruct(JSContext* WXUNUSED(cx), wxDirDialog *p)
WXJS_BEGIN_DESTRUCTOR(wxDirDialog, DirDialog)

WXJS_END_DESTRUCTOR
