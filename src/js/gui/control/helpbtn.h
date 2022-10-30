/*
 * wxJavaScript - helpbtn.h
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
 * $Id: helpbtn.h 684 2007-04-25 19:25:02Z fbraem $
 */
#ifndef _WXJSContextHelpButton_H
#define _WXJSContextHelpButton_H

#include <wx/cshelp.h>

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
      class ContextHelpButton : public ApiWrapper<ContextHelpButton,
                                                  wxContextHelpButton>
      {
      public:
			WXJS_DECLARE_ADD_PROP(wxContextHelpButton)
			WXJS_DECLARE_DEL_PROP(wxContextHelpButton)
			WXJS_DECLARE_SET_STR_PROP(wxContextHelpButton)
			WXJS_DECLARE_CONSTRUCTOR(wxContextHelpButton)
            WXJS_DECLARE_DESTRUCTOR(wxContextHelpButton)
      };
    }; // namespace gui
}; // namespace wxjs
#endif //_WXJSContextHelpButton_H
