/*
 * wxJavaScript - bmpbtn.h
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
 * $Id: bmpbtn.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _ZZZJS_GUI_GDI_AutoBufferedPaintDC_H_
#define _ZZZJS_GUI_GDI_AutoBufferedPaintDC_H_

#include "js/common/apiwrap.h"
#include <wx/dc.h>
#include <wx/dcbuffer.h>


namespace zzzJs
{
    namespace gui
    {
		namespace gdi 
		{
			class AutoBufferedPaintDC : public ApiWrapper<AutoBufferedPaintDC, wxAutoBufferedPaintDC>
			{
			public:
				
				WXJS_DECLARE_CONSTRUCTOR(wxAutoBufferedPaintDC)
				WXJS_DECLARE_DESTRUCTOR(wxAutoBufferedPaintDC)
				WXJS_DECLARE_SET_STR_PROP(wxAutoBufferedPaintDC)

			};
		};	// namespace dc
    }; // namespace gui
}; //namespace wxjs
#endif //_ZZZJS_GUI_GDI_AutoBufferedPaintDC_H_
