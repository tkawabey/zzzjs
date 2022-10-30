/*
 * wxJavaScript - metafile.h
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
#ifndef _ZZZJS_GUI_GDU_METAFILE_H_
#define _ZZZJS_GUI_GDU_METAFILE_H_

#include "js/common/apiwrap.h"
#include <wx/metafile.h>

namespace zzzJs
{
    namespace gui
    {
		namespace gdi 
		{
			class Metafile : public ApiWrapper<Metafile, wxMetafile>
			{
			public:

				WXJS_DECLARE_GET_PROP(wxMetafile)
				WXJS_DECLARE_CONSTRUCTOR(wxMetafile)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				 * Property Ids.
				 */
				enum
				{
						P_ISOK // IsOk  
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(play)
				WXJS_DECLARE_METHOD(setClipboard)

			};
		};	// namespace dc
    }; // namespace gui
}; //namespace wxjs
#endif //_ZZZJS_GUI_GDU_METAFILE_H_
