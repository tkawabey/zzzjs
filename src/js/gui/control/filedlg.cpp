/*
 * wxJavaScript - filedlg.cpp
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
 * $Id: filedlg.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/ext/point.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/control/filedlg.h"
#include "js/gui/control/window.h"
#include "js/gui/control/dialog.h"

#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/filedlg</file>
 * <module>gui</module>
 * <class name="wxFileDialog" prototype="@wxDialog">
 *	A dialog for saving or opening a file. The following shows a save dialog:
 *  <pre><code class="whjs">
 *   var dlg = new wxFileDialog(frame, "Save a file");
 *   dlg.style = wxFileDialog.SAVE;
 *   dlg.showModal();
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(FileDialog, "FileDialog", 1)

/***
 * <properties>
 *	<property name="directory" type=WXJS_TYPE_STRING>
 *	 Get/Set the default directory
 *  </property>
 *  <property name="filename" type=WXJS_TYPE_STRING>
 *	 Get/Set the default filename
 *  </property>
 *	<property name="filenames" type="Array" readonly="Y">
 *	 Get an array of the selected file names
 *  </property>
 *	<property name="filterIndex" type=WXJS_TYPE_NUMBER>
 *	 Get/Set the filter index (wildcards)
 *  </property>
 *	<property name="message" type=WXJS_TYPE_STRING>
 *	 Get/Set the message of the dialog
 *  </property>
 *	<property name="path" type=WXJS_TYPE_STRING>
 *	 Get/Set the full path of the selected file
 *  </property>
 *	<property name="paths" type="Array" readonly="Y">
 *	 Gets the full path of all selected files
 *  </property>
 *	<property name="wildcard" type=WXJS_TYPE_STRING>
 *	 Gets/Sets the wildcard such as "*.*" or 
 *	 "BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif". 
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(FileDialog)
  WXJS_PROPERTY(P_DIRECTORY, "directory")
  WXJS_PROPERTY(P_FILENAME, "filename")
  WXJS_READONLY_PROPERTY(P_FILENAMES, "filenames")
  WXJS_PROPERTY(P_FILTER_INDEX, "filterIndex")
  WXJS_PROPERTY(P_MESSAGE, "message")
  WXJS_PROPERTY(P_PATH, "path")
  WXJS_READONLY_PROPERTY(P_PATHS, "paths")
  WXJS_PROPERTY(P_WILDCARD, "wildcard")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxFileDialog, FileDialog)
	switch(id) 
	{
	case P_DIRECTORY:
		ToJSVal(cx, vp,p->GetDirectory());
		break;
	case P_FILENAME:
		ToJSVal(cx, vp,p->GetFilename());
		break;
	case P_FILENAMES:
        {
            wxArrayString filenames;
            p->GetFilenames(filenames);
            ToJSVal(cx, vp,filenames);
			break;
		}
	case P_FILTER_INDEX:
		ToJSVal(cx, vp,p->GetFilterIndex());
		break;
	case P_MESSAGE:
		ToJSVal(cx, vp,p->GetMessage());
		break;
	case P_PATH:
		ToJSVal(cx, vp,p->GetPath());
		break;
	case P_PATHS:
		{
			wxArrayString paths;
			p->GetPaths(paths);
            ToJSVal(cx, vp,paths);
			break;
		}
	case P_WILDCARD:
		ToJSVal(cx, vp,p->GetWildcard());
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxFileDialog, FileDialog)
	switch (id) 
	{
	case P_DIRECTORY:
		{
			wxString dir;
			FromJS(cx, vp, dir);
			p->SetDirectory(dir);
			break;
		}
	case P_FILENAME:
		{
			wxString f;
			FromJS(cx, vp, f);
			p->SetFilename(f);
			break;
		}
	case P_FILTER_INDEX:
		{
			int idx;
			if ( FromJS(cx, vp, idx) )
				p->SetFilterIndex(idx);
			break;
		}
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
	case P_WILDCARD:
		{
			wxString wildcard;
			FromJS(cx, vp, wildcard);
			p->SetWildcard(wildcard);
			break;
		}
	}
	return true;
WXJS_END_SET_PROP
	
WXJS_BEGIN_GET_SET_STR_PROP(wxFileDialog, FileDialog)
	Dialog::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

/***
 * <constants>
 *	<type name="Style">
 *	 <constant name="OPEN" />
 *	 <constant name="SAVE" />
 *	 <constant name="OVERWRITE_PROMPT" />
 *	 <constant name="MULTIPLE" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(FileDialog)
  WXJS_CONSTANT(wxFD_, OPEN)
  WXJS_CONSTANT(wxFD_, SAVE)
  WXJS_CONSTANT(wxFD_, OVERWRITE_PROMPT)
  WXJS_CONSTANT(wxFD_, NO_FOLLOW)
  WXJS_CONSTANT(wxFD_, FILE_MUST_EXIST)
  WXJS_CONSTANT(wxFD_, CHANGE_DIR)
  WXJS_CONSTANT(wxFD_, PREVIEW)
  WXJS_CONSTANT(wxFD_, MULTIPLE)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *	<function>
 *	 <arg name="Parent" type="@wxWindow">
 *	  The parent of wxFileDialog.
 *   </arg>
 *	 <arg name="Message" type=WXJS_TYPE_STRING default="'Choose a file'">
 *	  The title of the dialog
 *   </arg>
 *	 <arg name="DefaultDir" type=WXJS_TYPE_STRING default="''">
 *	  The default directory
 *   </arg>
 * 	 <arg name="DefaultFile" type=WXJS_TYPE_STRING default="''">
 *	  The default file
 *   </arg>
 *	 <arg name="WildCard" type=WXJS_TYPE_STRING default="'*.*'">
 *	  A wildcard, such as "*.*"
 *    or "BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif".
 *   </arg>
 *	 <arg name="Style" type=WXJS_TYPE_NUMBER default="0">
 *	  The style
 *   </arg>
 *	 <arg name="Position" type="@wxPoint" default="wxDefaultPosition"> 
 *	  The position of the dialog.
 *   </arg>
 *  </function>
 *	<desc>
 *   Constructs a new wxFileDialog object
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxFileDialog, FileDialog)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	int style = 0;
	wxString message = wxFileSelectorPromptStr;
	wxString wildcard = wxFileSelectorDefaultWildcardStr;
	wxString defaultFile = wxEmptyString;
	wxString defaultDir = wxEmptyString;
	


	ZZZJS_CHECK_ARG_COUNT(1, 7);
	
	argIndex = argc -1;
	switch(argc)
	{
	case 7:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	case 6:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 5:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(wildcard, WXJS_TYPE_STRING);
		argIndex--;
	case 4:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(defaultFile, WXJS_TYPE_STRING);
		argIndex--;
	case 3:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(defaultDir, WXJS_TYPE_STRING);
		argIndex--;
	case 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(message, WXJS_TYPE_STRING);
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
		return new wxFileDialog(parent, message, defaultDir, defaultFile,
					wildcard, style, *(apPoint.get()));
	}
	return NULL;
 }
WXJS_END_CONSTRUCTOR

//void FileDialog::Destruct(JSContext* WXUNUSED(cx), wxFileDialog *p)
//void FileDialog::Destruct( wxFileDialog *p)
//{
WXJS_BEGIN_DESTRUCTOR(wxFileDialog, FileDialog)
{
	wxLogDebug(_T("FileDialog::Destruct"));
	if( p != NULL ) {
//		delete p;
	}
//	p->Destroy();
}
WXJS_END_DESTRUCTOR
