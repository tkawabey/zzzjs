/*
 * wxJavaScript - dirdlg.h
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
 * $Id: dirdlg.h 672 2007-04-12 20:29:39Z fbraem $
 */
#ifndef _WXJSDirDialog_H
#define _WXJSDirDialog_H

#include <wx/dirdlg.h>

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class DirDialog : public ApiWrapper<DirDialog, wxDirDialog>
        {
        public:
			
			WXJS_DECLARE_GET_PROP(wxDirDialog)
			WXJS_DECLARE_SET_PROP(wxDirDialog)
			WXJS_DECLARE_SET_STR_PROP(wxDirDialog)
			WXJS_DECLARE_CONSTRUCTOR(wxDirDialog)
//            static void Destruct(JSContext *cx, wxDirDialog *p);
            WXJS_DECLARE_DESTRUCTOR(wxDirDialog)

	        WXJS_DECLARE_PROPERTY_MAP()

	        enum 
	        {
		        P_MESSAGE
		        , P_PATH
		        , P_STYLE
	        };
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSDirDialog_H
