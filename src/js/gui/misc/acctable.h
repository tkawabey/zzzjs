/*
 * wxJavaScript - acctable.h
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
 * $Id: acctable.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSAcceleratorTable_H
#define _WXJSAcceleratorTable_H


#include "js/common/jswrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        acctable.h
// Purpose:		AcceleratorTable ports wxAcceleratorTable to JavaScript.
// Author:      Franky Braem
// Modified by:
// Created:     06.06.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class AcceleratorTable : public JsWrapper<AcceleratorTable, wxAcceleratorTable>
        {
        public:
			ZZZJS_DECLARE_GET_PROP(wxAcceleratorTable)

			/**
			 * Callback for when a wxAcceleratorTable object is created
			 */
			ZZZJS_DECLARE_CONSTRUCTOR(wxAcceleratorTable)
        	
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxAcceleratorTable)


	        /**
	         * Property Ids.
	         */
	        enum
	        {
		          P_OK
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()
        };
    }; // namespace gui
}; // namespace zzzJs

#endif //_WXJSAcceleratorTable_H
