/*
 * wxJavaScript - sizer.h
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
 * $Id: sizer.h 733 2007-06-05 21:17:25Z fbraem $
 */
#ifndef _WXJSSIZER_H
#define _WXJSSIZER_H

#include "js/common/jswrap.h"


namespace zzzJs
{
    namespace gui
    {
        class Sizer : public JsWrapper<Sizer, wxSizer>
        {
        public:
	        /**
	         * Callback for retrieving properties.
	         * @param vp Contains the value of the property.
	         */
			ZZZJS_DECLARE_GET_PROP(wxSizer)


	        /**
	         * Callback for setting properties
	         * @param vp Contains the new value of the property.
	         */
			ZZZJS_DECLARE_SET_PROP(wxSizer)
			
			// Propeties
	        enum
	        { 
					P_MIN_SIZE
				,	P_POSITION
				,	P_SIZE
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()


			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
	        ZZZJS_DECLARE_METHOD(add);
	        ZZZJS_DECLARE_METHOD(layout);
	        ZZZJS_DECLARE_METHOD(prepend);
	        ZZZJS_DECLARE_METHOD(remove);
	        ZZZJS_DECLARE_METHOD(setDimension);
	        ZZZJS_DECLARE_METHOD(setMinSize);
	        ZZZJS_DECLARE_METHOD(setItemMinSize);

        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSSIZER_H
