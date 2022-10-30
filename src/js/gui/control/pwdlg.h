/*
 * wxJavaScript - pwdlg.h
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
 * $Id: pwdlg.h 690 2007-04-30 13:09:52Z fbraem $
 */
#ifndef _WXJSPasswordEntryDialog_H
#define _WXJSPasswordEntryDialog_H


#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
      class PasswordEntryDialog : public ApiWrapper<PasswordEntryDialog, 
                                                    wxPasswordEntryDialog>
        {
        public:


			WXJS_DECLARE_ADD_PROP(wxPasswordEntryDialog)
			WXJS_DECLARE_DEL_PROP(wxPasswordEntryDialog)
			WXJS_DECLARE_SET_STR_PROP(wxPasswordEntryDialog)
			WXJS_DECLARE_CONSTRUCTOR(wxPasswordEntryDialog)
            WXJS_DECLARE_DESTRUCTOR(wxPasswordEntryDialog)
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSPasswordEntryDialog_H
