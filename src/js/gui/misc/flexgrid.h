/*
 * wxJavaScript - flexgrid.h
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
 * $Id: flexgrid.h 715 2007-05-18 20:38:04Z fbraem $
 */
#ifndef _WXJSFlexGridSizer_H
#define _WXJSFlexGridSizer_H
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace gui
    {
      class FlexGridSizer : public JsWrapper<FlexGridSizer, wxFlexGridSizer>
        {
        public:
			
			ZZZJS_DECLARE_CONSTRUCTOR(wxFlexGridSizer)
			ZZZJS_DECLARE_DESTRUCTOR(wxFlexGridSizer)
			ZZZJS_DECLARE_GET_PROP(wxFlexGridSizer)
			ZZZJS_DECLARE_SET_PROP(wxFlexGridSizer)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxFlexGridSizer)
			// Propeties
	        enum
	        {
		          P_FlexibleDirection
		        , P_NonFlexibleGrowMode
		        , P_RowHeights 
		        , P_ColWidths 
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()


			// Methods
	        ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(addGrowableCol);
			ZZZJS_DECLARE_METHOD(addGrowableRow);
			ZZZJS_DECLARE_METHOD(removeGrowableCol);
			ZZZJS_DECLARE_METHOD(removeGrowableRow);
			ZZZJS_DECLARE_METHOD(isColGrowable);
			ZZZJS_DECLARE_METHOD(isRowGrowable);
			ZZZJS_DECLARE_METHOD(recalcSizes);
			ZZZJS_DECLARE_METHOD(calcMin);


        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSFlexGridSizer_H
