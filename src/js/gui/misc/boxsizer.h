/*
 * wxJavaScript - boxsizer.h
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
 * $Id: boxsizer.h 715 2007-05-18 20:38:04Z fbraem $
 */
#ifndef _WXJSBoxSizer_H
#define _WXJSBoxSizer_H

#include "js/common/jswrap.h"


namespace zzzJs
{
    namespace gui
    {
      class BoxSizer : public JsWrapper<BoxSizer, wxBoxSizer>
        {
        public:

            /**
             * Callback for when a wxBoxSizer object is created
             */
			ZZZJS_DECLARE_CONSTRUCTOR(wxBoxSizer)
			ZZZJS_DECLARE_DESTRUCTOR(wxBoxSizer)
			ZZZJS_DECLARE_GET_PROP(wxBoxSizer)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxBoxSizer)
			
			// Propeties
	        enum
	        {
		        P_ORIENTATION
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()
        };
    }; // namespace gui
}; // namespace zzzJs

#endif //_WXJSBoxSizer_H
