/*
 * wxJavaScript - gdi_init.h
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
 * $Id: gdi_init.h 607 2007-03-12 21:41:14Z fbraem $
 */
#ifndef _ZZZJS_GUI_GDI_INIT_h
#define _ZZZJS_GUI_GDI_INIT_h

// Use this to initialize the XML module

#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace gdi 
		{
			bool InitClass(JSContext *cx, JSObject *global);
			bool InitObject(JSContext *cx, JSObject *obj);
			void Destroy();
		};
	};
};

#endif // _ZZZJS_GUI_GDI_INIT_h
