/*
 * wxJavaScript - filedlg.h
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
 * $Id: filedlg.h 672 2007-04-12 20:29:39Z fbraem $
 */
#ifndef _WXJSFileDialog_H
#define _WXJSFileDialog_H

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class FileDialog : public ApiWrapper<FileDialog, wxFileDialog>
        {
        public:

			WXJS_DECLARE_GET_PROP(wxFileDialog)
			WXJS_DECLARE_SET_PROP(wxFileDialog)
			WXJS_DECLARE_SET_STR_PROP(wxFileDialog)
			WXJS_DECLARE_CONSTRUCTOR(wxFileDialog)
//	        static void Destruct(JSContext *cx, wxFileDialog *p);
			WXJS_DECLARE_DESTRUCTOR(wxFileDialog)

	        WXJS_DECLARE_PROPERTY_MAP()
	        WXJS_DECLARE_CONSTANT_MAP()

	        enum 
	        {
		        P_DIRECTORY
		        , P_FILENAME
		        , P_FILENAMES
		        , P_FILTER_INDEX
		        , P_MESSAGE
		        , P_PATH
		        , P_PATHS
		        , P_WILDCARD
	        };
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSFileDialog_H
