/*
 * zzzJs - art_provider.h
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
 * $Id: art_provider.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _ZZZJS_GUI_MISC_ART_PROVIDER_H
#define _ZZZJS_GUI_MISC_ART_PROVIDER_H

#include "js/common/jswrap.h"
#include <wx/artprov.h>
/////////////////////////////////////////////////////////////////////////////
// Name:        bitmap.h
// Purpose:		Ports wxBitmap to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     09.08.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
// Since:       version 0.4
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class ArtProvider : public JsWrapper<ArtProvider, wxArtProvider>
        {
        public:
			ZZZJS_DECLARE_CONSTRUCTOR(wxArtProvider)

			// Static property
			ZZZJS_DECLARE_STATIC_PROPERTY_MAP()
	        enum
	        {
				// Art IDs
				  P_ADD_BOOKMARK
				, P_DEL_BOOKMARK
				, P_HELP_SIDE_PANEL
				, P_HELP_SETTINGS
				, P_HELP_BOOK
				, P_HELP_FOLDER
				, P_HELP_PAGE
				, P_GO_BACK
				, P_GO_FORWARD
				, P_GO_UP
				, P_GO_DOWN
				, P_GO_TO_PARENT
				, P_GO_HOME
				, P_GOTO_FIRST
				, P_GOTO_LAST
				, P_FILE_OPEN
				, P_FILE_SAVE
				, P_FILE_SAVE_AS
				, P_PRINT
				, P_HELP
				, P_TIP
				, P_REPORT_VIEW
				, P_LIST_VIEW
				, P_NEW_DIR
				, P_HARDDISK
				, P_FLOPPY
				, P_CDROM
				, P_REMOVABLE
				, P_FOLDER
				, P_FOLDER_OPEN
				, P_GO_DIR_UP
				, P_EXECUTABLE_FILE
				, P_NORMAL_FILE
				, P_TICK_MARK
				, P_CROSS_MARK
				, P_ERROR
				, P_QUESTION
				, P_WARNING
				, P_INFORMATION
				, P_MISSING_IMAGE
				, P_COPY
				, P_CUT
				, P_PASTE
				, P_DELETE
				, P_NEW
				, P_UNDO
				, P_REDO
				, P_PLUS
				, P_MINUS
				, P_CLOSE
				, P_QUIT
				, P_FIND
				, P_FIND_AND_REPLACE
				, P_FULL_SCREEN
				, P_EDIT
				// Art clients
				, P_TOOLBAR
				, P_MENU
				, P_FRAME_ICON
				, P_CMN_DIALOG
				, P_HELP_BROWSER
				, P_MESSAGE_BOX
				, P_BUTTON
				, P_LIST
				, P_OTHER
	        };
			static bool GetStaticProperty(JSContext* cx,
                                    int id,
                                    JS::MutableHandle<JS::Value>& vp);

			// Static Methods
			ZZZJS_DECLARE_STATIC_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(Delete)
			ZZZJS_DECLARE_METHOD(getBitmap)
			ZZZJS_DECLARE_METHOD(getIcon)
			ZZZJS_DECLARE_METHOD(getNativeSizeHint)
			ZZZJS_DECLARE_METHOD(getSizeHint)
			//ZZZJS_DECLARE_METHOD(getIconBundle) ...TODO
			ZZZJS_DECLARE_METHOD(hasNativeProvider)
			ZZZJS_DECLARE_METHOD(pop)
			ZZZJS_DECLARE_METHOD(push)
			ZZZJS_DECLARE_METHOD(pushBack)
			ZZZJS_DECLARE_METHOD(remove)
			ZZZJS_DECLARE_METHOD(getMessageBoxIconId)
			ZZZJS_DECLARE_METHOD(getMessageBoxIcon)


        };
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZJS_GUI_MISC_ART_PROVIDER_H
