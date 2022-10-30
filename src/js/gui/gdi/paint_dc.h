/*
 * wxJavaScript - paint_dc.h
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
 * $Id: paint_dc.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _ZZZJS_GUI_GDI_PAINT_DC_H_
#define _ZZZJS_GUI_GDI_PAINT_DC_H_

#include "js/common/apiwrap.h"
#include <wx/dc.h>
#include <wx/dcclient.h>


namespace zzzJs
{
    namespace gui
    {
		namespace gdi 
		{
			class PaintDC : public ApiWrapper<PaintDC, wxPaintDC>
			{
			public:
				
				WXJS_DECLARE_CONSTRUCTOR(wxPaintDC)
				WXJS_DECLARE_SET_STR_PROP(wxPaintDC)
		

			};
		};	// namespace dc
    }; // namespace gui
}; //namespace _ZZZJS_GUI_GDI_METAFILE_DC_H_
#endif //_ZZZJS_GUI_GDI_PAINT_DC_H_
