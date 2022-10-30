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
#ifndef _ZZZJS_GUI_DC_MIRROR_DC_H_
#define _ZZZJS_GUI_DC_MIRROR_DC_H_

#include "js/common/apiwrap.h"
#include <wx/dc.h>
#include <wx/dcmemory.h>


namespace zzzJs
{
    namespace gui
    {
		namespace gdi 
		{
			class MemoryDC : public ApiWrapper<MemoryDC, wxMemoryDC>
			{
			public:
				
				WXJS_DECLARE_CONSTRUCTOR(wxMemoryDC)
				WXJS_DECLARE_DESTRUCTOR(wxMemoryDC)
				WXJS_DECLARE_GET_PROP(wxMemoryDC)
				WXJS_DECLARE_SET_PROP(wxMemoryDC)
				WXJS_DECLARE_SET_STR_PROP(wxMemoryDC)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				 * Property Ids.
				 */
				enum
				{
						//P_GraphicsContext // GetGraphicsContext / SetGraphicsContext 
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(selectObject)
				WXJS_DECLARE_METHOD(selectObjectAsSource)
			};
		};	// namespace dc
    }; // namespace gui
}; //namespace wxjs
#endif //_ZZZJS_GUI_DC_MIRROR_DC_H_
